/*******************************************************************************
* File Name: CrankTriggerCaptureCounter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CrankTriggerCaptureCounter.h"

static CrankTriggerCaptureCounter_backupStruct CrankTriggerCaptureCounter_backup;


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_SaveConfig
********************************************************************************
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
*  CrankTriggerCaptureCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CrankTriggerCaptureCounter_SaveConfig(void) 
{
    #if (!CrankTriggerCaptureCounter_UsingFixedFunction)

        CrankTriggerCaptureCounter_backup.CounterUdb = CrankTriggerCaptureCounter_ReadCounter();

        #if(!CrankTriggerCaptureCounter_ControlRegRemoved)
            CrankTriggerCaptureCounter_backup.CounterControlRegister = CrankTriggerCaptureCounter_ReadControlRegister();
        #endif /* (!CrankTriggerCaptureCounter_ControlRegRemoved) */

    #endif /* (!CrankTriggerCaptureCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_RestoreConfig
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
*  CrankTriggerCaptureCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CrankTriggerCaptureCounter_RestoreConfig(void) 
{      
    #if (!CrankTriggerCaptureCounter_UsingFixedFunction)

       CrankTriggerCaptureCounter_WriteCounter(CrankTriggerCaptureCounter_backup.CounterUdb);

        #if(!CrankTriggerCaptureCounter_ControlRegRemoved)
            CrankTriggerCaptureCounter_WriteControlRegister(CrankTriggerCaptureCounter_backup.CounterControlRegister);
        #endif /* (!CrankTriggerCaptureCounter_ControlRegRemoved) */

    #endif /* (!CrankTriggerCaptureCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_Sleep
********************************************************************************
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
*  CrankTriggerCaptureCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CrankTriggerCaptureCounter_Sleep(void) 
{
    #if(!CrankTriggerCaptureCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CrankTriggerCaptureCounter_CTRL_ENABLE == (CrankTriggerCaptureCounter_CONTROL & CrankTriggerCaptureCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CrankTriggerCaptureCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CrankTriggerCaptureCounter_backup.CounterEnableState = 0u;
        }
    #else
        CrankTriggerCaptureCounter_backup.CounterEnableState = 1u;
        if(CrankTriggerCaptureCounter_backup.CounterEnableState != 0u)
        {
            CrankTriggerCaptureCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!CrankTriggerCaptureCounter_ControlRegRemoved) */
    
    CrankTriggerCaptureCounter_Stop();
    CrankTriggerCaptureCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_Wakeup
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
*  CrankTriggerCaptureCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CrankTriggerCaptureCounter_Wakeup(void) 
{
    CrankTriggerCaptureCounter_RestoreConfig();
    #if(!CrankTriggerCaptureCounter_ControlRegRemoved)
        if(CrankTriggerCaptureCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CrankTriggerCaptureCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CrankTriggerCaptureCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
