// Rahin Jain, 665219123 (rjain56)
// Lab 3 - Liquid Crystal Display – LCD
// Task: Show your name and quote on a 16x2 LCD display.

// Assumption: The 16x2 LCD is managed by the Arduino using the LiquidCrystal library. We assume that both the Arduino IDE and the library are correctly installed and functioning. The library will take care of the necessary setup and operation of the LCD.
// References - https://docs.arduino.cc/learn/electronics/lcd-displays
// Date - Sept 27, 2024
// Time - 9:25am
// TA - Yamaan

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
int lenToDisplay = 0;
unsigned long previousMillis = 0;  
const long interval = 500;  
int curr = 0;
const char stringToDisplay[] = "I want an A in this course :) ";  

void setup() {
  lcd.begin(16, 2); 
  // lcd.setCursor(0, 0);  
  lcd.print("                ");  
  lcd.setCursor(0, 1);  
  lcd.print(centerAligned("Rahin", 16));  
  lenToDisplay = strlen(stringToDisplay);  
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // lcd.setCursor(0, 1);  
    lcd.print("                ");  
    lcd.setCursor(0, 0);  

    for (int j = 0; j < 16; j++) {
      lcd.print(stringToDisplay[(curr + j) % lenToDisplay]);
    }

    curr++;
    if (curr >= lenToDisplay) {
      curr = 0;
    }
  }
}

String centerAligned(const char* text, int length) {
  int spaces = length - strlen(text);  

  if (spaces > 0) {
    String centeredText = "";
    for (int i = 0; i < spaces / 2; i++) {
      centeredText += " ";
    }

    centeredText += text;
    for (int i = 0; i < spaces / 2; i++) {
      centeredText += " ";
    }

    return centeredText;
  } else {
    return String(text);
  }
}
