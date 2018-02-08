/*******************************************************
 * This file includes timers and counters needed for Speeduino
 * but can be used for other Arduino PSOC5 projects if you find 
 * it use full
 *
 ******************************************************/

#include "Arduino_TimerCounters.h"


// START - One shot timer code 
void (*CTDOSFunction)(void);

CY_ISR_PROTO(CTDOS_INT_ISR);

void CrankTriggerDummyOneShotTimer_attachinterupt( void (*isr)() )
{
    // Start timer
    CrankTriggerDummyTimer_Start(); 
    
    // Wait for the TC interrupt to be executed
    CyDelayUs(200);
    
    // Set the isr user functio
    CTDOSFunction = isr;
    
    // Clear the status register before attaching the function
    CrankTriggerDummyTimer_ReadStatusRegister();
    
    // Attach ISR function
    CrankTriggerDummyTimer_isr_StartEx(CTDOS_INT_ISR);
}

void CrankTriggerDummyOneShotTimer_reload( uint16_t timerPeriode )
{
    // Write the new periode to the timer
    CrankTriggerDummyTimer_WritePeriod( timerPeriode );
    
    //Start the one shot periode by sending a reset to the timer
    CrankTriggerDummyTimerReg_Write( 1 );
}
  
CY_ISR(CTDOS_INT_ISR)
{
    // Clear the status register
    CrankTriggerDummyTimer_ReadStatusRegister();
  
    // Execute the user attached function
    CTDOSFunction();
}
// END - one shot timer code


/* [] END OF FILE */





