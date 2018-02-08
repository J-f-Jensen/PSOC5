/*******************************************************************************
* File Name: InjectionTimer.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_InjectionTimer_H)
#define CY_Timer_v2_60_InjectionTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 InjectionTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define InjectionTimer_Resolution                 16u
#define InjectionTimer_UsingFixedFunction         1u
#define InjectionTimer_UsingHWCaptureCounter      0u
#define InjectionTimer_SoftwareCaptureMode        0u
#define InjectionTimer_SoftwareTriggerMode        0u
#define InjectionTimer_UsingHWEnable              0u
#define InjectionTimer_EnableTriggerMode          0u
#define InjectionTimer_InterruptOnCaptureCount    0u
#define InjectionTimer_RunModeUsed                1u
#define InjectionTimer_ControlRegRemoved          0u

#if defined(InjectionTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define InjectionTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (InjectionTimer_UsingFixedFunction)
    #define InjectionTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define InjectionTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End InjectionTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!InjectionTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (InjectionTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!InjectionTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}InjectionTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    InjectionTimer_Start(void) ;
void    InjectionTimer_Stop(void) ;

void    InjectionTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   InjectionTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define InjectionTimer_GetInterruptSource() InjectionTimer_ReadStatusRegister()

#if(!InjectionTimer_UDB_CONTROL_REG_REMOVED)
    uint8   InjectionTimer_ReadControlRegister(void) ;
    void    InjectionTimer_WriteControlRegister(uint8 control) ;
#endif /* (!InjectionTimer_UDB_CONTROL_REG_REMOVED) */

uint16  InjectionTimer_ReadPeriod(void) ;
void    InjectionTimer_WritePeriod(uint16 period) ;
uint16  InjectionTimer_ReadCounter(void) ;
void    InjectionTimer_WriteCounter(uint16 counter) ;
uint16  InjectionTimer_ReadCapture(void) ;
void    InjectionTimer_SoftwareCapture(void) ;

#if(!InjectionTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (InjectionTimer_SoftwareCaptureMode)
        void    InjectionTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!InjectionTimer_UsingFixedFunction) */

    #if (InjectionTimer_SoftwareTriggerMode)
        void    InjectionTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (InjectionTimer_SoftwareTriggerMode) */

    #if (InjectionTimer_EnableTriggerMode)
        void    InjectionTimer_EnableTrigger(void) ;
        void    InjectionTimer_DisableTrigger(void) ;
    #endif /* (InjectionTimer_EnableTriggerMode) */


    #if(InjectionTimer_InterruptOnCaptureCount)
        void    InjectionTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (InjectionTimer_InterruptOnCaptureCount) */

    #if (InjectionTimer_UsingHWCaptureCounter)
        void    InjectionTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   InjectionTimer_ReadCaptureCount(void) ;
    #endif /* (InjectionTimer_UsingHWCaptureCounter) */

    void InjectionTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void InjectionTimer_Init(void)          ;
void InjectionTimer_Enable(void)        ;
void InjectionTimer_SaveConfig(void)    ;
void InjectionTimer_RestoreConfig(void) ;
void InjectionTimer_Sleep(void)         ;
void InjectionTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define InjectionTimer__B_TIMER__CM_NONE 0
#define InjectionTimer__B_TIMER__CM_RISINGEDGE 1
#define InjectionTimer__B_TIMER__CM_FALLINGEDGE 2
#define InjectionTimer__B_TIMER__CM_EITHEREDGE 3
#define InjectionTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define InjectionTimer__B_TIMER__TM_NONE 0x00u
#define InjectionTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define InjectionTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define InjectionTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define InjectionTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define InjectionTimer_INIT_PERIOD             1u
#define InjectionTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << InjectionTimer_CTRL_CAP_MODE_SHIFT))
#define InjectionTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << InjectionTimer_CTRL_TRIG_MODE_SHIFT))
#if (InjectionTimer_UsingFixedFunction)
    #define InjectionTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << InjectionTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << InjectionTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define InjectionTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << InjectionTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << InjectionTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << InjectionTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (InjectionTimer_UsingFixedFunction) */
#define InjectionTimer_INIT_CAPTURE_COUNT      (2u)
#define InjectionTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << InjectionTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (InjectionTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define InjectionTimer_STATUS         (*(reg8 *) InjectionTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define InjectionTimer_STATUS_MASK    (*(reg8 *) InjectionTimer_TimerHW__SR0 )
    #define InjectionTimer_CONTROL        (*(reg8 *) InjectionTimer_TimerHW__CFG0)
    #define InjectionTimer_CONTROL2       (*(reg8 *) InjectionTimer_TimerHW__CFG1)
    #define InjectionTimer_CONTROL2_PTR   ( (reg8 *) InjectionTimer_TimerHW__CFG1)
    #define InjectionTimer_RT1            (*(reg8 *) InjectionTimer_TimerHW__RT1)
    #define InjectionTimer_RT1_PTR        ( (reg8 *) InjectionTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define InjectionTimer_CONTROL3       (*(reg8 *) InjectionTimer_TimerHW__CFG2)
        #define InjectionTimer_CONTROL3_PTR   ( (reg8 *) InjectionTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define InjectionTimer_GLOBAL_ENABLE  (*(reg8 *) InjectionTimer_TimerHW__PM_ACT_CFG)
    #define InjectionTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) InjectionTimer_TimerHW__PM_STBY_CFG)

    #define InjectionTimer_CAPTURE_LSB         (* (reg16 *) InjectionTimer_TimerHW__CAP0 )
    #define InjectionTimer_CAPTURE_LSB_PTR       ((reg16 *) InjectionTimer_TimerHW__CAP0 )
    #define InjectionTimer_PERIOD_LSB          (* (reg16 *) InjectionTimer_TimerHW__PER0 )
    #define InjectionTimer_PERIOD_LSB_PTR        ((reg16 *) InjectionTimer_TimerHW__PER0 )
    #define InjectionTimer_COUNTER_LSB         (* (reg16 *) InjectionTimer_TimerHW__CNT_CMP0 )
    #define InjectionTimer_COUNTER_LSB_PTR       ((reg16 *) InjectionTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define InjectionTimer_BLOCK_EN_MASK                     InjectionTimer_TimerHW__PM_ACT_MSK
    #define InjectionTimer_BLOCK_STBY_EN_MASK                InjectionTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define InjectionTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define InjectionTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define InjectionTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define InjectionTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define InjectionTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define InjectionTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << InjectionTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define InjectionTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define InjectionTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << InjectionTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define InjectionTimer_CTRL_MODE_SHIFT                 0x01u
        #define InjectionTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << InjectionTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define InjectionTimer_CTRL_RCOD_SHIFT        0x02u
        #define InjectionTimer_CTRL_ENBL_SHIFT        0x00u
        #define InjectionTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define InjectionTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << InjectionTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define InjectionTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << InjectionTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define InjectionTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << InjectionTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define InjectionTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << InjectionTimer_CTRL_RCOD_SHIFT))
        #define InjectionTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << InjectionTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define InjectionTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define InjectionTimer_RT1_MASK                        ((uint8)((uint8)0x03u << InjectionTimer_RT1_SHIFT))
    #define InjectionTimer_SYNC                            ((uint8)((uint8)0x03u << InjectionTimer_RT1_SHIFT))
    #define InjectionTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define InjectionTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << InjectionTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define InjectionTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << InjectionTimer_SYNCDSI_SHIFT))

    #define InjectionTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << InjectionTimer_CTRL_MODE_SHIFT))
    #define InjectionTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << InjectionTimer_CTRL_MODE_SHIFT))
    #define InjectionTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << InjectionTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define InjectionTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define InjectionTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define InjectionTimer_STATUS_TC_INT_MASK_SHIFT        (InjectionTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define InjectionTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (InjectionTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define InjectionTimer_STATUS_TC                       ((uint8)((uint8)0x01u << InjectionTimer_STATUS_TC_SHIFT))
    #define InjectionTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << InjectionTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define InjectionTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << InjectionTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define InjectionTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << InjectionTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define InjectionTimer_STATUS              (* (reg8 *) InjectionTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define InjectionTimer_STATUS_MASK         (* (reg8 *) InjectionTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define InjectionTimer_STATUS_AUX_CTRL     (* (reg8 *) InjectionTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define InjectionTimer_CONTROL             (* (reg8 *) InjectionTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(InjectionTimer_Resolution <= 8u) /* 8-bit Timer */
        #define InjectionTimer_CAPTURE_LSB         (* (reg8 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define InjectionTimer_CAPTURE_LSB_PTR       ((reg8 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define InjectionTimer_PERIOD_LSB          (* (reg8 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define InjectionTimer_PERIOD_LSB_PTR        ((reg8 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define InjectionTimer_COUNTER_LSB         (* (reg8 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define InjectionTimer_COUNTER_LSB_PTR       ((reg8 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(InjectionTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define InjectionTimer_CAPTURE_LSB         (* (reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define InjectionTimer_CAPTURE_LSB_PTR       ((reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define InjectionTimer_PERIOD_LSB          (* (reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define InjectionTimer_PERIOD_LSB_PTR        ((reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define InjectionTimer_COUNTER_LSB         (* (reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define InjectionTimer_COUNTER_LSB_PTR       ((reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define InjectionTimer_CAPTURE_LSB         (* (reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define InjectionTimer_CAPTURE_LSB_PTR       ((reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define InjectionTimer_PERIOD_LSB          (* (reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define InjectionTimer_PERIOD_LSB_PTR        ((reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define InjectionTimer_COUNTER_LSB         (* (reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define InjectionTimer_COUNTER_LSB_PTR       ((reg16 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(InjectionTimer_Resolution <= 24u)/* 24-bit Timer */
        #define InjectionTimer_CAPTURE_LSB         (* (reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define InjectionTimer_CAPTURE_LSB_PTR       ((reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define InjectionTimer_PERIOD_LSB          (* (reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define InjectionTimer_PERIOD_LSB_PTR        ((reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define InjectionTimer_COUNTER_LSB         (* (reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define InjectionTimer_COUNTER_LSB_PTR       ((reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define InjectionTimer_CAPTURE_LSB         (* (reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define InjectionTimer_CAPTURE_LSB_PTR       ((reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define InjectionTimer_PERIOD_LSB          (* (reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define InjectionTimer_PERIOD_LSB_PTR        ((reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define InjectionTimer_COUNTER_LSB         (* (reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define InjectionTimer_COUNTER_LSB_PTR       ((reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define InjectionTimer_CAPTURE_LSB         (* (reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define InjectionTimer_CAPTURE_LSB_PTR       ((reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define InjectionTimer_PERIOD_LSB          (* (reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define InjectionTimer_PERIOD_LSB_PTR        ((reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define InjectionTimer_COUNTER_LSB         (* (reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define InjectionTimer_COUNTER_LSB_PTR       ((reg32 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define InjectionTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) InjectionTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (InjectionTimer_UsingHWCaptureCounter)
        #define InjectionTimer_CAP_COUNT              (*(reg8 *) InjectionTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define InjectionTimer_CAP_COUNT_PTR          ( (reg8 *) InjectionTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define InjectionTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) InjectionTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define InjectionTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) InjectionTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (InjectionTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define InjectionTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define InjectionTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define InjectionTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define InjectionTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define InjectionTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define InjectionTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << InjectionTimer_CTRL_INTCNT_SHIFT))
    #define InjectionTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << InjectionTimer_CTRL_TRIG_MODE_SHIFT))
    #define InjectionTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << InjectionTimer_CTRL_TRIG_EN_SHIFT))
    #define InjectionTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << InjectionTimer_CTRL_CAP_MODE_SHIFT))
    #define InjectionTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << InjectionTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define InjectionTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define InjectionTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define InjectionTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define InjectionTimer_STATUS_TC_INT_MASK_SHIFT       InjectionTimer_STATUS_TC_SHIFT
    #define InjectionTimer_STATUS_CAPTURE_INT_MASK_SHIFT  InjectionTimer_STATUS_CAPTURE_SHIFT
    #define InjectionTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define InjectionTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define InjectionTimer_STATUS_FIFOFULL_INT_MASK_SHIFT InjectionTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define InjectionTimer_STATUS_TC                      ((uint8)((uint8)0x01u << InjectionTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define InjectionTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << InjectionTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define InjectionTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << InjectionTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define InjectionTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << InjectionTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define InjectionTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << InjectionTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define InjectionTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << InjectionTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define InjectionTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << InjectionTimer_STATUS_FIFOFULL_SHIFT))

    #define InjectionTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define InjectionTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define InjectionTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define InjectionTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define InjectionTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define InjectionTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_InjectionTimer_H */


/* [] END OF FILE */
