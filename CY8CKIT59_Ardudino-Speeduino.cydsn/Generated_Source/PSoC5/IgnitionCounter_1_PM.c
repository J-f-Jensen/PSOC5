/*******************************************************************************
* File Name: IgnitionCounter_1_PM.c  
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

#include "IgnitionCounter_1.h"

static IgnitionCounter_1_backupStruct IgnitionCounter_1_backup;


/*******************************************************************************
* Function Name: IgnitionCounter_1_SaveConfig
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
*  IgnitionCounter_1_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void IgnitionCounter_1_SaveConfig(void) 
{
    #if (!IgnitionCounter_1_UsingFixedFunction)

        IgnitionCounter_1_backup.CounterUdb = IgnitionCounter_1_ReadCounter();

        #if(!IgnitionCounter_1_ControlRegRemoved)
            IgnitionCounter_1_backup.CounterControlRegister = IgnitionCounter_1_ReadControlRegister();
        #endif /* (!IgnitionCounter_1_ControlRegRemoved) */

    #endif /* (!IgnitionCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_1_RestoreConfig
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
*  IgnitionCounter_1_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void IgnitionCounter_1_RestoreConfig(void) 
{      
    #if (!IgnitionCounter_1_UsingFixedFunction)

       IgnitionCounter_1_WriteCounter(IgnitionCounter_1_backup.CounterUdb);

        #if(!IgnitionCounter_1_ControlRegRemoved)
            IgnitionCounter_1_WriteControlRegister(IgnitionCounter_1_backup.CounterControlRegister);
        #endif /* (!IgnitionCounter_1_ControlRegRemoved) */

    #endif /* (!IgnitionCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_1_Sleep
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
*  IgnitionCounter_1_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void IgnitionCounter_1_Sleep(void) 
{
    #if(!IgnitionCounter_1_ControlRegRemoved)
        /* Save Counter's enable state */
        if(IgnitionCounter_1_CTRL_ENABLE == (IgnitionCounter_1_CONTROL & IgnitionCounter_1_CTRL_ENABLE))
        {
            /* Counter is enabled */
            IgnitionCounter_1_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            IgnitionCounter_1_backup.CounterEnableState = 0u;
        }
    #else
        IgnitionCounter_1_backup.CounterEnableState = 1u;
        if(IgnitionCounter_1_backup.CounterEnableState != 0u)
        {
            IgnitionCounter_1_backup.CounterEnableState = 0u;
        }
    #endif /* (!IgnitionCounter_1_ControlRegRemoved) */
    
    IgnitionCounter_1_Stop();
    IgnitionCounter_1_SaveConfig();
}


/*******************************************************************************
* Function Name: IgnitionCounter_1_Wakeup
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
*  IgnitionCounter_1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void IgnitionCounter_1_Wakeup(void) 
{
    IgnitionCounter_1_RestoreConfig();
    #if(!IgnitionCounter_1_ControlRegRemoved)
        if(IgnitionCounter_1_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            IgnitionCounter_1_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!IgnitionCounter_1_ControlRegRemoved) */
    
}


/* [] END OF FILE */
