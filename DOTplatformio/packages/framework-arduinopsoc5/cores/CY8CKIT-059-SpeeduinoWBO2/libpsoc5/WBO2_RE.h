/*******************************************************************************
* File Name: WBO2_RE.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_WBO2_RE_H) /* Pins WBO2_RE_H */
#define CY_PINS_WBO2_RE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WBO2_RE_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WBO2_RE__PORT == 15 && ((WBO2_RE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WBO2_RE_Write(uint8 value);
void    WBO2_RE_SetDriveMode(uint8 mode);
uint8   WBO2_RE_ReadDataReg(void);
uint8   WBO2_RE_Read(void);
void    WBO2_RE_SetInterruptMode(uint16 position, uint16 mode);
uint8   WBO2_RE_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WBO2_RE_SetDriveMode() function.
     *  @{
     */
        #define WBO2_RE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WBO2_RE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WBO2_RE_DM_RES_UP          PIN_DM_RES_UP
        #define WBO2_RE_DM_RES_DWN         PIN_DM_RES_DWN
        #define WBO2_RE_DM_OD_LO           PIN_DM_OD_LO
        #define WBO2_RE_DM_OD_HI           PIN_DM_OD_HI
        #define WBO2_RE_DM_STRONG          PIN_DM_STRONG
        #define WBO2_RE_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WBO2_RE_MASK               WBO2_RE__MASK
#define WBO2_RE_SHIFT              WBO2_RE__SHIFT
#define WBO2_RE_WIDTH              1u

/* Interrupt constants */
#if defined(WBO2_RE__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WBO2_RE_SetInterruptMode() function.
     *  @{
     */
        #define WBO2_RE_INTR_NONE      (uint16)(0x0000u)
        #define WBO2_RE_INTR_RISING    (uint16)(0x0001u)
        #define WBO2_RE_INTR_FALLING   (uint16)(0x0002u)
        #define WBO2_RE_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WBO2_RE_INTR_MASK      (0x01u) 
#endif /* (WBO2_RE__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WBO2_RE_PS                     (* (reg8 *) WBO2_RE__PS)
/* Data Register */
#define WBO2_RE_DR                     (* (reg8 *) WBO2_RE__DR)
/* Port Number */
#define WBO2_RE_PRT_NUM                (* (reg8 *) WBO2_RE__PRT) 
/* Connect to Analog Globals */                                                  
#define WBO2_RE_AG                     (* (reg8 *) WBO2_RE__AG)                       
/* Analog MUX bux enable */
#define WBO2_RE_AMUX                   (* (reg8 *) WBO2_RE__AMUX) 
/* Bidirectional Enable */                                                        
#define WBO2_RE_BIE                    (* (reg8 *) WBO2_RE__BIE)
/* Bit-mask for Aliased Register Access */
#define WBO2_RE_BIT_MASK               (* (reg8 *) WBO2_RE__BIT_MASK)
/* Bypass Enable */
#define WBO2_RE_BYP                    (* (reg8 *) WBO2_RE__BYP)
/* Port wide control signals */                                                   
#define WBO2_RE_CTL                    (* (reg8 *) WBO2_RE__CTL)
/* Drive Modes */
#define WBO2_RE_DM0                    (* (reg8 *) WBO2_RE__DM0) 
#define WBO2_RE_DM1                    (* (reg8 *) WBO2_RE__DM1)
#define WBO2_RE_DM2                    (* (reg8 *) WBO2_RE__DM2) 
/* Input Buffer Disable Override */
#define WBO2_RE_INP_DIS                (* (reg8 *) WBO2_RE__INP_DIS)
/* LCD Common or Segment Drive */
#define WBO2_RE_LCD_COM_SEG            (* (reg8 *) WBO2_RE__LCD_COM_SEG)
/* Enable Segment LCD */
#define WBO2_RE_LCD_EN                 (* (reg8 *) WBO2_RE__LCD_EN)
/* Slew Rate Control */
#define WBO2_RE_SLW                    (* (reg8 *) WBO2_RE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WBO2_RE_PRTDSI__CAPS_SEL       (* (reg8 *) WBO2_RE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WBO2_RE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WBO2_RE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WBO2_RE_PRTDSI__OE_SEL0        (* (reg8 *) WBO2_RE__PRTDSI__OE_SEL0) 
#define WBO2_RE_PRTDSI__OE_SEL1        (* (reg8 *) WBO2_RE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WBO2_RE_PRTDSI__OUT_SEL0       (* (reg8 *) WBO2_RE__PRTDSI__OUT_SEL0) 
#define WBO2_RE_PRTDSI__OUT_SEL1       (* (reg8 *) WBO2_RE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WBO2_RE_PRTDSI__SYNC_OUT       (* (reg8 *) WBO2_RE__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WBO2_RE__SIO_CFG)
    #define WBO2_RE_SIO_HYST_EN        (* (reg8 *) WBO2_RE__SIO_HYST_EN)
    #define WBO2_RE_SIO_REG_HIFREQ     (* (reg8 *) WBO2_RE__SIO_REG_HIFREQ)
    #define WBO2_RE_SIO_CFG            (* (reg8 *) WBO2_RE__SIO_CFG)
    #define WBO2_RE_SIO_DIFF           (* (reg8 *) WBO2_RE__SIO_DIFF)
#endif /* (WBO2_RE__SIO_CFG) */

/* Interrupt Registers */
#if defined(WBO2_RE__INTSTAT)
    #define WBO2_RE_INTSTAT            (* (reg8 *) WBO2_RE__INTSTAT)
    #define WBO2_RE_SNAP               (* (reg8 *) WBO2_RE__SNAP)
    
	#define WBO2_RE_0_INTTYPE_REG 		(* (reg8 *) WBO2_RE__0__INTTYPE)
#endif /* (WBO2_RE__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WBO2_RE_H */


/* [] END OF FILE */
