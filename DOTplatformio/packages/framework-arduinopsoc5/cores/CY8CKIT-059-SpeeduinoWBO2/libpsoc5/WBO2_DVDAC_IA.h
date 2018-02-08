/*******************************************************************************
* File Name: WBO2_DVDAC_IA.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the DVDAC component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_DVDAC_WBO2_DVDAC_IA_H)
#define CY_DVDAC_WBO2_DVDAC_IA_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Data Struct Definition
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} WBO2_DVDAC_IA_BACKUP_STRUCT;

/* Component init state */
extern uint8 WBO2_DVDAC_IA_initVar;


/***************************************
*        API constants
***************************************/
#define WBO2_DVDAC_IA_RESOLUTION                 (9u)
#define WBO2_DVDAC_IA_INTERNAL_CLOCK_USED        (1u)

#define WBO2_DVDAC_IA_INTEGER_PORTION_SHIFT      (WBO2_DVDAC_IA_RESOLUTION - 8u)
#define WBO2_DVDAC_IA_DITHERED_ARRAY_SIZE        ((uint8)(1u << WBO2_DVDAC_IA_INTEGER_PORTION_SHIFT))
#define WBO2_DVDAC_IA_FRACTIONAL_PORTION_MASK    (WBO2_DVDAC_IA_DITHERED_ARRAY_SIZE - 1u)
#define WBO2_DVDAC_IA_INTEGER_PORTION_MAX_VALUE  (0xFFu)

/* DMA Configuration */
#define WBO2_DVDAC_IA_DMA_BYTES_PER_BURST        (1u)
#define WBO2_DVDAC_IA_DMA_REQUEST_PER_BURST      (1u)
#define WBO2_DVDAC_IA_DMA_SRC_BASE               (CYDEV_SRAM_BASE)
#define WBO2_DVDAC_IA_DMA_DST_BASE               (CYDEV_PERIPH_BASE)


#if   (WBO2_DVDAC_IA_RESOLUTION ==  9u)
    #define WBO2_DVDAC_IA_DVDAC_MAX_VALUE        (0x1FEu)
#elif (WBO2_DVDAC_IA_RESOLUTION == 10u)
    #define WBO2_DVDAC_IA_DVDAC_MAX_VALUE        (0x3FCu)
#elif (WBO2_DVDAC_IA_RESOLUTION == 11u)
    #define WBO2_DVDAC_IA_DVDAC_MAX_VALUE        (0x7F8u)
#else   /* Resolution 12 bits */
    #define WBO2_DVDAC_IA_DVDAC_MAX_VALUE        (0xFF0u)
#endif  /* (WBO2_DVDAC_IA_RESOLUTION ==  9u) */


/***************************************
*        Function Prototypes
***************************************/

void WBO2_DVDAC_IA_Init(void)                ;
void WBO2_DVDAC_IA_Enable(void)              ;
void WBO2_DVDAC_IA_Start(void)               ;
void WBO2_DVDAC_IA_Stop(void)                ;
void WBO2_DVDAC_IA_SetValue(uint16 value)    ;
void WBO2_DVDAC_IA_Sleep(void)               ;
void WBO2_DVDAC_IA_Wakeup(void)              ;
void WBO2_DVDAC_IA_SaveConfig(void)          ;
void WBO2_DVDAC_IA_RestoreConfig(void)       ;

#endif /* CY_DVDAC_WBO2_DVDAC_IA_H */


/* [] END OF FILE */
