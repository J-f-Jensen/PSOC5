/*******************************************************************************
* File Name: Pin_IAT.h  
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

#if !defined(CY_PINS_Pin_IAT_H) /* Pins Pin_IAT_H */
#define CY_PINS_Pin_IAT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_IAT_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_IAT__PORT == 15 && ((Pin_IAT__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pin_IAT_Write(uint8 value);
void    Pin_IAT_SetDriveMode(uint8 mode);
uint8   Pin_IAT_ReadDataReg(void);
uint8   Pin_IAT_Read(void);
void    Pin_IAT_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pin_IAT_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pin_IAT_SetDriveMode() function.
     *  @{
     */
        #define Pin_IAT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pin_IAT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pin_IAT_DM_RES_UP          PIN_DM_RES_UP
        #define Pin_IAT_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pin_IAT_DM_OD_LO           PIN_DM_OD_LO
        #define Pin_IAT_DM_OD_HI           PIN_DM_OD_HI
        #define Pin_IAT_DM_STRONG          PIN_DM_STRONG
        #define Pin_IAT_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pin_IAT_MASK               Pin_IAT__MASK
#define Pin_IAT_SHIFT              Pin_IAT__SHIFT
#define Pin_IAT_WIDTH              1u

/* Interrupt constants */
#if defined(Pin_IAT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pin_IAT_SetInterruptMode() function.
     *  @{
     */
        #define Pin_IAT_INTR_NONE      (uint16)(0x0000u)
        #define Pin_IAT_INTR_RISING    (uint16)(0x0001u)
        #define Pin_IAT_INTR_FALLING   (uint16)(0x0002u)
        #define Pin_IAT_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pin_IAT_INTR_MASK      (0x01u) 
#endif /* (Pin_IAT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_IAT_PS                     (* (reg8 *) Pin_IAT__PS)
/* Data Register */
#define Pin_IAT_DR                     (* (reg8 *) Pin_IAT__DR)
/* Port Number */
#define Pin_IAT_PRT_NUM                (* (reg8 *) Pin_IAT__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_IAT_AG                     (* (reg8 *) Pin_IAT__AG)                       
/* Analog MUX bux enable */
#define Pin_IAT_AMUX                   (* (reg8 *) Pin_IAT__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_IAT_BIE                    (* (reg8 *) Pin_IAT__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_IAT_BIT_MASK               (* (reg8 *) Pin_IAT__BIT_MASK)
/* Bypass Enable */
#define Pin_IAT_BYP                    (* (reg8 *) Pin_IAT__BYP)
/* Port wide control signals */                                                   
#define Pin_IAT_CTL                    (* (reg8 *) Pin_IAT__CTL)
/* Drive Modes */
#define Pin_IAT_DM0                    (* (reg8 *) Pin_IAT__DM0) 
#define Pin_IAT_DM1                    (* (reg8 *) Pin_IAT__DM1)
#define Pin_IAT_DM2                    (* (reg8 *) Pin_IAT__DM2) 
/* Input Buffer Disable Override */
#define Pin_IAT_INP_DIS                (* (reg8 *) Pin_IAT__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_IAT_LCD_COM_SEG            (* (reg8 *) Pin_IAT__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_IAT_LCD_EN                 (* (reg8 *) Pin_IAT__LCD_EN)
/* Slew Rate Control */
#define Pin_IAT_SLW                    (* (reg8 *) Pin_IAT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_IAT_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_IAT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_IAT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_IAT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_IAT_PRTDSI__OE_SEL0        (* (reg8 *) Pin_IAT__PRTDSI__OE_SEL0) 
#define Pin_IAT_PRTDSI__OE_SEL1        (* (reg8 *) Pin_IAT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_IAT_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_IAT__PRTDSI__OUT_SEL0) 
#define Pin_IAT_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_IAT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_IAT_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_IAT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pin_IAT__SIO_CFG)
    #define Pin_IAT_SIO_HYST_EN        (* (reg8 *) Pin_IAT__SIO_HYST_EN)
    #define Pin_IAT_SIO_REG_HIFREQ     (* (reg8 *) Pin_IAT__SIO_REG_HIFREQ)
    #define Pin_IAT_SIO_CFG            (* (reg8 *) Pin_IAT__SIO_CFG)
    #define Pin_IAT_SIO_DIFF           (* (reg8 *) Pin_IAT__SIO_DIFF)
#endif /* (Pin_IAT__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pin_IAT__INTSTAT)
    #define Pin_IAT_INTSTAT            (* (reg8 *) Pin_IAT__INTSTAT)
    #define Pin_IAT_SNAP               (* (reg8 *) Pin_IAT__SNAP)
    
	#define Pin_IAT_0_INTTYPE_REG 		(* (reg8 *) Pin_IAT__0__INTTYPE)
#endif /* (Pin_IAT__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin_IAT_H */


/* [] END OF FILE */
