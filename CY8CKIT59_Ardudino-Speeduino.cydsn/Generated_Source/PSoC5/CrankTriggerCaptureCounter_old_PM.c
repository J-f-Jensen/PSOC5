/*******************************************************************************
* File Name: CrankTriggerCaptureCounter_old_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "CrankTriggerCaptureCounter_old.h"

static CrankTriggerCaptureCounter_old_backupStruct CrankTriggerCaptureCounter_old_backup;


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_old_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  CrankTriggerCaptureCounter_old_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void CrankTriggerCaptureCounter_old_SaveConfig(void) 
{
    #if (!CrankTriggerCaptureCounter_old_UsingFixedFunction)
        CrankTriggerCaptureCounter_old_backup.TimerUdb = CrankTriggerCaptureCounter_old_ReadCounter();
        CrankTriggerCaptureCounter_old_backup.InterruptMaskValue = CrankTriggerCaptureCounter_old_STATUS_MASK;
        #if (CrankTriggerCaptureCounter_old_UsingHWCaptureCounter)
            CrankTriggerCaptureCounter_old_backup.TimerCaptureCounter = CrankTriggerCaptureCounter_old_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!CrankTriggerCaptureCounter_old_UDB_CONTROL_REG_REMOVED)
            CrankTriggerCaptureCounter_old_backup.TimerControlRegister = CrankTriggerCaptureCounter_old_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_old_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  CrankTriggerCaptureCounter_old_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CrankTriggerCaptureCounter_old_RestoreConfig(void) 
{   
    #if (!CrankTriggerCaptureCounter_old_UsingFixedFunction)

        CrankTriggerCaptureCounter_old_WriteCounter(CrankTriggerCaptureCounter_old_backup.TimerUdb);
        CrankTriggerCaptureCounter_old_STATUS_MASK =CrankTriggerCaptureCounter_old_backup.InterruptMaskValue;
        #if (CrankTriggerCaptureCounter_old_UsingHWCaptureCounter)
            CrankTriggerCaptureCounter_old_SetCaptureCount(CrankTriggerCaptureCounter_old_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!CrankTriggerCaptureCounter_old_UDB_CONTROL_REG_REMOVED)
            CrankTriggerCaptureCounter_old_WriteControlRegister(CrankTriggerCaptureCounter_old_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_old_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  CrankTriggerCaptureCounter_old_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void CrankTriggerCaptureCounter_old_Sleep(void) 
{
    #if(!CrankTriggerCaptureCounter_old_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(CrankTriggerCaptureCounter_old_CTRL_ENABLE == (CrankTriggerCaptureCounter_old_CONTROL & CrankTriggerCaptureCounter_old_CTRL_ENABLE))
        {
            /* Timer is enabled */
            CrankTriggerCaptureCounter_old_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            CrankTriggerCaptureCounter_old_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    CrankTriggerCaptureCounter_old_Stop();
    CrankTriggerCaptureCounter_old_SaveConfig();
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_old_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  CrankTriggerCaptureCounter_old_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CrankTriggerCaptureCounter_old_Wakeup(void) 
{
    CrankTriggerCaptureCounter_old_RestoreConfig();
    #if(!CrankTriggerCaptureCounter_old_UDB_CONTROL_REG_REMOVED)
        if(CrankTriggerCaptureCounter_old_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                CrankTriggerCaptureCounter_old_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
