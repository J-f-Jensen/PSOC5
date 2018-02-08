/*******************************************************************************
* File Name: InjectionTimerControlReg_PM.c
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

#include "InjectionTimerControlReg.h"

/* Check for removal by optimization */
#if !defined(InjectionTimerControlReg_Sync_ctrl_reg__REMOVED)

static InjectionTimerControlReg_BACKUP_STRUCT  InjectionTimerControlReg_backup = {0u};

    
/*******************************************************************************
* Function Name: InjectionTimerControlReg_SaveConfig
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
void InjectionTimerControlReg_SaveConfig(void) 
{
    InjectionTimerControlReg_backup.controlState = InjectionTimerControlReg_Control;
}


/*******************************************************************************
* Function Name: InjectionTimerControlReg_RestoreConfig
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
void InjectionTimerControlReg_RestoreConfig(void) 
{
     InjectionTimerControlReg_Control = InjectionTimerControlReg_backup.controlState;
}


/*******************************************************************************
* Function Name: InjectionTimerControlReg_Sleep
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
void InjectionTimerControlReg_Sleep(void) 
{
    InjectionTimerControlReg_SaveConfig();
}


/*******************************************************************************
* Function Name: InjectionTimerControlReg_Wakeup
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
void InjectionTimerControlReg_Wakeup(void)  
{
    InjectionTimerControlReg_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
