/*******************************************************************************
* File Name: IgnitionCounter_PM.c  
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

#include "IgnitionCounter.h"

static IgnitionCounter_backupStruct IgnitionCounter_backup;


/*******************************************************************************
* Function Name: IgnitionCounter_SaveConfig
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
*  IgnitionCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void IgnitionCounter_SaveConfig(void) 
{
    #if (!IgnitionCounter_UsingFixedFunction)

        IgnitionCounter_backup.CounterUdb = IgnitionCounter_ReadCounter();

        #if(!IgnitionCounter_ControlRegRemoved)
            IgnitionCounter_backup.CounterControlRegister = IgnitionCounter_ReadControlRegister();
        #endif /* (!IgnitionCounter_ControlRegRemoved) */

    #endif /* (!IgnitionCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_RestoreConfig
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
*  IgnitionCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void IgnitionCounter_RestoreConfig(void) 
{      
    #if (!IgnitionCounter_UsingFixedFunction)

       IgnitionCounter_WriteCounter(IgnitionCounter_backup.CounterUdb);

        #if(!IgnitionCounter_ControlRegRemoved)
            IgnitionCounter_WriteControlRegister(IgnitionCounter_backup.CounterControlRegister);
        #endif /* (!IgnitionCounter_ControlRegRemoved) */

    #endif /* (!IgnitionCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_Sleep
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
*  IgnitionCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void IgnitionCounter_Sleep(void) 
{
    #if(!IgnitionCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(IgnitionCounter_CTRL_ENABLE == (IgnitionCounter_CONTROL & IgnitionCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            IgnitionCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            IgnitionCounter_backup.CounterEnableState = 0u;
        }
    #else
        IgnitionCounter_backup.CounterEnableState = 1u;
        if(IgnitionCounter_backup.CounterEnableState != 0u)
        {
            IgnitionCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!IgnitionCounter_ControlRegRemoved) */
    
    IgnitionCounter_Stop();
    IgnitionCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: IgnitionCounter_Wakeup
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
*  IgnitionCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void IgnitionCounter_Wakeup(void) 
{
    IgnitionCounter_RestoreConfig();
    #if(!IgnitionCounter_ControlRegRemoved)
        if(IgnitionCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            IgnitionCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!IgnitionCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
