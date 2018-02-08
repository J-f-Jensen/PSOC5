/*******************************************************************************
* File Name: InjectionTimerControlReg.h  
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

#if !defined(CY_CONTROL_REG_InjectionTimerControlReg_H) /* CY_CONTROL_REG_InjectionTimerControlReg_H */
#define CY_CONTROL_REG_InjectionTimerControlReg_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} InjectionTimerControlReg_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    InjectionTimerControlReg_Write(uint8 control) ;
uint8   InjectionTimerControlReg_Read(void) ;

void InjectionTimerControlReg_SaveConfig(void) ;
void InjectionTimerControlReg_RestoreConfig(void) ;
void InjectionTimerControlReg_Sleep(void) ; 
void InjectionTimerControlReg_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define InjectionTimerControlReg_Control        (* (reg8 *) InjectionTimerControlReg_Sync_ctrl_reg__CONTROL_REG )
#define InjectionTimerControlReg_Control_PTR    (  (reg8 *) InjectionTimerControlReg_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_InjectionTimerControlReg_H */


/* [] END OF FILE */
