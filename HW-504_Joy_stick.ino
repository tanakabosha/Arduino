/* This is Arduino Uno code for HW-504 joystick module*/
 
const int Sw_pin = 2;  //connect SW to digital pin 2
const int X_pin  = A1; //connect VRx to analog in pin A1 
const int Y_pin  = A0; //connect VRy to analog in pin A0
const int ledPin = 13; //onboard led is connected to digital pin 13 

bool buttonState;
int xValue;
int yValue;

void setup() {
  
  Serial.begin(9600);  
  pinMode(Sw_pin, INPUT_PULLUP); //set switch as input with internal pull-up resistor
  pinMode(ledPin, OUTPUT);

}

void loop() {
  //press down the joystick
  buttonState = digitalRead(Sw_pin);
  if(!buttonState){
  digitalWrite(ledPin, HIGH);
}else{
  digitalWrite(ledPin, LOW);
}

  xValue = analogRead(X_pin);
  xValue = map(xValue, 0, 1023, 2, -3);
  Serial.print("X:");
  Serial.println(xValue);

  yValue = analogRead(Y_pin);
  yValue = map(yValue, 0, 1023, -4, 6);
  Serial.print("Y:");
  Serial.println(yValue);

  delay(100);
}
