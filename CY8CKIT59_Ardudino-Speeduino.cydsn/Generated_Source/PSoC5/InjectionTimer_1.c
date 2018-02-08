/*******************************************************************************
* File Name: InjectionTimer_1.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "InjectionTimer_1.h"

/* Error message for removed <resource> through optimization */
#ifdef InjectionTimer_1_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* InjectionTimer_1_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 InjectionTimer_1_initVar = 0u;


/*******************************************************************************
* Function Name: InjectionTimer_1_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  InjectionTimer_1_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void InjectionTimer_1_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(InjectionTimer_1_initVar == 0u)
    {
        InjectionTimer_1_Init();
        InjectionTimer_1_initVar = 1u;
    }
    InjectionTimer_1_Enable();

}


/*******************************************************************************
* Function Name: InjectionTimer_1_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  InjectionTimer_1_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void InjectionTimer_1_Init(void) 
{
    #if (InjectionTimer_1_UsingFixedFunction || InjectionTimer_1_UseControl)
        uint8 ctrl;
    #endif /* (InjectionTimer_1_UsingFixedFunction || InjectionTimer_1_UseControl) */

    #if(!InjectionTimer_1_UsingFixedFunction)
        #if(InjectionTimer_1_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 InjectionTimer_1_interruptState;
        #endif /* (InjectionTimer_1_UseStatus) */
    #endif /* (!InjectionTimer_1_UsingFixedFunction) */

    #if (InjectionTimer_1_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        InjectionTimer_1_CONTROL |= InjectionTimer_1_CFG0_MODE;
        #if (InjectionTimer_1_DeadBand2_4)
            InjectionTimer_1_CONTROL |= InjectionTimer_1_CFG0_DB;
        #endif /* (InjectionTimer_1_DeadBand2_4) */

        ctrl = InjectionTimer_1_CONTROL3 & ((uint8 )(~InjectionTimer_1_CTRL_CMPMODE1_MASK));
        InjectionTimer_1_CONTROL3 = ctrl | InjectionTimer_1_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        InjectionTimer_1_RT1 &= ((uint8)(~InjectionTimer_1_RT1_MASK));
        InjectionTimer_1_RT1 |= InjectionTimer_1_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        InjectionTimer_1_RT1 &= ((uint8)(~InjectionTimer_1_SYNCDSI_MASK));
        InjectionTimer_1_RT1 |= InjectionTimer_1_SYNCDSI_EN;

    #elif (InjectionTimer_1_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = InjectionTimer_1_CONTROL & ((uint8)(~InjectionTimer_1_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~InjectionTimer_1_CTRL_CMPMODE1_MASK));
        InjectionTimer_1_CONTROL = ctrl | InjectionTimer_1_DEFAULT_COMPARE2_MODE |
                                   InjectionTimer_1_DEFAULT_COMPARE1_MODE;
    #endif /* (InjectionTimer_1_UsingFixedFunction) */

    #if (!InjectionTimer_1_UsingFixedFunction)
        #if (InjectionTimer_1_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            InjectionTimer_1_AUX_CONTROLDP0 |= (InjectionTimer_1_AUX_CTRL_FIFO0_CLR);
        #else /* (InjectionTimer_1_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            InjectionTimer_1_AUX_CONTROLDP0 |= (InjectionTimer_1_AUX_CTRL_FIFO0_CLR);
            InjectionTimer_1_AUX_CONTROLDP1 |= (InjectionTimer_1_AUX_CTRL_FIFO0_CLR);
        #endif /* (InjectionTimer_1_Resolution == 8) */

        InjectionTimer_1_WriteCounter(InjectionTimer_1_INIT_PERIOD_VALUE);
    #endif /* (!InjectionTimer_1_UsingFixedFunction) */

    InjectionTimer_1_WritePeriod(InjectionTimer_1_INIT_PERIOD_VALUE);

        #if (InjectionTimer_1_UseOneCompareMode)
            InjectionTimer_1_WriteCompare(InjectionTimer_1_INIT_COMPARE_VALUE1);
        #else
            InjectionTimer_1_WriteCompare1(InjectionTimer_1_INIT_COMPARE_VALUE1);
            InjectionTimer_1_WriteCompare2(InjectionTimer_1_INIT_COMPARE_VALUE2);
        #endif /* (InjectionTimer_1_UseOneCompareMode) */

        #if (InjectionTimer_1_KillModeMinTime)
            InjectionTimer_1_WriteKillTime(InjectionTimer_1_MinimumKillTime);
        #endif /* (InjectionTimer_1_KillModeMinTime) */

        #if (InjectionTimer_1_DeadBandUsed)
            InjectionTimer_1_WriteDeadTime(InjectionTimer_1_INIT_DEAD_TIME);
        #endif /* (InjectionTimer_1_DeadBandUsed) */

    #if (InjectionTimer_1_UseStatus || InjectionTimer_1_UsingFixedFunction)
        InjectionTimer_1_SetInterruptMode(InjectionTimer_1_INIT_INTERRUPTS_MODE);
    #endif /* (InjectionTimer_1_UseStatus || InjectionTimer_1_UsingFixedFunction) */

    #if (InjectionTimer_1_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        InjectionTimer_1_GLOBAL_ENABLE |= InjectionTimer_1_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        InjectionTimer_1_CONTROL2 |= InjectionTimer_1_CTRL2_IRQ_SEL;
    #else
        #if(InjectionTimer_1_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            InjectionTimer_1_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            InjectionTimer_1_STATUS_AUX_CTRL |= InjectionTimer_1_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(InjectionTimer_1_interruptState);

            /* Clear the FIFO to enable the InjectionTimer_1_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            InjectionTimer_1_ClearFIFO();
        #endif /* (InjectionTimer_1_UseStatus) */
    #endif /* (InjectionTimer_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionTimer_1_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void InjectionTimer_1_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (InjectionTimer_1_UsingFixedFunction)
        InjectionTimer_1_GLOBAL_ENABLE |= InjectionTimer_1_BLOCK_EN_MASK;
        InjectionTimer_1_GLOBAL_STBY_ENABLE |= InjectionTimer_1_BLOCK_STBY_EN_MASK;
    #endif /* (InjectionTimer_1_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (InjectionTimer_1_UseControl || InjectionTimer_1_UsingFixedFunction)
        InjectionTimer_1_CONTROL |= InjectionTimer_1_CTRL_ENABLE;
    #endif /* (InjectionTimer_1_UseControl || InjectionTimer_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionTimer_1_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void InjectionTimer_1_Stop(void) 
{
    #if (InjectionTimer_1_UseControl || InjectionTimer_1_UsingFixedFunction)
        InjectionTimer_1_CONTROL &= ((uint8)(~InjectionTimer_1_CTRL_ENABLE));
    #endif /* (InjectionTimer_1_UseControl || InjectionTimer_1_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (InjectionTimer_1_UsingFixedFunction)
        InjectionTimer_1_GLOBAL_ENABLE &= ((uint8)(~InjectionTimer_1_BLOCK_EN_MASK));
        InjectionTimer_1_GLOBAL_STBY_ENABLE &= ((uint8)(~InjectionTimer_1_BLOCK_STBY_EN_MASK));
    #endif /* (InjectionTimer_1_UsingFixedFunction) */
}

#if (InjectionTimer_1_UseOneCompareMode)
    #if (InjectionTimer_1_CompareMode1SW)


        /*******************************************************************************
        * Function Name: InjectionTimer_1_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void InjectionTimer_1_SetCompareMode(uint8 comparemode) 
        {
            #if(InjectionTimer_1_UsingFixedFunction)

                #if(0 != InjectionTimer_1_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << InjectionTimer_1_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != InjectionTimer_1_CTRL_CMPMODE1_SHIFT) */

                InjectionTimer_1_CONTROL3 &= ((uint8)(~InjectionTimer_1_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                InjectionTimer_1_CONTROL3 |= comparemodemasked;

            #elif (InjectionTimer_1_UseControl)

                #if(0 != InjectionTimer_1_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << InjectionTimer_1_CTRL_CMPMODE1_SHIFT)) &
                                                InjectionTimer_1_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & InjectionTimer_1_CTRL_CMPMODE1_MASK;
                #endif /* (0 != InjectionTimer_1_CTRL_CMPMODE1_SHIFT) */

                #if(0 != InjectionTimer_1_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << InjectionTimer_1_CTRL_CMPMODE2_SHIFT)) &
                                               InjectionTimer_1_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & InjectionTimer_1_CTRL_CMPMODE2_MASK;
                #endif /* (0 != InjectionTimer_1_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                InjectionTimer_1_CONTROL &= ((uint8)(~(InjectionTimer_1_CTRL_CMPMODE1_MASK |
                                            InjectionTimer_1_CTRL_CMPMODE2_MASK)));
                InjectionTimer_1_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (InjectionTimer_1_UsingFixedFunction) */
        }
    #endif /* InjectionTimer_1_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (InjectionTimer_1_CompareMode1SW)


        /*******************************************************************************
        * Function Name: InjectionTimer_1_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void InjectionTimer_1_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != InjectionTimer_1_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << InjectionTimer_1_CTRL_CMPMODE1_SHIFT)) &
                                           InjectionTimer_1_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & InjectionTimer_1_CTRL_CMPMODE1_MASK;
            #endif /* (0 != InjectionTimer_1_CTRL_CMPMODE1_SHIFT) */

            #if (InjectionTimer_1_UseControl)
                InjectionTimer_1_CONTROL &= ((uint8)(~InjectionTimer_1_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                InjectionTimer_1_CONTROL |= comparemodemasked;
            #endif /* (InjectionTimer_1_UseControl) */
        }
    #endif /* InjectionTimer_1_CompareMode1SW */

#if (InjectionTimer_1_CompareMode2SW)


    /*******************************************************************************
    * Function Name: InjectionTimer_1_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void InjectionTimer_1_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != InjectionTimer_1_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << InjectionTimer_1_CTRL_CMPMODE2_SHIFT)) &
                                                 InjectionTimer_1_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & InjectionTimer_1_CTRL_CMPMODE2_MASK;
        #endif /* (0 != InjectionTimer_1_CTRL_CMPMODE2_SHIFT) */

        #if (InjectionTimer_1_UseControl)
            InjectionTimer_1_CONTROL &= ((uint8)(~InjectionTimer_1_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            InjectionTimer_1_CONTROL |= comparemodemasked;
        #endif /* (InjectionTimer_1_UseControl) */
    }
    #endif /*InjectionTimer_1_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!InjectionTimer_1_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: InjectionTimer_1_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void InjectionTimer_1_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(InjectionTimer_1_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: InjectionTimer_1_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 InjectionTimer_1_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(InjectionTimer_1_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(InjectionTimer_1_CAPTURE_LSB_PTR));
    }

    #if (InjectionTimer_1_UseStatus)


        /*******************************************************************************
        * Function Name: InjectionTimer_1_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void InjectionTimer_1_ClearFIFO(void) 
        {
            while(0u != (InjectionTimer_1_ReadStatusRegister() & InjectionTimer_1_STATUS_FIFONEMPTY))
            {
                (void)InjectionTimer_1_ReadCapture();
            }
        }

    #endif /* InjectionTimer_1_UseStatus */

#endif /* !InjectionTimer_1_UsingFixedFunction */


/*******************************************************************************
* Function Name: InjectionTimer_1_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void InjectionTimer_1_WritePeriod(uint16 period) 
{
    #if(InjectionTimer_1_UsingFixedFunction)
        CY_SET_REG16(InjectionTimer_1_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(InjectionTimer_1_PERIOD_LSB_PTR, period);
    #endif /* (InjectionTimer_1_UsingFixedFunction) */
}

#if (InjectionTimer_1_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: InjectionTimer_1_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void InjectionTimer_1_WriteCompare(uint16 compare) \
                                       
    {
        #if(InjectionTimer_1_UsingFixedFunction)
            CY_SET_REG16(InjectionTimer_1_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(InjectionTimer_1_COMPARE1_LSB_PTR, compare);
        #endif /* (InjectionTimer_1_UsingFixedFunction) */

        #if (InjectionTimer_1_PWMMode == InjectionTimer_1__B_PWM__DITHER)
            #if(InjectionTimer_1_UsingFixedFunction)
                CY_SET_REG16(InjectionTimer_1_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(InjectionTimer_1_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (InjectionTimer_1_UsingFixedFunction) */
        #endif /* (InjectionTimer_1_PWMMode == InjectionTimer_1__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: InjectionTimer_1_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void InjectionTimer_1_WriteCompare1(uint16 compare) \
                                        
    {
        #if(InjectionTimer_1_UsingFixedFunction)
            CY_SET_REG16(InjectionTimer_1_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(InjectionTimer_1_COMPARE1_LSB_PTR, compare);
        #endif /* (InjectionTimer_1_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: InjectionTimer_1_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void InjectionTimer_1_WriteCompare2(uint16 compare) \
                                        
    {
        #if(InjectionTimer_1_UsingFixedFunction)
            CY_SET_REG16(InjectionTimer_1_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(InjectionTimer_1_COMPARE2_LSB_PTR, compare);
        #endif /* (InjectionTimer_1_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (InjectionTimer_1_DeadBandUsed)


    /*******************************************************************************
    * Function Name: InjectionTimer_1_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void InjectionTimer_1_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!InjectionTimer_1_DeadBand2_4)
            CY_SET_REG8(InjectionTimer_1_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            InjectionTimer_1_DEADBAND_COUNT &= ((uint8)(~InjectionTimer_1_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(InjectionTimer_1_DEADBAND_COUNT_SHIFT)
                InjectionTimer_1_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << InjectionTimer_1_DEADBAND_COUNT_SHIFT)) &
                                                    InjectionTimer_1_DEADBAND_COUNT_MASK;
            #else
                InjectionTimer_1_DEADBAND_COUNT |= deadtime & InjectionTimer_1_DEADBAND_COUNT_MASK;
            #endif /* (InjectionTimer_1_DEADBAND_COUNT_SHIFT) */

        #endif /* (!InjectionTimer_1_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: InjectionTimer_1_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 InjectionTimer_1_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!InjectionTimer_1_DeadBand2_4)
            return (CY_GET_REG8(InjectionTimer_1_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(InjectionTimer_1_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(InjectionTimer_1_DEADBAND_COUNT & InjectionTimer_1_DEADBAND_COUNT_MASK)) >>
                                                                           InjectionTimer_1_DEADBAND_COUNT_SHIFT));
            #else
                return (InjectionTimer_1_DEADBAND_COUNT & InjectionTimer_1_DEADBAND_COUNT_MASK);
            #endif /* (InjectionTimer_1_DEADBAND_COUNT_SHIFT) */
        #endif /* (!InjectionTimer_1_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (InjectionTimer_1_UseStatus || InjectionTimer_1_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: InjectionTimer_1_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void InjectionTimer_1_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(InjectionTimer_1_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: InjectionTimer_1_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 InjectionTimer_1_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(InjectionTimer_1_STATUS_PTR));
    }

#endif /* (InjectionTimer_1_UseStatus || InjectionTimer_1_UsingFixedFunction) */


#if (InjectionTimer_1_UseControl)


    /*******************************************************************************
    * Function Name: InjectionTimer_1_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 InjectionTimer_1_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(InjectionTimer_1_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: InjectionTimer_1_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void InjectionTimer_1_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(InjectionTimer_1_CONTROL_PTR, control);
    }

#endif /* (InjectionTimer_1_UseControl) */


#if (!InjectionTimer_1_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: InjectionTimer_1_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 InjectionTimer_1_ReadCapture(void) 
    {
        return (CY_GET_REG16(InjectionTimer_1_CAPTURE_LSB_PTR));
    }

#endif /* (!InjectionTimer_1_UsingFixedFunction) */


#if (InjectionTimer_1_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: InjectionTimer_1_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 InjectionTimer_1_ReadCompare(void) 
    {
        #if(InjectionTimer_1_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(InjectionTimer_1_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(InjectionTimer_1_COMPARE1_LSB_PTR));
        #endif /* (InjectionTimer_1_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: InjectionTimer_1_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 InjectionTimer_1_ReadCompare1(void) 
    {
        return (CY_GET_REG16(InjectionTimer_1_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: InjectionTimer_1_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 InjectionTimer_1_ReadCompare2(void) 
    {
        return (CY_GET_REG16(InjectionTimer_1_COMPARE2_LSB_PTR));
    }

#endif /* (InjectionTimer_1_UseOneCompareMode) */


/*******************************************************************************
* Function Name: InjectionTimer_1_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 InjectionTimer_1_ReadPeriod(void) 
{
    #if(InjectionTimer_1_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(InjectionTimer_1_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(InjectionTimer_1_PERIOD_LSB_PTR));
    #endif /* (InjectionTimer_1_UsingFixedFunction) */
}

#if ( InjectionTimer_1_KillModeMinTime)


    /*******************************************************************************
    * Function Name: InjectionTimer_1_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void InjectionTimer_1_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(InjectionTimer_1_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: InjectionTimer_1_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 InjectionTimer_1_ReadKillTime(void) 
    {
        return (CY_GET_REG8(InjectionTimer_1_KILLMODEMINTIME_PTR));
    }

#endif /* ( InjectionTimer_1_KillModeMinTime) */

/* [] END OF FILE */
