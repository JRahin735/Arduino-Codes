/*
* Author: Yamaan Nandolia
* UIN: 671068709
* NETID: ynand3
* Title: Lab 3 - Scrolling Output
* Description: The following is a simple program that runs a loop and uses the sprintf() & millis functions.
*              Using the loop it isplays a message 
* References: 1) Used the prelab program documentation provided in the lab handout
* Assumptions: My hardware(potentiometer s are not placed properly and my LCD works)
* Lab Info: Monday, Feb 5th at 11:55 am (In Lab) 
* TA: Anshuman
*/
#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13; //pin numbers
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char arr[] = "The one piece is real "; //quote array
char nameBuf[20]; // name buffer

const int arrSize = sizeof(arr) / sizeof(arr[0]); // array size calculation

unsigned long previous = 0;
const long interval = 750; // millis() interval

// Static variable to keep track of the current index in the quote
static int currentIndex = 0;

void setup() {
  lcd.begin(16, 2);
  sprintf(nameBuf, "%s", "Yamaan"); // name
  lcd.setCursor(5,1); //alignment
  lcd.print(nameBuf);
}

void loop() {
  unsigned long currentMillis = millis(); // getting time

  // Check for time to display characters
  if (currentMillis - previous >= interval) {
    // Print the next 16 characters from the quote
    printNext16Chars(currentIndex);
    currentIndex = (currentIndex + 1) % (arrSize - 1);   // update index
    previous = currentMillis;
  }
}

void printNext16Chars(int begin) {
  lcd.setCursor(0,0);
  int end = begin + 16;
  int effectiveEnd = end % (arrSize - 1);    // Calculate end index after wrapping
  int i = begin;
  while (i != effectiveEnd) {
    lcd.print(arr[i]);
    i = (i + 1) % (arrSize - 1); // wrapping handling
  }
}