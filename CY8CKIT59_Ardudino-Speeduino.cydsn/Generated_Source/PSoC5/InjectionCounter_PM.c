/*******************************************************************************
* File Name: InjectionCounter_PM.c  
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

#include "InjectionCounter.h"

static InjectionCounter_backupStruct InjectionCounter_backup;


/*******************************************************************************
* Function Name: InjectionCounter_SaveConfig
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
*  InjectionCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void InjectionCounter_SaveConfig(void) 
{
    #if (!InjectionCounter_UsingFixedFunction)

        InjectionCounter_backup.CounterUdb = InjectionCounter_ReadCounter();

        #if(!InjectionCounter_ControlRegRemoved)
            InjectionCounter_backup.CounterControlRegister = InjectionCounter_ReadControlRegister();
        #endif /* (!InjectionCounter_ControlRegRemoved) */

    #endif /* (!InjectionCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionCounter_RestoreConfig
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
*  InjectionCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void InjectionCounter_RestoreConfig(void) 
{      
    #if (!InjectionCounter_UsingFixedFunction)

       InjectionCounter_WriteCounter(InjectionCounter_backup.CounterUdb);

        #if(!InjectionCounter_ControlRegRemoved)
            InjectionCounter_WriteControlRegister(InjectionCounter_backup.CounterControlRegister);
        #endif /* (!InjectionCounter_ControlRegRemoved) */

    #endif /* (!InjectionCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionCounter_Sleep
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
*  InjectionCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void InjectionCounter_Sleep(void) 
{
    #if(!InjectionCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(InjectionCounter_CTRL_ENABLE == (InjectionCounter_CONTROL & InjectionCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            InjectionCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            InjectionCounter_backup.CounterEnableState = 0u;
        }
    #else
        InjectionCounter_backup.CounterEnableState = 1u;
        if(InjectionCounter_backup.CounterEnableState != 0u)
        {
            InjectionCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!InjectionCounter_ControlRegRemoved) */
    
    InjectionCounter_Stop();
    InjectionCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: InjectionCounter_Wakeup
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
*  InjectionCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void InjectionCounter_Wakeup(void) 
{
    InjectionCounter_RestoreConfig();
    #if(!InjectionCounter_ControlRegRemoved)
        if(InjectionCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            InjectionCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!InjectionCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
