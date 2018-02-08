/*******************************************************************************
* File Name: ToneTimer_PM.c
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

#include "ToneTimer.h"

static ToneTimer_backupStruct ToneTimer_backup;


/*******************************************************************************
* Function Name: ToneTimer_SaveConfig
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
*  ToneTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ToneTimer_SaveConfig(void) 
{
    #if (!ToneTimer_UsingFixedFunction)
        ToneTimer_backup.TimerUdb = ToneTimer_ReadCounter();
        ToneTimer_backup.InterruptMaskValue = ToneTimer_STATUS_MASK;
        #if (ToneTimer_UsingHWCaptureCounter)
            ToneTimer_backup.TimerCaptureCounter = ToneTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!ToneTimer_UDB_CONTROL_REG_REMOVED)
            ToneTimer_backup.TimerControlRegister = ToneTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: ToneTimer_RestoreConfig
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
*  ToneTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ToneTimer_RestoreConfig(void) 
{   
    #if (!ToneTimer_UsingFixedFunction)

        ToneTimer_WriteCounter(ToneTimer_backup.TimerUdb);
        ToneTimer_STATUS_MASK =ToneTimer_backup.InterruptMaskValue;
        #if (ToneTimer_UsingHWCaptureCounter)
            ToneTimer_SetCaptureCount(ToneTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!ToneTimer_UDB_CONTROL_REG_REMOVED)
            ToneTimer_WriteControlRegister(ToneTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: ToneTimer_Sleep
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
*  ToneTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void ToneTimer_Sleep(void) 
{
    #if(!ToneTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(ToneTimer_CTRL_ENABLE == (ToneTimer_CONTROL & ToneTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            ToneTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            ToneTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    ToneTimer_Stop();
    ToneTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: ToneTimer_Wakeup
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
*  ToneTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ToneTimer_Wakeup(void) 
{
    ToneTimer_RestoreConfig();
    #if(!ToneTimer_UDB_CONTROL_REG_REMOVED)
        if(ToneTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                ToneTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
