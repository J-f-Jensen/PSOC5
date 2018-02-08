/*******************************************************************************
* File Name: Ignition_Timer_1_PM.c
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

#include "Ignition_Timer_1.h"

static Ignition_Timer_1_backupStruct Ignition_Timer_1_backup;


/*******************************************************************************
* Function Name: Ignition_Timer_1_SaveConfig
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
*  Ignition_Timer_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Ignition_Timer_1_SaveConfig(void) 
{

    #if(!Ignition_Timer_1_UsingFixedFunction)
        #if(!Ignition_Timer_1_PWMModeIsCenterAligned)
            Ignition_Timer_1_backup.PWMPeriod = Ignition_Timer_1_ReadPeriod();
        #endif /* (!Ignition_Timer_1_PWMModeIsCenterAligned) */
        Ignition_Timer_1_backup.PWMUdb = Ignition_Timer_1_ReadCounter();
        #if (Ignition_Timer_1_UseStatus)
            Ignition_Timer_1_backup.InterruptMaskValue = Ignition_Timer_1_STATUS_MASK;
        #endif /* (Ignition_Timer_1_UseStatus) */

        #if(Ignition_Timer_1_DeadBandMode == Ignition_Timer_1__B_PWM__DBM_256_CLOCKS || \
            Ignition_Timer_1_DeadBandMode == Ignition_Timer_1__B_PWM__DBM_2_4_CLOCKS)
            Ignition_Timer_1_backup.PWMdeadBandValue = Ignition_Timer_1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Ignition_Timer_1_KillModeMinTime)
             Ignition_Timer_1_backup.PWMKillCounterPeriod = Ignition_Timer_1_ReadKillTime();
        #endif /* (Ignition_Timer_1_KillModeMinTime) */

        #if(Ignition_Timer_1_UseControl)
            Ignition_Timer_1_backup.PWMControlRegister = Ignition_Timer_1_ReadControlRegister();
        #endif /* (Ignition_Timer_1_UseControl) */
    #endif  /* (!Ignition_Timer_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Ignition_Timer_1_RestoreConfig
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
*  Ignition_Timer_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Ignition_Timer_1_RestoreConfig(void) 
{
        #if(!Ignition_Timer_1_UsingFixedFunction)
            #if(!Ignition_Timer_1_PWMModeIsCenterAligned)
                Ignition_Timer_1_WritePeriod(Ignition_Timer_1_backup.PWMPeriod);
            #endif /* (!Ignition_Timer_1_PWMModeIsCenterAligned) */

            Ignition_Timer_1_WriteCounter(Ignition_Timer_1_backup.PWMUdb);

            #if (Ignition_Timer_1_UseStatus)
                Ignition_Timer_1_STATUS_MASK = Ignition_Timer_1_backup.InterruptMaskValue;
            #endif /* (Ignition_Timer_1_UseStatus) */

            #if(Ignition_Timer_1_DeadBandMode == Ignition_Timer_1__B_PWM__DBM_256_CLOCKS || \
                Ignition_Timer_1_DeadBandMode == Ignition_Timer_1__B_PWM__DBM_2_4_CLOCKS)
                Ignition_Timer_1_WriteDeadTime(Ignition_Timer_1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Ignition_Timer_1_KillModeMinTime)
                Ignition_Timer_1_WriteKillTime(Ignition_Timer_1_backup.PWMKillCounterPeriod);
            #endif /* (Ignition_Timer_1_KillModeMinTime) */

            #if(Ignition_Timer_1_UseControl)
                Ignition_Timer_1_WriteControlRegister(Ignition_Timer_1_backup.PWMControlRegister);
            #endif /* (Ignition_Timer_1_UseControl) */
        #endif  /* (!Ignition_Timer_1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Ignition_Timer_1_Sleep
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
*  Ignition_Timer_1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Ignition_Timer_1_Sleep(void) 
{
    #if(Ignition_Timer_1_UseControl)
        if(Ignition_Timer_1_CTRL_ENABLE == (Ignition_Timer_1_CONTROL & Ignition_Timer_1_CTRL_ENABLE))
        {
            /*Component is enabled */
            Ignition_Timer_1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Ignition_Timer_1_backup.PWMEnableState = 0u;
        }
    #endif /* (Ignition_Timer_1_UseControl) */

    /* Stop component */
    Ignition_Timer_1_Stop();

    /* Save registers configuration */
    Ignition_Timer_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Ignition_Timer_1_Wakeup
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
*  Ignition_Timer_1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Ignition_Timer_1_Wakeup(void) 
{
     /* Restore registers values */
    Ignition_Timer_1_RestoreConfig();

    if(Ignition_Timer_1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Ignition_Timer_1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
