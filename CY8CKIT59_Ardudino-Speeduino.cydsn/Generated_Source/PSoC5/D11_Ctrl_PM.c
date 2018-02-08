/*******************************************************************************
* File Name: D11_Ctrl_PM.c
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

#include "D11_Ctrl.h"

/* Check for removal by optimization */
#if !defined(D11_Ctrl_Sync_ctrl_reg__REMOVED)

static D11_Ctrl_BACKUP_STRUCT  D11_Ctrl_backup = {0u};

    
/*******************************************************************************
* Function Name: D11_Ctrl_SaveConfig
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
void D11_Ctrl_SaveConfig(void) 
{
    D11_Ctrl_backup.controlState = D11_Ctrl_Control;
}


/*******************************************************************************
* Function Name: D11_Ctrl_RestoreConfig
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
void D11_Ctrl_RestoreConfig(void) 
{
     D11_Ctrl_Control = D11_Ctrl_backup.controlState;
}


/*******************************************************************************
* Function Name: D11_Ctrl_Sleep
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
void D11_Ctrl_Sleep(void) 
{
    D11_Ctrl_SaveConfig();
}


/*******************************************************************************
* Function Name: D11_Ctrl_Wakeup
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
void D11_Ctrl_Wakeup(void)  
{
    D11_Ctrl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
