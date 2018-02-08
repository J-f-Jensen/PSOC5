/*******************************************************************************
* File Name: InjectionTimer_1_PM.c
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

#include "InjectionTimer_1.h"

static InjectionTimer_1_backupStruct InjectionTimer_1_backup;


/*******************************************************************************
* Function Name: InjectionTimer_1_SaveConfig
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
*  InjectionTimer_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void InjectionTimer_1_SaveConfig(void) 
{

    #if(!InjectionTimer_1_UsingFixedFunction)
        #if(!InjectionTimer_1_PWMModeIsCenterAligned)
            InjectionTimer_1_backup.PWMPeriod = InjectionTimer_1_ReadPeriod();
        #endif /* (!InjectionTimer_1_PWMModeIsCenterAligned) */
        InjectionTimer_1_backup.PWMUdb = InjectionTimer_1_ReadCounter();
        #if (InjectionTimer_1_UseStatus)
            InjectionTimer_1_backup.InterruptMaskValue = InjectionTimer_1_STATUS_MASK;
        #endif /* (InjectionTimer_1_UseStatus) */

        #if(InjectionTimer_1_DeadBandMode == InjectionTimer_1__B_PWM__DBM_256_CLOCKS || \
            InjectionTimer_1_DeadBandMode == InjectionTimer_1__B_PWM__DBM_2_4_CLOCKS)
            InjectionTimer_1_backup.PWMdeadBandValue = InjectionTimer_1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(InjectionTimer_1_KillModeMinTime)
             InjectionTimer_1_backup.PWMKillCounterPeriod = InjectionTimer_1_ReadKillTime();
        #endif /* (InjectionTimer_1_KillModeMinTime) */

        #if(InjectionTimer_1_UseControl)
            InjectionTimer_1_backup.PWMControlRegister = InjectionTimer_1_ReadControlRegister();
        #endif /* (InjectionTimer_1_UseControl) */
    #endif  /* (!InjectionTimer_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionTimer_1_RestoreConfig
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
*  InjectionTimer_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void InjectionTimer_1_RestoreConfig(void) 
{
        #if(!InjectionTimer_1_UsingFixedFunction)
            #if(!InjectionTimer_1_PWMModeIsCenterAligned)
                InjectionTimer_1_WritePeriod(InjectionTimer_1_backup.PWMPeriod);
            #endif /* (!InjectionTimer_1_PWMModeIsCenterAligned) */

            InjectionTimer_1_WriteCounter(InjectionTimer_1_backup.PWMUdb);

            #if (InjectionTimer_1_UseStatus)
                InjectionTimer_1_STATUS_MASK = InjectionTimer_1_backup.InterruptMaskValue;
            #endif /* (InjectionTimer_1_UseStatus) */

            #if(InjectionTimer_1_DeadBandMode == InjectionTimer_1__B_PWM__DBM_256_CLOCKS || \
                InjectionTimer_1_DeadBandMode == InjectionTimer_1__B_PWM__DBM_2_4_CLOCKS)
                InjectionTimer_1_WriteDeadTime(InjectionTimer_1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(InjectionTimer_1_KillModeMinTime)
                InjectionTimer_1_WriteKillTime(InjectionTimer_1_backup.PWMKillCounterPeriod);
            #endif /* (InjectionTimer_1_KillModeMinTime) */

            #if(InjectionTimer_1_UseControl)
                InjectionTimer_1_WriteControlRegister(InjectionTimer_1_backup.PWMControlRegister);
            #endif /* (InjectionTimer_1_UseControl) */
        #endif  /* (!InjectionTimer_1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: InjectionTimer_1_Sleep
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
*  InjectionTimer_1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void InjectionTimer_1_Sleep(void) 
{
    #if(InjectionTimer_1_UseControl)
        if(InjectionTimer_1_CTRL_ENABLE == (InjectionTimer_1_CONTROL & InjectionTimer_1_CTRL_ENABLE))
        {
            /*Component is enabled */
            InjectionTimer_1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            InjectionTimer_1_backup.PWMEnableState = 0u;
        }
    #endif /* (InjectionTimer_1_UseControl) */

    /* Stop component */
    InjectionTimer_1_Stop();

    /* Save registers configuration */
    InjectionTimer_1_SaveConfig();
}


/*******************************************************************************
* Function Name: InjectionTimer_1_Wakeup
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
*  InjectionTimer_1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void InjectionTimer_1_Wakeup(void) 
{
     /* Restore registers values */
    InjectionTimer_1_RestoreConfig();

    if(InjectionTimer_1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        InjectionTimer_1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
