#include <LiquidCrystal.h>

// LCD Setup
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Ultrasonic Sensor Pins
const int trigPin = 2;
const int echoPin = 3;

// Piezo Buzzer Pin
const int buzzer = 6;

// Thresholds
const int objectThreshold = 5; // Distance to count objects
const int alienThreshold = 20; // Distance for alien object detection

// Global Variables
int objectCount = 0;

void setup() {
  // Initialize Serial Communication
  Serial.begin(9600);

  // Initialize Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Measure distance
  int distance = measureDistance();

  // Check for object or alien detection
  if (distance > 0 && distance < objectThreshold) {
    // Count object and send data to Arduino 2
    objectCount++;
    lcd.clear();
    lcd.print("Count: ");
    lcd.print(objectCount);
    Serial.println("OBJECT_DETECTED");
    delay(500); // Debounce

  } else if (distance >= objectThreshold && distance <= alienThreshold) {
    // Alien object detected
    lcd.clear();
    lcd.print("Alien Object!");
    Serial.println("ALIEN_DETECTED");
    tone(buzzer, 1000, 500); // Buzz for 0.5 sec
    delay(1000); // Debounce

  } else {
    // No object detected
    Serial.println("NO_OBJECT");
    delay(1000);
  }
}

// Measure distance using Ultrasonic Sensor
int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}
