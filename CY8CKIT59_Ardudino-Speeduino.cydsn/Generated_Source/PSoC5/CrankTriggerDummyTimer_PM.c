/*******************************************************************************
* File Name: CrankTriggerDummyTimer_PM.c
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

#include "CrankTriggerDummyTimer.h"

static CrankTriggerDummyTimer_backupStruct CrankTriggerDummyTimer_backup;


/*******************************************************************************
* Function Name: CrankTriggerDummyTimer_SaveConfig
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
*  CrankTriggerDummyTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void CrankTriggerDummyTimer_SaveConfig(void) 
{
    #if (!CrankTriggerDummyTimer_UsingFixedFunction)
        CrankTriggerDummyTimer_backup.TimerUdb = CrankTriggerDummyTimer_ReadCounter();
        CrankTriggerDummyTimer_backup.InterruptMaskValue = CrankTriggerDummyTimer_STATUS_MASK;
        #if (CrankTriggerDummyTimer_UsingHWCaptureCounter)
            CrankTriggerDummyTimer_backup.TimerCaptureCounter = CrankTriggerDummyTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!CrankTriggerDummyTimer_UDB_CONTROL_REG_REMOVED)
            CrankTriggerDummyTimer_backup.TimerControlRegister = CrankTriggerDummyTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: CrankTriggerDummyTimer_RestoreConfig
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
*  CrankTriggerDummyTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CrankTriggerDummyTimer_RestoreConfig(void) 
{   
    #if (!CrankTriggerDummyTimer_UsingFixedFunction)

        CrankTriggerDummyTimer_WriteCounter(CrankTriggerDummyTimer_backup.TimerUdb);
        CrankTriggerDummyTimer_STATUS_MASK =CrankTriggerDummyTimer_backup.InterruptMaskValue;
        #if (CrankTriggerDummyTimer_UsingHWCaptureCounter)
            CrankTriggerDummyTimer_SetCaptureCount(CrankTriggerDummyTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!CrankTriggerDummyTimer_UDB_CONTROL_REG_REMOVED)
            CrankTriggerDummyTimer_WriteControlRegister(CrankTriggerDummyTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: CrankTriggerDummyTimer_Sleep
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
*  CrankTriggerDummyTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void CrankTriggerDummyTimer_Sleep(void) 
{
    #if(!CrankTriggerDummyTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(CrankTriggerDummyTimer_CTRL_ENABLE == (CrankTriggerDummyTimer_CONTROL & CrankTriggerDummyTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            CrankTriggerDummyTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            CrankTriggerDummyTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    CrankTriggerDummyTimer_Stop();
    CrankTriggerDummyTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: CrankTriggerDummyTimer_Wakeup
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
*  CrankTriggerDummyTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CrankTriggerDummyTimer_Wakeup(void) 
{
    CrankTriggerDummyTimer_RestoreConfig();
    #if(!CrankTriggerDummyTimer_UDB_CONTROL_REG_REMOVED)
        if(CrankTriggerDummyTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                CrankTriggerDummyTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
