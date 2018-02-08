/*******************************************************************************
* File Name: DB.h  
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

#if !defined(CY_PINS_DB_ALIASES_H) /* Pins DB_ALIASES_H */
#define CY_PINS_DB_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define DB_0			(DB__0__PC)
#define DB_0_INTR	((uint16)((uint16)0x0001u << DB__0__SHIFT))

#define DB_1			(DB__1__PC)
#define DB_1_INTR	((uint16)((uint16)0x0001u << DB__1__SHIFT))

#define DB_2			(DB__2__PC)
#define DB_2_INTR	((uint16)((uint16)0x0001u << DB__2__SHIFT))

#define DB_3			(DB__3__PC)
#define DB_3_INTR	((uint16)((uint16)0x0001u << DB__3__SHIFT))

#define DB_4			(DB__4__PC)
#define DB_4_INTR	((uint16)((uint16)0x0001u << DB__4__SHIFT))

#define DB_5			(DB__5__PC)
#define DB_5_INTR	((uint16)((uint16)0x0001u << DB__5__SHIFT))

#define DB_INTR_ALL	 ((uint16)(DB_0_INTR| DB_1_INTR| DB_2_INTR| DB_3_INTR| DB_4_INTR| DB_5_INTR))

#endif /* End Pins DB_ALIASES_H */


/* [] END OF FILE */
