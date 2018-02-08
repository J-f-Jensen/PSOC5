/*******************************************************************************
* File Name: Inj1_PM.c
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

#include "Inj1.h"

static Inj1_backupStruct Inj1_backup;


/*******************************************************************************
* Function Name: Inj1_SaveConfig
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
*  Inj1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Inj1_SaveConfig(void) 
{

    #if(!Inj1_UsingFixedFunction)
        #if(!Inj1_PWMModeIsCenterAligned)
            Inj1_backup.PWMPeriod = Inj1_ReadPeriod();
        #endif /* (!Inj1_PWMModeIsCenterAligned) */
        Inj1_backup.PWMUdb = Inj1_ReadCounter();
        #if (Inj1_UseStatus)
            Inj1_backup.InterruptMaskValue = Inj1_STATUS_MASK;
        #endif /* (Inj1_UseStatus) */

        #if(Inj1_DeadBandMode == Inj1__B_PWM__DBM_256_CLOCKS || \
            Inj1_DeadBandMode == Inj1__B_PWM__DBM_2_4_CLOCKS)
            Inj1_backup.PWMdeadBandValue = Inj1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Inj1_KillModeMinTime)
             Inj1_backup.PWMKillCounterPeriod = Inj1_ReadKillTime();
        #endif /* (Inj1_KillModeMinTime) */

        #if(Inj1_UseControl)
            Inj1_backup.PWMControlRegister = Inj1_ReadControlRegister();
        #endif /* (Inj1_UseControl) */
    #endif  /* (!Inj1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Inj1_RestoreConfig
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
*  Inj1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Inj1_RestoreConfig(void) 
{
        #if(!Inj1_UsingFixedFunction)
            #if(!Inj1_PWMModeIsCenterAligned)
                Inj1_WritePeriod(Inj1_backup.PWMPeriod);
            #endif /* (!Inj1_PWMModeIsCenterAligned) */

            Inj1_WriteCounter(Inj1_backup.PWMUdb);

            #if (Inj1_UseStatus)
                Inj1_STATUS_MASK = Inj1_backup.InterruptMaskValue;
            #endif /* (Inj1_UseStatus) */

            #if(Inj1_DeadBandMode == Inj1__B_PWM__DBM_256_CLOCKS || \
                Inj1_DeadBandMode == Inj1__B_PWM__DBM_2_4_CLOCKS)
                Inj1_WriteDeadTime(Inj1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Inj1_KillModeMinTime)
                Inj1_WriteKillTime(Inj1_backup.PWMKillCounterPeriod);
            #endif /* (Inj1_KillModeMinTime) */

            #if(Inj1_UseControl)
                Inj1_WriteControlRegister(Inj1_backup.PWMControlRegister);
            #endif /* (Inj1_UseControl) */
        #endif  /* (!Inj1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Inj1_Sleep
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
*  Inj1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Inj1_Sleep(void) 
{
    #if(Inj1_UseControl)
        if(Inj1_CTRL_ENABLE == (Inj1_CONTROL & Inj1_CTRL_ENABLE))
        {
            /*Component is enabled */
            Inj1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Inj1_backup.PWMEnableState = 0u;
        }
    #endif /* (Inj1_UseControl) */

    /* Stop component */
    Inj1_Stop();

    /* Save registers configuration */
    Inj1_SaveConfig();
}


/*******************************************************************************
* Function Name: Inj1_Wakeup
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
*  Inj1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Inj1_Wakeup(void) 
{
     /* Restore registers values */
    Inj1_RestoreConfig();

    if(Inj1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Inj1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
