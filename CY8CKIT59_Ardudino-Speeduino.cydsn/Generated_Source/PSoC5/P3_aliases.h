/*******************************************************************************
* File Name: P3.h  
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

#if !defined(CY_PINS_P3_ALIASES_H) /* Pins P3_ALIASES_H */
#define CY_PINS_P3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define P3_0			(P3__0__PC)
#define P3_0_INTR	((uint16)((uint16)0x0001u << P3__0__SHIFT))

#define P3_1			(P3__1__PC)
#define P3_1_INTR	((uint16)((uint16)0x0001u << P3__1__SHIFT))

#define P3_2			(P3__2__PC)
#define P3_2_INTR	((uint16)((uint16)0x0001u << P3__2__SHIFT))

#define P3_3			(P3__3__PC)
#define P3_3_INTR	((uint16)((uint16)0x0001u << P3__3__SHIFT))

#define P3_4			(P3__4__PC)
#define P3_4_INTR	((uint16)((uint16)0x0001u << P3__4__SHIFT))

#define P3_5			(P3__5__PC)
#define P3_5_INTR	((uint16)((uint16)0x0001u << P3__5__SHIFT))

#define P3_6			(P3__6__PC)
#define P3_6_INTR	((uint16)((uint16)0x0001u << P3__6__SHIFT))

#define P3_7			(P3__7__PC)
#define P3_7_INTR	((uint16)((uint16)0x0001u << P3__7__SHIFT))

#define P3_INTR_ALL	 ((uint16)(P3_0_INTR| P3_1_INTR| P3_2_INTR| P3_3_INTR| P3_4_INTR| P3_5_INTR| P3_6_INTR| P3_7_INTR))

#endif /* End Pins P3_ALIASES_H */


/* [] END OF FILE */
