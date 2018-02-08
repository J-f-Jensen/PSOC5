/*******************************************************************************
* File Name: IgnitionCounter_2.c  
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

#include "IgnitionCounter_2.h"

uint8 IgnitionCounter_2_initVar = 0u;


/*******************************************************************************
* Function Name: IgnitionCounter_2_Init
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
void IgnitionCounter_2_Init(void) 
{
        #if (!IgnitionCounter_2_UsingFixedFunction && !IgnitionCounter_2_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!IgnitionCounter_2_UsingFixedFunction && !IgnitionCounter_2_ControlRegRemoved) */
        
        #if(!IgnitionCounter_2_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 IgnitionCounter_2_interruptState;
        #endif /* (!IgnitionCounter_2_UsingFixedFunction) */
        
        #if (IgnitionCounter_2_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            IgnitionCounter_2_CONTROL &= IgnitionCounter_2_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                IgnitionCounter_2_CONTROL2 &= ((uint8)(~IgnitionCounter_2_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                IgnitionCounter_2_CONTROL3 &= ((uint8)(~IgnitionCounter_2_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (IgnitionCounter_2_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                IgnitionCounter_2_CONTROL |= IgnitionCounter_2_ONESHOT;
            #endif /* (IgnitionCounter_2_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            IgnitionCounter_2_CONTROL2 |= IgnitionCounter_2_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            IgnitionCounter_2_RT1 &= ((uint8)(~IgnitionCounter_2_RT1_MASK));
            IgnitionCounter_2_RT1 |= IgnitionCounter_2_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            IgnitionCounter_2_RT1 &= ((uint8)(~IgnitionCounter_2_SYNCDSI_MASK));
            IgnitionCounter_2_RT1 |= IgnitionCounter_2_SYNCDSI_EN;

        #else
            #if(!IgnitionCounter_2_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = IgnitionCounter_2_CONTROL & ((uint8)(~IgnitionCounter_2_CTRL_CMPMODE_MASK));
            IgnitionCounter_2_CONTROL = ctrl | IgnitionCounter_2_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = IgnitionCounter_2_CONTROL & ((uint8)(~IgnitionCounter_2_CTRL_CAPMODE_MASK));
            
            #if( 0 != IgnitionCounter_2_CAPTURE_MODE_CONF)
                IgnitionCounter_2_CONTROL = ctrl | IgnitionCounter_2_DEFAULT_CAPTURE_MODE;
            #else
                IgnitionCounter_2_CONTROL = ctrl;
            #endif /* 0 != IgnitionCounter_2_CAPTURE_MODE */ 
            
            #endif /* (!IgnitionCounter_2_ControlRegRemoved) */
        #endif /* (IgnitionCounter_2_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!IgnitionCounter_2_UsingFixedFunction)
            IgnitionCounter_2_ClearFIFO();
        #endif /* (!IgnitionCounter_2_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        IgnitionCounter_2_WritePeriod(IgnitionCounter_2_INIT_PERIOD_VALUE);
        #if (!(IgnitionCounter_2_UsingFixedFunction && (CY_PSOC5A)))
            IgnitionCounter_2_WriteCounter(IgnitionCounter_2_INIT_COUNTER_VALUE);
        #endif /* (!(IgnitionCounter_2_UsingFixedFunction && (CY_PSOC5A))) */
        IgnitionCounter_2_SetInterruptMode(IgnitionCounter_2_INIT_INTERRUPTS_MASK);
        
        #if (!IgnitionCounter_2_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)IgnitionCounter_2_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            IgnitionCounter_2_WriteCompare(IgnitionCounter_2_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            IgnitionCounter_2_interruptState = CyEnterCriticalSection();
            
            IgnitionCounter_2_STATUS_AUX_CTRL |= IgnitionCounter_2_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(IgnitionCounter_2_interruptState);
            
        #endif /* (!IgnitionCounter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_Enable
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
void IgnitionCounter_2_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (IgnitionCounter_2_UsingFixedFunction)
        IgnitionCounter_2_GLOBAL_ENABLE |= IgnitionCounter_2_BLOCK_EN_MASK;
        IgnitionCounter_2_GLOBAL_STBY_ENABLE |= IgnitionCounter_2_BLOCK_STBY_EN_MASK;
    #endif /* (IgnitionCounter_2_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!IgnitionCounter_2_ControlRegRemoved || IgnitionCounter_2_UsingFixedFunction)
        IgnitionCounter_2_CONTROL |= IgnitionCounter_2_CTRL_ENABLE;                
    #endif /* (!IgnitionCounter_2_ControlRegRemoved || IgnitionCounter_2_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_Start
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
*  IgnitionCounter_2_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void IgnitionCounter_2_Start(void) 
{
    if(IgnitionCounter_2_initVar == 0u)
    {
        IgnitionCounter_2_Init();
        
        IgnitionCounter_2_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    IgnitionCounter_2_Enable();        
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_Stop
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
void IgnitionCounter_2_Stop(void) 
{
    /* Disable Counter */
    #if(!IgnitionCounter_2_ControlRegRemoved || IgnitionCounter_2_UsingFixedFunction)
        IgnitionCounter_2_CONTROL &= ((uint8)(~IgnitionCounter_2_CTRL_ENABLE));        
    #endif /* (!IgnitionCounter_2_ControlRegRemoved || IgnitionCounter_2_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (IgnitionCounter_2_UsingFixedFunction)
        IgnitionCounter_2_GLOBAL_ENABLE &= ((uint8)(~IgnitionCounter_2_BLOCK_EN_MASK));
        IgnitionCounter_2_GLOBAL_STBY_ENABLE &= ((uint8)(~IgnitionCounter_2_BLOCK_STBY_EN_MASK));
    #endif /* (IgnitionCounter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_SetInterruptMode
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
void IgnitionCounter_2_SetInterruptMode(uint8 interruptsMask) 
{
    IgnitionCounter_2_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_ReadStatusRegister
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
uint8   IgnitionCounter_2_ReadStatusRegister(void) 
{
    return IgnitionCounter_2_STATUS;
}


#if(!IgnitionCounter_2_ControlRegRemoved)
/*******************************************************************************
* Function Name: IgnitionCounter_2_ReadControlRegister
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
uint8   IgnitionCounter_2_ReadControlRegister(void) 
{
    return IgnitionCounter_2_CONTROL;
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_WriteControlRegister
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
void    IgnitionCounter_2_WriteControlRegister(uint8 control) 
{
    IgnitionCounter_2_CONTROL = control;
}

#endif  /* (!IgnitionCounter_2_ControlRegRemoved) */


#if (!(IgnitionCounter_2_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: IgnitionCounter_2_WriteCounter
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
void IgnitionCounter_2_WriteCounter(uint16 counter) \
                                   
{
    #if(IgnitionCounter_2_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (IgnitionCounter_2_GLOBAL_ENABLE & IgnitionCounter_2_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        IgnitionCounter_2_GLOBAL_ENABLE |= IgnitionCounter_2_BLOCK_EN_MASK;
        CY_SET_REG16(IgnitionCounter_2_COUNTER_LSB_PTR, (uint16)counter);
        IgnitionCounter_2_GLOBAL_ENABLE &= ((uint8)(~IgnitionCounter_2_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(IgnitionCounter_2_COUNTER_LSB_PTR, counter);
    #endif /* (IgnitionCounter_2_UsingFixedFunction) */
}
#endif /* (!(IgnitionCounter_2_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: IgnitionCounter_2_ReadCounter
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
uint16 IgnitionCounter_2_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(IgnitionCounter_2_UsingFixedFunction)
		(void)CY_GET_REG16(IgnitionCounter_2_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(IgnitionCounter_2_COUNTER_LSB_PTR_8BIT);
	#endif/* (IgnitionCounter_2_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(IgnitionCounter_2_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(IgnitionCounter_2_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(IgnitionCounter_2_STATICCOUNT_LSB_PTR));
    #endif /* (IgnitionCounter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_ReadCapture
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
uint16 IgnitionCounter_2_ReadCapture(void) 
{
    #if(IgnitionCounter_2_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(IgnitionCounter_2_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(IgnitionCounter_2_STATICCOUNT_LSB_PTR));
    #endif /* (IgnitionCounter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_WritePeriod
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
void IgnitionCounter_2_WritePeriod(uint16 period) 
{
    #if(IgnitionCounter_2_UsingFixedFunction)
        CY_SET_REG16(IgnitionCounter_2_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(IgnitionCounter_2_PERIOD_LSB_PTR, period);
    #endif /* (IgnitionCounter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_ReadPeriod
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
uint16 IgnitionCounter_2_ReadPeriod(void) 
{
    #if(IgnitionCounter_2_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(IgnitionCounter_2_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(IgnitionCounter_2_PERIOD_LSB_PTR));
    #endif /* (IgnitionCounter_2_UsingFixedFunction) */
}


#if (!IgnitionCounter_2_UsingFixedFunction)
/*******************************************************************************
* Function Name: IgnitionCounter_2_WriteCompare
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
void IgnitionCounter_2_WriteCompare(uint16 compare) \
                                   
{
    #if(IgnitionCounter_2_UsingFixedFunction)
        CY_SET_REG16(IgnitionCounter_2_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(IgnitionCounter_2_COMPARE_LSB_PTR, compare);
    #endif /* (IgnitionCounter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: IgnitionCounter_2_ReadCompare
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
uint16 IgnitionCounter_2_ReadCompare(void) 
{
    return (CY_GET_REG16(IgnitionCounter_2_COMPARE_LSB_PTR));
}


#if (IgnitionCounter_2_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: IgnitionCounter_2_SetCompareMode
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
void IgnitionCounter_2_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    IgnitionCounter_2_CONTROL &= ((uint8)(~IgnitionCounter_2_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    IgnitionCounter_2_CONTROL |= compareMode;
}
#endif  /* (IgnitionCounter_2_COMPARE_MODE_SOFTWARE) */


#if (IgnitionCounter_2_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: IgnitionCounter_2_SetCaptureMode
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
void IgnitionCounter_2_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    IgnitionCounter_2_CONTROL &= ((uint8)(~IgnitionCounter_2_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    IgnitionCounter_2_CONTROL |= ((uint8)((uint8)captureMode << IgnitionCounter_2_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (IgnitionCounter_2_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: IgnitionCounter_2_ClearFIFO
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
void IgnitionCounter_2_ClearFIFO(void) 
{

    while(0u != (IgnitionCounter_2_ReadStatusRegister() & IgnitionCounter_2_STATUS_FIFONEMP))
    {
        (void)IgnitionCounter_2_ReadCapture();
    }

}
#endif  /* (!IgnitionCounter_2_UsingFixedFunction) */


/* [] END OF FILE */

