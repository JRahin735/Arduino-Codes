/* UIN: 665219123
* NETID: rjain56
* Title: Lab 7 - Communication Between Arduinos
* Description: This lab demonstrates communication between two Arduino boards using serial communication. 
*              When a signal is received on pin 5 (button press or sensor trigger), it sends the character 'x' 
*              via serial communication to the other Arduino. When the other Arduino receives 'x', it toggles 
*              the light state connected to pin 4 (turning it ON or OFF).
* References: Arduino Serial.read() documentation, Arduino digitalWrite() documentation
* Assumptions: Both Arduino boards are set to communicate at a baud rate of 9600, 
*              and the second Arduino is programmed to respond to the 'x' character.
* Partner: Ayush Bhardwaj 651465377
* TA: 
*/

int light_state = LOW;  // Initialize the light state as LOW (OFF)

void setup() {
  pinMode(4, OUTPUT);    // Set pin 4 as an output (for controlling light)
  pinMode(5, INPUT);     // Set pin 5 as an input (for receiving a signal)
  Serial.begin(9600);    // Start serial communication at a baud rate of 9600
}

void loop() {
  // Check if there's any data available to read from the Serial
  if (Serial.available() > 0) {

    // Toggle the light state if the received character is 'x'
    if (Serial.read() == 'x') {
      light_state = !light_state;      // Flip the light state
      digitalWrite(4, light_state);    // Update the light state on pin 4
    }
  }

  // Check if pin 5 is HIGH (button or sensor is activated)
  if (digitalRead(5) == HIGH) {
    Serial.write('x');  // Send character 'x' over serial to trigger the other Arduino
  }
}
