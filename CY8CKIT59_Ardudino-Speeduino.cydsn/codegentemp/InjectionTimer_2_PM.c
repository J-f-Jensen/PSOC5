/*******************************************************************************
* File Name: InjectionTimer_2_PM.c
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

#include "InjectionTimer_2.h"

static InjectionTimer_2_backupStruct InjectionTimer_2_backup;


/*******************************************************************************
* Function Name: InjectionTimer_2_SaveConfig
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
*  InjectionTimer_2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void InjectionTimer_2_SaveConfig(void) 
{

    #if(!InjectionTimer_2_UsingFixedFunction)
        #if(!InjectionTimer_2_PWMModeIsCenterAligned)
            InjectionTimer_2_backup.PWMPeriod = InjectionTimer_2_ReadPeriod();
        #endif /* (!InjectionTimer_2_PWMModeIsCenterAligned) */
        InjectionTimer_2_backup.PWMUdb = InjectionTimer_2_ReadCounter();
        #if (InjectionTimer_2_UseStatus)
            InjectionTimer_2_backup.InterruptMaskValue = InjectionTimer_2_STATUS_MASK;
        #endif /* (InjectionTimer_2_UseStatus) */

        #if(InjectionTimer_2_DeadBandMode == InjectionTimer_2__B_PWM__DBM_256_CLOCKS || \
            InjectionTimer_2_DeadBandMode == InjectionTimer_2__B_PWM__DBM_2_4_CLOCKS)
            InjectionTimer_2_backup.PWMdeadBandValue = InjectionTimer_2_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(InjectionTimer_2_KillModeMinTime)
             InjectionTimer_2_backup.PWMKillCounterPeriod = InjectionTimer_2_ReadKillTime();
        #endif /* (InjectionTimer_2_KillModeMinTime) */

        #if(InjectionTimer_2_UseControl)
            InjectionTimer_2_backup.PWMControlRegister = InjectionTimer_2_ReadControlRegister();
        #endif /* (InjectionTimer_2_UseControl) */
    #endif  /* (!InjectionTimer_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionTimer_2_RestoreConfig
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
*  InjectionTimer_2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void InjectionTimer_2_RestoreConfig(void) 
{
        #if(!InjectionTimer_2_UsingFixedFunction)
            #if(!InjectionTimer_2_PWMModeIsCenterAligned)
                InjectionTimer_2_WritePeriod(InjectionTimer_2_backup.PWMPeriod);
            #endif /* (!InjectionTimer_2_PWMModeIsCenterAligned) */

            InjectionTimer_2_WriteCounter(InjectionTimer_2_backup.PWMUdb);

            #if (InjectionTimer_2_UseStatus)
                InjectionTimer_2_STATUS_MASK = InjectionTimer_2_backup.InterruptMaskValue;
            #endif /* (InjectionTimer_2_UseStatus) */

            #if(InjectionTimer_2_DeadBandMode == InjectionTimer_2__B_PWM__DBM_256_CLOCKS || \
                InjectionTimer_2_DeadBandMode == InjectionTimer_2__B_PWM__DBM_2_4_CLOCKS)
                InjectionTimer_2_WriteDeadTime(InjectionTimer_2_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(InjectionTimer_2_KillModeMinTime)
                InjectionTimer_2_WriteKillTime(InjectionTimer_2_backup.PWMKillCounterPeriod);
            #endif /* (InjectionTimer_2_KillModeMinTime) */

            #if(InjectionTimer_2_UseControl)
                InjectionTimer_2_WriteControlRegister(InjectionTimer_2_backup.PWMControlRegister);
            #endif /* (InjectionTimer_2_UseControl) */
        #endif  /* (!InjectionTimer_2_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: InjectionTimer_2_Sleep
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
*  InjectionTimer_2_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void InjectionTimer_2_Sleep(void) 
{
    #if(InjectionTimer_2_UseControl)
        if(InjectionTimer_2_CTRL_ENABLE == (InjectionTimer_2_CONTROL & InjectionTimer_2_CTRL_ENABLE))
        {
            /*Component is enabled */
            InjectionTimer_2_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            InjectionTimer_2_backup.PWMEnableState = 0u;
        }
    #endif /* (InjectionTimer_2_UseControl) */

    /* Stop component */
    InjectionTimer_2_Stop();

    /* Save registers configuration */
    InjectionTimer_2_SaveConfig();
}


/*******************************************************************************
* Function Name: InjectionTimer_2_Wakeup
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
*  InjectionTimer_2_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void InjectionTimer_2_Wakeup(void) 
{
     /* Restore registers values */
    InjectionTimer_2_RestoreConfig();

    if(InjectionTimer_2_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        InjectionTimer_2_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
