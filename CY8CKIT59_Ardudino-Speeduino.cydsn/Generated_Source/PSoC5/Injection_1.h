/*******************************************************************************
* File Name: Injection_1.h
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

#if !defined(CY_PWM_Injection_1_H)
#define CY_PWM_Injection_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Injection_1_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Injection_1_Resolution                     (16u)
#define Injection_1_UsingFixedFunction             (0u)
#define Injection_1_DeadBandMode                   (0u)
#define Injection_1_KillModeMinTime                (0u)
#define Injection_1_KillMode                       (0u)
#define Injection_1_PWMMode                        (0u)
#define Injection_1_PWMModeIsCenterAligned         (0u)
#define Injection_1_DeadBandUsed                   (0u)
#define Injection_1_DeadBand2_4                    (0u)

#if !defined(Injection_1_PWMUDB_genblk8_stsreg__REMOVED)
    #define Injection_1_UseStatus                  (1u)
#else
    #define Injection_1_UseStatus                  (0u)
#endif /* !defined(Injection_1_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Injection_1_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Injection_1_UseControl                 (1u)
#else
    #define Injection_1_UseControl                 (0u)
#endif /* !defined(Injection_1_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Injection_1_UseOneCompareMode              (1u)
#define Injection_1_MinimumKillTime                (1u)
#define Injection_1_EnableMode                     (0u)

#define Injection_1_CompareMode1SW                 (0u)
#define Injection_1_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Injection_1__B_PWM__DISABLED 0
#define Injection_1__B_PWM__ASYNCHRONOUS 1
#define Injection_1__B_PWM__SINGLECYCLE 2
#define Injection_1__B_PWM__LATCHED 3
#define Injection_1__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Injection_1__B_PWM__DBMDISABLED 0
#define Injection_1__B_PWM__DBM_2_4_CLOCKS 1
#define Injection_1__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Injection_1__B_PWM__ONE_OUTPUT 0
#define Injection_1__B_PWM__TWO_OUTPUTS 1
#define Injection_1__B_PWM__DUAL_EDGE 2
#define Injection_1__B_PWM__CENTER_ALIGN 3
#define Injection_1__B_PWM__DITHER 5
#define Injection_1__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Injection_1__B_PWM__LESS_THAN 1
#define Injection_1__B_PWM__LESS_THAN_OR_EQUAL 2
#define Injection_1__B_PWM__GREATER_THAN 3
#define Injection_1__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Injection_1__B_PWM__EQUAL 0
#define Injection_1__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Injection_1_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Injection_1_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Injection_1_PWMModeIsCenterAligned) */
        #if (Injection_1_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Injection_1_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Injection_1_DeadBandMode == Injection_1__B_PWM__DBM_256_CLOCKS || \
            Injection_1_DeadBandMode == Injection_1__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Injection_1_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Injection_1_KillModeMinTime) */

        /* Backup control register */
        #if(Injection_1_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Injection_1_UseControl) */

    #endif /* (!Injection_1_UsingFixedFunction) */

}Injection_1_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Injection_1_Start(void) ;
void    Injection_1_Stop(void) ;

#if (Injection_1_UseStatus || Injection_1_UsingFixedFunction)
    void  Injection_1_SetInterruptMode(uint8 interruptMode) ;
    uint8 Injection_1_ReadStatusRegister(void) ;
#endif /* (Injection_1_UseStatus || Injection_1_UsingFixedFunction) */

#define Injection_1_GetInterruptSource() Injection_1_ReadStatusRegister()

#if (Injection_1_UseControl)
    uint8 Injection_1_ReadControlRegister(void) ;
    void  Injection_1_WriteControlRegister(uint8 control)
          ;
#endif /* (Injection_1_UseControl) */

#if (Injection_1_UseOneCompareMode)
   #if (Injection_1_CompareMode1SW)
       void    Injection_1_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Injection_1_CompareMode1SW) */
#else
    #if (Injection_1_CompareMode1SW)
        void    Injection_1_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Injection_1_CompareMode1SW) */
    #if (Injection_1_CompareMode2SW)
        void    Injection_1_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Injection_1_CompareMode2SW) */
#endif /* (Injection_1_UseOneCompareMode) */

#if (!Injection_1_UsingFixedFunction)
    uint16   Injection_1_ReadCounter(void) ;
    uint16 Injection_1_ReadCapture(void) ;

    #if (Injection_1_UseStatus)
            void Injection_1_ClearFIFO(void) ;
    #endif /* (Injection_1_UseStatus) */

    void    Injection_1_WriteCounter(uint16 counter)
            ;
#endif /* (!Injection_1_UsingFixedFunction) */

void    Injection_1_WritePeriod(uint16 period)
        ;
uint16 Injection_1_ReadPeriod(void) ;

#if (Injection_1_UseOneCompareMode)
    void    Injection_1_WriteCompare(uint16 compare)
            ;
    uint16 Injection_1_ReadCompare(void) ;
#else
    void    Injection_1_WriteCompare1(uint16 compare)
            ;
    uint16 Injection_1_ReadCompare1(void) ;
    void    Injection_1_WriteCompare2(uint16 compare)
            ;
    uint16 Injection_1_ReadCompare2(void) ;
#endif /* (Injection_1_UseOneCompareMode) */


#if (Injection_1_DeadBandUsed)
    void    Injection_1_WriteDeadTime(uint8 deadtime) ;
    uint8   Injection_1_ReadDeadTime(void) ;
#endif /* (Injection_1_DeadBandUsed) */

#if ( Injection_1_KillModeMinTime)
    void Injection_1_WriteKillTime(uint8 killtime) ;
    uint8 Injection_1_ReadKillTime(void) ;
#endif /* ( Injection_1_KillModeMinTime) */

void Injection_1_Init(void) ;
void Injection_1_Enable(void) ;
void Injection_1_Sleep(void) ;
void Injection_1_Wakeup(void) ;
void Injection_1_SaveConfig(void) ;
void Injection_1_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Injection_1_INIT_PERIOD_VALUE          (45000u)
#define Injection_1_INIT_COMPARE_VALUE1        (32000u)
#define Injection_1_INIT_COMPARE_VALUE2        (15000u)
#define Injection_1_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Injection_1_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Injection_1_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Injection_1_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Injection_1_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Injection_1_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Injection_1_CTRL_CMPMODE2_SHIFT)
#define Injection_1_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Injection_1_CTRL_CMPMODE1_SHIFT)
#define Injection_1_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Injection_1_UsingFixedFunction)
   #define Injection_1_PERIOD_LSB              (*(reg16 *) Injection_1_PWMHW__PER0)
   #define Injection_1_PERIOD_LSB_PTR          ( (reg16 *) Injection_1_PWMHW__PER0)
   #define Injection_1_COMPARE1_LSB            (*(reg16 *) Injection_1_PWMHW__CNT_CMP0)
   #define Injection_1_COMPARE1_LSB_PTR        ( (reg16 *) Injection_1_PWMHW__CNT_CMP0)
   #define Injection_1_COMPARE2_LSB            (0x00u)
   #define Injection_1_COMPARE2_LSB_PTR        (0x00u)
   #define Injection_1_COUNTER_LSB             (*(reg16 *) Injection_1_PWMHW__CNT_CMP0)
   #define Injection_1_COUNTER_LSB_PTR         ( (reg16 *) Injection_1_PWMHW__CNT_CMP0)
   #define Injection_1_CAPTURE_LSB             (*(reg16 *) Injection_1_PWMHW__CAP0)
   #define Injection_1_CAPTURE_LSB_PTR         ( (reg16 *) Injection_1_PWMHW__CAP0)
   #define Injection_1_RT1                     (*(reg8 *)  Injection_1_PWMHW__RT1)
   #define Injection_1_RT1_PTR                 ( (reg8 *)  Injection_1_PWMHW__RT1)

#else
   #if (Injection_1_Resolution == 8u) /* 8bit - PWM */

       #if(Injection_1_PWMModeIsCenterAligned)
           #define Injection_1_PERIOD_LSB      (*(reg8 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Injection_1_PERIOD_LSB_PTR  ((reg8 *)   Injection_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Injection_1_PERIOD_LSB      (*(reg8 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Injection_1_PERIOD_LSB_PTR  ((reg8 *)   Injection_1_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Injection_1_PWMModeIsCenterAligned) */

       #define Injection_1_COMPARE1_LSB        (*(reg8 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Injection_1_COMPARE1_LSB_PTR    ((reg8 *)   Injection_1_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Injection_1_COMPARE2_LSB        (*(reg8 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Injection_1_COMPARE2_LSB_PTR    ((reg8 *)   Injection_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Injection_1_COUNTERCAP_LSB      (*(reg8 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Injection_1_COUNTERCAP_LSB_PTR  ((reg8 *)   Injection_1_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Injection_1_COUNTER_LSB         (*(reg8 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Injection_1_COUNTER_LSB_PTR     ((reg8 *)   Injection_1_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Injection_1_CAPTURE_LSB         (*(reg8 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Injection_1_CAPTURE_LSB_PTR     ((reg8 *)   Injection_1_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Injection_1_PWMModeIsCenterAligned)
               #define Injection_1_PERIOD_LSB      (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Injection_1_PERIOD_LSB_PTR  ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Injection_1_PERIOD_LSB      (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Injection_1_PERIOD_LSB_PTR  ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Injection_1_PWMModeIsCenterAligned) */

            #define Injection_1_COMPARE1_LSB       (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Injection_1_COMPARE1_LSB_PTR   ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Injection_1_COMPARE2_LSB       (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Injection_1_COMPARE2_LSB_PTR   ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Injection_1_COUNTERCAP_LSB     (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Injection_1_COUNTERCAP_LSB_PTR ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Injection_1_COUNTER_LSB        (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Injection_1_COUNTER_LSB_PTR    ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Injection_1_CAPTURE_LSB        (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Injection_1_CAPTURE_LSB_PTR    ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Injection_1_PWMModeIsCenterAligned)
               #define Injection_1_PERIOD_LSB      (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Injection_1_PERIOD_LSB_PTR  ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Injection_1_PERIOD_LSB      (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Injection_1_PERIOD_LSB_PTR  ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Injection_1_PWMModeIsCenterAligned) */

            #define Injection_1_COMPARE1_LSB       (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Injection_1_COMPARE1_LSB_PTR   ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Injection_1_COMPARE2_LSB       (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Injection_1_COMPARE2_LSB_PTR   ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Injection_1_COUNTERCAP_LSB     (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Injection_1_COUNTERCAP_LSB_PTR ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Injection_1_COUNTER_LSB        (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Injection_1_COUNTER_LSB_PTR    ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Injection_1_CAPTURE_LSB        (*(reg16 *) Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Injection_1_CAPTURE_LSB_PTR    ((reg16 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Injection_1_AUX_CONTROLDP1          (*(reg8 *)  Injection_1_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Injection_1_AUX_CONTROLDP1_PTR      ((reg8 *)   Injection_1_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Injection_1_Resolution == 8) */

   #define Injection_1_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Injection_1_AUX_CONTROLDP0          (*(reg8 *)  Injection_1_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Injection_1_AUX_CONTROLDP0_PTR      ((reg8 *)   Injection_1_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Injection_1_UsingFixedFunction) */

#if(Injection_1_KillModeMinTime )
    #define Injection_1_KILLMODEMINTIME        (*(reg8 *)  Injection_1_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Injection_1_KILLMODEMINTIME_PTR    ((reg8 *)   Injection_1_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Injection_1_KillModeMinTime ) */

#if(Injection_1_DeadBandMode == Injection_1__B_PWM__DBM_256_CLOCKS)
    #define Injection_1_DEADBAND_COUNT         (*(reg8 *)  Injection_1_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Injection_1_DEADBAND_COUNT_PTR     ((reg8 *)   Injection_1_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Injection_1_DEADBAND_LSB_PTR       ((reg8 *)   Injection_1_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Injection_1_DEADBAND_LSB           (*(reg8 *)  Injection_1_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Injection_1_DeadBandMode == Injection_1__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Injection_1_UsingFixedFunction)
        #define Injection_1_DEADBAND_COUNT         (*(reg8 *)  Injection_1_PWMHW__CFG0)
        #define Injection_1_DEADBAND_COUNT_PTR     ((reg8 *)   Injection_1_PWMHW__CFG0)
        #define Injection_1_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Injection_1_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Injection_1_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Injection_1_DEADBAND_COUNT         (*(reg8 *)  Injection_1_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Injection_1_DEADBAND_COUNT_PTR     ((reg8 *)   Injection_1_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Injection_1_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Injection_1_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Injection_1_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Injection_1_UsingFixedFunction) */
#endif /* (Injection_1_DeadBandMode == Injection_1__B_PWM__DBM_256_CLOCKS) */



#if (Injection_1_UsingFixedFunction)
    #define Injection_1_STATUS                 (*(reg8 *) Injection_1_PWMHW__SR0)
    #define Injection_1_STATUS_PTR             ((reg8 *) Injection_1_PWMHW__SR0)
    #define Injection_1_STATUS_MASK            (*(reg8 *) Injection_1_PWMHW__SR0)
    #define Injection_1_STATUS_MASK_PTR        ((reg8 *) Injection_1_PWMHW__SR0)
    #define Injection_1_CONTROL                (*(reg8 *) Injection_1_PWMHW__CFG0)
    #define Injection_1_CONTROL_PTR            ((reg8 *) Injection_1_PWMHW__CFG0)
    #define Injection_1_CONTROL2               (*(reg8 *) Injection_1_PWMHW__CFG1)
    #define Injection_1_CONTROL3               (*(reg8 *) Injection_1_PWMHW__CFG2)
    #define Injection_1_GLOBAL_ENABLE          (*(reg8 *) Injection_1_PWMHW__PM_ACT_CFG)
    #define Injection_1_GLOBAL_ENABLE_PTR      ( (reg8 *) Injection_1_PWMHW__PM_ACT_CFG)
    #define Injection_1_GLOBAL_STBY_ENABLE     (*(reg8 *) Injection_1_PWMHW__PM_STBY_CFG)
    #define Injection_1_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Injection_1_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Injection_1_BLOCK_EN_MASK          (Injection_1_PWMHW__PM_ACT_MSK)
    #define Injection_1_BLOCK_STBY_EN_MASK     (Injection_1_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Injection_1_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Injection_1_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Injection_1_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Injection_1_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Injection_1_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Injection_1_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Injection_1_CTRL_ENABLE            (uint8)((uint8)0x01u << Injection_1_CTRL_ENABLE_SHIFT)
    #define Injection_1_CTRL_RESET             (uint8)((uint8)0x01u << Injection_1_CTRL_RESET_SHIFT)
    #define Injection_1_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Injection_1_CTRL_CMPMODE2_SHIFT)
    #define Injection_1_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Injection_1_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Injection_1_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Injection_1_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Injection_1_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Injection_1_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Injection_1_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Injection_1_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Injection_1_STATUS_TC_INT_EN_MASK_SHIFT            (Injection_1_STATUS_TC_SHIFT - 4u)
    #define Injection_1_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Injection_1_STATUS_CMP1_INT_EN_MASK_SHIFT          (Injection_1_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Injection_1_STATUS_TC              (uint8)((uint8)0x01u << Injection_1_STATUS_TC_SHIFT)
    #define Injection_1_STATUS_CMP1            (uint8)((uint8)0x01u << Injection_1_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Injection_1_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Injection_1_STATUS_TC >> 4u)
    #define Injection_1_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Injection_1_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Injection_1_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Injection_1_RT1_MASK              (uint8)((uint8)0x03u << Injection_1_RT1_SHIFT)
    #define Injection_1_SYNC                  (uint8)((uint8)0x03u << Injection_1_RT1_SHIFT)
    #define Injection_1_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Injection_1_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Injection_1_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Injection_1_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Injection_1_SYNCDSI_SHIFT)


#else
    #define Injection_1_STATUS                (*(reg8 *)   Injection_1_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Injection_1_STATUS_PTR            ((reg8 *)    Injection_1_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Injection_1_STATUS_MASK           (*(reg8 *)   Injection_1_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Injection_1_STATUS_MASK_PTR       ((reg8 *)    Injection_1_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Injection_1_STATUS_AUX_CTRL       (*(reg8 *)   Injection_1_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Injection_1_CONTROL               (*(reg8 *)   Injection_1_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Injection_1_CONTROL_PTR           ((reg8 *)    Injection_1_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Injection_1_CTRL_ENABLE_SHIFT      (0x07u)
    #define Injection_1_CTRL_RESET_SHIFT       (0x06u)
    #define Injection_1_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Injection_1_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Injection_1_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Injection_1_CTRL_ENABLE            (uint8)((uint8)0x01u << Injection_1_CTRL_ENABLE_SHIFT)
    #define Injection_1_CTRL_RESET             (uint8)((uint8)0x01u << Injection_1_CTRL_RESET_SHIFT)
    #define Injection_1_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Injection_1_CTRL_CMPMODE2_SHIFT)
    #define Injection_1_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Injection_1_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Injection_1_STATUS_KILL_SHIFT          (0x05u)
    #define Injection_1_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Injection_1_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Injection_1_STATUS_TC_SHIFT            (0x02u)
    #define Injection_1_STATUS_CMP2_SHIFT          (0x01u)
    #define Injection_1_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Injection_1_STATUS_KILL_INT_EN_MASK_SHIFT          (Injection_1_STATUS_KILL_SHIFT)
    #define Injection_1_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Injection_1_STATUS_FIFONEMPTY_SHIFT)
    #define Injection_1_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Injection_1_STATUS_FIFOFULL_SHIFT)
    #define Injection_1_STATUS_TC_INT_EN_MASK_SHIFT            (Injection_1_STATUS_TC_SHIFT)
    #define Injection_1_STATUS_CMP2_INT_EN_MASK_SHIFT          (Injection_1_STATUS_CMP2_SHIFT)
    #define Injection_1_STATUS_CMP1_INT_EN_MASK_SHIFT          (Injection_1_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Injection_1_STATUS_KILL            (uint8)((uint8)0x00u << Injection_1_STATUS_KILL_SHIFT )
    #define Injection_1_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Injection_1_STATUS_FIFOFULL_SHIFT)
    #define Injection_1_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Injection_1_STATUS_FIFONEMPTY_SHIFT)
    #define Injection_1_STATUS_TC              (uint8)((uint8)0x01u << Injection_1_STATUS_TC_SHIFT)
    #define Injection_1_STATUS_CMP2            (uint8)((uint8)0x01u << Injection_1_STATUS_CMP2_SHIFT)
    #define Injection_1_STATUS_CMP1            (uint8)((uint8)0x01u << Injection_1_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Injection_1_STATUS_KILL_INT_EN_MASK            (Injection_1_STATUS_KILL)
    #define Injection_1_STATUS_FIFOFULL_INT_EN_MASK        (Injection_1_STATUS_FIFOFULL)
    #define Injection_1_STATUS_FIFONEMPTY_INT_EN_MASK      (Injection_1_STATUS_FIFONEMPTY)
    #define Injection_1_STATUS_TC_INT_EN_MASK              (Injection_1_STATUS_TC)
    #define Injection_1_STATUS_CMP2_INT_EN_MASK            (Injection_1_STATUS_CMP2)
    #define Injection_1_STATUS_CMP1_INT_EN_MASK            (Injection_1_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Injection_1_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Injection_1_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Injection_1_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Injection_1_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Injection_1_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Injection_1_UsingFixedFunction */

#endif  /* CY_PWM_Injection_1_H */


/* [] END OF FILE */
