/*******************************************************************************
* File Name: InjectionPortControlReg_PM.c
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

#include "InjectionPortControlReg.h"

/* Check for removal by optimization */
#if !defined(InjectionPortControlReg_Sync_ctrl_reg__REMOVED)

static InjectionPortControlReg_BACKUP_STRUCT  InjectionPortControlReg_backup = {0u};

    
/*******************************************************************************
* Function Name: InjectionPortControlReg_SaveConfig
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
void InjectionPortControlReg_SaveConfig(void) 
{
    InjectionPortControlReg_backup.controlState = InjectionPortControlReg_Control;
}


/*******************************************************************************
* Function Name: InjectionPortControlReg_RestoreConfig
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
void InjectionPortControlReg_RestoreConfig(void) 
{
     InjectionPortControlReg_Control = InjectionPortControlReg_backup.controlState;
}


/*******************************************************************************
* Function Name: InjectionPortControlReg_Sleep
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
void InjectionPortControlReg_Sleep(void) 
{
    InjectionPortControlReg_SaveConfig();
}


/*******************************************************************************
* Function Name: InjectionPortControlReg_Wakeup
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
void InjectionPortControlReg_Wakeup(void)  
{
    InjectionPortControlReg_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
