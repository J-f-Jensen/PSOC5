/*******************************************************************************
* File Name: Counter_1ms_PM.c  
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

#include "Counter_1ms.h"

static Counter_1ms_backupStruct Counter_1ms_backup;


/*******************************************************************************
* Function Name: Counter_1ms_SaveConfig
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
*  Counter_1ms_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_1ms_SaveConfig(void) 
{
    #if (!Counter_1ms_UsingFixedFunction)

        Counter_1ms_backup.CounterUdb = Counter_1ms_ReadCounter();

        #if(!Counter_1ms_ControlRegRemoved)
            Counter_1ms_backup.CounterControlRegister = Counter_1ms_ReadControlRegister();
        #endif /* (!Counter_1ms_ControlRegRemoved) */

    #endif /* (!Counter_1ms_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_1ms_RestoreConfig
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
*  Counter_1ms_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_1ms_RestoreConfig(void) 
{      
    #if (!Counter_1ms_UsingFixedFunction)

       Counter_1ms_WriteCounter(Counter_1ms_backup.CounterUdb);

        #if(!Counter_1ms_ControlRegRemoved)
            Counter_1ms_WriteControlRegister(Counter_1ms_backup.CounterControlRegister);
        #endif /* (!Counter_1ms_ControlRegRemoved) */

    #endif /* (!Counter_1ms_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_1ms_Sleep
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
*  Counter_1ms_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_1ms_Sleep(void) 
{
    #if(!Counter_1ms_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_1ms_CTRL_ENABLE == (Counter_1ms_CONTROL & Counter_1ms_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_1ms_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_1ms_backup.CounterEnableState = 0u;
        }
    #else
        Counter_1ms_backup.CounterEnableState = 1u;
        if(Counter_1ms_backup.CounterEnableState != 0u)
        {
            Counter_1ms_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_1ms_ControlRegRemoved) */
    
    Counter_1ms_Stop();
    Counter_1ms_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_1ms_Wakeup
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
*  Counter_1ms_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_1ms_Wakeup(void) 
{
    Counter_1ms_RestoreConfig();
    #if(!Counter_1ms_ControlRegRemoved)
        if(Counter_1ms_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_1ms_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_1ms_ControlRegRemoved) */
    
}


/* [] END OF FILE */
