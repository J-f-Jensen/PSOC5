/*******************************************************************************
* File Name: Millis_Counter.c  
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

#include "Millis_Counter.h"

uint8 Millis_Counter_initVar = 0u;


/*******************************************************************************
* Function Name: Millis_Counter_Init
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
void Millis_Counter_Init(void) 
{
        #if (!Millis_Counter_UsingFixedFunction && !Millis_Counter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!Millis_Counter_UsingFixedFunction && !Millis_Counter_ControlRegRemoved) */
        
        #if(!Millis_Counter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 Millis_Counter_interruptState;
        #endif /* (!Millis_Counter_UsingFixedFunction) */
        
        #if (Millis_Counter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            Millis_Counter_CONTROL &= Millis_Counter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                Millis_Counter_CONTROL2 &= ((uint8)(~Millis_Counter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                Millis_Counter_CONTROL3 &= ((uint8)(~Millis_Counter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (Millis_Counter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                Millis_Counter_CONTROL |= Millis_Counter_ONESHOT;
            #endif /* (Millis_Counter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            Millis_Counter_CONTROL2 |= Millis_Counter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            Millis_Counter_RT1 &= ((uint8)(~Millis_Counter_RT1_MASK));
            Millis_Counter_RT1 |= Millis_Counter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            Millis_Counter_RT1 &= ((uint8)(~Millis_Counter_SYNCDSI_MASK));
            Millis_Counter_RT1 |= Millis_Counter_SYNCDSI_EN;

        #else
            #if(!Millis_Counter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = Millis_Counter_CONTROL & ((uint8)(~Millis_Counter_CTRL_CMPMODE_MASK));
            Millis_Counter_CONTROL = ctrl | Millis_Counter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = Millis_Counter_CONTROL & ((uint8)(~Millis_Counter_CTRL_CAPMODE_MASK));
            
            #if( 0 != Millis_Counter_CAPTURE_MODE_CONF)
                Millis_Counter_CONTROL = ctrl | Millis_Counter_DEFAULT_CAPTURE_MODE;
            #else
                Millis_Counter_CONTROL = ctrl;
            #endif /* 0 != Millis_Counter_CAPTURE_MODE */ 
            
            #endif /* (!Millis_Counter_ControlRegRemoved) */
        #endif /* (Millis_Counter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!Millis_Counter_UsingFixedFunction)
            Millis_Counter_ClearFIFO();
        #endif /* (!Millis_Counter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        Millis_Counter_WritePeriod(Millis_Counter_INIT_PERIOD_VALUE);
        #if (!(Millis_Counter_UsingFixedFunction && (CY_PSOC5A)))
            Millis_Counter_WriteCounter(Millis_Counter_INIT_COUNTER_VALUE);
        #endif /* (!(Millis_Counter_UsingFixedFunction && (CY_PSOC5A))) */
        Millis_Counter_SetInterruptMode(Millis_Counter_INIT_INTERRUPTS_MASK);
        
        #if (!Millis_Counter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)Millis_Counter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            Millis_Counter_WriteCompare(Millis_Counter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Millis_Counter_interruptState = CyEnterCriticalSection();
            
            Millis_Counter_STATUS_AUX_CTRL |= Millis_Counter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(Millis_Counter_interruptState);
            
        #endif /* (!Millis_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Millis_Counter_Enable
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
void Millis_Counter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Millis_Counter_UsingFixedFunction)
        Millis_Counter_GLOBAL_ENABLE |= Millis_Counter_BLOCK_EN_MASK;
        Millis_Counter_GLOBAL_STBY_ENABLE |= Millis_Counter_BLOCK_STBY_EN_MASK;
    #endif /* (Millis_Counter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!Millis_Counter_ControlRegRemoved || Millis_Counter_UsingFixedFunction)
        Millis_Counter_CONTROL |= Millis_Counter_CTRL_ENABLE;                
    #endif /* (!Millis_Counter_ControlRegRemoved || Millis_Counter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: Millis_Counter_Start
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
*  Millis_Counter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Millis_Counter_Start(void) 
{
    if(Millis_Counter_initVar == 0u)
    {
        Millis_Counter_Init();
        
        Millis_Counter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    Millis_Counter_Enable();        
}


/*******************************************************************************
* Function Name: Millis_Counter_Stop
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
void Millis_Counter_Stop(void) 
{
    /* Disable Counter */
    #if(!Millis_Counter_ControlRegRemoved || Millis_Counter_UsingFixedFunction)
        Millis_Counter_CONTROL &= ((uint8)(~Millis_Counter_CTRL_ENABLE));        
    #endif /* (!Millis_Counter_ControlRegRemoved || Millis_Counter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (Millis_Counter_UsingFixedFunction)
        Millis_Counter_GLOBAL_ENABLE &= ((uint8)(~Millis_Counter_BLOCK_EN_MASK));
        Millis_Counter_GLOBAL_STBY_ENABLE &= ((uint8)(~Millis_Counter_BLOCK_STBY_EN_MASK));
    #endif /* (Millis_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Millis_Counter_SetInterruptMode
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
void Millis_Counter_SetInterruptMode(uint8 interruptsMask) 
{
    Millis_Counter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: Millis_Counter_ReadStatusRegister
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
uint8   Millis_Counter_ReadStatusRegister(void) 
{
    return Millis_Counter_STATUS;
}


#if(!Millis_Counter_ControlRegRemoved)
/*******************************************************************************
* Function Name: Millis_Counter_ReadControlRegister
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
uint8   Millis_Counter_ReadControlRegister(void) 
{
    return Millis_Counter_CONTROL;
}


/*******************************************************************************
* Function Name: Millis_Counter_WriteControlRegister
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
void    Millis_Counter_WriteControlRegister(uint8 control) 
{
    Millis_Counter_CONTROL = control;
}

#endif  /* (!Millis_Counter_ControlRegRemoved) */


#if (!(Millis_Counter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: Millis_Counter_WriteCounter
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
void Millis_Counter_WriteCounter(uint32 counter) \
                                   
{
    #if(Millis_Counter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (Millis_Counter_GLOBAL_ENABLE & Millis_Counter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        Millis_Counter_GLOBAL_ENABLE |= Millis_Counter_BLOCK_EN_MASK;
        CY_SET_REG16(Millis_Counter_COUNTER_LSB_PTR, (uint16)counter);
        Millis_Counter_GLOBAL_ENABLE &= ((uint8)(~Millis_Counter_BLOCK_EN_MASK));
    #else
        CY_SET_REG32(Millis_Counter_COUNTER_LSB_PTR, counter);
    #endif /* (Millis_Counter_UsingFixedFunction) */
}
#endif /* (!(Millis_Counter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: Millis_Counter_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) The present value of the counter.
*
*******************************************************************************/
uint32 Millis_Counter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(Millis_Counter_UsingFixedFunction)
		(void)CY_GET_REG16(Millis_Counter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(Millis_Counter_COUNTER_LSB_PTR_8BIT);
	#endif/* (Millis_Counter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(Millis_Counter_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Millis_Counter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(Millis_Counter_STATICCOUNT_LSB_PTR));
    #endif /* (Millis_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Millis_Counter_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint32) Present Capture value.
*
*******************************************************************************/
uint32 Millis_Counter_ReadCapture(void) 
{
    #if(Millis_Counter_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Millis_Counter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(Millis_Counter_STATICCOUNT_LSB_PTR));
    #endif /* (Millis_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Millis_Counter_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint32) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void Millis_Counter_WritePeriod(uint32 period) 
{
    #if(Millis_Counter_UsingFixedFunction)
        CY_SET_REG16(Millis_Counter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(Millis_Counter_PERIOD_LSB_PTR, period);
    #endif /* (Millis_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Millis_Counter_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) Present period value.
*
*******************************************************************************/
uint32 Millis_Counter_ReadPeriod(void) 
{
    #if(Millis_Counter_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Millis_Counter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG32(Millis_Counter_PERIOD_LSB_PTR));
    #endif /* (Millis_Counter_UsingFixedFunction) */
}


#if (!Millis_Counter_UsingFixedFunction)
/*******************************************************************************
* Function Name: Millis_Counter_WriteCompare
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
void Millis_Counter_WriteCompare(uint32 compare) \
                                   
{
    #if(Millis_Counter_UsingFixedFunction)
        CY_SET_REG16(Millis_Counter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG32(Millis_Counter_COMPARE_LSB_PTR, compare);
    #endif /* (Millis_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Millis_Counter_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint32) Present compare value.
*
*******************************************************************************/
uint32 Millis_Counter_ReadCompare(void) 
{
    return (CY_GET_REG32(Millis_Counter_COMPARE_LSB_PTR));
}


#if (Millis_Counter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Millis_Counter_SetCompareMode
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
void Millis_Counter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    Millis_Counter_CONTROL &= ((uint8)(~Millis_Counter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    Millis_Counter_CONTROL |= compareMode;
}
#endif  /* (Millis_Counter_COMPARE_MODE_SOFTWARE) */


#if (Millis_Counter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Millis_Counter_SetCaptureMode
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
void Millis_Counter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    Millis_Counter_CONTROL &= ((uint8)(~Millis_Counter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    Millis_Counter_CONTROL |= ((uint8)((uint8)captureMode << Millis_Counter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (Millis_Counter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: Millis_Counter_ClearFIFO
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
void Millis_Counter_ClearFIFO(void) 
{

    while(0u != (Millis_Counter_ReadStatusRegister() & Millis_Counter_STATUS_FIFONEMP))
    {
        (void)Millis_Counter_ReadCapture();
    }

}
#endif  /* (!Millis_Counter_UsingFixedFunction) */


/* [] END OF FILE */

