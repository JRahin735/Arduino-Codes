/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 1000;  // interval at which to blink (milliseconds)
int curr = 13;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
}



// the loop function runs over and over again forever
void loop() {

  unsigned long currentMillis = millis();


    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    digitalWrite(13, LOW);
    digitalWrite(5, LOW);
    digitalWrite(8, LOW);



    // if the LED is off turn it on and vice-versa:
    if (curr == 13) {
      curr = 5;
    } else if (curr == 5) {
      curr = 8;
    } else {
      curr = 13;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(curr, HIGH);
  }

  
  // digitalWrite(8, HIGH);
  // delay(1000);                      // wait for a second
  // digitalWrite(13, LOW);   // turn the LED off by making the voltage LOW
  // digitalWrite(5, LOW);
  // digitalWrite(8, LOW);
  // delay(1000);                      // wait for a second
}
