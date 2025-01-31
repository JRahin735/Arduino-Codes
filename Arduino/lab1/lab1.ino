
/*
Rahin Jain
rjain56
665219123

Lab-01: Three Blinking Lights
the code hould make the 13, 5 and 8 nodes (default on board, red and green light blink one after the another. Ijust assumed we don't need to put a light for 13 since, it seems to be connected right on the board. I used the blink example on the IDE as a reference.)
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
