/*******************************************************************************
* File Name: IgnitionCounter_2_PM.c  
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

#include "IgnitionCounter_2.h"

static IgnitionCounter_2_backupStruct IgnitionCounter_2_backup;


/*******************************************************************************
* Function Name: IgnitionCounter_2_SaveConfig
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
*  IgnitionCounter_2_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void IgnitionCounter_2_SaveConfig(void) 
{
    #if (!IgnitionCounter_2_UsingFixedFunction)

        IgnitionCounter_2_backup.CounterUdb = IgnitionCounter_2_ReadCounter();

        #if(!IgnitionCounter_2_ControlRegRemoved)
            IgnitionCounter_2_backup.CounterControlRegister = IgnitionCounter_2_ReadControlRegister();
        #endif /* (!IgnitionCounter_2_ControlRegRemoved) */

    #endif /* (!IgnitionCounter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_RestoreConfig
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
*  IgnitionCounter_2_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void IgnitionCounter_2_RestoreConfig(void) 
{      
    #if (!IgnitionCounter_2_UsingFixedFunction)

       IgnitionCounter_2_WriteCounter(IgnitionCounter_2_backup.CounterUdb);

        #if(!IgnitionCounter_2_ControlRegRemoved)
            IgnitionCounter_2_WriteControlRegister(IgnitionCounter_2_backup.CounterControlRegister);
        #endif /* (!IgnitionCounter_2_ControlRegRemoved) */

    #endif /* (!IgnitionCounter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_Sleep
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
*  IgnitionCounter_2_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void IgnitionCounter_2_Sleep(void) 
{
    #if(!IgnitionCounter_2_ControlRegRemoved)
        /* Save Counter's enable state */
        if(IgnitionCounter_2_CTRL_ENABLE == (IgnitionCounter_2_CONTROL & IgnitionCounter_2_CTRL_ENABLE))
        {
            /* Counter is enabled */
            IgnitionCounter_2_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            IgnitionCounter_2_backup.CounterEnableState = 0u;
        }
    #else
        IgnitionCounter_2_backup.CounterEnableState = 1u;
        if(IgnitionCounter_2_backup.CounterEnableState != 0u)
        {
            IgnitionCounter_2_backup.CounterEnableState = 0u;
        }
    #endif /* (!IgnitionCounter_2_ControlRegRemoved) */
    
    IgnitionCounter_2_Stop();
    IgnitionCounter_2_SaveConfig();
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_Wakeup
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
*  IgnitionCounter_2_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void IgnitionCounter_2_Wakeup(void) 
{
    IgnitionCounter_2_RestoreConfig();
    #if(!IgnitionCounter_2_ControlRegRemoved)
        if(IgnitionCounter_2_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            IgnitionCounter_2_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!IgnitionCounter_2_ControlRegRemoved) */
    
}


/* [] END OF FILE */
