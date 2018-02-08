#ifndef _arduino_pins_h
#define _arduino_pins_h
  
#include <stdint.h>
#include <Project.h>

#define NUM_BASE_PINS 38

#define D0 P2_0       // Interupt
#define D1 P2_UserLed //LED
#define D2 P2_UserButton //Pushbutton
#define D3 P2_3     // PWM3
#define D4 P2_4 
#define D5 P2_5     // PWM5
#define D6 P2_6     // PWM6
#define D7 P2_7 
#define D8 DB_0 
#define D9 DB_1     // PWM9
#define D10 DB_2    // PWM10, SS
#define D11 DB_3    // PWM11, MOSI
#define D12 DB_4    // MISO
#define D13 DB_5    // SCLK
#define D14 P0_0    // Analog
#define D15 P0_1    // Analog
#define D16 P0_2    // Analog
#define D17 P0_3    // Analog
#define D18 P0_4    // Analog
#define D19 P0_5    // Analog
#define D20 P0_6    // Analog
#define D21 P0_7    // Analog
#define D22 P12_0   // SCL
#define D23 P12_1   // SDA
#define D24 P12_2
#define D25 P12_3  
#define D26 P12_4
#define D27 P12_5
#define D28 P12_6   // RX
#define D29 P12_7   // TX
#define D30 P3_0
#define D31 P3_1
#define D32 P3_2
#define D33 P3_3
#define D34 P3_4
#define D35 P3_5
#define D36 P3_6
#define D37 P3_7
#define A0 D14 
#define A1 D15 
#define A2 D16 
#define A3 D17 
#define A4 D18 
#define A5 D19
#define A6 D20
#define A7 D21
  
#define P2_D2 UserButton_0


#define HIGH 1u
#define LOW 0u
    
/* PinDescription structure */
//typedef struct _PinDescription
//{
//  uint32_t pPort ;
//  uint32_t ulPin ;
//  uint32_t ulPeripheralId ;
//  EPioType ulPinType ;
//  uint32_t ulPinConfiguration ;
//  uint32_t ulPinAttribute ;
//  EAnalogChannel ulAnalogChannel ; /* Analog pin in the Arduino context (label on the board) */
//  EAnalogChannel ulADCChannelNumber ; /* ADC Channel number in the SAM device */
//  EPWMChannel ulPWMChannel ;
//  ETCChannel ulTCChannel ;
//} PinDescription ;

/* Pins table to be instanciated into Arduino_Pins.cpp */
//extern const PinDescription g_APinDescription[] ;


enum PIN_MODE {OUTPUT, INPUT, INPUT_PULLUP, PERIPHERAL, PERIPHERAL_OUT,
               PERIPHERAL_IN, PERIPHERAL_OD};

enum BYPASS_MODE {PIN_ENABLE_BYPASS = 0x80, PIN_DISABLE_BYPASS = 0x7f};

extern uint32_t pinNameToPointers[NUM_BASE_PINS];

// Needs to be corrected
//#define digitalPinToPort(P)        ( g_APinDescription[P].pPort )
//#define digitalPinToBitMask(P)     ( g_APinDescription[P].ulPin )
//#define portOutputRegister(port)   ( &(port->PIO_ODSR) )
//#define portInputRegister(port)    ( &(port->PIO_PDSR) )

//Dummy to please Speeduino :-)
#define digitalPinToPort(P)        (P)
#define digitalPinToBitMask(P)     (P)
#define portOutputRegister(port)   (port)
#define portInputRegister(port)    (port)


void pinMode(uint32_t pin, enum PIN_MODE mode);

void digitalWrite(uint32_t pin, uint8_t level);

uint8_t digitalRead(uint32_t pin);
  
#endif

/* [] END OF FILE */
