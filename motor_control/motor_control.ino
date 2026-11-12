/* This is an Arduino Uno sketch for 28BYJ-48 stepper motor control using HW-504 joystick */

#include <Stepper.h>

const int y_pin  = A0; //connect VRy to analog pin A0 

const int IN1 = 8; //connect IN1 to digital pin 8  
const int IN2 = 9; //connect IN2 to digital pin 9
const int IN3 = 10; //connect IN3 to digital pin 10
const int IN4 = 11; //connect IN4 to digital pin 11

const int steps_per_revolution = 2048; //steps for full-step mode
int y_centre_value = 512; //temporary centre value for joystick y-axis
const int deadzone = 15; //prevents drift when joystick is centered

int motor_speed = 0; //initialize motor speed at zero
int step_direction;

//initialize stepper motor
//pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper stepperMotor(steps_per_revolution, IN1, IN3, IN2, IN4); 

void setup() {

  Serial.begin(9600); //initialize serial port

  pinMode(y_pin, INPUT);

  Serial.println("calibrating joystick center...please keep stick released!");
  
  //auto calibration of joystick center value routine
  long sum = 0;
  for (int i = 0; i < 50; i++) {
    sum += analogRead(y_pin);
    delay(10); //take 50 samples spaced over 500ms
  }

  y_centre_value = sum / 50; //average resting center
  
  Serial.print("calibration complete...center value: ");
  Serial.println(y_centre_value);
}

void loop() {

  //read joystick y-axis
  int y_value = analogRead(y_pin);

  //check if joystick is moved outside the center deadzone
  if (abs(y_value - y_centre_value) > deadzone) {

    if (y_value > y_centre_value) {

     //clockwise rotation
      //map into a safe speed range (1 to 15 RPM)
      motor_speed = map(y_value, y_centre_value + deadzone, 1023, 1, 15);
      step_direction = 1;
    } else {

      //counter-clockwise rotation
      //map into speed range (1 to 15 RPM)
      motor_speed = map(y_value, 0, y_centre_value - deadzone, 15, 1);
      step_direction = -1;
    }

    //set speed
    stepperMotor.setSpeed(motor_speed);

    //take a single step in the evaluated direction
    stepperMotor.step(step_direction * 1);
  } 
  else {

    //joystick is centered
  }
}
