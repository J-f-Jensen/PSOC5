/*******************************************************************************
* File Name: P0.h  
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

#if !defined(CY_PINS_P0_ALIASES_H) /* Pins P0_ALIASES_H */
#define CY_PINS_P0_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define P0_0			(P0__0__PC)
#define P0_0_INTR	((uint16)((uint16)0x0001u << P0__0__SHIFT))

#define P0_1			(P0__1__PC)
#define P0_1_INTR	((uint16)((uint16)0x0001u << P0__1__SHIFT))

#define P0_2			(P0__2__PC)
#define P0_2_INTR	((uint16)((uint16)0x0001u << P0__2__SHIFT))

#define P0_3			(P0__3__PC)
#define P0_3_INTR	((uint16)((uint16)0x0001u << P0__3__SHIFT))

#define P0_4			(P0__4__PC)
#define P0_4_INTR	((uint16)((uint16)0x0001u << P0__4__SHIFT))

#define P0_5			(P0__5__PC)
#define P0_5_INTR	((uint16)((uint16)0x0001u << P0__5__SHIFT))

#define P0_6			(P0__6__PC)
#define P0_6_INTR	((uint16)((uint16)0x0001u << P0__6__SHIFT))

#define P0_7			(P0__7__PC)
#define P0_7_INTR	((uint16)((uint16)0x0001u << P0__7__SHIFT))

#define P0_INTR_ALL	 ((uint16)(P0_0_INTR| P0_1_INTR| P0_2_INTR| P0_3_INTR| P0_4_INTR| P0_5_INTR| P0_6_INTR| P0_7_INTR))

#endif /* End Pins P0_ALIASES_H */


/* [] END OF FILE */
