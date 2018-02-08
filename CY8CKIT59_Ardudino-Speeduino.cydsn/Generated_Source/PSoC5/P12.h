/*******************************************************************************
* File Name: P12.h  
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

#if !defined(CY_PINS_P12_H) /* Pins P12_H */
#define CY_PINS_P12_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P12_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P12__PORT == 15 && ((P12__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P12_Write(uint8 value);
void    P12_SetDriveMode(uint8 mode);
uint8   P12_ReadDataReg(void);
uint8   P12_Read(void);
void    P12_SetInterruptMode(uint16 position, uint16 mode);
uint8   P12_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P12_SetDriveMode() function.
     *  @{
     */
        #define P12_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P12_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P12_DM_RES_UP          PIN_DM_RES_UP
        #define P12_DM_RES_DWN         PIN_DM_RES_DWN
        #define P12_DM_OD_LO           PIN_DM_OD_LO
        #define P12_DM_OD_HI           PIN_DM_OD_HI
        #define P12_DM_STRONG          PIN_DM_STRONG
        #define P12_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P12_MASK               P12__MASK
#define P12_SHIFT              P12__SHIFT
#define P12_WIDTH              6u

/* Interrupt constants */
#if defined(P12__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P12_SetInterruptMode() function.
     *  @{
     */
        #define P12_INTR_NONE      (uint16)(0x0000u)
        #define P12_INTR_RISING    (uint16)(0x0001u)
        #define P12_INTR_FALLING   (uint16)(0x0002u)
        #define P12_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P12_INTR_MASK      (0x01u) 
#endif /* (P12__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P12_PS                     (* (reg8 *) P12__PS)
/* Data Register */
#define P12_DR                     (* (reg8 *) P12__DR)
/* Port Number */
#define P12_PRT_NUM                (* (reg8 *) P12__PRT) 
/* Connect to Analog Globals */                                                  
#define P12_AG                     (* (reg8 *) P12__AG)                       
/* Analog MUX bux enable */
#define P12_AMUX                   (* (reg8 *) P12__AMUX) 
/* Bidirectional Enable */                                                        
#define P12_BIE                    (* (reg8 *) P12__BIE)
/* Bit-mask for Aliased Register Access */
#define P12_BIT_MASK               (* (reg8 *) P12__BIT_MASK)
/* Bypass Enable */
#define P12_BYP                    (* (reg8 *) P12__BYP)
/* Port wide control signals */                                                   
#define P12_CTL                    (* (reg8 *) P12__CTL)
/* Drive Modes */
#define P12_DM0                    (* (reg8 *) P12__DM0) 
#define P12_DM1                    (* (reg8 *) P12__DM1)
#define P12_DM2                    (* (reg8 *) P12__DM2) 
/* Input Buffer Disable Override */
#define P12_INP_DIS                (* (reg8 *) P12__INP_DIS)
/* LCD Common or Segment Drive */
#define P12_LCD_COM_SEG            (* (reg8 *) P12__LCD_COM_SEG)
/* Enable Segment LCD */
#define P12_LCD_EN                 (* (reg8 *) P12__LCD_EN)
/* Slew Rate Control */
#define P12_SLW                    (* (reg8 *) P12__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P12_PRTDSI__CAPS_SEL       (* (reg8 *) P12__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P12_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P12__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P12_PRTDSI__OE_SEL0        (* (reg8 *) P12__PRTDSI__OE_SEL0) 
#define P12_PRTDSI__OE_SEL1        (* (reg8 *) P12__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P12_PRTDSI__OUT_SEL0       (* (reg8 *) P12__PRTDSI__OUT_SEL0) 
#define P12_PRTDSI__OUT_SEL1       (* (reg8 *) P12__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P12_PRTDSI__SYNC_OUT       (* (reg8 *) P12__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P12__SIO_CFG)
    #define P12_SIO_HYST_EN        (* (reg8 *) P12__SIO_HYST_EN)
    #define P12_SIO_REG_HIFREQ     (* (reg8 *) P12__SIO_REG_HIFREQ)
    #define P12_SIO_CFG            (* (reg8 *) P12__SIO_CFG)
    #define P12_SIO_DIFF           (* (reg8 *) P12__SIO_DIFF)
#endif /* (P12__SIO_CFG) */

/* Interrupt Registers */
#if defined(P12__INTSTAT)
    #define P12_INTSTAT            (* (reg8 *) P12__INTSTAT)
    #define P12_SNAP               (* (reg8 *) P12__SNAP)
    
	#define P12_0_INTTYPE_REG 		(* (reg8 *) P12__0__INTTYPE)
	#define P12_1_INTTYPE_REG 		(* (reg8 *) P12__1__INTTYPE)
	#define P12_2_INTTYPE_REG 		(* (reg8 *) P12__2__INTTYPE)
	#define P12_3_INTTYPE_REG 		(* (reg8 *) P12__3__INTTYPE)
	#define P12_4_INTTYPE_REG 		(* (reg8 *) P12__4__INTTYPE)
	#define P12_5_INTTYPE_REG 		(* (reg8 *) P12__5__INTTYPE)
#endif /* (P12__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P12_H */


/* [] END OF FILE */
