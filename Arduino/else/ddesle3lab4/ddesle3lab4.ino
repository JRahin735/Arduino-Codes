// Dishant Desle, 652956059 and ddesle3
// Lab 4 - Photoresistor
// Description - This lab involves creating a circuit using a photoresistor 
//               and a 16x2 LCD display to display the relative light level 
//               in the environment as one of five predefined text values, 
//               based on readings from the photoresistor, providing hands-on 
//               experience with analog sensor input and digital output using an Arduino.
// Assumption - A photoresistor is connected to analog pin A0.
//              The 10k ohm resistor and photoresistor are appropriately 
//              wired together to form a voltage divider.
// References - https://docs.arduino.cc/learn/electronics/lcd-displays
//              https://www.instructables.com/How-to-use-a-photoresistor-or-photocell-Arduino-Tu/
//              https://playground.arduino.cc/Learning/PhotoResistor/
// Date - 10/03/2023
// Time - 10:45am
// TA - Kaz





#include <LiquidCrystal.h>

// LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // Adjust pins as per your setup

const int photoresistorPin = A0;
int photoresistorValue = 0;
String lightStatus;

void setup() {
  lcd.begin(16, 2); // Initialize the LCD
  pinMode(photoresistorPin, INPUT);
  Serial.begin(9600); // Initialize Serial communication for debugging
}

void loop() {
  // Read the value from the photoresistor
  photoresistorValue = analogRead(photoresistorPin);

  // Determine the light status based on the photoresistor reading
  if (photoresistorValue < 200) {
    lightStatus = "Dark";
  } else if (photoresistorValue < 400) {
    lightStatus = "Partially Dark";
  } else if (photoresistorValue < 600) {
    lightStatus = "Medium";
  } else if (photoresistorValue < 800) {
    lightStatus = "Fully Lit";
  } else {
    lightStatus = "Brightly Lit";
  }

  // Clear the previous message on the LCD
  lcd.clear();

  // Display the light status on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Light Level:");
  lcd.setCursor(0, 1);
  lcd.print(lightStatus);

  // Print the light status to the Serial Monitor for testing
  Serial.print("Light Status: ");
  Serial.println(lightStatus);

  delay(1000); // Delay for readability
}

