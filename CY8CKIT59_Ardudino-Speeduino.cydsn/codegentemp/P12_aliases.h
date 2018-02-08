/*******************************************************************************
* File Name: P12.h  
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

#if !defined(CY_PINS_P12_ALIASES_H) /* Pins P12_ALIASES_H */
#define CY_PINS_P12_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define P12_0			(P12__0__PC)
#define P12_0_INTR	((uint16)((uint16)0x0001u << P12__0__SHIFT))

#define P12_1			(P12__1__PC)
#define P12_1_INTR	((uint16)((uint16)0x0001u << P12__1__SHIFT))

#define P12_2			(P12__2__PC)
#define P12_2_INTR	((uint16)((uint16)0x0001u << P12__2__SHIFT))

#define P12_3			(P12__3__PC)
#define P12_3_INTR	((uint16)((uint16)0x0001u << P12__3__SHIFT))

#define P12_4			(P12__4__PC)
#define P12_4_INTR	((uint16)((uint16)0x0001u << P12__4__SHIFT))

#define P12_5			(P12__5__PC)
#define P12_5_INTR	((uint16)((uint16)0x0001u << P12__5__SHIFT))

#define P12_INTR_ALL	 ((uint16)(P12_0_INTR| P12_1_INTR| P12_2_INTR| P12_3_INTR| P12_4_INTR| P12_5_INTR))

#endif /* End Pins P12_ALIASES_H */


/* [] END OF FILE */
