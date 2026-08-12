
#ifndef EEPROM_RANO_H
#define EEPROM_RANO_H

#ifdef __cplusplus
extern "C" {
#endif

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);

#ifdef __cplusplus
}
#endif

#endif

