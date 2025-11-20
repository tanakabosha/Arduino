
void setup() {
  
   pinMode(LED_BUILTIN, OUTPUT); //set on-board led on digital pin 13 as output
   Serial.begin(9600); //initialize serial port
}

void loop() {

   if (Serial.available()  > 0) {
      String command = Serial.readStringUntil('\n'); //read string until newline character
      command.trim(); //remove whitespace
      if (command == "on") {
         digitalWrite(LED_BUILTIN, HIGH); //turn on on-board led
         Serial.println("On-board LED is turned on");
      } else if (command == "off") {
         digitalWrite(LED_BUILTIN, LOW); //turn off on-board led
         Serial.println("On-board LED is turned off");
      }
   } 
   delay(100);
}

