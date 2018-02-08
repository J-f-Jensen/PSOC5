/*******************************************************************************
* File Name: Micros_Counter_PM.c  
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

#include "Micros_Counter.h"

static Micros_Counter_backupStruct Micros_Counter_backup;


/*******************************************************************************
* Function Name: Micros_Counter_SaveConfig
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
*  Micros_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Micros_Counter_SaveConfig(void) 
{
    #if (!Micros_Counter_UsingFixedFunction)

        Micros_Counter_backup.CounterUdb = Micros_Counter_ReadCounter();

        #if(!Micros_Counter_ControlRegRemoved)
            Micros_Counter_backup.CounterControlRegister = Micros_Counter_ReadControlRegister();
        #endif /* (!Micros_Counter_ControlRegRemoved) */

    #endif /* (!Micros_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Micros_Counter_RestoreConfig
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
*  Micros_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Micros_Counter_RestoreConfig(void) 
{      
    #if (!Micros_Counter_UsingFixedFunction)

       Micros_Counter_WriteCounter(Micros_Counter_backup.CounterUdb);

        #if(!Micros_Counter_ControlRegRemoved)
            Micros_Counter_WriteControlRegister(Micros_Counter_backup.CounterControlRegister);
        #endif /* (!Micros_Counter_ControlRegRemoved) */

    #endif /* (!Micros_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Micros_Counter_Sleep
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
*  Micros_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Micros_Counter_Sleep(void) 
{
    #if(!Micros_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Micros_Counter_CTRL_ENABLE == (Micros_Counter_CONTROL & Micros_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Micros_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Micros_Counter_backup.CounterEnableState = 0u;
        }
    #else
        Micros_Counter_backup.CounterEnableState = 1u;
        if(Micros_Counter_backup.CounterEnableState != 0u)
        {
            Micros_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!Micros_Counter_ControlRegRemoved) */
    
    Micros_Counter_Stop();
    Micros_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Micros_Counter_Wakeup
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
*  Micros_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Micros_Counter_Wakeup(void) 
{
    Micros_Counter_RestoreConfig();
    #if(!Micros_Counter_ControlRegRemoved)
        if(Micros_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Micros_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Micros_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
