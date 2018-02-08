/*******************************************************************************
* File Name: InjectionTimer_PM.c
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

#include "InjectionTimer.h"

static InjectionTimer_backupStruct InjectionTimer_backup;


/*******************************************************************************
* Function Name: InjectionTimer_SaveConfig
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
*  InjectionTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void InjectionTimer_SaveConfig(void) 
{
    #if (!InjectionTimer_UsingFixedFunction)
        InjectionTimer_backup.TimerUdb = InjectionTimer_ReadCounter();
        InjectionTimer_backup.InterruptMaskValue = InjectionTimer_STATUS_MASK;
        #if (InjectionTimer_UsingHWCaptureCounter)
            InjectionTimer_backup.TimerCaptureCounter = InjectionTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!InjectionTimer_UDB_CONTROL_REG_REMOVED)
            InjectionTimer_backup.TimerControlRegister = InjectionTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: InjectionTimer_RestoreConfig
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
*  InjectionTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void InjectionTimer_RestoreConfig(void) 
{   
    #if (!InjectionTimer_UsingFixedFunction)

        InjectionTimer_WriteCounter(InjectionTimer_backup.TimerUdb);
        InjectionTimer_STATUS_MASK =InjectionTimer_backup.InterruptMaskValue;
        #if (InjectionTimer_UsingHWCaptureCounter)
            InjectionTimer_SetCaptureCount(InjectionTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!InjectionTimer_UDB_CONTROL_REG_REMOVED)
            InjectionTimer_WriteControlRegister(InjectionTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: InjectionTimer_Sleep
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
*  InjectionTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void InjectionTimer_Sleep(void) 
{
    #if(!InjectionTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(InjectionTimer_CTRL_ENABLE == (InjectionTimer_CONTROL & InjectionTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            InjectionTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            InjectionTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    InjectionTimer_Stop();
    InjectionTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: InjectionTimer_Wakeup
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
*  InjectionTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void InjectionTimer_Wakeup(void) 
{
    InjectionTimer_RestoreConfig();
    #if(!InjectionTimer_UDB_CONTROL_REG_REMOVED)
        if(InjectionTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                InjectionTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
