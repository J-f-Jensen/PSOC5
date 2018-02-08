/* 
* Emulated EEPROM for PSOC5
* Created under the beer license rules :-)
* Simpel mapper to the EM_EEPROM_1 functions created by PSOC Creator
*/

#ifndef _EM_EEPROM_H_
#define _EM_EEPROM_H_ 1

#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
    
extern "C" {
#include <Project.h>
}

// EEPROM size
#define E2END 0x7FF

// Dummy
void em_eeprom_initialize(void);

// Write the source to flash
void em_eeprom_write(const uint8 *srcBuf, const uint8 *eepromPtr, uint32 byteCount);


#endif
