// Rahin Jain, 665219123 and rjain56
// Lab 5 - Multiple Inputs and Outputs.
// Description - The lab provides hands-on experience using Arduino to control multiple input and output devices, teaching how to manage them simultaneously.
//              Optional button for buzzer control is connected to digital pin 7.
// References - https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
// https://www.arduino.cc/reference/en/language/functions/math/map/
// https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
// Date - 10/11/2024
// Time - 
// TA -                       
               
bool isEnabled = true;                         
const int ledPins[] = {2, 3, 4, 5}; 


unsigned long lastBuzzTime = 0;
int buzzIntervals[] = {8000, 4000, 2000, 1000, 500, 0}; 
int interval_buzz = 8000; 

void setup() {

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(6, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {

  int val = analogRead(A0);  
  Serial.println(val); 

  if (val <= 100) {

      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
  } 
  else if (val <= 200) {

      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
  } 
  else if (val <= 300) {

      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
  } 
  else if (val <= 350) {

      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
  } 
  else if (val >= 400) {  

      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
  } 
  else {

    int num = map(val, 100, 900, 4, 0);

    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], i < num ? HIGH : LOW);
    }
  }


  int val_A = analogRead(A1);

 int idx = map(val_A, 0, 1023, 0, 4);
  interval_buzz = buzzIntervals[idx];

  unsigned long currentTime = millis();

  if (interval_buzz == 0 || (currentTime - lastBuzzTime) >= interval_buzz) {
    
    lastBuzzTime = currentTime;
    tone(6, 11000);  // 10000 is the fixed freq of the buzzer
  } 
  else {
    
    noTone(6);  
  }
}

