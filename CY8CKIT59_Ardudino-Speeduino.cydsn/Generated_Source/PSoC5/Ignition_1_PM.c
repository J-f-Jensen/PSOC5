/*******************************************************************************
* File Name: Ignition_1_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Ignition_1.h"

static Ignition_1_backupStruct Ignition_1_backup;


/*******************************************************************************
* Function Name: Ignition_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Ignition_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Ignition_1_SaveConfig(void) 
{

    #if(!Ignition_1_UsingFixedFunction)
        #if(!Ignition_1_PWMModeIsCenterAligned)
            Ignition_1_backup.PWMPeriod = Ignition_1_ReadPeriod();
        #endif /* (!Ignition_1_PWMModeIsCenterAligned) */
        Ignition_1_backup.PWMUdb = Ignition_1_ReadCounter();
        #if (Ignition_1_UseStatus)
            Ignition_1_backup.InterruptMaskValue = Ignition_1_STATUS_MASK;
        #endif /* (Ignition_1_UseStatus) */

        #if(Ignition_1_DeadBandMode == Ignition_1__B_PWM__DBM_256_CLOCKS || \
            Ignition_1_DeadBandMode == Ignition_1__B_PWM__DBM_2_4_CLOCKS)
            Ignition_1_backup.PWMdeadBandValue = Ignition_1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Ignition_1_KillModeMinTime)
             Ignition_1_backup.PWMKillCounterPeriod = Ignition_1_ReadKillTime();
        #endif /* (Ignition_1_KillModeMinTime) */

        #if(Ignition_1_UseControl)
            Ignition_1_backup.PWMControlRegister = Ignition_1_ReadControlRegister();
        #endif /* (Ignition_1_UseControl) */
    #endif  /* (!Ignition_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Ignition_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Ignition_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Ignition_1_RestoreConfig(void) 
{
        #if(!Ignition_1_UsingFixedFunction)
            #if(!Ignition_1_PWMModeIsCenterAligned)
                Ignition_1_WritePeriod(Ignition_1_backup.PWMPeriod);
            #endif /* (!Ignition_1_PWMModeIsCenterAligned) */

            Ignition_1_WriteCounter(Ignition_1_backup.PWMUdb);

            #if (Ignition_1_UseStatus)
                Ignition_1_STATUS_MASK = Ignition_1_backup.InterruptMaskValue;
            #endif /* (Ignition_1_UseStatus) */

            #if(Ignition_1_DeadBandMode == Ignition_1__B_PWM__DBM_256_CLOCKS || \
                Ignition_1_DeadBandMode == Ignition_1__B_PWM__DBM_2_4_CLOCKS)
                Ignition_1_WriteDeadTime(Ignition_1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Ignition_1_KillModeMinTime)
                Ignition_1_WriteKillTime(Ignition_1_backup.PWMKillCounterPeriod);
            #endif /* (Ignition_1_KillModeMinTime) */

            #if(Ignition_1_UseControl)
                Ignition_1_WriteControlRegister(Ignition_1_backup.PWMControlRegister);
            #endif /* (Ignition_1_UseControl) */
        #endif  /* (!Ignition_1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Ignition_1_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Ignition_1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Ignition_1_Sleep(void) 
{
    #if(Ignition_1_UseControl)
        if(Ignition_1_CTRL_ENABLE == (Ignition_1_CONTROL & Ignition_1_CTRL_ENABLE))
        {
            /*Component is enabled */
            Ignition_1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Ignition_1_backup.PWMEnableState = 0u;
        }
    #endif /* (Ignition_1_UseControl) */

    /* Stop component */
    Ignition_1_Stop();

    /* Save registers configuration */
    Ignition_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Ignition_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Ignition_1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Ignition_1_Wakeup(void) 
{
     /* Restore registers values */
    Ignition_1_RestoreConfig();

    if(Ignition_1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Ignition_1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
