/*******************************************************************************
* File Name: ServoCounter.c  
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

#include "ServoCounter.h"

uint8 ServoCounter_initVar = 0u;


/*******************************************************************************
* Function Name: ServoCounter_Init
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
void ServoCounter_Init(void) 
{
        #if (!ServoCounter_UsingFixedFunction && !ServoCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!ServoCounter_UsingFixedFunction && !ServoCounter_ControlRegRemoved) */
        
        #if(!ServoCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 ServoCounter_interruptState;
        #endif /* (!ServoCounter_UsingFixedFunction) */
        
        #if (ServoCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            ServoCounter_CONTROL &= ServoCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                ServoCounter_CONTROL2 &= ((uint8)(~ServoCounter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                ServoCounter_CONTROL3 &= ((uint8)(~ServoCounter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (ServoCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                ServoCounter_CONTROL |= ServoCounter_ONESHOT;
            #endif /* (ServoCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            ServoCounter_CONTROL2 |= ServoCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            ServoCounter_RT1 &= ((uint8)(~ServoCounter_RT1_MASK));
            ServoCounter_RT1 |= ServoCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            ServoCounter_RT1 &= ((uint8)(~ServoCounter_SYNCDSI_MASK));
            ServoCounter_RT1 |= ServoCounter_SYNCDSI_EN;

        #else
            #if(!ServoCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = ServoCounter_CONTROL & ((uint8)(~ServoCounter_CTRL_CMPMODE_MASK));
            ServoCounter_CONTROL = ctrl | ServoCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = ServoCounter_CONTROL & ((uint8)(~ServoCounter_CTRL_CAPMODE_MASK));
            
            #if( 0 != ServoCounter_CAPTURE_MODE_CONF)
                ServoCounter_CONTROL = ctrl | ServoCounter_DEFAULT_CAPTURE_MODE;
            #else
                ServoCounter_CONTROL = ctrl;
            #endif /* 0 != ServoCounter_CAPTURE_MODE */ 
            
            #endif /* (!ServoCounter_ControlRegRemoved) */
        #endif /* (ServoCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!ServoCounter_UsingFixedFunction)
            ServoCounter_ClearFIFO();
        #endif /* (!ServoCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        ServoCounter_WritePeriod(ServoCounter_INIT_PERIOD_VALUE);
        #if (!(ServoCounter_UsingFixedFunction && (CY_PSOC5A)))
            ServoCounter_WriteCounter(ServoCounter_INIT_COUNTER_VALUE);
        #endif /* (!(ServoCounter_UsingFixedFunction && (CY_PSOC5A))) */
        ServoCounter_SetInterruptMode(ServoCounter_INIT_INTERRUPTS_MASK);
        
        #if (!ServoCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)ServoCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            ServoCounter_WriteCompare(ServoCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ServoCounter_interruptState = CyEnterCriticalSection();
            
            ServoCounter_STATUS_AUX_CTRL |= ServoCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(ServoCounter_interruptState);
            
        #endif /* (!ServoCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCounter_Enable
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
void ServoCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ServoCounter_UsingFixedFunction)
        ServoCounter_GLOBAL_ENABLE |= ServoCounter_BLOCK_EN_MASK;
        ServoCounter_GLOBAL_STBY_ENABLE |= ServoCounter_BLOCK_STBY_EN_MASK;
    #endif /* (ServoCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!ServoCounter_ControlRegRemoved || ServoCounter_UsingFixedFunction)
        ServoCounter_CONTROL |= ServoCounter_CTRL_ENABLE;                
    #endif /* (!ServoCounter_ControlRegRemoved || ServoCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: ServoCounter_Start
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
*  ServoCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ServoCounter_Start(void) 
{
    if(ServoCounter_initVar == 0u)
    {
        ServoCounter_Init();
        
        ServoCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    ServoCounter_Enable();        
}


/*******************************************************************************
* Function Name: ServoCounter_Stop
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
void ServoCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!ServoCounter_ControlRegRemoved || ServoCounter_UsingFixedFunction)
        ServoCounter_CONTROL &= ((uint8)(~ServoCounter_CTRL_ENABLE));        
    #endif /* (!ServoCounter_ControlRegRemoved || ServoCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (ServoCounter_UsingFixedFunction)
        ServoCounter_GLOBAL_ENABLE &= ((uint8)(~ServoCounter_BLOCK_EN_MASK));
        ServoCounter_GLOBAL_STBY_ENABLE &= ((uint8)(~ServoCounter_BLOCK_STBY_EN_MASK));
    #endif /* (ServoCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCounter_SetInterruptMode
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
void ServoCounter_SetInterruptMode(uint8 interruptsMask) 
{
    ServoCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: ServoCounter_ReadStatusRegister
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
uint8   ServoCounter_ReadStatusRegister(void) 
{
    return ServoCounter_STATUS;
}


#if(!ServoCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: ServoCounter_ReadControlRegister
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
uint8   ServoCounter_ReadControlRegister(void) 
{
    return ServoCounter_CONTROL;
}


/*******************************************************************************
* Function Name: ServoCounter_WriteControlRegister
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
void    ServoCounter_WriteControlRegister(uint8 control) 
{
    ServoCounter_CONTROL = control;
}

#endif  /* (!ServoCounter_ControlRegRemoved) */


#if (!(ServoCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: ServoCounter_WriteCounter
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
void ServoCounter_WriteCounter(uint16 counter) \
                                   
{
    #if(ServoCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (ServoCounter_GLOBAL_ENABLE & ServoCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        ServoCounter_GLOBAL_ENABLE |= ServoCounter_BLOCK_EN_MASK;
        CY_SET_REG16(ServoCounter_COUNTER_LSB_PTR, (uint16)counter);
        ServoCounter_GLOBAL_ENABLE &= ((uint8)(~ServoCounter_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(ServoCounter_COUNTER_LSB_PTR, counter);
    #endif /* (ServoCounter_UsingFixedFunction) */
}
#endif /* (!(ServoCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: ServoCounter_ReadCounter
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
uint16 ServoCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(ServoCounter_UsingFixedFunction)
		(void)CY_GET_REG16(ServoCounter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(ServoCounter_COUNTER_LSB_PTR_8BIT);
	#endif/* (ServoCounter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(ServoCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ServoCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(ServoCounter_STATICCOUNT_LSB_PTR));
    #endif /* (ServoCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCounter_ReadCapture
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
uint16 ServoCounter_ReadCapture(void) 
{
    #if(ServoCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ServoCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(ServoCounter_STATICCOUNT_LSB_PTR));
    #endif /* (ServoCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCounter_WritePeriod
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
void ServoCounter_WritePeriod(uint16 period) 
{
    #if(ServoCounter_UsingFixedFunction)
        CY_SET_REG16(ServoCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(ServoCounter_PERIOD_LSB_PTR, period);
    #endif /* (ServoCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCounter_ReadPeriod
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
uint16 ServoCounter_ReadPeriod(void) 
{
    #if(ServoCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ServoCounter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(ServoCounter_PERIOD_LSB_PTR));
    #endif /* (ServoCounter_UsingFixedFunction) */
}


#if (!ServoCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: ServoCounter_WriteCompare
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
void ServoCounter_WriteCompare(uint16 compare) \
                                   
{
    #if(ServoCounter_UsingFixedFunction)
        CY_SET_REG16(ServoCounter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(ServoCounter_COMPARE_LSB_PTR, compare);
    #endif /* (ServoCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCounter_ReadCompare
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
uint16 ServoCounter_ReadCompare(void) 
{
    return (CY_GET_REG16(ServoCounter_COMPARE_LSB_PTR));
}


#if (ServoCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ServoCounter_SetCompareMode
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
void ServoCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    ServoCounter_CONTROL &= ((uint8)(~ServoCounter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    ServoCounter_CONTROL |= compareMode;
}
#endif  /* (ServoCounter_COMPARE_MODE_SOFTWARE) */


#if (ServoCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ServoCounter_SetCaptureMode
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
void ServoCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    ServoCounter_CONTROL &= ((uint8)(~ServoCounter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    ServoCounter_CONTROL |= ((uint8)((uint8)captureMode << ServoCounter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (ServoCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: ServoCounter_ClearFIFO
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
void ServoCounter_ClearFIFO(void) 
{

    while(0u != (ServoCounter_ReadStatusRegister() & ServoCounter_STATUS_FIFONEMP))
    {
        (void)ServoCounter_ReadCapture();
    }

}
#endif  /* (!ServoCounter_UsingFixedFunction) */


/* [] END OF FILE */

