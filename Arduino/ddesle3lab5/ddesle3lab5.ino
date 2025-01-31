// Dishant Desle, 652956059 and ddesle3
// Lab 5 - Multiple Inputs and Outputs.
// Description - This lab gives you practical experience using an Arduino to control 
//              numerous input and output devices, so you can learn how to manage 
//              multiple components at once.
// Assumption - A photoresistor is connected to analog pin A0.
//              A potentiometer is connected to analog pin A1.
//              A passive buzzer is connected to digital pin 6.
//              Optional button for buzzer control is connected to digital pin 7.
// References - https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
//              https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
//              https://www.arduino.cc/reference/en/language/functions/math/map/
// Date - 10/10/2023
// Time - 10:30am
// TA - Sanjana




// Pin definitions
const int photoresistorPin = A0;                   // Analog input pin for the photoresistor
const int ledPins[] = {2, 3, 4, 5};                // Array holding the pin numbers for the LEDs
const int potentiometerPin = A1;                   // Analog input pin for the potentiometer
const int buzzerPin = 6;                           // Digital output pin for the buzzer
const int buzzerEnablePin = 7;                     // Digital input pin for the buzzer toggle button

// Light thresholds for LED control
int darkThreshold = 100;                           // Threshold for darkness detected by the photoresistor (adjustable)
int brightThreshold = 900;                         // Threshold for bright light (e.g., flashlight, adjustable)

// Buzzer frequency range
int buzzerMinFrequency = 31;                       // Minimum frequency the buzzer can produce (due to hardware limitation)
int buzzerMaxFrequency = 20000;                    // Maximum frequency within human hearing range

bool buzzerEnabled = true;                         // Flag to control whether the buzzer is enabled or not

void setup() {
  // Set up LED pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Set up buzzer pin as output
  pinMode(buzzerPin, OUTPUT);

  // Set up the buzzer control button pin as input with internal pull-up resistor
  pinMode(buzzerEnablePin, INPUT_PULLUP);

  // Initialize serial communication for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Part 1: Control LEDs based on light level
  int lightValue = analogRead(photoresistorPin);   // Read the light level

  // Control LEDs based on the light value
  if (lightValue <= darkThreshold) {
    // It's dark: turn on all LEDs
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
  } else if (lightValue >= brightThreshold) {
    // It's very bright: turn off all LEDs
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  } else {
    // For intermediate light levels: turn on a proportional number of LEDs
    int numLEDs = map(lightValue, darkThreshold, brightThreshold, 4, 0);
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], i < numLEDs ? HIGH : LOW);
    }
  }

  // Part 2: Control buzzer tone based on potentiometer value
  int potValue = analogRead(potentiometerPin);     // Read the potentiometer position
  int buzzerFrequency = map(potValue, 0, 1023, buzzerMinFrequency, buzzerMaxFrequency); // Map the potentiometer value to a valid buzzer frequency

  // Part 3: Toggle buzzer on/off using the button
  bool buttonPressed = digitalRead(buzzerEnablePin) == LOW; // Read the button state (active low due to INPUT_PULLUP)

  // If the button is pressed, toggle the buzzer on/off
  if (buttonPressed) {
    buzzerEnabled = !buzzerEnabled;                // Toggle the buzzer's enabled state
    delay(200);                                    // Debounce delay to avoid reading multiple presses
  }

  // Produce a tone if the buzzer is enabled; otherwise, ensure it's off
  if (buzzerEnabled) {
    tone(buzzerPin, buzzerFrequency);              // Play the tone with the calculated frequency
  } else {
    noTone(buzzerPin);                             // Stop playing any tone
  }
}

