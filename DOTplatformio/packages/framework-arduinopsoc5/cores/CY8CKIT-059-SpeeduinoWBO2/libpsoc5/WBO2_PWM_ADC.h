/*******************************************************************************
* File Name: WBO2_PWM_ADC.h
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

#if !defined(CY_PWM_WBO2_PWM_ADC_H)
#define CY_PWM_WBO2_PWM_ADC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 WBO2_PWM_ADC_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define WBO2_PWM_ADC_Resolution                     (8u)
#define WBO2_PWM_ADC_UsingFixedFunction             (0u)
#define WBO2_PWM_ADC_DeadBandMode                   (0u)
#define WBO2_PWM_ADC_KillModeMinTime                (0u)
#define WBO2_PWM_ADC_KillMode                       (0u)
#define WBO2_PWM_ADC_PWMMode                        (0u)
#define WBO2_PWM_ADC_PWMModeIsCenterAligned         (0u)
#define WBO2_PWM_ADC_DeadBandUsed                   (0u)
#define WBO2_PWM_ADC_DeadBand2_4                    (0u)

#if !defined(WBO2_PWM_ADC_PWMUDB_genblk8_stsreg__REMOVED)
    #define WBO2_PWM_ADC_UseStatus                  (1u)
#else
    #define WBO2_PWM_ADC_UseStatus                  (0u)
#endif /* !defined(WBO2_PWM_ADC_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(WBO2_PWM_ADC_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define WBO2_PWM_ADC_UseControl                 (1u)
#else
    #define WBO2_PWM_ADC_UseControl                 (0u)
#endif /* !defined(WBO2_PWM_ADC_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define WBO2_PWM_ADC_UseOneCompareMode              (1u)
#define WBO2_PWM_ADC_MinimumKillTime                (1u)
#define WBO2_PWM_ADC_EnableMode                     (0u)

#define WBO2_PWM_ADC_CompareMode1SW                 (0u)
#define WBO2_PWM_ADC_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define WBO2_PWM_ADC__B_PWM__DISABLED 0
#define WBO2_PWM_ADC__B_PWM__ASYNCHRONOUS 1
#define WBO2_PWM_ADC__B_PWM__SINGLECYCLE 2
#define WBO2_PWM_ADC__B_PWM__LATCHED 3
#define WBO2_PWM_ADC__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define WBO2_PWM_ADC__B_PWM__DBMDISABLED 0
#define WBO2_PWM_ADC__B_PWM__DBM_2_4_CLOCKS 1
#define WBO2_PWM_ADC__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define WBO2_PWM_ADC__B_PWM__ONE_OUTPUT 0
#define WBO2_PWM_ADC__B_PWM__TWO_OUTPUTS 1
#define WBO2_PWM_ADC__B_PWM__DUAL_EDGE 2
#define WBO2_PWM_ADC__B_PWM__CENTER_ALIGN 3
#define WBO2_PWM_ADC__B_PWM__DITHER 5
#define WBO2_PWM_ADC__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define WBO2_PWM_ADC__B_PWM__LESS_THAN 1
#define WBO2_PWM_ADC__B_PWM__LESS_THAN_OR_EQUAL 2
#define WBO2_PWM_ADC__B_PWM__GREATER_THAN 3
#define WBO2_PWM_ADC__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define WBO2_PWM_ADC__B_PWM__EQUAL 0
#define WBO2_PWM_ADC__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!WBO2_PWM_ADC_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!WBO2_PWM_ADC_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!WBO2_PWM_ADC_PWMModeIsCenterAligned) */
        #if (WBO2_PWM_ADC_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (WBO2_PWM_ADC_UseStatus) */

        /* Backup for Deadband parameters */
        #if(WBO2_PWM_ADC_DeadBandMode == WBO2_PWM_ADC__B_PWM__DBM_256_CLOCKS || \
            WBO2_PWM_ADC_DeadBandMode == WBO2_PWM_ADC__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(WBO2_PWM_ADC_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (WBO2_PWM_ADC_KillModeMinTime) */

        /* Backup control register */
        #if(WBO2_PWM_ADC_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (WBO2_PWM_ADC_UseControl) */

    #endif /* (!WBO2_PWM_ADC_UsingFixedFunction) */

}WBO2_PWM_ADC_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    WBO2_PWM_ADC_Start(void) ;
void    WBO2_PWM_ADC_Stop(void) ;

#if (WBO2_PWM_ADC_UseStatus || WBO2_PWM_ADC_UsingFixedFunction)
    void  WBO2_PWM_ADC_SetInterruptMode(uint8 interruptMode) ;
    uint8 WBO2_PWM_ADC_ReadStatusRegister(void) ;
#endif /* (WBO2_PWM_ADC_UseStatus || WBO2_PWM_ADC_UsingFixedFunction) */

#define WBO2_PWM_ADC_GetInterruptSource() WBO2_PWM_ADC_ReadStatusRegister()

#if (WBO2_PWM_ADC_UseControl)
    uint8 WBO2_PWM_ADC_ReadControlRegister(void) ;
    void  WBO2_PWM_ADC_WriteControlRegister(uint8 control)
          ;
#endif /* (WBO2_PWM_ADC_UseControl) */

#if (WBO2_PWM_ADC_UseOneCompareMode)
   #if (WBO2_PWM_ADC_CompareMode1SW)
       void    WBO2_PWM_ADC_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (WBO2_PWM_ADC_CompareMode1SW) */
#else
    #if (WBO2_PWM_ADC_CompareMode1SW)
        void    WBO2_PWM_ADC_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (WBO2_PWM_ADC_CompareMode1SW) */
    #if (WBO2_PWM_ADC_CompareMode2SW)
        void    WBO2_PWM_ADC_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (WBO2_PWM_ADC_CompareMode2SW) */
#endif /* (WBO2_PWM_ADC_UseOneCompareMode) */

#if (!WBO2_PWM_ADC_UsingFixedFunction)
    uint8   WBO2_PWM_ADC_ReadCounter(void) ;
    uint8 WBO2_PWM_ADC_ReadCapture(void) ;

    #if (WBO2_PWM_ADC_UseStatus)
            void WBO2_PWM_ADC_ClearFIFO(void) ;
    #endif /* (WBO2_PWM_ADC_UseStatus) */

    void    WBO2_PWM_ADC_WriteCounter(uint8 counter)
            ;
#endif /* (!WBO2_PWM_ADC_UsingFixedFunction) */

void    WBO2_PWM_ADC_WritePeriod(uint8 period)
        ;
uint8 WBO2_PWM_ADC_ReadPeriod(void) ;

#if (WBO2_PWM_ADC_UseOneCompareMode)
    void    WBO2_PWM_ADC_WriteCompare(uint8 compare)
            ;
    uint8 WBO2_PWM_ADC_ReadCompare(void) ;
#else
    void    WBO2_PWM_ADC_WriteCompare1(uint8 compare)
            ;
    uint8 WBO2_PWM_ADC_ReadCompare1(void) ;
    void    WBO2_PWM_ADC_WriteCompare2(uint8 compare)
            ;
    uint8 WBO2_PWM_ADC_ReadCompare2(void) ;
#endif /* (WBO2_PWM_ADC_UseOneCompareMode) */


#if (WBO2_PWM_ADC_DeadBandUsed)
    void    WBO2_PWM_ADC_WriteDeadTime(uint8 deadtime) ;
    uint8   WBO2_PWM_ADC_ReadDeadTime(void) ;
#endif /* (WBO2_PWM_ADC_DeadBandUsed) */

#if ( WBO2_PWM_ADC_KillModeMinTime)
    void WBO2_PWM_ADC_WriteKillTime(uint8 killtime) ;
    uint8 WBO2_PWM_ADC_ReadKillTime(void) ;
#endif /* ( WBO2_PWM_ADC_KillModeMinTime) */

void WBO2_PWM_ADC_Init(void) ;
void WBO2_PWM_ADC_Enable(void) ;
void WBO2_PWM_ADC_Sleep(void) ;
void WBO2_PWM_ADC_Wakeup(void) ;
void WBO2_PWM_ADC_SaveConfig(void) ;
void WBO2_PWM_ADC_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define WBO2_PWM_ADC_INIT_PERIOD_VALUE          (255u)
#define WBO2_PWM_ADC_INIT_COMPARE_VALUE1        (127u)
#define WBO2_PWM_ADC_INIT_COMPARE_VALUE2        (63u)
#define WBO2_PWM_ADC_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    WBO2_PWM_ADC_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    WBO2_PWM_ADC_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    WBO2_PWM_ADC_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    WBO2_PWM_ADC_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define WBO2_PWM_ADC_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  WBO2_PWM_ADC_CTRL_CMPMODE2_SHIFT)
#define WBO2_PWM_ADC_DEFAULT_COMPARE1_MODE      (uint8)((uint8)3u <<  WBO2_PWM_ADC_CTRL_CMPMODE1_SHIFT)
#define WBO2_PWM_ADC_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (WBO2_PWM_ADC_UsingFixedFunction)
   #define WBO2_PWM_ADC_PERIOD_LSB              (*(reg16 *) WBO2_PWM_ADC_PWMHW__PER0)
   #define WBO2_PWM_ADC_PERIOD_LSB_PTR          ( (reg16 *) WBO2_PWM_ADC_PWMHW__PER0)
   #define WBO2_PWM_ADC_COMPARE1_LSB            (*(reg16 *) WBO2_PWM_ADC_PWMHW__CNT_CMP0)
   #define WBO2_PWM_ADC_COMPARE1_LSB_PTR        ( (reg16 *) WBO2_PWM_ADC_PWMHW__CNT_CMP0)
   #define WBO2_PWM_ADC_COMPARE2_LSB            (0x00u)
   #define WBO2_PWM_ADC_COMPARE2_LSB_PTR        (0x00u)
   #define WBO2_PWM_ADC_COUNTER_LSB             (*(reg16 *) WBO2_PWM_ADC_PWMHW__CNT_CMP0)
   #define WBO2_PWM_ADC_COUNTER_LSB_PTR         ( (reg16 *) WBO2_PWM_ADC_PWMHW__CNT_CMP0)
   #define WBO2_PWM_ADC_CAPTURE_LSB             (*(reg16 *) WBO2_PWM_ADC_PWMHW__CAP0)
   #define WBO2_PWM_ADC_CAPTURE_LSB_PTR         ( (reg16 *) WBO2_PWM_ADC_PWMHW__CAP0)
   #define WBO2_PWM_ADC_RT1                     (*(reg8 *)  WBO2_PWM_ADC_PWMHW__RT1)
   #define WBO2_PWM_ADC_RT1_PTR                 ( (reg8 *)  WBO2_PWM_ADC_PWMHW__RT1)

#else
   #if (WBO2_PWM_ADC_Resolution == 8u) /* 8bit - PWM */

       #if(WBO2_PWM_ADC_PWMModeIsCenterAligned)
           #define WBO2_PWM_ADC_PERIOD_LSB      (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define WBO2_PWM_ADC_PERIOD_LSB_PTR  ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define WBO2_PWM_ADC_PERIOD_LSB      (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define WBO2_PWM_ADC_PERIOD_LSB_PTR  ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (WBO2_PWM_ADC_PWMModeIsCenterAligned) */

       #define WBO2_PWM_ADC_COMPARE1_LSB        (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define WBO2_PWM_ADC_COMPARE1_LSB_PTR    ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define WBO2_PWM_ADC_COMPARE2_LSB        (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define WBO2_PWM_ADC_COMPARE2_LSB_PTR    ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define WBO2_PWM_ADC_COUNTERCAP_LSB      (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define WBO2_PWM_ADC_COUNTERCAP_LSB_PTR  ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define WBO2_PWM_ADC_COUNTER_LSB         (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define WBO2_PWM_ADC_COUNTER_LSB_PTR     ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define WBO2_PWM_ADC_CAPTURE_LSB         (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define WBO2_PWM_ADC_CAPTURE_LSB_PTR     ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(WBO2_PWM_ADC_PWMModeIsCenterAligned)
               #define WBO2_PWM_ADC_PERIOD_LSB      (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define WBO2_PWM_ADC_PERIOD_LSB_PTR  ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define WBO2_PWM_ADC_PERIOD_LSB      (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define WBO2_PWM_ADC_PERIOD_LSB_PTR  ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (WBO2_PWM_ADC_PWMModeIsCenterAligned) */

            #define WBO2_PWM_ADC_COMPARE1_LSB       (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define WBO2_PWM_ADC_COMPARE1_LSB_PTR   ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define WBO2_PWM_ADC_COMPARE2_LSB       (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define WBO2_PWM_ADC_COMPARE2_LSB_PTR   ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define WBO2_PWM_ADC_COUNTERCAP_LSB     (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define WBO2_PWM_ADC_COUNTERCAP_LSB_PTR ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define WBO2_PWM_ADC_COUNTER_LSB        (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define WBO2_PWM_ADC_COUNTER_LSB_PTR    ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define WBO2_PWM_ADC_CAPTURE_LSB        (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define WBO2_PWM_ADC_CAPTURE_LSB_PTR    ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(WBO2_PWM_ADC_PWMModeIsCenterAligned)
               #define WBO2_PWM_ADC_PERIOD_LSB      (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define WBO2_PWM_ADC_PERIOD_LSB_PTR  ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define WBO2_PWM_ADC_PERIOD_LSB      (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define WBO2_PWM_ADC_PERIOD_LSB_PTR  ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (WBO2_PWM_ADC_PWMModeIsCenterAligned) */

            #define WBO2_PWM_ADC_COMPARE1_LSB       (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define WBO2_PWM_ADC_COMPARE1_LSB_PTR   ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define WBO2_PWM_ADC_COMPARE2_LSB       (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define WBO2_PWM_ADC_COMPARE2_LSB_PTR   ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define WBO2_PWM_ADC_COUNTERCAP_LSB     (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define WBO2_PWM_ADC_COUNTERCAP_LSB_PTR ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define WBO2_PWM_ADC_COUNTER_LSB        (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define WBO2_PWM_ADC_COUNTER_LSB_PTR    ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define WBO2_PWM_ADC_CAPTURE_LSB        (*(reg16 *) WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define WBO2_PWM_ADC_CAPTURE_LSB_PTR    ((reg16 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define WBO2_PWM_ADC_AUX_CONTROLDP1          (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define WBO2_PWM_ADC_AUX_CONTROLDP1_PTR      ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (WBO2_PWM_ADC_Resolution == 8) */

   #define WBO2_PWM_ADC_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define WBO2_PWM_ADC_AUX_CONTROLDP0          (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define WBO2_PWM_ADC_AUX_CONTROLDP0_PTR      ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (WBO2_PWM_ADC_UsingFixedFunction) */

#if(WBO2_PWM_ADC_KillModeMinTime )
    #define WBO2_PWM_ADC_KILLMODEMINTIME        (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define WBO2_PWM_ADC_KILLMODEMINTIME_PTR    ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (WBO2_PWM_ADC_KillModeMinTime ) */

#if(WBO2_PWM_ADC_DeadBandMode == WBO2_PWM_ADC__B_PWM__DBM_256_CLOCKS)
    #define WBO2_PWM_ADC_DEADBAND_COUNT         (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define WBO2_PWM_ADC_DEADBAND_COUNT_PTR     ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define WBO2_PWM_ADC_DEADBAND_LSB_PTR       ((reg8 *)   WBO2_PWM_ADC_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define WBO2_PWM_ADC_DEADBAND_LSB           (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(WBO2_PWM_ADC_DeadBandMode == WBO2_PWM_ADC__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (WBO2_PWM_ADC_UsingFixedFunction)
        #define WBO2_PWM_ADC_DEADBAND_COUNT         (*(reg8 *)  WBO2_PWM_ADC_PWMHW__CFG0)
        #define WBO2_PWM_ADC_DEADBAND_COUNT_PTR     ((reg8 *)   WBO2_PWM_ADC_PWMHW__CFG0)
        #define WBO2_PWM_ADC_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << WBO2_PWM_ADC_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define WBO2_PWM_ADC_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define WBO2_PWM_ADC_DEADBAND_COUNT         (*(reg8 *)  WBO2_PWM_ADC_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define WBO2_PWM_ADC_DEADBAND_COUNT_PTR     ((reg8 *)   WBO2_PWM_ADC_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define WBO2_PWM_ADC_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << WBO2_PWM_ADC_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define WBO2_PWM_ADC_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (WBO2_PWM_ADC_UsingFixedFunction) */
#endif /* (WBO2_PWM_ADC_DeadBandMode == WBO2_PWM_ADC__B_PWM__DBM_256_CLOCKS) */



#if (WBO2_PWM_ADC_UsingFixedFunction)
    #define WBO2_PWM_ADC_STATUS                 (*(reg8 *) WBO2_PWM_ADC_PWMHW__SR0)
    #define WBO2_PWM_ADC_STATUS_PTR             ((reg8 *) WBO2_PWM_ADC_PWMHW__SR0)
    #define WBO2_PWM_ADC_STATUS_MASK            (*(reg8 *) WBO2_PWM_ADC_PWMHW__SR0)
    #define WBO2_PWM_ADC_STATUS_MASK_PTR        ((reg8 *) WBO2_PWM_ADC_PWMHW__SR0)
    #define WBO2_PWM_ADC_CONTROL                (*(reg8 *) WBO2_PWM_ADC_PWMHW__CFG0)
    #define WBO2_PWM_ADC_CONTROL_PTR            ((reg8 *) WBO2_PWM_ADC_PWMHW__CFG0)
    #define WBO2_PWM_ADC_CONTROL2               (*(reg8 *) WBO2_PWM_ADC_PWMHW__CFG1)
    #define WBO2_PWM_ADC_CONTROL3               (*(reg8 *) WBO2_PWM_ADC_PWMHW__CFG2)
    #define WBO2_PWM_ADC_GLOBAL_ENABLE          (*(reg8 *) WBO2_PWM_ADC_PWMHW__PM_ACT_CFG)
    #define WBO2_PWM_ADC_GLOBAL_ENABLE_PTR      ( (reg8 *) WBO2_PWM_ADC_PWMHW__PM_ACT_CFG)
    #define WBO2_PWM_ADC_GLOBAL_STBY_ENABLE     (*(reg8 *) WBO2_PWM_ADC_PWMHW__PM_STBY_CFG)
    #define WBO2_PWM_ADC_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) WBO2_PWM_ADC_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define WBO2_PWM_ADC_BLOCK_EN_MASK          (WBO2_PWM_ADC_PWMHW__PM_ACT_MSK)
    #define WBO2_PWM_ADC_BLOCK_STBY_EN_MASK     (WBO2_PWM_ADC_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define WBO2_PWM_ADC_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define WBO2_PWM_ADC_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define WBO2_PWM_ADC_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define WBO2_PWM_ADC_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define WBO2_PWM_ADC_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define WBO2_PWM_ADC_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define WBO2_PWM_ADC_CTRL_ENABLE            (uint8)((uint8)0x01u << WBO2_PWM_ADC_CTRL_ENABLE_SHIFT)
    #define WBO2_PWM_ADC_CTRL_RESET             (uint8)((uint8)0x01u << WBO2_PWM_ADC_CTRL_RESET_SHIFT)
    #define WBO2_PWM_ADC_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << WBO2_PWM_ADC_CTRL_CMPMODE2_SHIFT)
    #define WBO2_PWM_ADC_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << WBO2_PWM_ADC_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define WBO2_PWM_ADC_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define WBO2_PWM_ADC_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << WBO2_PWM_ADC_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define WBO2_PWM_ADC_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define WBO2_PWM_ADC_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define WBO2_PWM_ADC_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define WBO2_PWM_ADC_STATUS_TC_INT_EN_MASK_SHIFT            (WBO2_PWM_ADC_STATUS_TC_SHIFT - 4u)
    #define WBO2_PWM_ADC_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define WBO2_PWM_ADC_STATUS_CMP1_INT_EN_MASK_SHIFT          (WBO2_PWM_ADC_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define WBO2_PWM_ADC_STATUS_TC              (uint8)((uint8)0x01u << WBO2_PWM_ADC_STATUS_TC_SHIFT)
    #define WBO2_PWM_ADC_STATUS_CMP1            (uint8)((uint8)0x01u << WBO2_PWM_ADC_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define WBO2_PWM_ADC_STATUS_TC_INT_EN_MASK              (uint8)((uint8)WBO2_PWM_ADC_STATUS_TC >> 4u)
    #define WBO2_PWM_ADC_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)WBO2_PWM_ADC_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define WBO2_PWM_ADC_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define WBO2_PWM_ADC_RT1_MASK              (uint8)((uint8)0x03u << WBO2_PWM_ADC_RT1_SHIFT)
    #define WBO2_PWM_ADC_SYNC                  (uint8)((uint8)0x03u << WBO2_PWM_ADC_RT1_SHIFT)
    #define WBO2_PWM_ADC_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define WBO2_PWM_ADC_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << WBO2_PWM_ADC_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define WBO2_PWM_ADC_SYNCDSI_EN            (uint8)((uint8)0x0Fu << WBO2_PWM_ADC_SYNCDSI_SHIFT)


#else
    #define WBO2_PWM_ADC_STATUS                (*(reg8 *)   WBO2_PWM_ADC_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define WBO2_PWM_ADC_STATUS_PTR            ((reg8 *)    WBO2_PWM_ADC_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define WBO2_PWM_ADC_STATUS_MASK           (*(reg8 *)   WBO2_PWM_ADC_PWMUDB_genblk8_stsreg__MASK_REG)
    #define WBO2_PWM_ADC_STATUS_MASK_PTR       ((reg8 *)    WBO2_PWM_ADC_PWMUDB_genblk8_stsreg__MASK_REG)
    #define WBO2_PWM_ADC_STATUS_AUX_CTRL       (*(reg8 *)   WBO2_PWM_ADC_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define WBO2_PWM_ADC_CONTROL               (*(reg8 *)   WBO2_PWM_ADC_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define WBO2_PWM_ADC_CONTROL_PTR           ((reg8 *)    WBO2_PWM_ADC_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define WBO2_PWM_ADC_CTRL_ENABLE_SHIFT      (0x07u)
    #define WBO2_PWM_ADC_CTRL_RESET_SHIFT       (0x06u)
    #define WBO2_PWM_ADC_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define WBO2_PWM_ADC_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define WBO2_PWM_ADC_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define WBO2_PWM_ADC_CTRL_ENABLE            (uint8)((uint8)0x01u << WBO2_PWM_ADC_CTRL_ENABLE_SHIFT)
    #define WBO2_PWM_ADC_CTRL_RESET             (uint8)((uint8)0x01u << WBO2_PWM_ADC_CTRL_RESET_SHIFT)
    #define WBO2_PWM_ADC_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << WBO2_PWM_ADC_CTRL_CMPMODE2_SHIFT)
    #define WBO2_PWM_ADC_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << WBO2_PWM_ADC_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define WBO2_PWM_ADC_STATUS_KILL_SHIFT          (0x05u)
    #define WBO2_PWM_ADC_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define WBO2_PWM_ADC_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define WBO2_PWM_ADC_STATUS_TC_SHIFT            (0x02u)
    #define WBO2_PWM_ADC_STATUS_CMP2_SHIFT          (0x01u)
    #define WBO2_PWM_ADC_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define WBO2_PWM_ADC_STATUS_KILL_INT_EN_MASK_SHIFT          (WBO2_PWM_ADC_STATUS_KILL_SHIFT)
    #define WBO2_PWM_ADC_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (WBO2_PWM_ADC_STATUS_FIFONEMPTY_SHIFT)
    #define WBO2_PWM_ADC_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (WBO2_PWM_ADC_STATUS_FIFOFULL_SHIFT)
    #define WBO2_PWM_ADC_STATUS_TC_INT_EN_MASK_SHIFT            (WBO2_PWM_ADC_STATUS_TC_SHIFT)
    #define WBO2_PWM_ADC_STATUS_CMP2_INT_EN_MASK_SHIFT          (WBO2_PWM_ADC_STATUS_CMP2_SHIFT)
    #define WBO2_PWM_ADC_STATUS_CMP1_INT_EN_MASK_SHIFT          (WBO2_PWM_ADC_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define WBO2_PWM_ADC_STATUS_KILL            (uint8)((uint8)0x00u << WBO2_PWM_ADC_STATUS_KILL_SHIFT )
    #define WBO2_PWM_ADC_STATUS_FIFOFULL        (uint8)((uint8)0x01u << WBO2_PWM_ADC_STATUS_FIFOFULL_SHIFT)
    #define WBO2_PWM_ADC_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << WBO2_PWM_ADC_STATUS_FIFONEMPTY_SHIFT)
    #define WBO2_PWM_ADC_STATUS_TC              (uint8)((uint8)0x01u << WBO2_PWM_ADC_STATUS_TC_SHIFT)
    #define WBO2_PWM_ADC_STATUS_CMP2            (uint8)((uint8)0x01u << WBO2_PWM_ADC_STATUS_CMP2_SHIFT)
    #define WBO2_PWM_ADC_STATUS_CMP1            (uint8)((uint8)0x01u << WBO2_PWM_ADC_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define WBO2_PWM_ADC_STATUS_KILL_INT_EN_MASK            (WBO2_PWM_ADC_STATUS_KILL)
    #define WBO2_PWM_ADC_STATUS_FIFOFULL_INT_EN_MASK        (WBO2_PWM_ADC_STATUS_FIFOFULL)
    #define WBO2_PWM_ADC_STATUS_FIFONEMPTY_INT_EN_MASK      (WBO2_PWM_ADC_STATUS_FIFONEMPTY)
    #define WBO2_PWM_ADC_STATUS_TC_INT_EN_MASK              (WBO2_PWM_ADC_STATUS_TC)
    #define WBO2_PWM_ADC_STATUS_CMP2_INT_EN_MASK            (WBO2_PWM_ADC_STATUS_CMP2)
    #define WBO2_PWM_ADC_STATUS_CMP1_INT_EN_MASK            (WBO2_PWM_ADC_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define WBO2_PWM_ADC_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define WBO2_PWM_ADC_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define WBO2_PWM_ADC_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define WBO2_PWM_ADC_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define WBO2_PWM_ADC_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* WBO2_PWM_ADC_UsingFixedFunction */

#endif  /* CY_PWM_WBO2_PWM_ADC_H */


/* [] END OF FILE */
