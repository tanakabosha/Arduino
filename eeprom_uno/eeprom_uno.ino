/* This is an Arduino Uno sketch for manual EEPROM read/write */

#include "EEPROM_RANO.h"

// assign the address value
unsigned int addr = 10;

// assign the data value
// unsigned char val_write = 155;
  
void setup() {

  Serial.begin(9600);
  
  // write the value
  // EEPROM_write(addr, val_write);
  
  // Serial.println("Data written!");

  // read back the value
  unsigned char val_read = EEPROM_read(addr);
  
  Serial.print("Value at address ");
  Serial.print(addr);
  Serial.print(" is: ");
  Serial.println(val_read);
  
}

void loop() {
  // keep empty to avoid repetitive writing
}
