/*******************************************************************************
* File Name: P2.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_P2_ALIASES_H) /* Pins P2_ALIASES_H */
#define CY_PINS_P2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define P2_0			(P2__0__PC)
#define P2_0_INTR	((uint16)((uint16)0x0001u << P2__0__SHIFT))

#define P2_1			(P2__1__PC)
#define P2_1_INTR	((uint16)((uint16)0x0001u << P2__1__SHIFT))

#define P2_2			(P2__2__PC)
#define P2_2_INTR	((uint16)((uint16)0x0001u << P2__2__SHIFT))

#define P2_3			(P2__3__PC)
#define P2_3_INTR	((uint16)((uint16)0x0001u << P2__3__SHIFT))

#define P2_4			(P2__4__PC)
#define P2_4_INTR	((uint16)((uint16)0x0001u << P2__4__SHIFT))

#define P2_5			(P2__5__PC)
#define P2_5_INTR	((uint16)((uint16)0x0001u << P2__5__SHIFT))

#define P2_6			(P2__6__PC)
#define P2_6_INTR	((uint16)((uint16)0x0001u << P2__6__SHIFT))

#define P2_7			(P2__7__PC)
#define P2_7_INTR	((uint16)((uint16)0x0001u << P2__7__SHIFT))

#define P2_INTR_ALL	 ((uint16)(P2_0_INTR| P2_1_INTR| P2_2_INTR| P2_3_INTR| P2_4_INTR| P2_5_INTR| P2_6_INTR| P2_7_INTR))
#define P2_UserLed			(P2__UserLed__PC)
#define P2_UserLed_INTR	((uint16)((uint16)0x0001u << P2__1__SHIFT))

#define P2_UserButton			(P2__UserButton__PC)
#define P2_UserButton_INTR	((uint16)((uint16)0x0001u << P2__2__SHIFT))

#endif /* End Pins P2_ALIASES_H */


/* [] END OF FILE */
