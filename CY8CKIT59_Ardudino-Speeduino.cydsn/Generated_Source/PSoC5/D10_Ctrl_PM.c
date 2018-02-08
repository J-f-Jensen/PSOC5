/*******************************************************************************
* File Name: D10_Ctrl_PM.c
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

#include "D10_Ctrl.h"

/* Check for removal by optimization */
#if !defined(D10_Ctrl_Sync_ctrl_reg__REMOVED)

static D10_Ctrl_BACKUP_STRUCT  D10_Ctrl_backup = {0u};

    
/*******************************************************************************
* Function Name: D10_Ctrl_SaveConfig
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
void D10_Ctrl_SaveConfig(void) 
{
    D10_Ctrl_backup.controlState = D10_Ctrl_Control;
}


/*******************************************************************************
* Function Name: D10_Ctrl_RestoreConfig
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
void D10_Ctrl_RestoreConfig(void) 
{
     D10_Ctrl_Control = D10_Ctrl_backup.controlState;
}


/*******************************************************************************
* Function Name: D10_Ctrl_Sleep
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
void D10_Ctrl_Sleep(void) 
{
    D10_Ctrl_SaveConfig();
}


/*******************************************************************************
* Function Name: D10_Ctrl_Wakeup
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
void D10_Ctrl_Wakeup(void)  
{
    D10_Ctrl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
