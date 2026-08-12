/* This is an Arduino Uno sketch for 28BYJ-48 stepper motor control using HW-504 joystick */

#include <Stepper.h>

const int sw_pin = 2;  //connect SW to digital pin 2
const int x_pin  = A1; //connect VRx to analog in pin A1 
const int y_pin  = A0; //connect VRy to analog in pin A0 
const int steps_per_revolution = 2048; //steps for full-step mode
const int IN1 = 6; //connect IN1 to digital pin 6  
const int IN2 = 9; //connect IN2 to digital pin 9
const int IN3 = 10; //connect IN3 to digital pin 10
const int IN4 = 11; //connect IN4 to digital pin 11

Stepper Stepper(steps_per_revolution, IN1, IN2, IN3, IN4); //initialize stepper motor

void setup() {

  Serial.begin(9600); //initialize serial port
  pinMode(sw_pin, INPUT_PULLUP); //set switch as input with internal pull-up resistor 
}

void loop() {
  
  bool button_state = digitalRead(sw_pin);

  if(button_state){
  
    // int initial_x_value = analogRead(x_pin);
    // int mapped_x_value = map(initial_x_value, 0, 1023, 2, -3);
    int initial_y_value = analogRead(y_pin);
    int mapped_y_value = map(initial_y_value, 0, 1023, -4, 6);
    int final_y_value = constrain(mapped_y_value, 0, 6);
    int motor_speed = map(final_y_value, 0, 6, 5, 12);
    Stepper.setSpeed(motor_speed);
    Stepper.step(steps_per_revolution/2048);
  }  
}
