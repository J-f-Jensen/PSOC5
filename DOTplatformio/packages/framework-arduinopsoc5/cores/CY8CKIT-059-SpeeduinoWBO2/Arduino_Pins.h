#ifndef _arduino_pins_h
#define _arduino_pins_h
  
#include <stdint.h>
#include <Project.h>

#define NUM_BASE_PINS 20

#define D0 P2_0         // Interupt 0
#define D1 P2_UserLed   //LED
#define D2 P2_UserButton //Pushbutton
#define D3 P2_3         // Interupt 1
#define D4 P2_4         // pinTachOut
#define D5 P2_5         // pinStepperDir
#define D6 P2_6         // pinStepperStep
#define D7 P2_7         // pinStepperEnable
#define D8 P1_FuelPump    // pinFuelPump
#define D9 P1_Fan         // pinFan
#define D10 P1_Ignition_1        // Ignition 1
#define D11 P1_Ignition_2        // Ignition 2
#define D12 P1_Injector_1        // Injector 1
#define D13 P1_Injector_2        // Injector 2
#define D14 Pin_O2_0    // Analog //O2
#define D15 Pin_CLT_0   // Analog //CLT
#define D16 Pin_IAT_0   // Analog //IAT
#define D17 Pin_BAT_0   // Analog //BAT
#define D18 Pin_MAP_0   // Analog //MAP
#define D19 Pin_TPS_0   // Analog //TPS
#define A0 D14  
#define A1 D15
#define A2 D16 
#define A3 D17 
#define A4 D18 
#define A5 D19

  
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
