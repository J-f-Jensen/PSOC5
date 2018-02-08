/*******************************************************************************
* File Name: BootloaderResetTimer_PM.c
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

#include "BootloaderResetTimer.h"

static BootloaderResetTimer_backupStruct BootloaderResetTimer_backup;


/*******************************************************************************
* Function Name: BootloaderResetTimer_SaveConfig
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
*  BootloaderResetTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BootloaderResetTimer_SaveConfig(void) 
{
    #if (!BootloaderResetTimer_UsingFixedFunction)
        BootloaderResetTimer_backup.TimerUdb = BootloaderResetTimer_ReadCounter();
        BootloaderResetTimer_backup.InterruptMaskValue = BootloaderResetTimer_STATUS_MASK;
        #if (BootloaderResetTimer_UsingHWCaptureCounter)
            BootloaderResetTimer_backup.TimerCaptureCounter = BootloaderResetTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!BootloaderResetTimer_UDB_CONTROL_REG_REMOVED)
            BootloaderResetTimer_backup.TimerControlRegister = BootloaderResetTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: BootloaderResetTimer_RestoreConfig
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
*  BootloaderResetTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BootloaderResetTimer_RestoreConfig(void) 
{   
    #if (!BootloaderResetTimer_UsingFixedFunction)

        BootloaderResetTimer_WriteCounter(BootloaderResetTimer_backup.TimerUdb);
        BootloaderResetTimer_STATUS_MASK =BootloaderResetTimer_backup.InterruptMaskValue;
        #if (BootloaderResetTimer_UsingHWCaptureCounter)
            BootloaderResetTimer_SetCaptureCount(BootloaderResetTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!BootloaderResetTimer_UDB_CONTROL_REG_REMOVED)
            BootloaderResetTimer_WriteControlRegister(BootloaderResetTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: BootloaderResetTimer_Sleep
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
*  BootloaderResetTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void BootloaderResetTimer_Sleep(void) 
{
    #if(!BootloaderResetTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(BootloaderResetTimer_CTRL_ENABLE == (BootloaderResetTimer_CONTROL & BootloaderResetTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            BootloaderResetTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            BootloaderResetTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    BootloaderResetTimer_Stop();
    BootloaderResetTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: BootloaderResetTimer_Wakeup
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
*  BootloaderResetTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BootloaderResetTimer_Wakeup(void) 
{
    BootloaderResetTimer_RestoreConfig();
    #if(!BootloaderResetTimer_UDB_CONTROL_REG_REMOVED)
        if(BootloaderResetTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                BootloaderResetTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
