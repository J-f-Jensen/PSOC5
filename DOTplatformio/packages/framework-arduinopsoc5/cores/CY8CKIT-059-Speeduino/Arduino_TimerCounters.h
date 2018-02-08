/*******************************************************
 * This file includes timers and counters needed for Speeduino
 * but can be used for other Arduino PSOC5 projects if you find 
 * it use full
 *
 ******************************************************/
    
#ifndef _Arduino_TimerCounters_h_
#define _Arduino_TimerCounters_h_
    
extern "C" {
#include <project.h>
}
#include "Arduino.h"

// Use the following for the defined 1ms counter
#define Counter_1ms_initialize() Counter_1ms_Start()
#define Counter_1ms_attachinterupt(P) Counter_1ms_isr_StartEx(P)

void CrankTriggerDummyOneShotTimer_attachinterupt( void (*isr)() );

void CrankTriggerDummyOneShotTimer_reload( uint16_t timerPeriode );



#endif

/* [] END OF FILE */
