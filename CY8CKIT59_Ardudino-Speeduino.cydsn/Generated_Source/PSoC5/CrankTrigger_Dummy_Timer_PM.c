/*******************************************************************************
* File Name: CrankTrigger_Dummy_Timer_PM.c
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

#include "CrankTrigger_Dummy_Timer.h"

static CrankTrigger_Dummy_Timer_backupStruct CrankTrigger_Dummy_Timer_backup;


/*******************************************************************************
* Function Name: CrankTrigger_Dummy_Timer_SaveConfig
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
*  CrankTrigger_Dummy_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void CrankTrigger_Dummy_Timer_SaveConfig(void) 
{
    #if (!CrankTrigger_Dummy_Timer_UsingFixedFunction)
        CrankTrigger_Dummy_Timer_backup.TimerUdb = CrankTrigger_Dummy_Timer_ReadCounter();
        CrankTrigger_Dummy_Timer_backup.InterruptMaskValue = CrankTrigger_Dummy_Timer_STATUS_MASK;
        #if (CrankTrigger_Dummy_Timer_UsingHWCaptureCounter)
            CrankTrigger_Dummy_Timer_backup.TimerCaptureCounter = CrankTrigger_Dummy_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!CrankTrigger_Dummy_Timer_UDB_CONTROL_REG_REMOVED)
            CrankTrigger_Dummy_Timer_backup.TimerControlRegister = CrankTrigger_Dummy_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: CrankTrigger_Dummy_Timer_RestoreConfig
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
*  CrankTrigger_Dummy_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CrankTrigger_Dummy_Timer_RestoreConfig(void) 
{   
    #if (!CrankTrigger_Dummy_Timer_UsingFixedFunction)

        CrankTrigger_Dummy_Timer_WriteCounter(CrankTrigger_Dummy_Timer_backup.TimerUdb);
        CrankTrigger_Dummy_Timer_STATUS_MASK =CrankTrigger_Dummy_Timer_backup.InterruptMaskValue;
        #if (CrankTrigger_Dummy_Timer_UsingHWCaptureCounter)
            CrankTrigger_Dummy_Timer_SetCaptureCount(CrankTrigger_Dummy_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!CrankTrigger_Dummy_Timer_UDB_CONTROL_REG_REMOVED)
            CrankTrigger_Dummy_Timer_WriteControlRegister(CrankTrigger_Dummy_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: CrankTrigger_Dummy_Timer_Sleep
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
*  CrankTrigger_Dummy_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void CrankTrigger_Dummy_Timer_Sleep(void) 
{
    #if(!CrankTrigger_Dummy_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(CrankTrigger_Dummy_Timer_CTRL_ENABLE == (CrankTrigger_Dummy_Timer_CONTROL & CrankTrigger_Dummy_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            CrankTrigger_Dummy_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            CrankTrigger_Dummy_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    CrankTrigger_Dummy_Timer_Stop();
    CrankTrigger_Dummy_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: CrankTrigger_Dummy_Timer_Wakeup
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
*  CrankTrigger_Dummy_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CrankTrigger_Dummy_Timer_Wakeup(void) 
{
    CrankTrigger_Dummy_Timer_RestoreConfig();
    #if(!CrankTrigger_Dummy_Timer_UDB_CONTROL_REG_REMOVED)
        if(CrankTrigger_Dummy_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                CrankTrigger_Dummy_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
