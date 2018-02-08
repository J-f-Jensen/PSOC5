/*******************************************************************************
* File Name: InjectionCounter_1.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

#include "InjectionCounter_1.h"

uint8 InjectionCounter_1_initVar = 0u;


/*******************************************************************************
* Function Name: InjectionCounter_1_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void InjectionCounter_1_Init(void) 
{
        #if (!InjectionCounter_1_UsingFixedFunction && !InjectionCounter_1_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!InjectionCounter_1_UsingFixedFunction && !InjectionCounter_1_ControlRegRemoved) */
        
        #if(!InjectionCounter_1_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 InjectionCounter_1_interruptState;
        #endif /* (!InjectionCounter_1_UsingFixedFunction) */
        
        #if (InjectionCounter_1_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            InjectionCounter_1_CONTROL &= InjectionCounter_1_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                InjectionCounter_1_CONTROL2 &= ((uint8)(~InjectionCounter_1_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                InjectionCounter_1_CONTROL3 &= ((uint8)(~InjectionCounter_1_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (InjectionCounter_1_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                InjectionCounter_1_CONTROL |= InjectionCounter_1_ONESHOT;
            #endif /* (InjectionCounter_1_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            InjectionCounter_1_CONTROL2 |= InjectionCounter_1_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            InjectionCounter_1_RT1 &= ((uint8)(~InjectionCounter_1_RT1_MASK));
            InjectionCounter_1_RT1 |= InjectionCounter_1_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            InjectionCounter_1_RT1 &= ((uint8)(~InjectionCounter_1_SYNCDSI_MASK));
            InjectionCounter_1_RT1 |= InjectionCounter_1_SYNCDSI_EN;

        #else
            #if(!InjectionCounter_1_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = InjectionCounter_1_CONTROL & ((uint8)(~InjectionCounter_1_CTRL_CMPMODE_MASK));
            InjectionCounter_1_CONTROL = ctrl | InjectionCounter_1_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = InjectionCounter_1_CONTROL & ((uint8)(~InjectionCounter_1_CTRL_CAPMODE_MASK));
            
            #if( 0 != InjectionCounter_1_CAPTURE_MODE_CONF)
                InjectionCounter_1_CONTROL = ctrl | InjectionCounter_1_DEFAULT_CAPTURE_MODE;
            #else
                InjectionCounter_1_CONTROL = ctrl;
            #endif /* 0 != InjectionCounter_1_CAPTURE_MODE */ 
            
            #endif /* (!InjectionCounter_1_ControlRegRemoved) */
        #endif /* (InjectionCounter_1_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!InjectionCounter_1_UsingFixedFunction)
            InjectionCounter_1_ClearFIFO();
        #endif /* (!InjectionCounter_1_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        InjectionCounter_1_WritePeriod(InjectionCounter_1_INIT_PERIOD_VALUE);
        #if (!(InjectionCounter_1_UsingFixedFunction && (CY_PSOC5A)))
            InjectionCounter_1_WriteCounter(InjectionCounter_1_INIT_COUNTER_VALUE);
        #endif /* (!(InjectionCounter_1_UsingFixedFunction && (CY_PSOC5A))) */
        InjectionCounter_1_SetInterruptMode(InjectionCounter_1_INIT_INTERRUPTS_MASK);
        
        #if (!InjectionCounter_1_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)InjectionCounter_1_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            InjectionCounter_1_WriteCompare(InjectionCounter_1_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            InjectionCounter_1_interruptState = CyEnterCriticalSection();
            
            InjectionCounter_1_STATUS_AUX_CTRL |= InjectionCounter_1_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(InjectionCounter_1_interruptState);
            
        #endif /* (!InjectionCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionCounter_1_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void InjectionCounter_1_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (InjectionCounter_1_UsingFixedFunction)
        InjectionCounter_1_GLOBAL_ENABLE |= InjectionCounter_1_BLOCK_EN_MASK;
        InjectionCounter_1_GLOBAL_STBY_ENABLE |= InjectionCounter_1_BLOCK_STBY_EN_MASK;
    #endif /* (InjectionCounter_1_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!InjectionCounter_1_ControlRegRemoved || InjectionCounter_1_UsingFixedFunction)
        InjectionCounter_1_CONTROL |= InjectionCounter_1_CTRL_ENABLE;                
    #endif /* (!InjectionCounter_1_ControlRegRemoved || InjectionCounter_1_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: InjectionCounter_1_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  InjectionCounter_1_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void InjectionCounter_1_Start(void) 
{
    if(InjectionCounter_1_initVar == 0u)
    {
        InjectionCounter_1_Init();
        
        InjectionCounter_1_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    InjectionCounter_1_Enable();        
}


/*******************************************************************************
* Function Name: InjectionCounter_1_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void InjectionCounter_1_Stop(void) 
{
    /* Disable Counter */
    #if(!InjectionCounter_1_ControlRegRemoved || InjectionCounter_1_UsingFixedFunction)
        InjectionCounter_1_CONTROL &= ((uint8)(~InjectionCounter_1_CTRL_ENABLE));        
    #endif /* (!InjectionCounter_1_ControlRegRemoved || InjectionCounter_1_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (InjectionCounter_1_UsingFixedFunction)
        InjectionCounter_1_GLOBAL_ENABLE &= ((uint8)(~InjectionCounter_1_BLOCK_EN_MASK));
        InjectionCounter_1_GLOBAL_STBY_ENABLE &= ((uint8)(~InjectionCounter_1_BLOCK_STBY_EN_MASK));
    #endif /* (InjectionCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionCounter_1_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void InjectionCounter_1_SetInterruptMode(uint8 interruptsMask) 
{
    InjectionCounter_1_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: InjectionCounter_1_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   InjectionCounter_1_ReadStatusRegister(void) 
{
    return InjectionCounter_1_STATUS;
}


#if(!InjectionCounter_1_ControlRegRemoved)
/*******************************************************************************
* Function Name: InjectionCounter_1_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   InjectionCounter_1_ReadControlRegister(void) 
{
    return InjectionCounter_1_CONTROL;
}


/*******************************************************************************
* Function Name: InjectionCounter_1_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    InjectionCounter_1_WriteControlRegister(uint8 control) 
{
    InjectionCounter_1_CONTROL = control;
}

#endif  /* (!InjectionCounter_1_ControlRegRemoved) */


#if (!(InjectionCounter_1_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: InjectionCounter_1_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void InjectionCounter_1_WriteCounter(uint16 counter) \
                                   
{
    #if(InjectionCounter_1_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (InjectionCounter_1_GLOBAL_ENABLE & InjectionCounter_1_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        InjectionCounter_1_GLOBAL_ENABLE |= InjectionCounter_1_BLOCK_EN_MASK;
        CY_SET_REG16(InjectionCounter_1_COUNTER_LSB_PTR, (uint16)counter);
        InjectionCounter_1_GLOBAL_ENABLE &= ((uint8)(~InjectionCounter_1_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(InjectionCounter_1_COUNTER_LSB_PTR, counter);
    #endif /* (InjectionCounter_1_UsingFixedFunction) */
}
#endif /* (!(InjectionCounter_1_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: InjectionCounter_1_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 InjectionCounter_1_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(InjectionCounter_1_UsingFixedFunction)
		(void)CY_GET_REG16(InjectionCounter_1_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(InjectionCounter_1_COUNTER_LSB_PTR_8BIT);
	#endif/* (InjectionCounter_1_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(InjectionCounter_1_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(InjectionCounter_1_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(InjectionCounter_1_STATICCOUNT_LSB_PTR));
    #endif /* (InjectionCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionCounter_1_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 InjectionCounter_1_ReadCapture(void) 
{
    #if(InjectionCounter_1_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(InjectionCounter_1_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(InjectionCounter_1_STATICCOUNT_LSB_PTR));
    #endif /* (InjectionCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionCounter_1_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void InjectionCounter_1_WritePeriod(uint16 period) 
{
    #if(InjectionCounter_1_UsingFixedFunction)
        CY_SET_REG16(InjectionCounter_1_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(InjectionCounter_1_PERIOD_LSB_PTR, period);
    #endif /* (InjectionCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionCounter_1_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 InjectionCounter_1_ReadPeriod(void) 
{
    #if(InjectionCounter_1_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(InjectionCounter_1_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(InjectionCounter_1_PERIOD_LSB_PTR));
    #endif /* (InjectionCounter_1_UsingFixedFunction) */
}


#if (!InjectionCounter_1_UsingFixedFunction)
/*******************************************************************************
* Function Name: InjectionCounter_1_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void InjectionCounter_1_WriteCompare(uint16 compare) \
                                   
{
    #if(InjectionCounter_1_UsingFixedFunction)
        CY_SET_REG16(InjectionCounter_1_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(InjectionCounter_1_COMPARE_LSB_PTR, compare);
    #endif /* (InjectionCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: InjectionCounter_1_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 InjectionCounter_1_ReadCompare(void) 
{
    return (CY_GET_REG16(InjectionCounter_1_COMPARE_LSB_PTR));
}


#if (InjectionCounter_1_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: InjectionCounter_1_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void InjectionCounter_1_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    InjectionCounter_1_CONTROL &= ((uint8)(~InjectionCounter_1_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    InjectionCounter_1_CONTROL |= compareMode;
}
#endif  /* (InjectionCounter_1_COMPARE_MODE_SOFTWARE) */


#if (InjectionCounter_1_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: InjectionCounter_1_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void InjectionCounter_1_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    InjectionCounter_1_CONTROL &= ((uint8)(~InjectionCounter_1_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    InjectionCounter_1_CONTROL |= ((uint8)((uint8)captureMode << InjectionCounter_1_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (InjectionCounter_1_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: InjectionCounter_1_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void InjectionCounter_1_ClearFIFO(void) 
{

    while(0u != (InjectionCounter_1_ReadStatusRegister() & InjectionCounter_1_STATUS_FIFONEMP))
    {
        (void)InjectionCounter_1_ReadCapture();
    }

}
#endif  /* (!InjectionCounter_1_UsingFixedFunction) */


/* [] END OF FILE */

