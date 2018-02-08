/*******************************************************************************
* File Name: CrankTriggerCaptureCounter_old.h
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

#if !defined(CY_Timer_v2_60_CrankTriggerCaptureCounter_old_H)
#define CY_Timer_v2_60_CrankTriggerCaptureCounter_old_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 CrankTriggerCaptureCounter_old_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define CrankTriggerCaptureCounter_old_Resolution                 16u
#define CrankTriggerCaptureCounter_old_UsingFixedFunction         0u
#define CrankTriggerCaptureCounter_old_UsingHWCaptureCounter      0u
#define CrankTriggerCaptureCounter_old_SoftwareCaptureMode        0u
#define CrankTriggerCaptureCounter_old_SoftwareTriggerMode        0u
#define CrankTriggerCaptureCounter_old_UsingHWEnable              0u
#define CrankTriggerCaptureCounter_old_EnableTriggerMode          0u
#define CrankTriggerCaptureCounter_old_InterruptOnCaptureCount    1u
#define CrankTriggerCaptureCounter_old_RunModeUsed                2u
#define CrankTriggerCaptureCounter_old_ControlRegRemoved          0u

#if defined(CrankTriggerCaptureCounter_old_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define CrankTriggerCaptureCounter_old_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (CrankTriggerCaptureCounter_old_UsingFixedFunction)
    #define CrankTriggerCaptureCounter_old_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define CrankTriggerCaptureCounter_old_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End CrankTriggerCaptureCounter_old_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!CrankTriggerCaptureCounter_old_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (CrankTriggerCaptureCounter_old_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!CrankTriggerCaptureCounter_old_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}CrankTriggerCaptureCounter_old_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    CrankTriggerCaptureCounter_old_Start(void) ;
void    CrankTriggerCaptureCounter_old_Stop(void) ;

void    CrankTriggerCaptureCounter_old_SetInterruptMode(uint8 interruptMode) ;
uint8   CrankTriggerCaptureCounter_old_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define CrankTriggerCaptureCounter_old_GetInterruptSource() CrankTriggerCaptureCounter_old_ReadStatusRegister()

#if(!CrankTriggerCaptureCounter_old_UDB_CONTROL_REG_REMOVED)
    uint8   CrankTriggerCaptureCounter_old_ReadControlRegister(void) ;
    void    CrankTriggerCaptureCounter_old_WriteControlRegister(uint8 control) ;
#endif /* (!CrankTriggerCaptureCounter_old_UDB_CONTROL_REG_REMOVED) */

uint16  CrankTriggerCaptureCounter_old_ReadPeriod(void) ;
void    CrankTriggerCaptureCounter_old_WritePeriod(uint16 period) ;
uint16  CrankTriggerCaptureCounter_old_ReadCounter(void) ;
void    CrankTriggerCaptureCounter_old_WriteCounter(uint16 counter) ;
uint16  CrankTriggerCaptureCounter_old_ReadCapture(void) ;
void    CrankTriggerCaptureCounter_old_SoftwareCapture(void) ;

#if(!CrankTriggerCaptureCounter_old_UsingFixedFunction) /* UDB Prototypes */
    #if (CrankTriggerCaptureCounter_old_SoftwareCaptureMode)
        void    CrankTriggerCaptureCounter_old_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!CrankTriggerCaptureCounter_old_UsingFixedFunction) */

    #if (CrankTriggerCaptureCounter_old_SoftwareTriggerMode)
        void    CrankTriggerCaptureCounter_old_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (CrankTriggerCaptureCounter_old_SoftwareTriggerMode) */

    #if (CrankTriggerCaptureCounter_old_EnableTriggerMode)
        void    CrankTriggerCaptureCounter_old_EnableTrigger(void) ;
        void    CrankTriggerCaptureCounter_old_DisableTrigger(void) ;
    #endif /* (CrankTriggerCaptureCounter_old_EnableTriggerMode) */


    #if(CrankTriggerCaptureCounter_old_InterruptOnCaptureCount)
        void    CrankTriggerCaptureCounter_old_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (CrankTriggerCaptureCounter_old_InterruptOnCaptureCount) */

    #if (CrankTriggerCaptureCounter_old_UsingHWCaptureCounter)
        void    CrankTriggerCaptureCounter_old_SetCaptureCount(uint8 captureCount) ;
        uint8   CrankTriggerCaptureCounter_old_ReadCaptureCount(void) ;
    #endif /* (CrankTriggerCaptureCounter_old_UsingHWCaptureCounter) */

    void CrankTriggerCaptureCounter_old_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void CrankTriggerCaptureCounter_old_Init(void)          ;
void CrankTriggerCaptureCounter_old_Enable(void)        ;
void CrankTriggerCaptureCounter_old_SaveConfig(void)    ;
void CrankTriggerCaptureCounter_old_RestoreConfig(void) ;
void CrankTriggerCaptureCounter_old_Sleep(void)         ;
void CrankTriggerCaptureCounter_old_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define CrankTriggerCaptureCounter_old__B_TIMER__CM_NONE 0
#define CrankTriggerCaptureCounter_old__B_TIMER__CM_RISINGEDGE 1
#define CrankTriggerCaptureCounter_old__B_TIMER__CM_FALLINGEDGE 2
#define CrankTriggerCaptureCounter_old__B_TIMER__CM_EITHEREDGE 3
#define CrankTriggerCaptureCounter_old__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define CrankTriggerCaptureCounter_old__B_TIMER__TM_NONE 0x00u
#define CrankTriggerCaptureCounter_old__B_TIMER__TM_RISINGEDGE 0x04u
#define CrankTriggerCaptureCounter_old__B_TIMER__TM_FALLINGEDGE 0x08u
#define CrankTriggerCaptureCounter_old__B_TIMER__TM_EITHEREDGE 0x0Cu
#define CrankTriggerCaptureCounter_old__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define CrankTriggerCaptureCounter_old_INIT_PERIOD             65535u
#define CrankTriggerCaptureCounter_old_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << CrankTriggerCaptureCounter_old_CTRL_CAP_MODE_SHIFT))
#define CrankTriggerCaptureCounter_old_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << CrankTriggerCaptureCounter_old_CTRL_TRIG_MODE_SHIFT))
#if (CrankTriggerCaptureCounter_old_UsingFixedFunction)
    #define CrankTriggerCaptureCounter_old_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << CrankTriggerCaptureCounter_old_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)1 << CrankTriggerCaptureCounter_old_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define CrankTriggerCaptureCounter_old_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << CrankTriggerCaptureCounter_old_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)1 << CrankTriggerCaptureCounter_old_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << CrankTriggerCaptureCounter_old_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (CrankTriggerCaptureCounter_old_UsingFixedFunction) */
#define CrankTriggerCaptureCounter_old_INIT_CAPTURE_COUNT      (2u)
#define CrankTriggerCaptureCounter_old_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << CrankTriggerCaptureCounter_old_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (CrankTriggerCaptureCounter_old_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define CrankTriggerCaptureCounter_old_STATUS         (*(reg8 *) CrankTriggerCaptureCounter_old_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define CrankTriggerCaptureCounter_old_STATUS_MASK    (*(reg8 *) CrankTriggerCaptureCounter_old_TimerHW__SR0 )
    #define CrankTriggerCaptureCounter_old_CONTROL        (*(reg8 *) CrankTriggerCaptureCounter_old_TimerHW__CFG0)
    #define CrankTriggerCaptureCounter_old_CONTROL2       (*(reg8 *) CrankTriggerCaptureCounter_old_TimerHW__CFG1)
    #define CrankTriggerCaptureCounter_old_CONTROL2_PTR   ( (reg8 *) CrankTriggerCaptureCounter_old_TimerHW__CFG1)
    #define CrankTriggerCaptureCounter_old_RT1            (*(reg8 *) CrankTriggerCaptureCounter_old_TimerHW__RT1)
    #define CrankTriggerCaptureCounter_old_RT1_PTR        ( (reg8 *) CrankTriggerCaptureCounter_old_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define CrankTriggerCaptureCounter_old_CONTROL3       (*(reg8 *) CrankTriggerCaptureCounter_old_TimerHW__CFG2)
        #define CrankTriggerCaptureCounter_old_CONTROL3_PTR   ( (reg8 *) CrankTriggerCaptureCounter_old_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define CrankTriggerCaptureCounter_old_GLOBAL_ENABLE  (*(reg8 *) CrankTriggerCaptureCounter_old_TimerHW__PM_ACT_CFG)
    #define CrankTriggerCaptureCounter_old_GLOBAL_STBY_ENABLE  (*(reg8 *) CrankTriggerCaptureCounter_old_TimerHW__PM_STBY_CFG)

    #define CrankTriggerCaptureCounter_old_CAPTURE_LSB         (* (reg16 *) CrankTriggerCaptureCounter_old_TimerHW__CAP0 )
    #define CrankTriggerCaptureCounter_old_CAPTURE_LSB_PTR       ((reg16 *) CrankTriggerCaptureCounter_old_TimerHW__CAP0 )
    #define CrankTriggerCaptureCounter_old_PERIOD_LSB          (* (reg16 *) CrankTriggerCaptureCounter_old_TimerHW__PER0 )
    #define CrankTriggerCaptureCounter_old_PERIOD_LSB_PTR        ((reg16 *) CrankTriggerCaptureCounter_old_TimerHW__PER0 )
    #define CrankTriggerCaptureCounter_old_COUNTER_LSB         (* (reg16 *) CrankTriggerCaptureCounter_old_TimerHW__CNT_CMP0 )
    #define CrankTriggerCaptureCounter_old_COUNTER_LSB_PTR       ((reg16 *) CrankTriggerCaptureCounter_old_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define CrankTriggerCaptureCounter_old_BLOCK_EN_MASK                     CrankTriggerCaptureCounter_old_TimerHW__PM_ACT_MSK
    #define CrankTriggerCaptureCounter_old_BLOCK_STBY_EN_MASK                CrankTriggerCaptureCounter_old_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define CrankTriggerCaptureCounter_old_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define CrankTriggerCaptureCounter_old_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define CrankTriggerCaptureCounter_old_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define CrankTriggerCaptureCounter_old_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define CrankTriggerCaptureCounter_old_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define CrankTriggerCaptureCounter_old_CTRL_ENABLE                        ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define CrankTriggerCaptureCounter_old_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define CrankTriggerCaptureCounter_old_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define CrankTriggerCaptureCounter_old_CTRL_MODE_SHIFT                 0x01u
        #define CrankTriggerCaptureCounter_old_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << CrankTriggerCaptureCounter_old_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define CrankTriggerCaptureCounter_old_CTRL_RCOD_SHIFT        0x02u
        #define CrankTriggerCaptureCounter_old_CTRL_ENBL_SHIFT        0x00u
        #define CrankTriggerCaptureCounter_old_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define CrankTriggerCaptureCounter_old_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << CrankTriggerCaptureCounter_old_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define CrankTriggerCaptureCounter_old_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << CrankTriggerCaptureCounter_old_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define CrankTriggerCaptureCounter_old_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << CrankTriggerCaptureCounter_old_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define CrankTriggerCaptureCounter_old_CTRL_RCOD       ((uint8)((uint8)0x03u << CrankTriggerCaptureCounter_old_CTRL_RCOD_SHIFT))
        #define CrankTriggerCaptureCounter_old_CTRL_ENBL       ((uint8)((uint8)0x80u << CrankTriggerCaptureCounter_old_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define CrankTriggerCaptureCounter_old_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define CrankTriggerCaptureCounter_old_RT1_MASK                        ((uint8)((uint8)0x03u << CrankTriggerCaptureCounter_old_RT1_SHIFT))
    #define CrankTriggerCaptureCounter_old_SYNC                            ((uint8)((uint8)0x03u << CrankTriggerCaptureCounter_old_RT1_SHIFT))
    #define CrankTriggerCaptureCounter_old_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define CrankTriggerCaptureCounter_old_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << CrankTriggerCaptureCounter_old_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define CrankTriggerCaptureCounter_old_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << CrankTriggerCaptureCounter_old_SYNCDSI_SHIFT))

    #define CrankTriggerCaptureCounter_old_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_CTRL_MODE_SHIFT))
    #define CrankTriggerCaptureCounter_old_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << CrankTriggerCaptureCounter_old_CTRL_MODE_SHIFT))
    #define CrankTriggerCaptureCounter_old_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << CrankTriggerCaptureCounter_old_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define CrankTriggerCaptureCounter_old_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define CrankTriggerCaptureCounter_old_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define CrankTriggerCaptureCounter_old_STATUS_TC_INT_MASK_SHIFT        (CrankTriggerCaptureCounter_old_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define CrankTriggerCaptureCounter_old_STATUS_CAPTURE_INT_MASK_SHIFT   (CrankTriggerCaptureCounter_old_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define CrankTriggerCaptureCounter_old_STATUS_TC                       ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_TC_SHIFT))
    #define CrankTriggerCaptureCounter_old_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define CrankTriggerCaptureCounter_old_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define CrankTriggerCaptureCounter_old_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define CrankTriggerCaptureCounter_old_STATUS              (* (reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define CrankTriggerCaptureCounter_old_STATUS_MASK         (* (reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_rstSts_stsreg__MASK_REG)
    #define CrankTriggerCaptureCounter_old_STATUS_AUX_CTRL     (* (reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CrankTriggerCaptureCounter_old_CONTROL             (* (reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(CrankTriggerCaptureCounter_old_Resolution <= 8u) /* 8-bit Timer */
        #define CrankTriggerCaptureCounter_old_CAPTURE_LSB         (* (reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define CrankTriggerCaptureCounter_old_CAPTURE_LSB_PTR       ((reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define CrankTriggerCaptureCounter_old_PERIOD_LSB          (* (reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define CrankTriggerCaptureCounter_old_PERIOD_LSB_PTR        ((reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define CrankTriggerCaptureCounter_old_COUNTER_LSB         (* (reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define CrankTriggerCaptureCounter_old_COUNTER_LSB_PTR       ((reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(CrankTriggerCaptureCounter_old_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define CrankTriggerCaptureCounter_old_CAPTURE_LSB         (* (reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define CrankTriggerCaptureCounter_old_CAPTURE_LSB_PTR       ((reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define CrankTriggerCaptureCounter_old_PERIOD_LSB          (* (reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define CrankTriggerCaptureCounter_old_PERIOD_LSB_PTR        ((reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define CrankTriggerCaptureCounter_old_COUNTER_LSB         (* (reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define CrankTriggerCaptureCounter_old_COUNTER_LSB_PTR       ((reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define CrankTriggerCaptureCounter_old_CAPTURE_LSB         (* (reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define CrankTriggerCaptureCounter_old_CAPTURE_LSB_PTR       ((reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define CrankTriggerCaptureCounter_old_PERIOD_LSB          (* (reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define CrankTriggerCaptureCounter_old_PERIOD_LSB_PTR        ((reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define CrankTriggerCaptureCounter_old_COUNTER_LSB         (* (reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define CrankTriggerCaptureCounter_old_COUNTER_LSB_PTR       ((reg16 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(CrankTriggerCaptureCounter_old_Resolution <= 24u)/* 24-bit Timer */
        #define CrankTriggerCaptureCounter_old_CAPTURE_LSB         (* (reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define CrankTriggerCaptureCounter_old_CAPTURE_LSB_PTR       ((reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define CrankTriggerCaptureCounter_old_PERIOD_LSB          (* (reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define CrankTriggerCaptureCounter_old_PERIOD_LSB_PTR        ((reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define CrankTriggerCaptureCounter_old_COUNTER_LSB         (* (reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define CrankTriggerCaptureCounter_old_COUNTER_LSB_PTR       ((reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define CrankTriggerCaptureCounter_old_CAPTURE_LSB         (* (reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define CrankTriggerCaptureCounter_old_CAPTURE_LSB_PTR       ((reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define CrankTriggerCaptureCounter_old_PERIOD_LSB          (* (reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define CrankTriggerCaptureCounter_old_PERIOD_LSB_PTR        ((reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define CrankTriggerCaptureCounter_old_COUNTER_LSB         (* (reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define CrankTriggerCaptureCounter_old_COUNTER_LSB_PTR       ((reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define CrankTriggerCaptureCounter_old_CAPTURE_LSB         (* (reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define CrankTriggerCaptureCounter_old_CAPTURE_LSB_PTR       ((reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define CrankTriggerCaptureCounter_old_PERIOD_LSB          (* (reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define CrankTriggerCaptureCounter_old_PERIOD_LSB_PTR        ((reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define CrankTriggerCaptureCounter_old_COUNTER_LSB         (* (reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define CrankTriggerCaptureCounter_old_COUNTER_LSB_PTR       ((reg32 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define CrankTriggerCaptureCounter_old_COUNTER_LSB_PTR_8BIT       ((reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (CrankTriggerCaptureCounter_old_UsingHWCaptureCounter)
        #define CrankTriggerCaptureCounter_old_CAP_COUNT              (*(reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define CrankTriggerCaptureCounter_old_CAP_COUNT_PTR          ( (reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define CrankTriggerCaptureCounter_old_CAPTURE_COUNT_CTRL     (*(reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define CrankTriggerCaptureCounter_old_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) CrankTriggerCaptureCounter_old_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (CrankTriggerCaptureCounter_old_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define CrankTriggerCaptureCounter_old_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define CrankTriggerCaptureCounter_old_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define CrankTriggerCaptureCounter_old_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define CrankTriggerCaptureCounter_old_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define CrankTriggerCaptureCounter_old_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define CrankTriggerCaptureCounter_old_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << CrankTriggerCaptureCounter_old_CTRL_INTCNT_SHIFT))
    #define CrankTriggerCaptureCounter_old_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << CrankTriggerCaptureCounter_old_CTRL_TRIG_MODE_SHIFT))
    #define CrankTriggerCaptureCounter_old_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_CTRL_TRIG_EN_SHIFT))
    #define CrankTriggerCaptureCounter_old_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << CrankTriggerCaptureCounter_old_CTRL_CAP_MODE_SHIFT))
    #define CrankTriggerCaptureCounter_old_CTRL_ENABLE                    ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define CrankTriggerCaptureCounter_old_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define CrankTriggerCaptureCounter_old_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define CrankTriggerCaptureCounter_old_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define CrankTriggerCaptureCounter_old_STATUS_TC_INT_MASK_SHIFT       CrankTriggerCaptureCounter_old_STATUS_TC_SHIFT
    #define CrankTriggerCaptureCounter_old_STATUS_CAPTURE_INT_MASK_SHIFT  CrankTriggerCaptureCounter_old_STATUS_CAPTURE_SHIFT
    #define CrankTriggerCaptureCounter_old_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define CrankTriggerCaptureCounter_old_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define CrankTriggerCaptureCounter_old_STATUS_FIFOFULL_INT_MASK_SHIFT CrankTriggerCaptureCounter_old_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define CrankTriggerCaptureCounter_old_STATUS_TC                      ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define CrankTriggerCaptureCounter_old_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define CrankTriggerCaptureCounter_old_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define CrankTriggerCaptureCounter_old_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define CrankTriggerCaptureCounter_old_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define CrankTriggerCaptureCounter_old_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define CrankTriggerCaptureCounter_old_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << CrankTriggerCaptureCounter_old_STATUS_FIFOFULL_SHIFT))

    #define CrankTriggerCaptureCounter_old_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define CrankTriggerCaptureCounter_old_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define CrankTriggerCaptureCounter_old_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define CrankTriggerCaptureCounter_old_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define CrankTriggerCaptureCounter_old_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define CrankTriggerCaptureCounter_old_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_CrankTriggerCaptureCounter_old_H */


/* [] END OF FILE */
