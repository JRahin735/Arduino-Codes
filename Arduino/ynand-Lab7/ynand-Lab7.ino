/* UIN: 671068709
* NETID: ynand3
* Title: Lab 7 - Communication Between Arduinos
* Description: Lab 7 utilizes two adruinos to communicate between each other using different inputs and to simulataneously provide output 
* References: Prelab documentation provided in the lab handout for Lab 7 and also got help from my partner.  
* Assumptions: I assumed that the setup for this lab will be the same as the lab 2 as there was switch buttons and simple LEDS. 
* Lab Info: Thursday, Mar 7th at 12:10 am (In OH) 
* Partner: David Mei (NETID: tmei22, UIN: 675087303)
* TA: Dwij
*/

const int led = 4;
const int btn = 5;

int blink = LOW;
int prevBtnState = LOW;
int currBtnState = LOW;
unsigned long prevMillis = 0;
const long debounceInterval = 100;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    
    if (incomingByte == 'b') {

      blink = !blink;
      digitalWrite(led, blink);
    }
  }

  if (digitalRead(btn) == HIGH) {
    Serial.write('b');
  }

}