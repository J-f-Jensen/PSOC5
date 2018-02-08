/*******************************************************************************
* File Name: Millis_Counter_PM.c  
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

#include "Millis_Counter.h"

static Millis_Counter_backupStruct Millis_Counter_backup;


/*******************************************************************************
* Function Name: Millis_Counter_SaveConfig
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
*  Millis_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Millis_Counter_SaveConfig(void) 
{
    #if (!Millis_Counter_UsingFixedFunction)

        Millis_Counter_backup.CounterUdb = Millis_Counter_ReadCounter();

        #if(!Millis_Counter_ControlRegRemoved)
            Millis_Counter_backup.CounterControlRegister = Millis_Counter_ReadControlRegister();
        #endif /* (!Millis_Counter_ControlRegRemoved) */

    #endif /* (!Millis_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Millis_Counter_RestoreConfig
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
*  Millis_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Millis_Counter_RestoreConfig(void) 
{      
    #if (!Millis_Counter_UsingFixedFunction)

       Millis_Counter_WriteCounter(Millis_Counter_backup.CounterUdb);

        #if(!Millis_Counter_ControlRegRemoved)
            Millis_Counter_WriteControlRegister(Millis_Counter_backup.CounterControlRegister);
        #endif /* (!Millis_Counter_ControlRegRemoved) */

    #endif /* (!Millis_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Millis_Counter_Sleep
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
*  Millis_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Millis_Counter_Sleep(void) 
{
    #if(!Millis_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Millis_Counter_CTRL_ENABLE == (Millis_Counter_CONTROL & Millis_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Millis_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Millis_Counter_backup.CounterEnableState = 0u;
        }
    #else
        Millis_Counter_backup.CounterEnableState = 1u;
        if(Millis_Counter_backup.CounterEnableState != 0u)
        {
            Millis_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!Millis_Counter_ControlRegRemoved) */
    
    Millis_Counter_Stop();
    Millis_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Millis_Counter_Wakeup
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
*  Millis_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Millis_Counter_Wakeup(void) 
{
    Millis_Counter_RestoreConfig();
    #if(!Millis_Counter_ControlRegRemoved)
        if(Millis_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Millis_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Millis_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
