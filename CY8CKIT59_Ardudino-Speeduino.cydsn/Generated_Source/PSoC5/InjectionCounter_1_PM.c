/*******************************************************************************
* File Name: InjectionCounter_1_PM.c  
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

#include "InjectionCounter_1.h"

static InjectionCounter_1_backupStruct InjectionCounter_1_backup;


/*******************************************************************************
* Function Name: InjectionCounter_1_SaveConfig
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
*  InjectionCounter_1_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void InjectionCounter_1_SaveConfig(void) 
{
    #if (!InjectionCounter_1_UsingFixedFunction)

        InjectionCounter_1_backup.CounterUdb = InjectionCounter_1_ReadCounter();

        #if(!InjectionCounter_1_ControlRegRemoved)
            InjectionCounter_1_backup.CounterControlRegister = InjectionCounter_1_ReadControlRegister();
        #endif /* (!InjectionCounter_1_ControlRegRemoved) */

    #endif /* (!InjectionCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionCounter_1_RestoreConfig
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
*  InjectionCounter_1_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void InjectionCounter_1_RestoreConfig(void) 
{      
    #if (!InjectionCounter_1_UsingFixedFunction)

       InjectionCounter_1_WriteCounter(InjectionCounter_1_backup.CounterUdb);

        #if(!InjectionCounter_1_ControlRegRemoved)
            InjectionCounter_1_WriteControlRegister(InjectionCounter_1_backup.CounterControlRegister);
        #endif /* (!InjectionCounter_1_ControlRegRemoved) */

    #endif /* (!InjectionCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionCounter_1_Sleep
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
*  InjectionCounter_1_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void InjectionCounter_1_Sleep(void) 
{
    #if(!InjectionCounter_1_ControlRegRemoved)
        /* Save Counter's enable state */
        if(InjectionCounter_1_CTRL_ENABLE == (InjectionCounter_1_CONTROL & InjectionCounter_1_CTRL_ENABLE))
        {
            /* Counter is enabled */
            InjectionCounter_1_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            InjectionCounter_1_backup.CounterEnableState = 0u;
        }
    #else
        InjectionCounter_1_backup.CounterEnableState = 1u;
        if(InjectionCounter_1_backup.CounterEnableState != 0u)
        {
            InjectionCounter_1_backup.CounterEnableState = 0u;
        }
    #endif /* (!InjectionCounter_1_ControlRegRemoved) */
    
    InjectionCounter_1_Stop();
    InjectionCounter_1_SaveConfig();
}


/*******************************************************************************
* Function Name: InjectionCounter_1_Wakeup
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
*  InjectionCounter_1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void InjectionCounter_1_Wakeup(void) 
{
    InjectionCounter_1_RestoreConfig();
    #if(!InjectionCounter_1_ControlRegRemoved)
        if(InjectionCounter_1_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            InjectionCounter_1_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!InjectionCounter_1_ControlRegRemoved) */
    
}


/* [] END OF FILE */
