extern "C" {
#include <project.h>
}

#include "Arduino.h"
#include "Arduino_HW_Interrupt.h"
#include <cydevice_trm.h>

void (*INT0Function)(void);
void (*INT3Function)(void);

CY_ISR_PROTO(HW_INT_ISR);

void attachInterrupt(int interrupt, void (*isr)(), enum HW_INT_MODE mode)
{
  // Clear any pending interupts
  P2_ClearInterrupt();
  
  if (interrupt == 0) // Port 2.0 is used for interupt 0 
  {
    P2_SetInterruptMode(P2_0_INTR, mode);
    INT0Function = isr;
  }
  else if (interrupt == 3) // Port 2.3 is used for interupt 3 
  {
    P2_SetInterruptMode(P2_3_INTR, mode);
    INT3Function = isr;
  }    
  HW_INT_StartEx(HW_INT_ISR);
}

void detachInterrupt(int interrupt)
{
  if (interrupt == 0)
  {
    P2_SetInterruptMode(P2_0_INTR, DISABLE);
  }
  else if (interrupt == 3)
  {
     P2_SetInterruptMode(P2_3_INTR, DISABLE);
  }
}

CY_ISR(HW_INT_ISR)
{
  uint8_t intStat = P2_ClearInterrupt();
  if ((intStat & P2_0_INTR) != 0)
  {
    INT0Function();
  }
  if ((intStat & P2_3_INTR) != 0)
  {
    INT3Function();
  }
}

