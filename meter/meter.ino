/* This is an Arduino Uno sketch for an energy meter and logger 
 * using SCT-013 current sensor, ZMPT101B voltage sensor, 
 * buzzer module and LCD I2C 
 */

#include "EmonLib.h" 
#include <Keypad.h>
#include "LiquidCrystal_I2C.h"

// keypad variables
const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// pin connection variables
int lcd_address = 0x27, lcd_columns = 16, lcd_rows = 2;
int current_pin = 0;
int voltage_pin = 1;
int buzzer_pin = 12;
const int green_led = 10;
const int red_led = 11;
byte row_pins[rows] = {9, 8, 7, 6};
byte col_pins[cols] = {5, 4, 3, 2};

// energy variables
double credit = 0.0000;           
unsigned long last_compute_time = 0;
double low_credit = 5.0000;

// display variables
unsigned long last_update_time = 0;

// object initialization
EnergyMonitor Mon;
LiquidCrystal_I2C Lcd(lcd_address, lcd_columns, lcd_rows);
Keypad Pad = Keypad(makeKeymap(keys), row_pins, col_pins, rows, cols);

// string variables
String input_buffer = "";
String status = "";

void setup(){

	// begin serial communication
    Serial.begin(9600);
    
	// setup digital pin modes
    pinMode(buzzer_pin, OUTPUT);
    pinMode(green_led, OUTPUT);
	pinMode(red_led, OUTPUT);
	
	// setup sensors
    Mon.voltage(voltage_pin, 234.26, 1.7);
    Mon.current(current_pin, 111.1);
	
	// delay to allow sensors stabilization 
	delay(1000); 
    
	// LCD routine on start
    Lcd.init();
    Lcd.backlight();
    Lcd.setCursor(0, 0); 
    Lcd.print("Meter ready!");
	Lcd.clear();
    Lcd.setCursor(0, 0);
    Lcd.print("Load credit");
	Lcd.setCursor(0, 1);
    Lcd.print("Enter units + #");
    
	// delay to allow the user to see the startup prompt
    delay(5000);
	
	// clear the display
	Lcd.noBacklight();
    Lcd.clear();

	// initialize timers
    last_compute_time = millis();
    last_update_time = millis();
}

void loop() {

  // timers
  unsigned long current_time = millis();
  double delta_hours = (double)(current_time - last_compute_time) / 3600000.0;
  last_compute_time = current_time;

  // calculate instantaneous power
  Mon.calcVI(10, 2000);
  double actual_power = abs(Mon.realPower);

  // Energy deduction
  if (credit > 0 && actual_power > 5.0) {

    double consumed = (actual_power / 1000.0) * delta_hours;
    credit -= consumed;
  }
  
  // get keypad input
  char key = Pad.getKey();
  
  if (key) {

	// activate backlight on key press
	Lcd.backlight();
	
    if (key >= '0' && key <= '9') {

      input_buffer += key; // append digit to buffer
	  Lcd.clear();
      Lcd.setCursor(0, 0);
	  Lcd.print(input_buffer);
    } else if (key == '#') { // '#' acts as the "Enter" key

      if (input_buffer.length() > 0) {

        float recharge = input_buffer.toFloat();
        credit += recharge;
		
        input_buffer = ""; // clear buffer for next time
		Lcd.noBacklight();
      }
    } else if (key == '*') { // '*' acts as "Clear"

      input_buffer = "";
      Lcd.print(input_buffer);
    }
  }

  // credit display and log trigger
  if (current_time - last_update_time >= 1000) {

	if (input_buffer.length() == 0) {

		balanceLCD();
        log();
	}
	
	last_update_time = current_time;
  }
  
  indicators();
}

// log to serial in csv format
void log(){

  Serial.print(status);
  Serial.print(',');
  Serial.println(credit);
}

// Balance display logic
void balanceLCD() {

  Lcd.setCursor(0, 0);
  Lcd.print("Credit");
  Lcd.setCursor(0, 1);
  Lcd.print(credit, 5); 
  Lcd.print("kWh");
}

// credit status indicators
void indicators() {
	digitalWrite(green_led, LOW);
    digitalWrite(red_led, LOW);
	
	// led and buzzer logic
	if (credit <= 0) {

		status = "Null";
		
		if (millis() % 200 < 100){

			tone(buzzer_pin, 3000);
			digitalWrite(red_led, HIGH);
		} else {

			noTone(buzzer_pin);
		} 
	} else if (credit < low_credit) {
		
		status = "Low";
		
		if (millis() % 500 < 250){

			tone(buzzer_pin, 2000);
			digitalWrite(red_led, HIGH);
		} else {

			noTone(buzzer_pin);
		}
	} else {
		status = "Normal";
		
		noTone(buzzer_pin);
		digitalWrite(green_led, HIGH);
	}
}
