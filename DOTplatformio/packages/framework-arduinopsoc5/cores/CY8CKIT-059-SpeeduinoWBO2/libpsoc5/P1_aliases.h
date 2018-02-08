/*******************************************************************************
* File Name: P1.h  
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

#if !defined(CY_PINS_P1_ALIASES_H) /* Pins P1_ALIASES_H */
#define CY_PINS_P1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define P1_0			(P1__0__PC)
#define P1_0_INTR	((uint16)((uint16)0x0001u << P1__0__SHIFT))

#define P1_1			(P1__1__PC)
#define P1_1_INTR	((uint16)((uint16)0x0001u << P1__1__SHIFT))

#define P1_2			(P1__2__PC)
#define P1_2_INTR	((uint16)((uint16)0x0001u << P1__2__SHIFT))

#define P1_3			(P1__3__PC)
#define P1_3_INTR	((uint16)((uint16)0x0001u << P1__3__SHIFT))

#define P1_4			(P1__4__PC)
#define P1_4_INTR	((uint16)((uint16)0x0001u << P1__4__SHIFT))

#define P1_5			(P1__5__PC)
#define P1_5_INTR	((uint16)((uint16)0x0001u << P1__5__SHIFT))

#define P1_INTR_ALL	 ((uint16)(P1_0_INTR| P1_1_INTR| P1_2_INTR| P1_3_INTR| P1_4_INTR| P1_5_INTR))
#define P1_FuelPump			(P1__FuelPump__PC)
#define P1_FuelPump_INTR	((uint16)((uint16)0x0001u << P1__0__SHIFT))

#define P1_Fan			(P1__Fan__PC)
#define P1_Fan_INTR	((uint16)((uint16)0x0001u << P1__1__SHIFT))

#define P1_Ignition_1			(P1__Ignition_1__PC)
#define P1_Ignition_1_INTR	((uint16)((uint16)0x0001u << P1__2__SHIFT))

#define P1_Ignition_2			(P1__Ignition_2__PC)
#define P1_Ignition_2_INTR	((uint16)((uint16)0x0001u << P1__3__SHIFT))

#define P1_Injector_1			(P1__Injector_1__PC)
#define P1_Injector_1_INTR	((uint16)((uint16)0x0001u << P1__4__SHIFT))

#define P1_Injector_2			(P1__Injector_2__PC)
#define P1_Injector_2_INTR	((uint16)((uint16)0x0001u << P1__5__SHIFT))

#endif /* End Pins P1_ALIASES_H */


/* [] END OF FILE */
