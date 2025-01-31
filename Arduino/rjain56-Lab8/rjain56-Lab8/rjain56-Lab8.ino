/*
 * LCD Interrupt Program
 *  Rahin Jain, rjain56@uic,edu 665219123
 * Description:
 * This program uses an Arduino with a 16x2 LCD display and two push buttons. The system operates in two states:
 * - Normal State: Displays the elapsed time since the system started in seconds.
 * - Interrupt State: Activated when Button 1 is pressed, displaying an interrupt message. Button 2 returns the system to the normal state.
 * 
 * Assumptions:
 * - Button 1 and Button 2 are connected to pins 2 and 3 respectively, which are configured to handle interrupts.
 * - The LCD display is connected with the specified pin configuration (pins 12, 11, 7, 6, 5, 4).
 * - Button 1 triggers an interrupt to display a message, and Button 2 resets the system to the normal state.
 * - Interrupts are triggered on a falling edge signal.
 * - The LCD screen is a standard 16x2 character display.
 */

#include <LiquidCrystal.h>

// Setup for LCD display
LiquidCrystal lcdDisplay(12, 11, 7, 6, 5, 4);

// Button pin definitions
const int interruptButton1 = 2;
const int interruptButton2 = 3;

// System state variables
volatile int systemState = 0; // 0: Normal operation, 1: Interrupt state
volatile unsigned long systemStartTime = 0;

String lcdLineOne = "";
String lcdLineTwo = "";

void setup() {
  // Configure button pins as inputs with pull-up resistors
  pinMode(interruptButton1, INPUT_PULLUP);
  pinMode(interruptButton2, INPUT_PULLUP);

  // Attach interrupts to buttons for state changes
  attachInterrupt(digitalPinToInterrupt(interruptButton1), handleButton1Interrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptButton2), handleButton2Interrupt, FALLING);

  // Initialize the LCD display
  lcdDisplay.begin(16, 2);
  initializeDisplay();
  systemStartTime = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  if (systemState == 0) {
    updateElapsedTime(currentMillis); // Update the display with the elapsed time
  }
  else if (systemState == 1) {
    displayInterruptMessage(); // Display the interrupt message
  }
}

void updateElapsedTime(unsigned long currentMillis) {
  lcdDisplay.setCursor(0, 1);
  lcdDisplay.print((currentMillis - systemStartTime) / 1000); // Calculate and display elapsed seconds
  lcdDisplay.print(" seconds");
}

void displayInterruptMessage() {
  lcdDisplay.clear();
  lcdDisplay.setCursor(0, 0);
  lcdDisplay.print(lcdLineOne); // Display the first line of the interrupt message
  lcdDisplay.setCursor(0, 1);
  lcdDisplay.print(lcdLineTwo); // Display the second line of the interrupt message
}

void initializeDisplay() {
  lcdDisplay.clear();
  lcdDisplay.setCursor(0, 0);
  lcdDisplay.print("System on for:"); // Initial message indicating system is running
  lcdDisplay.setCursor(0, 1);
  lcdDisplay.print("0 seconds"); // Start time display
}

// Interrupt Service Routine for Button 1
void handleButton1Interrupt() {
  systemState = 1; // Set system state to interrupt mode
  lcdLineOne = "Interrupt received!"; // Set message for the first line
  lcdLineTwo = "Press button 2 to continue"; // Set message for the second line
}

// Interrupt Service Routine for Button 2
void handleButton2Interrupt() {
  if (systemState == 1) {
    systemState = 0; // Reset system state to normal operation
    systemStartTime = millis(); // Restart the timer
    initializeDisplay(); // Reinitialize the display
  }
}