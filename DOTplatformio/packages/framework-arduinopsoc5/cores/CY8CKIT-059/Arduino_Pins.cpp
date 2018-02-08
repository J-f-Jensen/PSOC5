/****************************************************************************
 * Arduino_Pins.cpp
 * Arduino Uno pin compatibility support for the PSoC5LP
 * Mike Hord @ SparkFun Electronics
 * 14 April 2015
 *
 * Implements the "standard" Arduino per-pin IO functionality on the PSoC5LP.
 *
 * Development environment specifics:
 * Code developed in PSoC Creator 3.1
 * Tested in Arduino IDE 1.6.3
 *
 * This code is beerware; if you see me (or any other SparkFun employee) at the
 * local, and you've found our code helpful, please buy us a round!
 * ****************************************************************************/

extern "C" {
#include <Project.h>
}

#include <Arduino_Pins.h>

// Map the I/O pin number to the actual address of the register as defined by
//  the IDE. These constants are mapped to the IDE constants in the header.
uint32_t pinNumberToPointer[NUM_BASE_PINS] = 
  { D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10,D11, D12, D13, D14, D15, D16, 
  D17, D18, D19, D20, D21, D23, D24, D25, D26, D27, D28, D29, D30, D31, D32, 
  D33, D34, D35, D36, D37};

/*
 * Pins descriptions
 */
//extern const PinDescription g_APinDescription[]=
//{
  // 0 .. 37 - Digital pins
  // ----------------------
  // 
//  { PIOA, PIO_PA8A_URXD,     ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT,  PIN_ATTR_DIGITAL,                 NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // URXD
//  { PIOA, PIO_PA9A_UTXD,     ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT,  PIN_ATTR_DIGITAL,                 NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // UTXD
//  { PIOB, PIO_PB25B_TIOA0,   ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC0_CHA0     }, // TIOA0
//  { PIOC, PIO_PC28B_TIOA7,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC2_CHA7     }, // TIOA7
//  { PIOC, PIO_PC26B_TIOB6,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC2_CHB6     }, // TIOB6
  
  // END
//  { NULL, 0, 0, PIO_NOT_A_PIN, PIO_DEFAULT, 0, NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }
//} ;
  

    
/* Port of the digitalWrite function used by Arduino. Includes a check to
 * ensure that the value passed is within the valid range for the aliases
 * or for the registers in question. */
void digitalWrite(uint32_t pin, uint8_t level)
{
  if ( pin < NUM_BASE_PINS )
  {
    pin = pinNumberToPointer[pin];
  }
  // See the TRM for the PSoC5LP for why these numbers were chosen.
  else if (pin < 0x40005000 || pin > 0x40005047)
  {
    return;
  }
  if (level == HIGH)
  {
    CyPins_SetPin(pin);
  }
  else
  {
    CyPins_ClearPin(pin);
  }
}
    
// See digitalWrite for explanation.
uint8_t digitalRead(uint32_t pin)
{
  if ( pin < NUM_BASE_PINS )
  {
    pin = pinNumberToPointer[pin];
  }
  else if (pin < 0x40005000 || pin > 0x40005047)
  {
    return 0;
  }
  return CyPins_ReadPin(pin);
}

/* A little more advanced than pinMode for the Arduino, as it needs to handle
 *  the case where we want to bypass the normal IO circuitry and attach the
 *  pin to the peripheral bus. */
void pinMode(uint32_t pin, enum PIN_MODE mode)
{
  if ( pin < NUM_BASE_PINS )
  {
    pin = pinNumberToPointer[pin];
  }
  else if (pin < 0x40005000 || pin > 0x40005047)
  {
    return;
  }
  uint8_t registerValue = *(reg8*)(pin);
  switch(mode)
  {
      case OUTPUT:
        registerValue &= PIN_DISABLE_BYPASS;
        registerValue |= PIN_DM_STRONG;
      break;
      case INPUT_PULLUP:
        registerValue &= PIN_DISABLE_BYPASS;
        registerValue |= PIN_DM_RES_UP;
      break;
      case PERIPHERAL:
        registerValue |= PIN_ENABLE_BYPASS;
      break;
      case PERIPHERAL_IN:
        registerValue |= PIN_ENABLE_BYPASS;
        registerValue |= PIN_DM_DIG_HIZ;
      break;
      case PERIPHERAL_OUT:
        registerValue |= PIN_ENABLE_BYPASS;
        registerValue |= PIN_DM_STRONG;
      break;
      case PERIPHERAL_OD:
        registerValue |= PIN_ENABLE_BYPASS;
        registerValue |= PIN_DM_OD_LO;
        CyPins_SetPin(pin);
      break;
      case INPUT:
      default:
        registerValue &= PIN_DISABLE_BYPASS;
        registerValue |= PIN_DM_DIG_HIZ;
      break; 
  }
  *(reg8*)(pin) = registerValue;
}

/* [] END OF FILE */
