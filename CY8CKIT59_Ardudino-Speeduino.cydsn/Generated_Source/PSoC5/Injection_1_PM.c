/*******************************************************************************
* File Name: Injection_1_PM.c
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

#include "Injection_1.h"

static Injection_1_backupStruct Injection_1_backup;


/*******************************************************************************
* Function Name: Injection_1_SaveConfig
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
*  Injection_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Injection_1_SaveConfig(void) 
{

    #if(!Injection_1_UsingFixedFunction)
        #if(!Injection_1_PWMModeIsCenterAligned)
            Injection_1_backup.PWMPeriod = Injection_1_ReadPeriod();
        #endif /* (!Injection_1_PWMModeIsCenterAligned) */
        Injection_1_backup.PWMUdb = Injection_1_ReadCounter();
        #if (Injection_1_UseStatus)
            Injection_1_backup.InterruptMaskValue = Injection_1_STATUS_MASK;
        #endif /* (Injection_1_UseStatus) */

        #if(Injection_1_DeadBandMode == Injection_1__B_PWM__DBM_256_CLOCKS || \
            Injection_1_DeadBandMode == Injection_1__B_PWM__DBM_2_4_CLOCKS)
            Injection_1_backup.PWMdeadBandValue = Injection_1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Injection_1_KillModeMinTime)
             Injection_1_backup.PWMKillCounterPeriod = Injection_1_ReadKillTime();
        #endif /* (Injection_1_KillModeMinTime) */

        #if(Injection_1_UseControl)
            Injection_1_backup.PWMControlRegister = Injection_1_ReadControlRegister();
        #endif /* (Injection_1_UseControl) */
    #endif  /* (!Injection_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Injection_1_RestoreConfig
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
*  Injection_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Injection_1_RestoreConfig(void) 
{
        #if(!Injection_1_UsingFixedFunction)
            #if(!Injection_1_PWMModeIsCenterAligned)
                Injection_1_WritePeriod(Injection_1_backup.PWMPeriod);
            #endif /* (!Injection_1_PWMModeIsCenterAligned) */

            Injection_1_WriteCounter(Injection_1_backup.PWMUdb);

            #if (Injection_1_UseStatus)
                Injection_1_STATUS_MASK = Injection_1_backup.InterruptMaskValue;
            #endif /* (Injection_1_UseStatus) */

            #if(Injection_1_DeadBandMode == Injection_1__B_PWM__DBM_256_CLOCKS || \
                Injection_1_DeadBandMode == Injection_1__B_PWM__DBM_2_4_CLOCKS)
                Injection_1_WriteDeadTime(Injection_1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Injection_1_KillModeMinTime)
                Injection_1_WriteKillTime(Injection_1_backup.PWMKillCounterPeriod);
            #endif /* (Injection_1_KillModeMinTime) */

            #if(Injection_1_UseControl)
                Injection_1_WriteControlRegister(Injection_1_backup.PWMControlRegister);
            #endif /* (Injection_1_UseControl) */
        #endif  /* (!Injection_1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Injection_1_Sleep
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
*  Injection_1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Injection_1_Sleep(void) 
{
    #if(Injection_1_UseControl)
        if(Injection_1_CTRL_ENABLE == (Injection_1_CONTROL & Injection_1_CTRL_ENABLE))
        {
            /*Component is enabled */
            Injection_1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Injection_1_backup.PWMEnableState = 0u;
        }
    #endif /* (Injection_1_UseControl) */

    /* Stop component */
    Injection_1_Stop();

    /* Save registers configuration */
    Injection_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Injection_1_Wakeup
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
*  Injection_1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Injection_1_Wakeup(void) 
{
     /* Restore registers values */
    Injection_1_RestoreConfig();

    if(Injection_1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Injection_1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
