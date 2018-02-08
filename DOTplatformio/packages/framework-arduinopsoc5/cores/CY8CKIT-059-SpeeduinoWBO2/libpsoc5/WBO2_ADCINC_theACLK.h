/*******************************************************************************
* File Name: WBO2_ADCINC_theACLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_WBO2_ADCINC_theACLK_H)
#define CY_CLOCK_WBO2_ADCINC_theACLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void WBO2_ADCINC_theACLK_Start(void) ;
void WBO2_ADCINC_theACLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void WBO2_ADCINC_theACLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void WBO2_ADCINC_theACLK_StandbyPower(uint8 state) ;
void WBO2_ADCINC_theACLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 WBO2_ADCINC_theACLK_GetDividerRegister(void) ;
void WBO2_ADCINC_theACLK_SetModeRegister(uint8 modeBitMask) ;
void WBO2_ADCINC_theACLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 WBO2_ADCINC_theACLK_GetModeRegister(void) ;
void WBO2_ADCINC_theACLK_SetSourceRegister(uint8 clkSource) ;
uint8 WBO2_ADCINC_theACLK_GetSourceRegister(void) ;
#if defined(WBO2_ADCINC_theACLK__CFG3)
void WBO2_ADCINC_theACLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 WBO2_ADCINC_theACLK_GetPhaseRegister(void) ;
#endif /* defined(WBO2_ADCINC_theACLK__CFG3) */

#define WBO2_ADCINC_theACLK_Enable()                       WBO2_ADCINC_theACLK_Start()
#define WBO2_ADCINC_theACLK_Disable()                      WBO2_ADCINC_theACLK_Stop()
#define WBO2_ADCINC_theACLK_SetDivider(clkDivider)         WBO2_ADCINC_theACLK_SetDividerRegister(clkDivider, 1u)
#define WBO2_ADCINC_theACLK_SetDividerValue(clkDivider)    WBO2_ADCINC_theACLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define WBO2_ADCINC_theACLK_SetMode(clkMode)               WBO2_ADCINC_theACLK_SetModeRegister(clkMode)
#define WBO2_ADCINC_theACLK_SetSource(clkSource)           WBO2_ADCINC_theACLK_SetSourceRegister(clkSource)
#if defined(WBO2_ADCINC_theACLK__CFG3)
#define WBO2_ADCINC_theACLK_SetPhase(clkPhase)             WBO2_ADCINC_theACLK_SetPhaseRegister(clkPhase)
#define WBO2_ADCINC_theACLK_SetPhaseValue(clkPhase)        WBO2_ADCINC_theACLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(WBO2_ADCINC_theACLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define WBO2_ADCINC_theACLK_CLKEN              (* (reg8 *) WBO2_ADCINC_theACLK__PM_ACT_CFG)
#define WBO2_ADCINC_theACLK_CLKEN_PTR          ((reg8 *) WBO2_ADCINC_theACLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define WBO2_ADCINC_theACLK_CLKSTBY            (* (reg8 *) WBO2_ADCINC_theACLK__PM_STBY_CFG)
#define WBO2_ADCINC_theACLK_CLKSTBY_PTR        ((reg8 *) WBO2_ADCINC_theACLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define WBO2_ADCINC_theACLK_DIV_LSB            (* (reg8 *) WBO2_ADCINC_theACLK__CFG0)
#define WBO2_ADCINC_theACLK_DIV_LSB_PTR        ((reg8 *) WBO2_ADCINC_theACLK__CFG0)
#define WBO2_ADCINC_theACLK_DIV_PTR            ((reg16 *) WBO2_ADCINC_theACLK__CFG0)

/* Clock MSB divider configuration register. */
#define WBO2_ADCINC_theACLK_DIV_MSB            (* (reg8 *) WBO2_ADCINC_theACLK__CFG1)
#define WBO2_ADCINC_theACLK_DIV_MSB_PTR        ((reg8 *) WBO2_ADCINC_theACLK__CFG1)

/* Mode and source configuration register */
#define WBO2_ADCINC_theACLK_MOD_SRC            (* (reg8 *) WBO2_ADCINC_theACLK__CFG2)
#define WBO2_ADCINC_theACLK_MOD_SRC_PTR        ((reg8 *) WBO2_ADCINC_theACLK__CFG2)

#if defined(WBO2_ADCINC_theACLK__CFG3)
/* Analog clock phase configuration register */
#define WBO2_ADCINC_theACLK_PHASE              (* (reg8 *) WBO2_ADCINC_theACLK__CFG3)
#define WBO2_ADCINC_theACLK_PHASE_PTR          ((reg8 *) WBO2_ADCINC_theACLK__CFG3)
#endif /* defined(WBO2_ADCINC_theACLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define WBO2_ADCINC_theACLK_CLKEN_MASK         WBO2_ADCINC_theACLK__PM_ACT_MSK
#define WBO2_ADCINC_theACLK_CLKSTBY_MASK       WBO2_ADCINC_theACLK__PM_STBY_MSK

/* CFG2 field masks */
#define WBO2_ADCINC_theACLK_SRC_SEL_MSK        WBO2_ADCINC_theACLK__CFG2_SRC_SEL_MASK
#define WBO2_ADCINC_theACLK_MODE_MASK          (~(WBO2_ADCINC_theACLK_SRC_SEL_MSK))

#if defined(WBO2_ADCINC_theACLK__CFG3)
/* CFG3 phase mask */
#define WBO2_ADCINC_theACLK_PHASE_MASK         WBO2_ADCINC_theACLK__CFG3_PHASE_DLY_MASK
#endif /* defined(WBO2_ADCINC_theACLK__CFG3) */

#endif /* CY_CLOCK_WBO2_ADCINC_theACLK_H */


/* [] END OF FILE */
