/*******************************************************************************
* File Name: Injection_2_PM.c
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

#include "Injection_2.h"

static Injection_2_backupStruct Injection_2_backup;


/*******************************************************************************
* Function Name: Injection_2_SaveConfig
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
*  Injection_2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Injection_2_SaveConfig(void) 
{

    #if(!Injection_2_UsingFixedFunction)
        #if(!Injection_2_PWMModeIsCenterAligned)
            Injection_2_backup.PWMPeriod = Injection_2_ReadPeriod();
        #endif /* (!Injection_2_PWMModeIsCenterAligned) */
        Injection_2_backup.PWMUdb = Injection_2_ReadCounter();
        #if (Injection_2_UseStatus)
            Injection_2_backup.InterruptMaskValue = Injection_2_STATUS_MASK;
        #endif /* (Injection_2_UseStatus) */

        #if(Injection_2_DeadBandMode == Injection_2__B_PWM__DBM_256_CLOCKS || \
            Injection_2_DeadBandMode == Injection_2__B_PWM__DBM_2_4_CLOCKS)
            Injection_2_backup.PWMdeadBandValue = Injection_2_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Injection_2_KillModeMinTime)
             Injection_2_backup.PWMKillCounterPeriod = Injection_2_ReadKillTime();
        #endif /* (Injection_2_KillModeMinTime) */

        #if(Injection_2_UseControl)
            Injection_2_backup.PWMControlRegister = Injection_2_ReadControlRegister();
        #endif /* (Injection_2_UseControl) */
    #endif  /* (!Injection_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Injection_2_RestoreConfig
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
*  Injection_2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Injection_2_RestoreConfig(void) 
{
        #if(!Injection_2_UsingFixedFunction)
            #if(!Injection_2_PWMModeIsCenterAligned)
                Injection_2_WritePeriod(Injection_2_backup.PWMPeriod);
            #endif /* (!Injection_2_PWMModeIsCenterAligned) */

            Injection_2_WriteCounter(Injection_2_backup.PWMUdb);

            #if (Injection_2_UseStatus)
                Injection_2_STATUS_MASK = Injection_2_backup.InterruptMaskValue;
            #endif /* (Injection_2_UseStatus) */

            #if(Injection_2_DeadBandMode == Injection_2__B_PWM__DBM_256_CLOCKS || \
                Injection_2_DeadBandMode == Injection_2__B_PWM__DBM_2_4_CLOCKS)
                Injection_2_WriteDeadTime(Injection_2_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Injection_2_KillModeMinTime)
                Injection_2_WriteKillTime(Injection_2_backup.PWMKillCounterPeriod);
            #endif /* (Injection_2_KillModeMinTime) */

            #if(Injection_2_UseControl)
                Injection_2_WriteControlRegister(Injection_2_backup.PWMControlRegister);
            #endif /* (Injection_2_UseControl) */
        #endif  /* (!Injection_2_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Injection_2_Sleep
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
*  Injection_2_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Injection_2_Sleep(void) 
{
    #if(Injection_2_UseControl)
        if(Injection_2_CTRL_ENABLE == (Injection_2_CONTROL & Injection_2_CTRL_ENABLE))
        {
            /*Component is enabled */
            Injection_2_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Injection_2_backup.PWMEnableState = 0u;
        }
    #endif /* (Injection_2_UseControl) */

    /* Stop component */
    Injection_2_Stop();

    /* Save registers configuration */
    Injection_2_SaveConfig();
}


/*******************************************************************************
* Function Name: Injection_2_Wakeup
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
*  Injection_2_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Injection_2_Wakeup(void) 
{
     /* Restore registers values */
    Injection_2_RestoreConfig();

    if(Injection_2_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Injection_2_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
