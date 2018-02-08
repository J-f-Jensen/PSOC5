/*******************************************************************************
* File Name: CrankTrigger_Dummy_Timer_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_CrankTrigger_Dummy_Timer_isr_H)
#define CY_ISR_CrankTrigger_Dummy_Timer_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CrankTrigger_Dummy_Timer_isr_Start(void);
void CrankTrigger_Dummy_Timer_isr_StartEx(cyisraddress address);
void CrankTrigger_Dummy_Timer_isr_Stop(void);

CY_ISR_PROTO(CrankTrigger_Dummy_Timer_isr_Interrupt);

void CrankTrigger_Dummy_Timer_isr_SetVector(cyisraddress address);
cyisraddress CrankTrigger_Dummy_Timer_isr_GetVector(void);

void CrankTrigger_Dummy_Timer_isr_SetPriority(uint8 priority);
uint8 CrankTrigger_Dummy_Timer_isr_GetPriority(void);

void CrankTrigger_Dummy_Timer_isr_Enable(void);
uint8 CrankTrigger_Dummy_Timer_isr_GetState(void);
void CrankTrigger_Dummy_Timer_isr_Disable(void);

void CrankTrigger_Dummy_Timer_isr_SetPending(void);
void CrankTrigger_Dummy_Timer_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CrankTrigger_Dummy_Timer_isr ISR. */
#define CrankTrigger_Dummy_Timer_isr_INTC_VECTOR            ((reg32 *) CrankTrigger_Dummy_Timer_isr__INTC_VECT)

/* Address of the CrankTrigger_Dummy_Timer_isr ISR priority. */
#define CrankTrigger_Dummy_Timer_isr_INTC_PRIOR             ((reg8 *) CrankTrigger_Dummy_Timer_isr__INTC_PRIOR_REG)

/* Priority of the CrankTrigger_Dummy_Timer_isr interrupt. */
#define CrankTrigger_Dummy_Timer_isr_INTC_PRIOR_NUMBER      CrankTrigger_Dummy_Timer_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CrankTrigger_Dummy_Timer_isr interrupt. */
#define CrankTrigger_Dummy_Timer_isr_INTC_SET_EN            ((reg32 *) CrankTrigger_Dummy_Timer_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CrankTrigger_Dummy_Timer_isr interrupt. */
#define CrankTrigger_Dummy_Timer_isr_INTC_CLR_EN            ((reg32 *) CrankTrigger_Dummy_Timer_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CrankTrigger_Dummy_Timer_isr interrupt state to pending. */
#define CrankTrigger_Dummy_Timer_isr_INTC_SET_PD            ((reg32 *) CrankTrigger_Dummy_Timer_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CrankTrigger_Dummy_Timer_isr interrupt. */
#define CrankTrigger_Dummy_Timer_isr_INTC_CLR_PD            ((reg32 *) CrankTrigger_Dummy_Timer_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_CrankTrigger_Dummy_Timer_isr_H */


/* [] END OF FILE */
