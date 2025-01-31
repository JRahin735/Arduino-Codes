/* Name: Rahin Jain, rjain56 (665219123)
* Lab 6 - Computer I/O
* Description: This program allows a user to input a date and time via Serial Monitor.
* The input is validated and then displayed on an LCD screen, updating every second.
* Assumptions: User inputs the date and time in the format mm/dd/yyyy hh:mm:ss.
* TA: 
*/

#include <LiquidCrystal.h>  // Include the library for LCD screen
#include <TimeLib.h>        // Include the library for handling time functions

// Initialize the LCD object with pin numbers (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Initialize Serial communication at 9600 baud rate for input/output
  Serial.begin(9600); 

  // Initialize the LCD with 16 columns and 2 rows
  lcd.begin(16, 2); 

  // Set the initial time to 12:00:00 on 01/01/2024
  setTime(12, 0, 0, 01, 01, 2024); 

  // Prompt the user to enter date and time in the specified format
  Serial.println("Enter date (mm/dd/yyyy) and time (hh:mm:ss): ");
}

void loop() {
  static unsigned long ref = 0;  // Variable to store the last time an update occurred

  // Check if the user has entered data in the Serial Monitor
  if (Serial.available()) { 
    // Read the input until a newline character is encountered
    String inp = Serial.readStringUntil('\n');
    bool isValid = true;  // Flag to check if the input is valid

    // Validate the format of the input string (19 characters in mm/dd/yyyy hh:mm:ss format)
    if (inp.length() != 19 || inp.charAt(2) != '/' || inp.charAt(5) != '/' || 
        inp.charAt(10) != ' ' || inp.charAt(13) != ':' || inp.charAt(16) != ':') {
      isValid = false;  // Set flag to false if format is incorrect
    } 
    else {
      // Extract month, day, hour, seconds, year, and minutes from the input string
      int mon = inp.substring(0, 2).toInt();      // Month
      int da = inp.substring(3, 5).toInt();      // Day
      int hrs = inp.substring(11, 13).toInt();    // Hour
      int secs = inp.substring(17, 19).toInt();    // Seconds
      int yrs = inp.substring(6, 10).toInt();     // Year
      int min = inp.substring(14, 16).toInt();  // Minutes

      // Check if the input values are within valid ranges
      if (mon < 1 || mon > 12 || da < 1 || hrs < 0 || hrs > 23 || min < 0 || min > 59 || secs < 0 || secs > 59) {
        isValid = false;  // Set flag to false if values are out of range
      } 
      else {
        // Validate the day based on the month (months with 30 or 31 days)
        if ((mon == 4 || mon == 6 || mon == 9 || mon == 11) && da > 30) {
          isValid = false;  // Set flag to false for invalid days in 30-day months
        } 
        else if ((mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12) && da > 31) {
          isValid = false;  // Set flag to false for invalid days in 31-day months
        } 
        // Handle February (leap year vs. non-leap year)
        else if (mon == 2) {
          bool isLeap = (yrs % 4 == 0 && (yrs % 100 != 0 || yrs % 400 == 0));  // Check leap year condition
          
          if ((isLeap && da > 29) || (!isLeap && da > 28)) {
            isValid = false;  // Set flag to false for invalid days in February
          }
        }
      }

      // If the input is valid, set the time accordingly
      if (isValid) {
        setTime(hrs, min, secs, da, mon, yrs);  // Update the system time
        Serial.println("Enter the date (mm/dd/yyyy) & time (hh:mm:ss):");  // Prompt for new input
      } 
      else {
        Serial.println("Invalid input. Try again:");  // Notify the user if the input is invalid
      }
    }
  }

  // Update the time displayed on the LCD every 1000 ms (1 second)
  if (millis() - ref >= 1000) { 
    ref = millis();  // Update the reference time to the current time

    lcd.clear();  // Clear the LCD screen

    // Set the cursor to the first row and display the date in mm/dd/yyyy format
    lcd.setCursor(0, 0);
    lcd.print((month() < 10 ? "0" : "") + String(month()) + "/" + (day() < 10 ? "0" : "") + String(day()) + "/" + String(year()));  

    // Set the cursor to the second row and display the time in hh:mm:ss format
    lcd.setCursor(0, 1);
    lcd.print((hour() < 10 ? "0" : "") + String(hour()) + ":" + (minute() < 10 ? "0" : "") + String(minute()) + ":" + (second() < 10 ? "0" : "") + String(second()));
  }
}
