/* This is an Arduino sketch that changes the on-board LED blink period using an interrupt */

const int interrupt_pin	=	2;
const int led_pin	=	13; 

int period	 = 500;

void setup() {

	pinMode(led_pin, OUTPUT);
	pinMode(interrupt_pin, INPUT_PULLUP);

	attachInterrupt(0,	 blinkFast, FALLING);
}

void loop() {

	digitalWrite(led_pin, HIGH);
	delay(period);
	digitalWrite(led_pin, LOW);
	delay(period);		
}

void	blinkFast() {

	period	=	100;
}
