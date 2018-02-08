/*******************************************************************************
* File Name: CrankTriggerDummyTimerReg_PM.c
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

#include "CrankTriggerDummyTimerReg.h"

/* Check for removal by optimization */
#if !defined(CrankTriggerDummyTimerReg_Sync_ctrl_reg__REMOVED)

static CrankTriggerDummyTimerReg_BACKUP_STRUCT  CrankTriggerDummyTimerReg_backup = {0u};

    
/*******************************************************************************
* Function Name: CrankTriggerDummyTimerReg_SaveConfig
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
void CrankTriggerDummyTimerReg_SaveConfig(void) 
{
    CrankTriggerDummyTimerReg_backup.controlState = CrankTriggerDummyTimerReg_Control;
}


/*******************************************************************************
* Function Name: CrankTriggerDummyTimerReg_RestoreConfig
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
void CrankTriggerDummyTimerReg_RestoreConfig(void) 
{
     CrankTriggerDummyTimerReg_Control = CrankTriggerDummyTimerReg_backup.controlState;
}


/*******************************************************************************
* Function Name: CrankTriggerDummyTimerReg_Sleep
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
void CrankTriggerDummyTimerReg_Sleep(void) 
{
    CrankTriggerDummyTimerReg_SaveConfig();
}


/*******************************************************************************
* Function Name: CrankTriggerDummyTimerReg_Wakeup
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
void CrankTriggerDummyTimerReg_Wakeup(void)  
{
    CrankTriggerDummyTimerReg_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
