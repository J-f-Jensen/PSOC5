/*******************************************************************************
* File Name: WBO2_Control_Reg.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_WBO2_Control_Reg_H) /* CY_CONTROL_REG_WBO2_Control_Reg_H */
#define CY_CONTROL_REG_WBO2_Control_Reg_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} WBO2_Control_Reg_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    WBO2_Control_Reg_Write(uint8 control) ;
uint8   WBO2_Control_Reg_Read(void) ;

void WBO2_Control_Reg_SaveConfig(void) ;
void WBO2_Control_Reg_RestoreConfig(void) ;
void WBO2_Control_Reg_Sleep(void) ; 
void WBO2_Control_Reg_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define WBO2_Control_Reg_Control        (* (reg8 *) WBO2_Control_Reg_Sync_ctrl_reg__CONTROL_REG )
#define WBO2_Control_Reg_Control_PTR    (  (reg8 *) WBO2_Control_Reg_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_WBO2_Control_Reg_H */


/* [] END OF FILE */
