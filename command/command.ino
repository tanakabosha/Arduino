/* This is an Arduino Uno sketch for switching a relay from serial command */

const int rl_pin = 3; // connect relay S to pin 3

void setup() {
  
   pinMode(rl_pin, OUTPUT); //set relay switch as output
   Serial.begin(9600); //initialize serial port
}

void loop() {

   if (Serial.available()  > 0) {

      String command = Serial.readStringUntil('\n'); //read string until newline character
      command.trim(); //remove whitespace

      if (command == "on") {

         digitalWrite(rl_pin, HIGH); //turn on on-board led
         Serial.println("Switch is turned on");
      } else if (command == "off") {

         digitalWrite(rl_pin, LOW); //turn off on-board led
         Serial.println("Switch is turned off");
      }
   } 
   delay(100);
}
