/*******************************************************************************
* File Name: IgnitionPortControlReg_PM.c
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

#include "IgnitionPortControlReg.h"

/* Check for removal by optimization */
#if !defined(IgnitionPortControlReg_Sync_ctrl_reg__REMOVED)

static IgnitionPortControlReg_BACKUP_STRUCT  IgnitionPortControlReg_backup = {0u};

    
/*******************************************************************************
* Function Name: IgnitionPortControlReg_SaveConfig
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
void IgnitionPortControlReg_SaveConfig(void) 
{
    IgnitionPortControlReg_backup.controlState = IgnitionPortControlReg_Control;
}


/*******************************************************************************
* Function Name: IgnitionPortControlReg_RestoreConfig
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
void IgnitionPortControlReg_RestoreConfig(void) 
{
     IgnitionPortControlReg_Control = IgnitionPortControlReg_backup.controlState;
}


/*******************************************************************************
* Function Name: IgnitionPortControlReg_Sleep
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
void IgnitionPortControlReg_Sleep(void) 
{
    IgnitionPortControlReg_SaveConfig();
}


/*******************************************************************************
* Function Name: IgnitionPortControlReg_Wakeup
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
void IgnitionPortControlReg_Wakeup(void)  
{
    IgnitionPortControlReg_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
