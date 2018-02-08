/*******************************************************************************
* File Name: CrankTriggerCaptureCounter.c  
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

#include "CrankTriggerCaptureCounter.h"

uint8 CrankTriggerCaptureCounter_initVar = 0u;


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_Init
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
void CrankTriggerCaptureCounter_Init(void) 
{
        #if (!CrankTriggerCaptureCounter_UsingFixedFunction && !CrankTriggerCaptureCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CrankTriggerCaptureCounter_UsingFixedFunction && !CrankTriggerCaptureCounter_ControlRegRemoved) */
        
        #if(!CrankTriggerCaptureCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CrankTriggerCaptureCounter_interruptState;
        #endif /* (!CrankTriggerCaptureCounter_UsingFixedFunction) */
        
        #if (CrankTriggerCaptureCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CrankTriggerCaptureCounter_CONTROL &= CrankTriggerCaptureCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CrankTriggerCaptureCounter_CONTROL2 &= ((uint8)(~CrankTriggerCaptureCounter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CrankTriggerCaptureCounter_CONTROL3 &= ((uint8)(~CrankTriggerCaptureCounter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CrankTriggerCaptureCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CrankTriggerCaptureCounter_CONTROL |= CrankTriggerCaptureCounter_ONESHOT;
            #endif /* (CrankTriggerCaptureCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CrankTriggerCaptureCounter_CONTROL2 |= CrankTriggerCaptureCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CrankTriggerCaptureCounter_RT1 &= ((uint8)(~CrankTriggerCaptureCounter_RT1_MASK));
            CrankTriggerCaptureCounter_RT1 |= CrankTriggerCaptureCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CrankTriggerCaptureCounter_RT1 &= ((uint8)(~CrankTriggerCaptureCounter_SYNCDSI_MASK));
            CrankTriggerCaptureCounter_RT1 |= CrankTriggerCaptureCounter_SYNCDSI_EN;

        #else
            #if(!CrankTriggerCaptureCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CrankTriggerCaptureCounter_CONTROL & ((uint8)(~CrankTriggerCaptureCounter_CTRL_CMPMODE_MASK));
            CrankTriggerCaptureCounter_CONTROL = ctrl | CrankTriggerCaptureCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CrankTriggerCaptureCounter_CONTROL & ((uint8)(~CrankTriggerCaptureCounter_CTRL_CAPMODE_MASK));
            
            #if( 0 != CrankTriggerCaptureCounter_CAPTURE_MODE_CONF)
                CrankTriggerCaptureCounter_CONTROL = ctrl | CrankTriggerCaptureCounter_DEFAULT_CAPTURE_MODE;
            #else
                CrankTriggerCaptureCounter_CONTROL = ctrl;
            #endif /* 0 != CrankTriggerCaptureCounter_CAPTURE_MODE */ 
            
            #endif /* (!CrankTriggerCaptureCounter_ControlRegRemoved) */
        #endif /* (CrankTriggerCaptureCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CrankTriggerCaptureCounter_UsingFixedFunction)
            CrankTriggerCaptureCounter_ClearFIFO();
        #endif /* (!CrankTriggerCaptureCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CrankTriggerCaptureCounter_WritePeriod(CrankTriggerCaptureCounter_INIT_PERIOD_VALUE);
        #if (!(CrankTriggerCaptureCounter_UsingFixedFunction && (CY_PSOC5A)))
            CrankTriggerCaptureCounter_WriteCounter(CrankTriggerCaptureCounter_INIT_COUNTER_VALUE);
        #endif /* (!(CrankTriggerCaptureCounter_UsingFixedFunction && (CY_PSOC5A))) */
        CrankTriggerCaptureCounter_SetInterruptMode(CrankTriggerCaptureCounter_INIT_INTERRUPTS_MASK);
        
        #if (!CrankTriggerCaptureCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)CrankTriggerCaptureCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CrankTriggerCaptureCounter_WriteCompare(CrankTriggerCaptureCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CrankTriggerCaptureCounter_interruptState = CyEnterCriticalSection();
            
            CrankTriggerCaptureCounter_STATUS_AUX_CTRL |= CrankTriggerCaptureCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CrankTriggerCaptureCounter_interruptState);
            
        #endif /* (!CrankTriggerCaptureCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_Enable
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
void CrankTriggerCaptureCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CrankTriggerCaptureCounter_UsingFixedFunction)
        CrankTriggerCaptureCounter_GLOBAL_ENABLE |= CrankTriggerCaptureCounter_BLOCK_EN_MASK;
        CrankTriggerCaptureCounter_GLOBAL_STBY_ENABLE |= CrankTriggerCaptureCounter_BLOCK_STBY_EN_MASK;
    #endif /* (CrankTriggerCaptureCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CrankTriggerCaptureCounter_ControlRegRemoved || CrankTriggerCaptureCounter_UsingFixedFunction)
        CrankTriggerCaptureCounter_CONTROL |= CrankTriggerCaptureCounter_CTRL_ENABLE;                
    #endif /* (!CrankTriggerCaptureCounter_ControlRegRemoved || CrankTriggerCaptureCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_Start
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
*  CrankTriggerCaptureCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CrankTriggerCaptureCounter_Start(void) 
{
    if(CrankTriggerCaptureCounter_initVar == 0u)
    {
        CrankTriggerCaptureCounter_Init();
        
        CrankTriggerCaptureCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CrankTriggerCaptureCounter_Enable();        
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_Stop
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
void CrankTriggerCaptureCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!CrankTriggerCaptureCounter_ControlRegRemoved || CrankTriggerCaptureCounter_UsingFixedFunction)
        CrankTriggerCaptureCounter_CONTROL &= ((uint8)(~CrankTriggerCaptureCounter_CTRL_ENABLE));        
    #endif /* (!CrankTriggerCaptureCounter_ControlRegRemoved || CrankTriggerCaptureCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CrankTriggerCaptureCounter_UsingFixedFunction)
        CrankTriggerCaptureCounter_GLOBAL_ENABLE &= ((uint8)(~CrankTriggerCaptureCounter_BLOCK_EN_MASK));
        CrankTriggerCaptureCounter_GLOBAL_STBY_ENABLE &= ((uint8)(~CrankTriggerCaptureCounter_BLOCK_STBY_EN_MASK));
    #endif /* (CrankTriggerCaptureCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_SetInterruptMode
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
void CrankTriggerCaptureCounter_SetInterruptMode(uint8 interruptsMask) 
{
    CrankTriggerCaptureCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_ReadStatusRegister
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
uint8   CrankTriggerCaptureCounter_ReadStatusRegister(void) 
{
    return CrankTriggerCaptureCounter_STATUS;
}


#if(!CrankTriggerCaptureCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_ReadControlRegister
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
uint8   CrankTriggerCaptureCounter_ReadControlRegister(void) 
{
    return CrankTriggerCaptureCounter_CONTROL;
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_WriteControlRegister
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
void    CrankTriggerCaptureCounter_WriteControlRegister(uint8 control) 
{
    CrankTriggerCaptureCounter_CONTROL = control;
}

#endif  /* (!CrankTriggerCaptureCounter_ControlRegRemoved) */


#if (!(CrankTriggerCaptureCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_WriteCounter
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
void CrankTriggerCaptureCounter_WriteCounter(uint16 counter) \
                                   
{
    #if(CrankTriggerCaptureCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (CrankTriggerCaptureCounter_GLOBAL_ENABLE & CrankTriggerCaptureCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CrankTriggerCaptureCounter_GLOBAL_ENABLE |= CrankTriggerCaptureCounter_BLOCK_EN_MASK;
        CY_SET_REG16(CrankTriggerCaptureCounter_COUNTER_LSB_PTR, (uint16)counter);
        CrankTriggerCaptureCounter_GLOBAL_ENABLE &= ((uint8)(~CrankTriggerCaptureCounter_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(CrankTriggerCaptureCounter_COUNTER_LSB_PTR, counter);
    #endif /* (CrankTriggerCaptureCounter_UsingFixedFunction) */
}
#endif /* (!(CrankTriggerCaptureCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_ReadCounter
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
uint16 CrankTriggerCaptureCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(CrankTriggerCaptureCounter_UsingFixedFunction)
		(void)CY_GET_REG16(CrankTriggerCaptureCounter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(CrankTriggerCaptureCounter_COUNTER_LSB_PTR_8BIT);
	#endif/* (CrankTriggerCaptureCounter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(CrankTriggerCaptureCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(CrankTriggerCaptureCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(CrankTriggerCaptureCounter_STATICCOUNT_LSB_PTR));
    #endif /* (CrankTriggerCaptureCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_ReadCapture
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
uint16 CrankTriggerCaptureCounter_ReadCapture(void) 
{
    #if(CrankTriggerCaptureCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(CrankTriggerCaptureCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(CrankTriggerCaptureCounter_STATICCOUNT_LSB_PTR));
    #endif /* (CrankTriggerCaptureCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_WritePeriod
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
void CrankTriggerCaptureCounter_WritePeriod(uint16 period) 
{
    #if(CrankTriggerCaptureCounter_UsingFixedFunction)
        CY_SET_REG16(CrankTriggerCaptureCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(CrankTriggerCaptureCounter_PERIOD_LSB_PTR, period);
    #endif /* (CrankTriggerCaptureCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_ReadPeriod
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
uint16 CrankTriggerCaptureCounter_ReadPeriod(void) 
{
    #if(CrankTriggerCaptureCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(CrankTriggerCaptureCounter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(CrankTriggerCaptureCounter_PERIOD_LSB_PTR));
    #endif /* (CrankTriggerCaptureCounter_UsingFixedFunction) */
}


#if (!CrankTriggerCaptureCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_WriteCompare
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
void CrankTriggerCaptureCounter_WriteCompare(uint16 compare) \
                                   
{
    #if(CrankTriggerCaptureCounter_UsingFixedFunction)
        CY_SET_REG16(CrankTriggerCaptureCounter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(CrankTriggerCaptureCounter_COMPARE_LSB_PTR, compare);
    #endif /* (CrankTriggerCaptureCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_ReadCompare
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
uint16 CrankTriggerCaptureCounter_ReadCompare(void) 
{
    return (CY_GET_REG16(CrankTriggerCaptureCounter_COMPARE_LSB_PTR));
}


#if (CrankTriggerCaptureCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_SetCompareMode
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
void CrankTriggerCaptureCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CrankTriggerCaptureCounter_CONTROL &= ((uint8)(~CrankTriggerCaptureCounter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    CrankTriggerCaptureCounter_CONTROL |= compareMode;
}
#endif  /* (CrankTriggerCaptureCounter_COMPARE_MODE_SOFTWARE) */


#if (CrankTriggerCaptureCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_SetCaptureMode
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
void CrankTriggerCaptureCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CrankTriggerCaptureCounter_CONTROL &= ((uint8)(~CrankTriggerCaptureCounter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    CrankTriggerCaptureCounter_CONTROL |= ((uint8)((uint8)captureMode << CrankTriggerCaptureCounter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (CrankTriggerCaptureCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CrankTriggerCaptureCounter_ClearFIFO
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
void CrankTriggerCaptureCounter_ClearFIFO(void) 
{

    while(0u != (CrankTriggerCaptureCounter_ReadStatusRegister() & CrankTriggerCaptureCounter_STATUS_FIFONEMP))
    {
        (void)CrankTriggerCaptureCounter_ReadCapture();
    }

}
#endif  /* (!CrankTriggerCaptureCounter_UsingFixedFunction) */


/* [] END OF FILE */

