/*
  Team Number: ?
  Factory Plus - A Smart Conveyor Belt System
  Team Member:
    - Ayush Bhardwaj [651465377] - abhard24@uic.edu
    - Rahin Jain [665219123] - rjain56@uic.edu

    FactoryPlus, the smart conveyor belt system enhances safety and productivity through an Arduino based 
    setup designed for factory environments. One of the Arduinos handles safety monitoring using an ultrasonic sensor, 
    temperature and humidity sensor, and photoresistor, identifying potential hazards and issuing alerts via visual and 
    auditory signals. The second Arduino focuses on productivity, tracking real-time product counts and conveyor movement 
    using servo motors, an LCD, and a piezo speaker. This integrated system aims to minimize risks, increase efficiency, 
    and offer a reliable solution for optimized operations.

*/

#include <Servo.h>
#include <Wire.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
Servo servo1, servo2;

const int buttonPin = 10; 
const int redLED = 7;
const int GreenLED = 6;
const int WhiteLED1 = 5;
const int WhiteLED2 = 4;
const int WhiteLED3 = 3;
const int photoresistorPin = A1; 
const int lightThreshold = 500; 

bool tempStop = false;   // Flag to indicate if motor should stop due to temperature condition
bool motorState = false; // Flag to indicate the current motor state (on/off)
int lastButtonState = LOW;
int currentButtonState = LOW; 

unsigned long lastRotationTime = 0; // To keep track of the last time motors rotated
const unsigned long interval = 4000; // Interval for motor rotation in milliseconds

void setup() {
  Serial.begin(9600);
  dht.begin();
  servo1.attach(8);
  servo2.attach(9);
  pinMode(buttonPin, INPUT_PULLUP);
  Wire.begin(8);  // Initialize I2C communication with address 8
 
  stopMotors(); // Initially stop motors
 
  // Set pin modes for LEDs
  pinMode(redLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(WhiteLED1, OUTPUT);
  pinMode(WhiteLED2, OUTPUT);
  pinMode(WhiteLED3, OUTPUT);

  Wire.onReceive(receiveEvent); // Register event handler for receiving data over I2C
}

void loop() {
    Serial.println( "outside");

  currentButtonState = digitalRead(buttonPin); // Read the state of the button

  checkTemperature(); // Check the temperature and handle motor stop if necessary
  Wire.onReceive(receiveEvent);  // Continuously listen for incoming I2C messages

  checkLightLevel(); // Check the light level and adjust LEDs accordingly

  // Handle button press for starting/stopping motors
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    tempStop = false;
    delay(50); // Debounce delay
    if (!tempStop) { // If temperature condition allows
      motorState = !motorState; // Toggle motor state
      if (motorState) {
        Serial.println("Motors started");
        digitalWrite(GreenLED, HIGH); // Turn on green LED to indicate motors are running
      } else {
        Serial.println("Motors stopped");
        digitalWrite(GreenLED, LOW); // Turn off green LED
        stopMotors(); // Stop the motors
      }
    } else {
      Serial.println("Motors cannot start. Temperature condition not met.");
    }
  }
  lastButtonState = currentButtonState; // Update last button state

  // Rotate motors at regular intervals if they are on
  if (motorState) {
    unsigned long currentTime = millis();
    if (currentTime - lastRotationTime >= interval) {
      lastRotationTime = currentTime;
      rotateMotors();
    }
  }
}

// Function to check temperature and handle conditions for motor stop
void checkTemperature() {
  float t = dht.readTemperature(); // Read temperature from DHT sensor
  if (isnan(t)) { // If reading failed
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println(t, "outside");
  if (t < 20 ) { // If temperature is below threshold
    Wire.beginTransmission(1); // Start I2C communication to address 1
    Wire.onRequest(requestEvent); // Set event for sending data

    Serial.println(t);
    Wire.endTransmission();
    stopMotors(); // Stop motors due to low temperature
 
    motorState = false; // Update motor state
    tempStop = true;    // Set temperature stop flag
    digitalWrite(redLED, HIGH); // Turn on red LED to indicate stop condition
  }
  else{
    Wire.onRequest(requestEvent2); // Set event for sending data when temperature is okay
  }
}

// Event handler for receiving data over I2C
void receiveEvent(int howMany) {
  Serial.print("check2");
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print("check1");
    if (c == 'S') { // If command is to stop
      stopMotors();
      digitalWrite(redLED, HIGH); // Turn on red LED
      motorState = false; // Update motor state to off
    }
  }
}

// Event handler for sending 'F' over I2C when temperature is below threshold
void requestEvent(){
    Wire.write('F'); 
} 

// Event handler for sending 'Q' over I2C when temperature is okay
void requestEvent2(){
    Wire.write('Q'); 
} 

// Function to rotate motors by 90 degrees
void rotateMotors() {
  digitalWrite(redLED, LOW); // Turn off red LED as motors are running

  Serial.println("Rotating motors by 90 degrees");
  servo1.write(1);
  servo2.write(1);
  
  servo1.write(90);
  servo2.write(90);
  delay(500); // Wait for servos to complete rotation
  servo1.write(91);
  servo2.write(91);
  delay(500); 
  servo1.write(180);
  servo2.write(180);
}

// Function to stop motors
void stopMotors() {
  servo1.write(0);
  servo2.write(0);
}

// Function to check light level and control LEDs accordingly
void checkLightLevel() {
  int lightLevel = analogRead(photoresistorPin); // Read light level from photoresistor

  if (lightLevel < lightThreshold) { // If it is dark
    digitalWrite(WhiteLED1, HIGH);
    digitalWrite(WhiteLED2, HIGH);
    digitalWrite(WhiteLED3, HIGH);
    Serial.println("It's dark - LEDs on");
  } 
  else { // If it is bright
    digitalWrite(WhiteLED1, LOW);
    digitalWrite(WhiteLED2, LOW);
    digitalWrite(WhiteLED3, LOW);
    Serial.println("It's bright - LEDs off");
  }
}
