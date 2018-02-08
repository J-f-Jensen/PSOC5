/*
* Emulated EEPROM for PSOC5
* Created under the beer license rules :-)
* Simpel mapper to the EM_EEPROM_1 functions created by PSOC Creator
*/

#include <em_eeprom.h>

cystatus status;

void em_eeprom_initialize(void)
{
    //Don't do any thing
}


void em_eeprom_write(const uint8 srcBuf[], const uint8 eepromPtr[], uint32 byteCount)
{
    // Write byte to flash (Emulated EEPROM), status is current not used
    status = Em_EEPROM_1_Write(srcBuf, eepromPtr, byteCount);
}
