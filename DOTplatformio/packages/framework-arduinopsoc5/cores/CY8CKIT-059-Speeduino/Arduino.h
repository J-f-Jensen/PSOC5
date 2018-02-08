#ifndef __arduino_h_
#define __arduino_h_
  

extern "C" {
#include <project.h>
}

#include "Arduino_HW_Interrupt.h"
#include "Arduino_Advanced_IO.h"
#include "Arduino_Analog_In.h"
//#include "Arduino_Analog_Out.h" // PWM has been removed
#include "Arduino_Pins.h"
#include "Arduino_Time.h"
#include "Arduino_TimerCounters.h"
#include "Wstring.h"
//#include "Arduino_Serial.h"
//#include "UARTClass.h"
#include "USBUARTClass.h"
#include "Stream.h"
#include "avr/pgmspace.h"
#include <math.h>
#include <pins_arduino.h>
#include "WMath.h"

void setup();
void loop();
long map(long, long, long, long, long);
long constrain(long, long, long);
long min(long, long);
long max(long, long);

#define NOT_AN_INTERRUPT -1

#define interrupts() (CyGlobalIntEnable)
#define noInterrupts() (CyGlobalIntDisable)

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

//extern UARTClass Serial1;

#define CORE_PSOC5
#define CY8CKIT059
#define boolean bool
#define byte uint8_t
#define PI 3.1415
#define _BV(bit) (1 << (bit))
#define F_CPU 72000000L
#define Bootloader_SCHEDULE_BTLDR   (0x40u)
#define Bootloader_SCHEDULE_BTLDB   (0x80u)
#define Bootloader_RESET_SR0_REG    (* (reg8 *) CYREG_RESET_SR0)
#define Bootloader_SET_RUN_TYPE(x)  (Bootloader_RESET_SR0_REG = (x))

#endif
/* [] END OF FILE */

