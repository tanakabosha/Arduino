/* This is an Arduino Uno sketch for access control using servo motor, push button and LCD module */

#include <HCSR04.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int lcd_address = 0x27, lcd_columns = 16, lcd_rows = 2;
const int servo_pin = 3;
const int trig_pin = 6, echo_pin = 5;
const int buzzer_pin = 8;
const int button_pin = 7;

int pos = 0;

long open_start_time = 0;
const long open_duration = 5000; 
bool door_open = false; 

long previous_proximity_time = 0;
const long proximity_interval = 2000;

UltraSonicDistanceSensor DistanceSensor(trig_pin, echo_pin); 
LiquidCrystal_I2C Lcd(lcd_address, lcd_columns, lcd_rows);
Servo Servo;

void setup() {

  // initialize serial communication
  Serial.begin(9600);

  // initialize the lcd in standby mode
  Lcd.init();
  Lcd.clear();
  Lcd.noBacklight();

  // initialize servo motor
  Servo.attach(servo_pin);
  // set initial closed position
  Servo.write(pos); 

  // set switch as input with internal pull-up resistor
  pinMode(button_pin, INPUT_PULLUP);

  // set buzzer pin as output
  pinMode(buzzer_pin, OUTPUT);
}

void allow() {

  if (door_open == false) {

    Lcd.backlight(); // activate  backlight for increased visibility
    Lcd.setCursor(0, 0); 
    Lcd.print("access granted"); // notify user of successful identification
    Lcd.setCursor(0, 1);
    Lcd.print("door opening"); // notify opening of door to user
    
    for (pos = 0; pos <= 90; pos += 1) {
    
      Servo.write(pos);
      delay(15);
    }

    Serial.println("door opened");

    open_start_time = millis(); // record the current time
    door_open = true; // set the flag that the door is now open
  }
}

void loop() {

  bool button_state = digitalRead(button_pin); // read the button state

  if(button_state == false){

    // execute the access allowed procedure if button is pressed
    allow();
  }

  if (door_open == true) {

      if (millis() - open_start_time >= open_duration) {

          Lcd.clear(); // clear the screen 
          Lcd.noBacklight(); // deactivate backlight for standby
          
          for (pos = 90; pos >= 0; pos -= 1) {
          
            Servo.write(pos); 
            delay(15);
          }

          Serial.println("door closed");
          door_open = false; 
      }
  }

  if (door_open == false) {

        long current_time = millis();
        
        if (current_time - previous_proximity_time >= proximity_interval) {

            previous_proximity_time = current_time; // save the last time of check
            
            float distance = DistanceSensor.measureDistanceCm(); // measure distance in centimetres
            
            if (distance > 0 && distance <= 50) { 

                Serial.println("person detected");
                
                Lcd.backlight();
                Lcd.setCursor(0, 0);
                Lcd.print("scan ID"); // print standby message to user
            } else {

                Lcd.clear();
                Lcd.noBacklight(); // return to standby
            }  
        }
    }
}
