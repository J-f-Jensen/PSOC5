/*******************************************************************************
* File Name: CAN_TX.h  
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

#if !defined(CY_PINS_CAN_TX_H) /* Pins CAN_TX_H */
#define CY_PINS_CAN_TX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CAN_TX_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CAN_TX__PORT == 15 && ((CAN_TX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CAN_TX_Write(uint8 value);
void    CAN_TX_SetDriveMode(uint8 mode);
uint8   CAN_TX_ReadDataReg(void);
uint8   CAN_TX_Read(void);
void    CAN_TX_SetInterruptMode(uint16 position, uint16 mode);
uint8   CAN_TX_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CAN_TX_SetDriveMode() function.
     *  @{
     */
        #define CAN_TX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CAN_TX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CAN_TX_DM_RES_UP          PIN_DM_RES_UP
        #define CAN_TX_DM_RES_DWN         PIN_DM_RES_DWN
        #define CAN_TX_DM_OD_LO           PIN_DM_OD_LO
        #define CAN_TX_DM_OD_HI           PIN_DM_OD_HI
        #define CAN_TX_DM_STRONG          PIN_DM_STRONG
        #define CAN_TX_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CAN_TX_MASK               CAN_TX__MASK
#define CAN_TX_SHIFT              CAN_TX__SHIFT
#define CAN_TX_WIDTH              1u

/* Interrupt constants */
#if defined(CAN_TX__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CAN_TX_SetInterruptMode() function.
     *  @{
     */
        #define CAN_TX_INTR_NONE      (uint16)(0x0000u)
        #define CAN_TX_INTR_RISING    (uint16)(0x0001u)
        #define CAN_TX_INTR_FALLING   (uint16)(0x0002u)
        #define CAN_TX_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CAN_TX_INTR_MASK      (0x01u) 
#endif /* (CAN_TX__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CAN_TX_PS                     (* (reg8 *) CAN_TX__PS)
/* Data Register */
#define CAN_TX_DR                     (* (reg8 *) CAN_TX__DR)
/* Port Number */
#define CAN_TX_PRT_NUM                (* (reg8 *) CAN_TX__PRT) 
/* Connect to Analog Globals */                                                  
#define CAN_TX_AG                     (* (reg8 *) CAN_TX__AG)                       
/* Analog MUX bux enable */
#define CAN_TX_AMUX                   (* (reg8 *) CAN_TX__AMUX) 
/* Bidirectional Enable */                                                        
#define CAN_TX_BIE                    (* (reg8 *) CAN_TX__BIE)
/* Bit-mask for Aliased Register Access */
#define CAN_TX_BIT_MASK               (* (reg8 *) CAN_TX__BIT_MASK)
/* Bypass Enable */
#define CAN_TX_BYP                    (* (reg8 *) CAN_TX__BYP)
/* Port wide control signals */                                                   
#define CAN_TX_CTL                    (* (reg8 *) CAN_TX__CTL)
/* Drive Modes */
#define CAN_TX_DM0                    (* (reg8 *) CAN_TX__DM0) 
#define CAN_TX_DM1                    (* (reg8 *) CAN_TX__DM1)
#define CAN_TX_DM2                    (* (reg8 *) CAN_TX__DM2) 
/* Input Buffer Disable Override */
#define CAN_TX_INP_DIS                (* (reg8 *) CAN_TX__INP_DIS)
/* LCD Common or Segment Drive */
#define CAN_TX_LCD_COM_SEG            (* (reg8 *) CAN_TX__LCD_COM_SEG)
/* Enable Segment LCD */
#define CAN_TX_LCD_EN                 (* (reg8 *) CAN_TX__LCD_EN)
/* Slew Rate Control */
#define CAN_TX_SLW                    (* (reg8 *) CAN_TX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CAN_TX_PRTDSI__CAPS_SEL       (* (reg8 *) CAN_TX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CAN_TX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CAN_TX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CAN_TX_PRTDSI__OE_SEL0        (* (reg8 *) CAN_TX__PRTDSI__OE_SEL0) 
#define CAN_TX_PRTDSI__OE_SEL1        (* (reg8 *) CAN_TX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CAN_TX_PRTDSI__OUT_SEL0       (* (reg8 *) CAN_TX__PRTDSI__OUT_SEL0) 
#define CAN_TX_PRTDSI__OUT_SEL1       (* (reg8 *) CAN_TX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CAN_TX_PRTDSI__SYNC_OUT       (* (reg8 *) CAN_TX__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CAN_TX__SIO_CFG)
    #define CAN_TX_SIO_HYST_EN        (* (reg8 *) CAN_TX__SIO_HYST_EN)
    #define CAN_TX_SIO_REG_HIFREQ     (* (reg8 *) CAN_TX__SIO_REG_HIFREQ)
    #define CAN_TX_SIO_CFG            (* (reg8 *) CAN_TX__SIO_CFG)
    #define CAN_TX_SIO_DIFF           (* (reg8 *) CAN_TX__SIO_DIFF)
#endif /* (CAN_TX__SIO_CFG) */

/* Interrupt Registers */
#if defined(CAN_TX__INTSTAT)
    #define CAN_TX_INTSTAT            (* (reg8 *) CAN_TX__INTSTAT)
    #define CAN_TX_SNAP               (* (reg8 *) CAN_TX__SNAP)
    
	#define CAN_TX_0_INTTYPE_REG 		(* (reg8 *) CAN_TX__0__INTTYPE)
#endif /* (CAN_TX__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CAN_TX_H */


/* [] END OF FILE */
