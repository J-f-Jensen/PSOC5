/*******************************************************************************
* File Name: ServoCounter_PM.c  
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

#include "ServoCounter.h"

static ServoCounter_backupStruct ServoCounter_backup;


/*******************************************************************************
* Function Name: ServoCounter_SaveConfig
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
*  ServoCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void ServoCounter_SaveConfig(void) 
{
    #if (!ServoCounter_UsingFixedFunction)

        ServoCounter_backup.CounterUdb = ServoCounter_ReadCounter();

        #if(!ServoCounter_ControlRegRemoved)
            ServoCounter_backup.CounterControlRegister = ServoCounter_ReadControlRegister();
        #endif /* (!ServoCounter_ControlRegRemoved) */

    #endif /* (!ServoCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCounter_RestoreConfig
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
*  ServoCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ServoCounter_RestoreConfig(void) 
{      
    #if (!ServoCounter_UsingFixedFunction)

       ServoCounter_WriteCounter(ServoCounter_backup.CounterUdb);

        #if(!ServoCounter_ControlRegRemoved)
            ServoCounter_WriteControlRegister(ServoCounter_backup.CounterControlRegister);
        #endif /* (!ServoCounter_ControlRegRemoved) */

    #endif /* (!ServoCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCounter_Sleep
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
*  ServoCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ServoCounter_Sleep(void) 
{
    #if(!ServoCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(ServoCounter_CTRL_ENABLE == (ServoCounter_CONTROL & ServoCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            ServoCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            ServoCounter_backup.CounterEnableState = 0u;
        }
    #else
        ServoCounter_backup.CounterEnableState = 1u;
        if(ServoCounter_backup.CounterEnableState != 0u)
        {
            ServoCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!ServoCounter_ControlRegRemoved) */
    
    ServoCounter_Stop();
    ServoCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: ServoCounter_Wakeup
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
*  ServoCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ServoCounter_Wakeup(void) 
{
    ServoCounter_RestoreConfig();
    #if(!ServoCounter_ControlRegRemoved)
        if(ServoCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            ServoCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!ServoCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
