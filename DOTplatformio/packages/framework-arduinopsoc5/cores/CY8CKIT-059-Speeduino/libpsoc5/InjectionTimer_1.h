/*******************************************************************************
* File Name: InjectionTimer_1.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_InjectionTimer_1_H)
#define CY_PWM_InjectionTimer_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 InjectionTimer_1_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define InjectionTimer_1_Resolution                     (16u)
#define InjectionTimer_1_UsingFixedFunction             (0u)
#define InjectionTimer_1_DeadBandMode                   (0u)
#define InjectionTimer_1_KillModeMinTime                (0u)
#define InjectionTimer_1_KillMode                       (0u)
#define InjectionTimer_1_PWMMode                        (0u)
#define InjectionTimer_1_PWMModeIsCenterAligned         (0u)
#define InjectionTimer_1_DeadBandUsed                   (0u)
#define InjectionTimer_1_DeadBand2_4                    (0u)

#if !defined(InjectionTimer_1_PWMUDB_genblk8_stsreg__REMOVED)
    #define InjectionTimer_1_UseStatus                  (1u)
#else
    #define InjectionTimer_1_UseStatus                  (0u)
#endif /* !defined(InjectionTimer_1_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(InjectionTimer_1_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define InjectionTimer_1_UseControl                 (1u)
#else
    #define InjectionTimer_1_UseControl                 (0u)
#endif /* !defined(InjectionTimer_1_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define InjectionTimer_1_UseOneCompareMode              (1u)
#define InjectionTimer_1_MinimumKillTime                (1u)
#define InjectionTimer_1_EnableMode                     (0u)

#define InjectionTimer_1_CompareMode1SW                 (0u)
#define InjectionTimer_1_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define InjectionTimer_1__B_PWM__DISABLED 0
#define InjectionTimer_1__B_PWM__ASYNCHRONOUS 1
#define InjectionTimer_1__B_PWM__SINGLECYCLE 2
#define InjectionTimer_1__B_PWM__LATCHED 3
#define InjectionTimer_1__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define InjectionTimer_1__B_PWM__DBMDISABLED 0
#define InjectionTimer_1__B_PWM__DBM_2_4_CLOCKS 1
#define InjectionTimer_1__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define InjectionTimer_1__B_PWM__ONE_OUTPUT 0
#define InjectionTimer_1__B_PWM__TWO_OUTPUTS 1
#define InjectionTimer_1__B_PWM__DUAL_EDGE 2
#define InjectionTimer_1__B_PWM__CENTER_ALIGN 3
#define InjectionTimer_1__B_PWM__DITHER 5
#define InjectionTimer_1__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define InjectionTimer_1__B_PWM__LESS_THAN 1
#define InjectionTimer_1__B_PWM__LESS_THAN_OR_EQUAL 2
#define InjectionTimer_1__B_PWM__GREATER_THAN 3
#define InjectionTimer_1__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define InjectionTimer_1__B_PWM__EQUAL 0
#define InjectionTimer_1__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!InjectionTimer_1_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!InjectionTimer_1_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!InjectionTimer_1_PWMModeIsCenterAligned) */
        #if (InjectionTimer_1_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (InjectionTimer_1_UseStatus) */

        /* Backup for Deadband parameters */
        #if(InjectionTimer_1_DeadBandMode == InjectionTimer_1__B_PWM__DBM_256_CLOCKS || \
            InjectionTimer_1_DeadBandMode == InjectionTimer_1__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(InjectionTimer_1_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (InjectionTimer_1_KillModeMinTime) */

        /* Backup control register */
        #if(InjectionTimer_1_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (InjectionTimer_1_UseControl) */

    #endif /* (!InjectionTimer_1_UsingFixedFunction) */

}InjectionTimer_1_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    InjectionTimer_1_Start(void) ;
void    InjectionTimer_1_Stop(void) ;

#if (InjectionTimer_1_UseStatus || InjectionTimer_1_UsingFixedFunction)
    void  InjectionTimer_1_SetInterruptMode(uint8 interruptMode) ;
    uint8 InjectionTimer_1_ReadStatusRegister(void) ;
#endif /* (InjectionTimer_1_UseStatus || InjectionTimer_1_UsingFixedFunction) */

#define InjectionTimer_1_GetInterruptSource() InjectionTimer_1_ReadStatusRegister()

#if (InjectionTimer_1_UseControl)
    uint8 InjectionTimer_1_ReadControlRegister(void) ;
    void  InjectionTimer_1_WriteControlRegister(uint8 control)
          ;
#endif /* (InjectionTimer_1_UseControl) */

#if (InjectionTimer_1_UseOneCompareMode)
   #if (InjectionTimer_1_CompareMode1SW)
       void    InjectionTimer_1_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (InjectionTimer_1_CompareMode1SW) */
#else
    #if (InjectionTimer_1_CompareMode1SW)
        void    InjectionTimer_1_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (InjectionTimer_1_CompareMode1SW) */
    #if (InjectionTimer_1_CompareMode2SW)
        void    InjectionTimer_1_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (InjectionTimer_1_CompareMode2SW) */
#endif /* (InjectionTimer_1_UseOneCompareMode) */

#if (!InjectionTimer_1_UsingFixedFunction)
    uint16   InjectionTimer_1_ReadCounter(void) ;
    uint16 InjectionTimer_1_ReadCapture(void) ;

    #if (InjectionTimer_1_UseStatus)
            void InjectionTimer_1_ClearFIFO(void) ;
    #endif /* (InjectionTimer_1_UseStatus) */

    void    InjectionTimer_1_WriteCounter(uint16 counter)
            ;
#endif /* (!InjectionTimer_1_UsingFixedFunction) */

void    InjectionTimer_1_WritePeriod(uint16 period)
        ;
uint16 InjectionTimer_1_ReadPeriod(void) ;

#if (InjectionTimer_1_UseOneCompareMode)
    void    InjectionTimer_1_WriteCompare(uint16 compare)
            ;
    uint16 InjectionTimer_1_ReadCompare(void) ;
#else
    void    InjectionTimer_1_WriteCompare1(uint16 compare)
            ;
    uint16 InjectionTimer_1_ReadCompare1(void) ;
    void    InjectionTimer_1_WriteCompare2(uint16 compare)
            ;
    uint16 InjectionTimer_1_ReadCompare2(void) ;
#endif /* (InjectionTimer_1_UseOneCompareMode) */


#if (InjectionTimer_1_DeadBandUsed)
    void    InjectionTimer_1_WriteDeadTime(uint8 deadtime) ;
    uint8   InjectionTimer_1_ReadDeadTime(void) ;
#endif /* (InjectionTimer_1_DeadBandUsed) */

#if ( InjectionTimer_1_KillModeMinTime)
    void InjectionTimer_1_WriteKillTime(uint8 killtime) ;
    uint8 InjectionTimer_1_ReadKillTime(void) ;
#endif /* ( InjectionTimer_1_KillModeMinTime) */

void InjectionTimer_1_Init(void) ;
void InjectionTimer_1_Enable(void) ;
void InjectionTimer_1_Sleep(void) ;
void InjectionTimer_1_Wakeup(void) ;
void InjectionTimer_1_SaveConfig(void) ;
void InjectionTimer_1_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define InjectionTimer_1_INIT_PERIOD_VALUE          (45000u)
#define InjectionTimer_1_INIT_COMPARE_VALUE1        (32000u)
#define InjectionTimer_1_INIT_COMPARE_VALUE2        (15000u)
#define InjectionTimer_1_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    InjectionTimer_1_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    InjectionTimer_1_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    InjectionTimer_1_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    InjectionTimer_1_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define InjectionTimer_1_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  InjectionTimer_1_CTRL_CMPMODE2_SHIFT)
#define InjectionTimer_1_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  InjectionTimer_1_CTRL_CMPMODE1_SHIFT)
#define InjectionTimer_1_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (InjectionTimer_1_UsingFixedFunction)
   #define InjectionTimer_1_PERIOD_LSB              (*(reg16 *) InjectionTimer_1_PWMHW__PER0)
   #define InjectionTimer_1_PERIOD_LSB_PTR          ( (reg16 *) InjectionTimer_1_PWMHW__PER0)
   #define InjectionTimer_1_COMPARE1_LSB            (*(reg16 *) InjectionTimer_1_PWMHW__CNT_CMP0)
   #define InjectionTimer_1_COMPARE1_LSB_PTR        ( (reg16 *) InjectionTimer_1_PWMHW__CNT_CMP0)
   #define InjectionTimer_1_COMPARE2_LSB            (0x00u)
   #define InjectionTimer_1_COMPARE2_LSB_PTR        (0x00u)
   #define InjectionTimer_1_COUNTER_LSB             (*(reg16 *) InjectionTimer_1_PWMHW__CNT_CMP0)
   #define InjectionTimer_1_COUNTER_LSB_PTR         ( (reg16 *) InjectionTimer_1_PWMHW__CNT_CMP0)
   #define InjectionTimer_1_CAPTURE_LSB             (*(reg16 *) InjectionTimer_1_PWMHW__CAP0)
   #define InjectionTimer_1_CAPTURE_LSB_PTR         ( (reg16 *) InjectionTimer_1_PWMHW__CAP0)
   #define InjectionTimer_1_RT1                     (*(reg8 *)  InjectionTimer_1_PWMHW__RT1)
   #define InjectionTimer_1_RT1_PTR                 ( (reg8 *)  InjectionTimer_1_PWMHW__RT1)

#else
   #if (InjectionTimer_1_Resolution == 8u) /* 8bit - PWM */

       #if(InjectionTimer_1_PWMModeIsCenterAligned)
           #define InjectionTimer_1_PERIOD_LSB      (*(reg8 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define InjectionTimer_1_PERIOD_LSB_PTR  ((reg8 *)   InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define InjectionTimer_1_PERIOD_LSB      (*(reg8 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define InjectionTimer_1_PERIOD_LSB_PTR  ((reg8 *)   InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (InjectionTimer_1_PWMModeIsCenterAligned) */

       #define InjectionTimer_1_COMPARE1_LSB        (*(reg8 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define InjectionTimer_1_COMPARE1_LSB_PTR    ((reg8 *)   InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define InjectionTimer_1_COMPARE2_LSB        (*(reg8 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define InjectionTimer_1_COMPARE2_LSB_PTR    ((reg8 *)   InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define InjectionTimer_1_COUNTERCAP_LSB      (*(reg8 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define InjectionTimer_1_COUNTERCAP_LSB_PTR  ((reg8 *)   InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define InjectionTimer_1_COUNTER_LSB         (*(reg8 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define InjectionTimer_1_COUNTER_LSB_PTR     ((reg8 *)   InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define InjectionTimer_1_CAPTURE_LSB         (*(reg8 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define InjectionTimer_1_CAPTURE_LSB_PTR     ((reg8 *)   InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(InjectionTimer_1_PWMModeIsCenterAligned)
               #define InjectionTimer_1_PERIOD_LSB      (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define InjectionTimer_1_PERIOD_LSB_PTR  ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define InjectionTimer_1_PERIOD_LSB      (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define InjectionTimer_1_PERIOD_LSB_PTR  ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (InjectionTimer_1_PWMModeIsCenterAligned) */

            #define InjectionTimer_1_COMPARE1_LSB       (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define InjectionTimer_1_COMPARE1_LSB_PTR   ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define InjectionTimer_1_COMPARE2_LSB       (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define InjectionTimer_1_COMPARE2_LSB_PTR   ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define InjectionTimer_1_COUNTERCAP_LSB     (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define InjectionTimer_1_COUNTERCAP_LSB_PTR ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define InjectionTimer_1_COUNTER_LSB        (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define InjectionTimer_1_COUNTER_LSB_PTR    ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define InjectionTimer_1_CAPTURE_LSB        (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define InjectionTimer_1_CAPTURE_LSB_PTR    ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(InjectionTimer_1_PWMModeIsCenterAligned)
               #define InjectionTimer_1_PERIOD_LSB      (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define InjectionTimer_1_PERIOD_LSB_PTR  ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define InjectionTimer_1_PERIOD_LSB      (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define InjectionTimer_1_PERIOD_LSB_PTR  ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (InjectionTimer_1_PWMModeIsCenterAligned) */

            #define InjectionTimer_1_COMPARE1_LSB       (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define InjectionTimer_1_COMPARE1_LSB_PTR   ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define InjectionTimer_1_COMPARE2_LSB       (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define InjectionTimer_1_COMPARE2_LSB_PTR   ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define InjectionTimer_1_COUNTERCAP_LSB     (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define InjectionTimer_1_COUNTERCAP_LSB_PTR ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define InjectionTimer_1_COUNTER_LSB        (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define InjectionTimer_1_COUNTER_LSB_PTR    ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define InjectionTimer_1_CAPTURE_LSB        (*(reg16 *) InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define InjectionTimer_1_CAPTURE_LSB_PTR    ((reg16 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define InjectionTimer_1_AUX_CONTROLDP1          (*(reg8 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define InjectionTimer_1_AUX_CONTROLDP1_PTR      ((reg8 *)   InjectionTimer_1_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (InjectionTimer_1_Resolution == 8) */

   #define InjectionTimer_1_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define InjectionTimer_1_AUX_CONTROLDP0          (*(reg8 *)  InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define InjectionTimer_1_AUX_CONTROLDP0_PTR      ((reg8 *)   InjectionTimer_1_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (InjectionTimer_1_UsingFixedFunction) */

#if(InjectionTimer_1_KillModeMinTime )
    #define InjectionTimer_1_KILLMODEMINTIME        (*(reg8 *)  InjectionTimer_1_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define InjectionTimer_1_KILLMODEMINTIME_PTR    ((reg8 *)   InjectionTimer_1_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (InjectionTimer_1_KillModeMinTime ) */

#if(InjectionTimer_1_DeadBandMode == InjectionTimer_1__B_PWM__DBM_256_CLOCKS)
    #define InjectionTimer_1_DEADBAND_COUNT         (*(reg8 *)  InjectionTimer_1_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define InjectionTimer_1_DEADBAND_COUNT_PTR     ((reg8 *)   InjectionTimer_1_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define InjectionTimer_1_DEADBAND_LSB_PTR       ((reg8 *)   InjectionTimer_1_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define InjectionTimer_1_DEADBAND_LSB           (*(reg8 *)  InjectionTimer_1_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(InjectionTimer_1_DeadBandMode == InjectionTimer_1__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (InjectionTimer_1_UsingFixedFunction)
        #define InjectionTimer_1_DEADBAND_COUNT         (*(reg8 *)  InjectionTimer_1_PWMHW__CFG0)
        #define InjectionTimer_1_DEADBAND_COUNT_PTR     ((reg8 *)   InjectionTimer_1_PWMHW__CFG0)
        #define InjectionTimer_1_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << InjectionTimer_1_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define InjectionTimer_1_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define InjectionTimer_1_DEADBAND_COUNT         (*(reg8 *)  InjectionTimer_1_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define InjectionTimer_1_DEADBAND_COUNT_PTR     ((reg8 *)   InjectionTimer_1_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define InjectionTimer_1_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << InjectionTimer_1_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define InjectionTimer_1_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (InjectionTimer_1_UsingFixedFunction) */
#endif /* (InjectionTimer_1_DeadBandMode == InjectionTimer_1__B_PWM__DBM_256_CLOCKS) */



#if (InjectionTimer_1_UsingFixedFunction)
    #define InjectionTimer_1_STATUS                 (*(reg8 *) InjectionTimer_1_PWMHW__SR0)
    #define InjectionTimer_1_STATUS_PTR             ((reg8 *) InjectionTimer_1_PWMHW__SR0)
    #define InjectionTimer_1_STATUS_MASK            (*(reg8 *) InjectionTimer_1_PWMHW__SR0)
    #define InjectionTimer_1_STATUS_MASK_PTR        ((reg8 *) InjectionTimer_1_PWMHW__SR0)
    #define InjectionTimer_1_CONTROL                (*(reg8 *) InjectionTimer_1_PWMHW__CFG0)
    #define InjectionTimer_1_CONTROL_PTR            ((reg8 *) InjectionTimer_1_PWMHW__CFG0)
    #define InjectionTimer_1_CONTROL2               (*(reg8 *) InjectionTimer_1_PWMHW__CFG1)
    #define InjectionTimer_1_CONTROL3               (*(reg8 *) InjectionTimer_1_PWMHW__CFG2)
    #define InjectionTimer_1_GLOBAL_ENABLE          (*(reg8 *) InjectionTimer_1_PWMHW__PM_ACT_CFG)
    #define InjectionTimer_1_GLOBAL_ENABLE_PTR      ( (reg8 *) InjectionTimer_1_PWMHW__PM_ACT_CFG)
    #define InjectionTimer_1_GLOBAL_STBY_ENABLE     (*(reg8 *) InjectionTimer_1_PWMHW__PM_STBY_CFG)
    #define InjectionTimer_1_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) InjectionTimer_1_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define InjectionTimer_1_BLOCK_EN_MASK          (InjectionTimer_1_PWMHW__PM_ACT_MSK)
    #define InjectionTimer_1_BLOCK_STBY_EN_MASK     (InjectionTimer_1_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define InjectionTimer_1_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define InjectionTimer_1_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define InjectionTimer_1_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define InjectionTimer_1_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define InjectionTimer_1_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define InjectionTimer_1_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define InjectionTimer_1_CTRL_ENABLE            (uint8)((uint8)0x01u << InjectionTimer_1_CTRL_ENABLE_SHIFT)
    #define InjectionTimer_1_CTRL_RESET             (uint8)((uint8)0x01u << InjectionTimer_1_CTRL_RESET_SHIFT)
    #define InjectionTimer_1_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << InjectionTimer_1_CTRL_CMPMODE2_SHIFT)
    #define InjectionTimer_1_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << InjectionTimer_1_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define InjectionTimer_1_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define InjectionTimer_1_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << InjectionTimer_1_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define InjectionTimer_1_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define InjectionTimer_1_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define InjectionTimer_1_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define InjectionTimer_1_STATUS_TC_INT_EN_MASK_SHIFT            (InjectionTimer_1_STATUS_TC_SHIFT - 4u)
    #define InjectionTimer_1_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define InjectionTimer_1_STATUS_CMP1_INT_EN_MASK_SHIFT          (InjectionTimer_1_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define InjectionTimer_1_STATUS_TC              (uint8)((uint8)0x01u << InjectionTimer_1_STATUS_TC_SHIFT)
    #define InjectionTimer_1_STATUS_CMP1            (uint8)((uint8)0x01u << InjectionTimer_1_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define InjectionTimer_1_STATUS_TC_INT_EN_MASK              (uint8)((uint8)InjectionTimer_1_STATUS_TC >> 4u)
    #define InjectionTimer_1_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)InjectionTimer_1_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define InjectionTimer_1_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define InjectionTimer_1_RT1_MASK              (uint8)((uint8)0x03u << InjectionTimer_1_RT1_SHIFT)
    #define InjectionTimer_1_SYNC                  (uint8)((uint8)0x03u << InjectionTimer_1_RT1_SHIFT)
    #define InjectionTimer_1_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define InjectionTimer_1_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << InjectionTimer_1_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define InjectionTimer_1_SYNCDSI_EN            (uint8)((uint8)0x0Fu << InjectionTimer_1_SYNCDSI_SHIFT)


#else
    #define InjectionTimer_1_STATUS                (*(reg8 *)   InjectionTimer_1_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define InjectionTimer_1_STATUS_PTR            ((reg8 *)    InjectionTimer_1_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define InjectionTimer_1_STATUS_MASK           (*(reg8 *)   InjectionTimer_1_PWMUDB_genblk8_stsreg__MASK_REG)
    #define InjectionTimer_1_STATUS_MASK_PTR       ((reg8 *)    InjectionTimer_1_PWMUDB_genblk8_stsreg__MASK_REG)
    #define InjectionTimer_1_STATUS_AUX_CTRL       (*(reg8 *)   InjectionTimer_1_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define InjectionTimer_1_CONTROL               (*(reg8 *)   InjectionTimer_1_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define InjectionTimer_1_CONTROL_PTR           ((reg8 *)    InjectionTimer_1_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define InjectionTimer_1_CTRL_ENABLE_SHIFT      (0x07u)
    #define InjectionTimer_1_CTRL_RESET_SHIFT       (0x06u)
    #define InjectionTimer_1_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define InjectionTimer_1_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define InjectionTimer_1_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define InjectionTimer_1_CTRL_ENABLE            (uint8)((uint8)0x01u << InjectionTimer_1_CTRL_ENABLE_SHIFT)
    #define InjectionTimer_1_CTRL_RESET             (uint8)((uint8)0x01u << InjectionTimer_1_CTRL_RESET_SHIFT)
    #define InjectionTimer_1_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << InjectionTimer_1_CTRL_CMPMODE2_SHIFT)
    #define InjectionTimer_1_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << InjectionTimer_1_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define InjectionTimer_1_STATUS_KILL_SHIFT          (0x05u)
    #define InjectionTimer_1_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define InjectionTimer_1_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define InjectionTimer_1_STATUS_TC_SHIFT            (0x02u)
    #define InjectionTimer_1_STATUS_CMP2_SHIFT          (0x01u)
    #define InjectionTimer_1_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define InjectionTimer_1_STATUS_KILL_INT_EN_MASK_SHIFT          (InjectionTimer_1_STATUS_KILL_SHIFT)
    #define InjectionTimer_1_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (InjectionTimer_1_STATUS_FIFONEMPTY_SHIFT)
    #define InjectionTimer_1_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (InjectionTimer_1_STATUS_FIFOFULL_SHIFT)
    #define InjectionTimer_1_STATUS_TC_INT_EN_MASK_SHIFT            (InjectionTimer_1_STATUS_TC_SHIFT)
    #define InjectionTimer_1_STATUS_CMP2_INT_EN_MASK_SHIFT          (InjectionTimer_1_STATUS_CMP2_SHIFT)
    #define InjectionTimer_1_STATUS_CMP1_INT_EN_MASK_SHIFT          (InjectionTimer_1_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define InjectionTimer_1_STATUS_KILL            (uint8)((uint8)0x00u << InjectionTimer_1_STATUS_KILL_SHIFT )
    #define InjectionTimer_1_STATUS_FIFOFULL        (uint8)((uint8)0x01u << InjectionTimer_1_STATUS_FIFOFULL_SHIFT)
    #define InjectionTimer_1_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << InjectionTimer_1_STATUS_FIFONEMPTY_SHIFT)
    #define InjectionTimer_1_STATUS_TC              (uint8)((uint8)0x01u << InjectionTimer_1_STATUS_TC_SHIFT)
    #define InjectionTimer_1_STATUS_CMP2            (uint8)((uint8)0x01u << InjectionTimer_1_STATUS_CMP2_SHIFT)
    #define InjectionTimer_1_STATUS_CMP1            (uint8)((uint8)0x01u << InjectionTimer_1_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define InjectionTimer_1_STATUS_KILL_INT_EN_MASK            (InjectionTimer_1_STATUS_KILL)
    #define InjectionTimer_1_STATUS_FIFOFULL_INT_EN_MASK        (InjectionTimer_1_STATUS_FIFOFULL)
    #define InjectionTimer_1_STATUS_FIFONEMPTY_INT_EN_MASK      (InjectionTimer_1_STATUS_FIFONEMPTY)
    #define InjectionTimer_1_STATUS_TC_INT_EN_MASK              (InjectionTimer_1_STATUS_TC)
    #define InjectionTimer_1_STATUS_CMP2_INT_EN_MASK            (InjectionTimer_1_STATUS_CMP2)
    #define InjectionTimer_1_STATUS_CMP1_INT_EN_MASK            (InjectionTimer_1_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define InjectionTimer_1_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define InjectionTimer_1_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define InjectionTimer_1_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define InjectionTimer_1_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define InjectionTimer_1_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* InjectionTimer_1_UsingFixedFunction */

#endif  /* CY_PWM_InjectionTimer_1_H */


/* [] END OF FILE */
