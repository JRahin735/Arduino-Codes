// Rahin Jain, 665219123 and rjain56
// Lab 4 - Analog Input: Photoresistor (LDR – Light Dependent Resistor)
// Description - This lab demonstrates using a photoresistor and LCD to show light levels in five categories based on sensor readings.
// Assumption - A photoresistor is connected to analog pin A0.
//              The 10k ohm resistor and photoresistor are appropriately 
//              wired together to form a voltage divider.
// References - https://docs.arduino.cc/learn/electronics/lcd-displays
//              https://www.instructables.com/How-to-use-a-photoresistor-or-photocell-Arduino-Tu/
//              https://playground.arduino.cc/Learning/PhotoResistor/
// Date - oct 4
// Time - 5:04
// TA - yuri

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Initialize serial communication at a baud rate of 9600 for debugging
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600); 
}

void loop() {

  lcd.clear();

  // Declare required variable
  String lev;
  int value = analogRead(A0); 
  unsigned long time_curr = millis(); 

  // Determine the lighting level based on the analog sensor value
  if (value < 40) {
    lev = "dark";
  } 
  else if (value < 60) {
    lev = "partially dark";
  } 
  else if (value < 80) {
    lev = "medium";
  } 
  else if (value < 100) {
    lev = "fully lit";
  } 
  else {
    lev = "brightly lit";
  }

  // Set the cursor to the first row, first column
  lcd.setCursor(0, 0);
  // lcd.print("Light ");
  lcd.print(lev);
  lcd.print("     "); 

  // Set the cursor to the second row, first column
  lcd.setCursor(0, 1);
  lcd.print("Millis: ");
  lcd.print(time_curr);
  lcd.print("    "); 

  // Print the light value to the serial monitor for debugging purposes
  Serial.print("Light value: ");
  Serial.println(value);
}
