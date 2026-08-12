#include "Arduino.h"
#include "EEPROM_RANO.h"

void EEPROM_write(unsigned int uiAddress, unsigned char ucData) {
  
  // wait for completion of previous write
  while(EECR & (1 << EEPE));
  
  // set up address and Data Registers
  EEAR = uiAddress;
  EEDR = ucData;
  
  // write logical one to EEMPE (Master Write Enable)
  EECR |= (1 << EEMPE);
  
  // start eeprom write by setting EEPE
  EECR |= (1 << EEPE);
}

unsigned char EEPROM_read(unsigned int uiAddress) {
	
  // wait for completion of previous write
  while(EECR & (1 << EEPE));
  
  // set up address register
  EEAR = uiAddress;
  
  // start eeprom read by writing EERE
  EECR |= (1 << EERE);
  
  // return data from Data Register
  return EEDR;
}
