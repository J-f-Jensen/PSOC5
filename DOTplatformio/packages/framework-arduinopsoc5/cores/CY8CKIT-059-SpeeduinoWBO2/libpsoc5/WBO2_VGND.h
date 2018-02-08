/*******************************************************************************
* File Name: WBO2_VGND.h  
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

#if !defined(CY_PINS_WBO2_VGND_H) /* Pins WBO2_VGND_H */
#define CY_PINS_WBO2_VGND_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WBO2_VGND_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WBO2_VGND__PORT == 15 && ((WBO2_VGND__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WBO2_VGND_Write(uint8 value);
void    WBO2_VGND_SetDriveMode(uint8 mode);
uint8   WBO2_VGND_ReadDataReg(void);
uint8   WBO2_VGND_Read(void);
void    WBO2_VGND_SetInterruptMode(uint16 position, uint16 mode);
uint8   WBO2_VGND_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WBO2_VGND_SetDriveMode() function.
     *  @{
     */
        #define WBO2_VGND_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WBO2_VGND_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WBO2_VGND_DM_RES_UP          PIN_DM_RES_UP
        #define WBO2_VGND_DM_RES_DWN         PIN_DM_RES_DWN
        #define WBO2_VGND_DM_OD_LO           PIN_DM_OD_LO
        #define WBO2_VGND_DM_OD_HI           PIN_DM_OD_HI
        #define WBO2_VGND_DM_STRONG          PIN_DM_STRONG
        #define WBO2_VGND_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WBO2_VGND_MASK               WBO2_VGND__MASK
#define WBO2_VGND_SHIFT              WBO2_VGND__SHIFT
#define WBO2_VGND_WIDTH              1u

/* Interrupt constants */
#if defined(WBO2_VGND__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WBO2_VGND_SetInterruptMode() function.
     *  @{
     */
        #define WBO2_VGND_INTR_NONE      (uint16)(0x0000u)
        #define WBO2_VGND_INTR_RISING    (uint16)(0x0001u)
        #define WBO2_VGND_INTR_FALLING   (uint16)(0x0002u)
        #define WBO2_VGND_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WBO2_VGND_INTR_MASK      (0x01u) 
#endif /* (WBO2_VGND__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WBO2_VGND_PS                     (* (reg8 *) WBO2_VGND__PS)
/* Data Register */
#define WBO2_VGND_DR                     (* (reg8 *) WBO2_VGND__DR)
/* Port Number */
#define WBO2_VGND_PRT_NUM                (* (reg8 *) WBO2_VGND__PRT) 
/* Connect to Analog Globals */                                                  
#define WBO2_VGND_AG                     (* (reg8 *) WBO2_VGND__AG)                       
/* Analog MUX bux enable */
#define WBO2_VGND_AMUX                   (* (reg8 *) WBO2_VGND__AMUX) 
/* Bidirectional Enable */                                                        
#define WBO2_VGND_BIE                    (* (reg8 *) WBO2_VGND__BIE)
/* Bit-mask for Aliased Register Access */
#define WBO2_VGND_BIT_MASK               (* (reg8 *) WBO2_VGND__BIT_MASK)
/* Bypass Enable */
#define WBO2_VGND_BYP                    (* (reg8 *) WBO2_VGND__BYP)
/* Port wide control signals */                                                   
#define WBO2_VGND_CTL                    (* (reg8 *) WBO2_VGND__CTL)
/* Drive Modes */
#define WBO2_VGND_DM0                    (* (reg8 *) WBO2_VGND__DM0) 
#define WBO2_VGND_DM1                    (* (reg8 *) WBO2_VGND__DM1)
#define WBO2_VGND_DM2                    (* (reg8 *) WBO2_VGND__DM2) 
/* Input Buffer Disable Override */
#define WBO2_VGND_INP_DIS                (* (reg8 *) WBO2_VGND__INP_DIS)
/* LCD Common or Segment Drive */
#define WBO2_VGND_LCD_COM_SEG            (* (reg8 *) WBO2_VGND__LCD_COM_SEG)
/* Enable Segment LCD */
#define WBO2_VGND_LCD_EN                 (* (reg8 *) WBO2_VGND__LCD_EN)
/* Slew Rate Control */
#define WBO2_VGND_SLW                    (* (reg8 *) WBO2_VGND__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WBO2_VGND_PRTDSI__CAPS_SEL       (* (reg8 *) WBO2_VGND__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WBO2_VGND_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WBO2_VGND__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WBO2_VGND_PRTDSI__OE_SEL0        (* (reg8 *) WBO2_VGND__PRTDSI__OE_SEL0) 
#define WBO2_VGND_PRTDSI__OE_SEL1        (* (reg8 *) WBO2_VGND__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WBO2_VGND_PRTDSI__OUT_SEL0       (* (reg8 *) WBO2_VGND__PRTDSI__OUT_SEL0) 
#define WBO2_VGND_PRTDSI__OUT_SEL1       (* (reg8 *) WBO2_VGND__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WBO2_VGND_PRTDSI__SYNC_OUT       (* (reg8 *) WBO2_VGND__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WBO2_VGND__SIO_CFG)
    #define WBO2_VGND_SIO_HYST_EN        (* (reg8 *) WBO2_VGND__SIO_HYST_EN)
    #define WBO2_VGND_SIO_REG_HIFREQ     (* (reg8 *) WBO2_VGND__SIO_REG_HIFREQ)
    #define WBO2_VGND_SIO_CFG            (* (reg8 *) WBO2_VGND__SIO_CFG)
    #define WBO2_VGND_SIO_DIFF           (* (reg8 *) WBO2_VGND__SIO_DIFF)
#endif /* (WBO2_VGND__SIO_CFG) */

/* Interrupt Registers */
#if defined(WBO2_VGND__INTSTAT)
    #define WBO2_VGND_INTSTAT            (* (reg8 *) WBO2_VGND__INTSTAT)
    #define WBO2_VGND_SNAP               (* (reg8 *) WBO2_VGND__SNAP)
    
	#define WBO2_VGND_0_INTTYPE_REG 		(* (reg8 *) WBO2_VGND__0__INTTYPE)
#endif /* (WBO2_VGND__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WBO2_VGND_H */


/* [] END OF FILE */
