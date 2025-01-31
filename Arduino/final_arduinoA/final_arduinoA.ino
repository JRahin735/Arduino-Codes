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

#include <LiquidCrystal.h>
#include <Wire.h>

// Initialize the LCD with the pins connected
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin numbers in use
const int buzzerPin = 7; 
const int echoPin = 8; 
const int trigPin = 9; 
int firesituation = false;

// Counter for products
int distanceCounter = 0; 

void setup() {

  // Setting up all devices
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600); 
  Wire.begin(); 
}

void loop() {
  
  // Display the current distance counter value on the LCD
  lcd.setCursor(0, 1); 
  lcd.print("Count: ");
  lcd.print(distanceCounter);
  lcd.print("          "); // Clear any remaining characters in the row

  // Request data from the other Arduino with address 8 and 5 bytes of data
  Wire.requestFrom(8, 5);
  while (Wire.available()) {
    char type = Wire.read(); // Read the data coming from the other Arduino
    Serial.println("Received from Arduino 2: " + String(type));
    
    // If the received data indicates fire ('F'), trigger a fire alert
    if (type == 'F') {
      Serial.println("Fire detected!");
      lcd.clear(); // Clear LCD display
      lcd.print("Fire!"); // Display fire warning on the LCD
      
      // Turn the buzzer on
      digitalWrite(buzzerPin, HIGH);
      delay(5000); 
      digitalWrite(buzzerPin, LOW); 

      lcd.clear(); // Clear the LCD
    }
  }

  // Check the distance using the ultrasonic sensor
  checkDistance();

  // Update the distance counter if applicable
  updateDistanceCounter();

  // Display monitoring status on the LCD
  lcd.print("Monitoring...");
  delay(500); // Short delay before repeating the loop
}

void checkDistance() {
  long duration, distance;

  // Send a 10 microsecond pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time taken for the pulse to return
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Calculate distance in centimeters

  // If the distance is below the threshold, trigger an alert
  if (distance < 4) {
    triggerAlert();
  }
}

void triggerAlert() {
  // Send an alert ('S') to the other Arduino over I2C
  Wire.beginTransmission(8);
  Wire.write('S');          
  Wire.endTransmission();

  // Turn the buzzer on and display an alert on the LCD
  digitalWrite(buzzerPin, HIGH);
  lcd.clear();
  lcd.print("Too close!");
  delay(5000); // Keep the alert on for 5 seconds
  digitalWrite(buzzerPin, LOW); // Turn the buzzer off
  lcd.clear(); // Clear the LCD after the alert
}

void updateDistanceCounter() {
  long duration, distance;

  // Send a 10 microsecond pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time taken for the pulse to return
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Calculate distance in centimeters

  // Increment the counter if the distance is within the specified range (4 to 10 cm)
  if (distance >= 4 && distance <= 10) {
    distanceCounter++;
    lcd.setCursor(0, 1); // Set the LCD cursor to the second row
    lcd.print("Dist Cnt: ");
    lcd.print(distanceCounter); // Display the updated distance counter
    delay(1000); // Delay to avoid rapid incrementing of the counter
  }
}
