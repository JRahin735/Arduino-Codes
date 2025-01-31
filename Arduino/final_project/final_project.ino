#include <NewPing.h>
#include <DHT.h>

// Pin definitions
#define ULTRASONIC_TRIG_PIN 2
#define ULTRASONIC_ECHO_PIN 3
#define TEMPERATURE_SENSOR_PIN 4
#define PHOTORESISTOR_PIN A0
#define LED_PIN_1 5
#define LED_PIN_2 6
#define LED_PIN_3 7
#define DHT_TYPE DHT11

// Object initialization
NewPing sonar(ULTRASONIC_TRIG_PIN, ULTRASONIC_ECHO_PIN, 200);
DHT dht(TEMPERATURE_SENSOR_PIN, DHT_TYPE);

// Variables
long distance;
float temperature;
float humidity;
int lightLevel;
int objectCount = 0;
bool objectDetected = false;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize sensors
  dht.begin();
  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);

  // Initial message
  Serial.println("ArduinoA Initialized");
}

void loop() {
  // Read ultrasonic sensor value
  distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Read temperature and humidity values
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Read light level from photoresistor
  lightLevel = analogRead(PHOTORESISTOR_PIN);
  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  // Threshold checks
  countObjects();
  checkForeignObjectDistance();
  checkOverheating();
  checkInternalLights();

  // Delay for stability
  delay(1000);
}

void countObjects() {
  if (distance < 10 && !objectDetected) {
    objectCount++;
    objectDetected = true;
    Serial.print("Object detected. Total count: ");
    Serial.println(objectCount);
  } else if (distance >= 10) {
    objectDetected = false;
  }
}

void checkForeignObjectDistance() {
  if (distance < 5) {
    Serial.println("Warning: Foreign object detected near the conveyor belt!");
  }
}

void checkOverheating() {
  if (temperature > 50) {
    Serial.println("Warning: High temperature detected!");
  }
}

void checkInternalLights() {
  if (lightLevel < 500) {
    Serial.println("Low light detected: Turning on system lights.");
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
    digitalWrite(LED_PIN_3, HIGH);
  } else {
    Serial.println("Sufficient ambient light: System lights off.");
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);
  }
}
