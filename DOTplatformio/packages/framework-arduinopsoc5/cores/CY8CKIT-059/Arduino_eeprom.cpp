/* 
Simpel mapper to the EEPROM_1 functions created by PSOC Creator
*/

#include <Arduino_eeprom.h>

extern "C" {
#include <Project.h>
}

//#define EEPROM_SIZE EEPROM_1_EEPROM_SIZE

void eeprom_initialize(void)
{
    // Enable the EEPROM 
    EEPROM_1_Enable();
    
    // Update the temperature for the EEPROM to ensure valid write
    EEPROM_1_UpdateTemperature();

}


void eeprom_updatetemperature(void)
{
    // Update the temperature for the EEPROM to ensure valid write, 
    //      should be executed if temperature have changed more than 10 degree or just to be shure
    EEPROM_1_UpdateTemperature();
}

uint8_t eeprom_read_byte(const uint8_t *addr)
{
	return EEPROM_1_ReadByte(*addr);
}


void eeprom_write_byte(uint8_t *addr, uint8_t data)
{
    // Write byte to eeprom
    EEPROM_1_WriteByte(data, *addr);
}

