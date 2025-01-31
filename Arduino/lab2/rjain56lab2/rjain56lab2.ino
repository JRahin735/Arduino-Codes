// Rahin Jain, 665219123 (rjain56)
// Lab 2 - Three Bit Counter
// Description - This Arduino code implements a three-bit counter that increments 
//       or decrements between 0 and 7 using two buttons. The current count is displayed 
//       in binary on three LEDs. Button inputs are debounced for reliability, and the counter 
//       wraps around when reaching the limits.
// References - "no references used"
// TA - Yamaan
// Date - Sept. 19 '24
// Time - 12:00

const int pinLED = 13;  // General purpose LED (not used here)
const int pinA = 12;    // LED for the least significant bit 
const int pinB = 10;    // LED for the middle bit
const int pinC = 8;     // LED for the most significant bit 
const int pinINC = 2;   // Increment button pin
const int pinDEC = 3;   // Decrement button pin

// Turning off button states as default
int incButtonState = LOW;  
int decButtonState = LOW;  
int lastIncButtonState = LOW;  
int lastDecButtonState = LOW; 

unsigned long lastIncDebounceTime = 0;  // Last debounce time for increment button
unsigned long prevDecDebounce = 0;  // Last debounce time for decrement button
unsigned long buffer = 50;  // Debounce buffer time in milliseconds

int counter = 0;  // Counter variable to track the current count (0-7)

// Function to update the LEDs based on the current counter value
void updateLEDs() {
    if ((counter >> 0) % 2 == 1) {  // Update LSB LED
        digitalWrite(pinA, HIGH);
    } else {
        digitalWrite(pinA, LOW);
    }

    if ((counter >> 1) % 2 == 1) {  // Update middle bit LED
        digitalWrite(pinB, HIGH);
    } else {
        digitalWrite(pinB, LOW);
    }

    if ((counter >> 2) % 2 == 1) {  // Update MSB LED
        digitalWrite(pinC, HIGH);
    } else {
        digitalWrite(pinC, LOW);
    }
}

// Setup function to initialize the pin modes
void setup() {
  // Set LED pins as outputs
    pinMode(pinA, OUTPUT);  
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinLED, OUTPUT);

// Set button pins as inputs
    pinMode(pinINC, INPUT);  
    pinMode(pinDEC, INPUT);
}

// Main loop to handle button presses and update the counter
void loop() {
    int incButtonReading = digitalRead(pinINC);  // Read increment button state
    int decButtonReading = digitalRead(pinDEC);  // Read decrement button state

    if (decButtonReading != lastDecButtonState) {  // Check for state change in decrement button
        prev = millis();  // Update debounce timer
    }

    // Debounce logic and decrement counter if button is pressed
    if (((millis() - prevDecDebounce) > buffer) && (decButtonReading != decButtonState)) {
        decButtonState = decButtonReading;  // Update current state
        if (decButtonState == HIGH && counter != 0) {  // Decrement counter if possible
            counter--;
            updateLEDs();  // Update LEDs to reflect new counter value
        }
    }

    if (incButtonReading != lastIncButtonState) {  // Check for state change in increment button
        lastIncDebounceTime = millis();  // Update debounce timer
    }

    // Debounce logic and increment counter if button is pressed
    if (((millis() - lastIncDebounceTime) > buffer) && (incButtonReading != incButtonState)) {
        incButtonState = incButtonReading;  // Update current state
        if (incButtonState == HIGH && counter != 7) {  // Increment counter if possible
            counter++;
            updateLEDs();  // Update LEDs to reflect new counter value
        }
    }

    lastIncButtonState = incButtonReading;  // Store the last state of increment button
    lastDecButtonState = decButtonReading;  // Store the last state of decrement button
}
