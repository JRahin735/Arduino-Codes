// Bridget Danaher, 665329073, bdana2
// Lab 2 - Three Bit Counter
// Lab Room: Taft Hall 204 
// Date Presented: Friday, September 13th, 2024
//             TA: Yamaan
// Description: 
//    This program creates a 3-bit binary counter, using 3 LEDs to 
//    represent the bits, and maintains values from 0 - 7.
//    One button represents increment, and one for decrement.
// Assumptions:
//    I had already known how binary bit masking works, but determining
//    how the debounce logic works was the most difficult part. I
//    remembered how the millis() function worked from the previous lab,
//    but applying it to this lab was much more difficult since we needed
//    to retrieve the time twice and compare it with the previous status.
// References: 
//    simple button: https://docs.arduino.cc/built-in-examples/digital/Button/
//    debounce logic: https://www.ladyada.net/learn/arduino/lesson5.html
//    bitmasking: https://www.geeksforgeeks.org/bitmasking-in-cpp/


const int ledPin = 13;
const int onesPin = 12;  
const int twosPin = 10;  
const int foursPin = 8;  

const int incButtonPin = 2;
const int decButtonPin = 3;

int incButtonState = LOW;
int decButtonState = LOW;  

int lastIncButtonState = LOW;
int lastDecButtonState = LOW;
unsigned long lastIncDebounceTime = 0;
unsigned long lastDecDebounceTime = 0;
unsigned long debounceDelay = 50;

int internalCount = 0; 

void updateLEDs(){

  if ((internalCount >> 0) % 2 == 1) 
    digitalWrite(onesPin, HIGH);
  else
    digitalWrite(onesPin, LOW);

  if ((internalCount >> 1) % 2 == 1) 
    digitalWrite(twosPin, HIGH);
  else
    digitalWrite(twosPin, LOW);

  if ((internalCount >> 2) % 2 == 1) 
    digitalWrite(foursPin, HIGH);
  else
    digitalWrite(foursPin, LOW);
} 


void setup() {
  pinMode(onesPin, OUTPUT);
  pinMode(twosPin, OUTPUT);
  pinMode(foursPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(incButtonPin, INPUT);
  pinMode(decButtonPin, INPUT);
}


void loop() {

  int incButtonReading = digitalRead(incButtonPin);
  int decButtonReading = digitalRead(decButtonPin);

  if (incButtonReading != lastIncButtonState)               
    lastIncDebounceTime = millis();                         
  
  if (((millis() - lastIncDebounceTime) > debounceDelay) && (incButtonReading != incButtonState)){   
    incButtonState = incButtonReading;                       
    if (incButtonState == HIGH && internalCount != 7) {      
      internalCount++;
      updateLEDs();
    } 
  }


  
  if (decButtonReading != lastDecButtonState)               
    lastDecDebounceTime = millis();                         
  
  if (((millis() - lastDecDebounceTime) > debounceDelay) && (decButtonReading != decButtonState)){   
    decButtonState = decButtonReading;                       // update the new state to be what we received from board
    if (decButtonState == HIGH && internalCount != 0) {      // was the button pressed and have we reached our lower limit
      internalCount--;
      updateLEDs();
    } 
  }

  //update the last button stats to reflect current reading
  lastIncButtonState = incButtonReading;
  lastDecButtonState = decButtonReading;
}
