/*******************************************************************************
* File Name: IgnitionTimer_1_PM.c
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

#include "IgnitionTimer_1.h"

static IgnitionTimer_1_backupStruct IgnitionTimer_1_backup;


/*******************************************************************************
* Function Name: IgnitionTimer_1_SaveConfig
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
*  IgnitionTimer_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void IgnitionTimer_1_SaveConfig(void) 
{

    #if(!IgnitionTimer_1_UsingFixedFunction)
        #if(!IgnitionTimer_1_PWMModeIsCenterAligned)
            IgnitionTimer_1_backup.PWMPeriod = IgnitionTimer_1_ReadPeriod();
        #endif /* (!IgnitionTimer_1_PWMModeIsCenterAligned) */
        IgnitionTimer_1_backup.PWMUdb = IgnitionTimer_1_ReadCounter();
        #if (IgnitionTimer_1_UseStatus)
            IgnitionTimer_1_backup.InterruptMaskValue = IgnitionTimer_1_STATUS_MASK;
        #endif /* (IgnitionTimer_1_UseStatus) */

        #if(IgnitionTimer_1_DeadBandMode == IgnitionTimer_1__B_PWM__DBM_256_CLOCKS || \
            IgnitionTimer_1_DeadBandMode == IgnitionTimer_1__B_PWM__DBM_2_4_CLOCKS)
            IgnitionTimer_1_backup.PWMdeadBandValue = IgnitionTimer_1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(IgnitionTimer_1_KillModeMinTime)
             IgnitionTimer_1_backup.PWMKillCounterPeriod = IgnitionTimer_1_ReadKillTime();
        #endif /* (IgnitionTimer_1_KillModeMinTime) */

        #if(IgnitionTimer_1_UseControl)
            IgnitionTimer_1_backup.PWMControlRegister = IgnitionTimer_1_ReadControlRegister();
        #endif /* (IgnitionTimer_1_UseControl) */
    #endif  /* (!IgnitionTimer_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionTimer_1_RestoreConfig
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
*  IgnitionTimer_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void IgnitionTimer_1_RestoreConfig(void) 
{
        #if(!IgnitionTimer_1_UsingFixedFunction)
            #if(!IgnitionTimer_1_PWMModeIsCenterAligned)
                IgnitionTimer_1_WritePeriod(IgnitionTimer_1_backup.PWMPeriod);
            #endif /* (!IgnitionTimer_1_PWMModeIsCenterAligned) */

            IgnitionTimer_1_WriteCounter(IgnitionTimer_1_backup.PWMUdb);

            #if (IgnitionTimer_1_UseStatus)
                IgnitionTimer_1_STATUS_MASK = IgnitionTimer_1_backup.InterruptMaskValue;
            #endif /* (IgnitionTimer_1_UseStatus) */

            #if(IgnitionTimer_1_DeadBandMode == IgnitionTimer_1__B_PWM__DBM_256_CLOCKS || \
                IgnitionTimer_1_DeadBandMode == IgnitionTimer_1__B_PWM__DBM_2_4_CLOCKS)
                IgnitionTimer_1_WriteDeadTime(IgnitionTimer_1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(IgnitionTimer_1_KillModeMinTime)
                IgnitionTimer_1_WriteKillTime(IgnitionTimer_1_backup.PWMKillCounterPeriod);
            #endif /* (IgnitionTimer_1_KillModeMinTime) */

            #if(IgnitionTimer_1_UseControl)
                IgnitionTimer_1_WriteControlRegister(IgnitionTimer_1_backup.PWMControlRegister);
            #endif /* (IgnitionTimer_1_UseControl) */
        #endif  /* (!IgnitionTimer_1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: IgnitionTimer_1_Sleep
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
*  IgnitionTimer_1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void IgnitionTimer_1_Sleep(void) 
{
    #if(IgnitionTimer_1_UseControl)
        if(IgnitionTimer_1_CTRL_ENABLE == (IgnitionTimer_1_CONTROL & IgnitionTimer_1_CTRL_ENABLE))
        {
            /*Component is enabled */
            IgnitionTimer_1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            IgnitionTimer_1_backup.PWMEnableState = 0u;
        }
    #endif /* (IgnitionTimer_1_UseControl) */

    /* Stop component */
    IgnitionTimer_1_Stop();

    /* Save registers configuration */
    IgnitionTimer_1_SaveConfig();
}


/*******************************************************************************
* Function Name: IgnitionTimer_1_Wakeup
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
*  IgnitionTimer_1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void IgnitionTimer_1_Wakeup(void) 
{
     /* Restore registers values */
    IgnitionTimer_1_RestoreConfig();

    if(IgnitionTimer_1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        IgnitionTimer_1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
