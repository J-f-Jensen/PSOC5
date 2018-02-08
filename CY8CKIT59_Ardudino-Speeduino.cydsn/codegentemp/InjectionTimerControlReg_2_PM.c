/*******************************************************************************
* File Name: InjectionTimerControlReg_2_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "InjectionTimerControlReg_2.h"

/* Check for removal by optimization */
#if !defined(InjectionTimerControlReg_2_Sync_ctrl_reg__REMOVED)

static InjectionTimerControlReg_2_BACKUP_STRUCT  InjectionTimerControlReg_2_backup = {0u};

    
/*******************************************************************************
* Function Name: InjectionTimerControlReg_2_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void InjectionTimerControlReg_2_SaveConfig(void) 
{
    InjectionTimerControlReg_2_backup.controlState = InjectionTimerControlReg_2_Control;
}


/*******************************************************************************
* Function Name: InjectionTimerControlReg_2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void InjectionTimerControlReg_2_RestoreConfig(void) 
{
     InjectionTimerControlReg_2_Control = InjectionTimerControlReg_2_backup.controlState;
}


/*******************************************************************************
* Function Name: InjectionTimerControlReg_2_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void InjectionTimerControlReg_2_Sleep(void) 
{
    InjectionTimerControlReg_2_SaveConfig();
}


/*******************************************************************************
* Function Name: InjectionTimerControlReg_2_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void InjectionTimerControlReg_2_Wakeup(void)  
{
    InjectionTimerControlReg_2_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
