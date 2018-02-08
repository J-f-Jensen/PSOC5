/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <stdint.h>

//extern "C" {
#include <Project.h>
//}

#include "WBO2.h"

/* There are 2 input channels but we need to read 3 different values, and due to that the LUT is used to create the RE pumpe pulses we get 4 values */
#define NUMCHAN (4u)

/* 8-bit wide SRAM buffer with 4 locations used when DMA writes ADC readings */
uint8_t WBO2_ADC_RESULT[NUMCHAN];

/* Define(s) used in WBO2_DMA */
#define WBO2_DMA_BYTES_PER_BURST 1
#define WBO2_DMA_REQUEST_PER_BURST 1
#define WBO2_DMA_SRC_BASE (CYDEV_PERIPH_BASE)
#define WBO2_DMA_DST_BASE (CYDEV_SRAM_BASE)

// Internal functions
void WBO2_DMA_init( void );
CY_ISR(WBO2_ISR_Function);
void Heater_PID(void);
void Ia_PID(void);
signed int IIR_Int(signed int Vin, signed int Vout, unsigned char A);

unsigned char Ia_PID_Counter=0;
unsigned char Vout_Lookup_Counter=0;
unsigned char Heater_PID_Counter=0;
unsigned char Heatup_Counter=0;
signed int Ri_Min;
signed int Ri_Max;
signed int ip;
signed int ip_Justified;
unsigned char Lambda_x100;
signed int LSU_Temperature_C;

unsigned long temp_ulong;
signed int temp_int;
signed int temp_int2;
unsigned char temp_unsigned_char;

unsigned char Ri_Max_x1;
unsigned char Ri_Min_x1;
unsigned char ip_x1;
unsigned char ADC_IF;

// Needed ??
unsigned char ADC_Counter;
unsigned char Sleep_Counter;

//#ifdef Lin_Out
	#define ip_to_Vout_Lookup_Start 135
	#define ip_to_Vout_Lookup_Size 158
	const uint8_t ip_to_Vout_Lookup[ip_to_Vout_Lookup_Size] = {0,1,1,2,3,4,4,5,6,7,8,8,9,10,11,12,12,13,14,15,16,17,17,18,19,20,21,22,22,23,24,25,26,27,27,28,29,30,31,32,33,34,34,35,36,37,38,39,40,41,42,43,44,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,76,77,78,79,80,81,82,83,84,86,87,88,89,90,91,92,94,95,96,97,98,100,101,102,103,105,106,107,108,110,111,112,113,115,116,117,119,120,123,126,129,132,135,138,141,144,147,151,154,157,161,164,168,171,175,178,182,186,190,194,197,201,206,210,214,218,222,227,231,236,240,245,250,255}; 
//#endif

#define Ia_PID_Counter_Set 1
#define Heatup_Counter_Set 100
#define Heater_PID_Counter_Set 25
#define Vout_Lookup_Counter_Set 25

//#define PID_Tune
#define Ri_Filter_Strength 4
#define ip_Filter_Strength 4

#ifdef PID_Tune
	signed int Ri_Mid_Target= 271; //256+14.769 = 2.53v = 2.08v(VGND) + 0.45v, PID Target Voltage of Nermest Cell 
	signed int Ia_PID_Kp = 35;
	signed int Ia_PID_Ki = 8;
	signed int Ia_Output_Bias = 256;
	signed int Ri_Delta_Target=143; //PID Target peak to peak Voltage of Nermest Cell
	signed int Heater_PID_Kp =-72;
	signed int Heater_PID_Ki =-4;
	signed int Heater_PID_Output_Bias =128;
#else
	#define Ri_Mid_Target 271 //256+14.769 = 2.53v = 2.08v(VGND) + 0.45v, PID Target Voltage of Nermest Cell
	#define Ia_PID_Kp 25
	#define Ia_PID_Ki 4
	#define Ia_Output_Bias 256
	#define Ri_Delta_Target 143 //PID Target peak to peak Voltage of Nermest Cell
	#define Heater_PID_Kp -72
	#define Heater_PID_Ki -4
	#define Heater_PID_Output_Bias 128
#endif


signed int Ri_Mid_Error_Sum=0;
signed int Ri_Mid;
signed int Ri_Delta_Error_Sum=0;
signed int Ri_Delta;
unsigned char Heatup_Heater_Output=100;

signed int Ri_Delta_Error;
signed int Heater_Output;
signed int Heater_Pout;
signed int Heater_Iout;

//PID Controller, Input is Ri_Delta (The Peak to peak voltage on the Vs Port of the sensor) output is PWM8_Heater, PWM8_Heater is controlled such that Ri_Delta is maintained at 80 (80 =750C)
//Only a PI controller is used as adding the D term does not effect performance 
//Everything is inflated by a factor of 4 so that floating point is avioded
void Heater_PID(void) // Ned to run this when counter >50
{

	Ri_Delta_Error=Ri_Delta_Target-Ri_Delta;
	//Put limits on Error so PID does not go Fubar, and also so that the worst case multiplication does not overflow
	if (Ri_Delta_Error>56)
	{
		Ri_Delta_Error=56;
	}
	if (Ri_Delta_Error<-56)
	{
		Ri_Delta_Error=-56;
	}
	Heater_Pout=(Heater_PID_Kp*Ri_Delta_Error)/16;
	Ri_Delta_Error_Sum=Ri_Delta_Error_Sum+Ri_Delta_Error;
	//If the sensor is too hot, then disreguard the Integratal contribution and just use the proportional to quickly correct the sensor temperature
	/*
	if((Ri_Delta<60)&&(Ri_Delta_Error_Sum>0))
	{
		Ri_Delta_Error_Sum=0;
	}
	*/
	//Put limits on Error so PID does not go Fubar, and also so that the worst case multiplication does not overflow
	if (Ri_Delta_Error_Sum>1024)
	{
		Ri_Delta_Error_Sum=1024;
	}
	if (Ri_Delta_Error_Sum<-1024)
	{
		Ri_Delta_Error_Sum=-1024;
	}
	Heater_Iout=(Heater_PID_Ki*Ri_Delta_Error_Sum)/16;
	if (Heatup_Heater_Output<255) // if Heatup_Heater_Output is < 255 that means the unit just turned on and to give control to the heatup routine
	{
		Heater_Output=Heatup_Heater_Output;	
	}
	else
	{	
		Heater_Output=Heater_PID_Output_Bias+Heater_Pout+Heater_Iout;			
	}
	//Heater_Output=Heater_PID_Output_Bias+Heater_Pout+Heater_Iout;	
	if (Heater_Output<0)
	{
		Heater_Output=0;
	}
	if (Heater_Output>255)
	{
		Heater_Output=255;
	}

    WBO2_PWM8_Heater_WriteCompare(Heater_Output);
}

signed int Ri_Mid_Error;
signed int Ia_Output;
signed int Ia_Pout;
signed int Ia_Iout;
//PID Controller, Input is Ri_Mid (The average voltage on the Vs Port of the sensor) output is DAC9_Ia, DAC9_Ia sink/sources current to the Sensor pump cell such that Ri_Mid is is the same voltage as Vref
//Only a PI controller is used as adding the D term does not effect performance 
//Everything is inflated by a factor of 4 so that floating point is avioded
void Ia_PID(void)
{


	Ri_Mid_Error=Ri_Mid_Target-Ri_Mid;
	//Put limits on Error so PID does not go Fubar, and also so that the worst case multiplication does not overflow
	if (Ri_Mid_Error>163)
	{
		Ri_Mid_Error=163;
	}
	if (Ri_Mid_Error<-163)
	{
		Ri_Mid_Error=-163;
	}
	Ia_Pout=(Ia_PID_Kp*Ri_Mid_Error)/16;
	Ri_Mid_Error_Sum=Ri_Mid_Error_Sum+Ri_Mid_Error;
	//Put limits on Error so PID does not go Fubar, and also so that the worst case multiplication does not overflow
	if (Ri_Mid_Error_Sum>1020)
	{
		Ri_Mid_Error_Sum=1020;
	}
	if (Ri_Mid_Error_Sum<-1020)
	{
		Ri_Mid_Error_Sum=-1020;
	}
	Ia_Iout=(Ia_PID_Ki*Ri_Mid_Error_Sum)/16;
	Ia_Output=Ia_Output_Bias+Ia_Pout+Ia_Iout;
	//9 Bit Dac so only 0-511 is allowed, for some reason i put the limit at 510, I foget exactly why.
	if (Ia_Output<0)
	{
		Ia_Output=0;
	}
	if (Ia_Output>510)
	{
		Ia_Output=510;
	}
	WBO2_DVDAC_IA_SetValue(Ia_Output);
}


signed int IIR_Int(signed int Vin, signed int Vout, unsigned char A)
{
	return (Vout + (Vin - Vout)/A);
}

// inilisation of all the functions used in the WBO2
void WBO2_init( void )
{
    // Start Heater PWM
    WBO2_PWM8_Heater_Start();
    
    //
   WBO2_isr_StartEx(WBO2_ISR_Function);
    
    // Start ADC
    WBO2_ADCINC_Start();
    
    // Setup DMA used for ADC data
    WBO2_DMA_init();
    
    // Start ADC trigger PWM
    WBO2_PWM_ADC_Start();
    
    // Enable ADC SOC to be triggered by PWM output
    WBO2_Control_Reg_Write(1u);
}

// This function is called by DMA nrq interrupt at ~ 512 Hz ~ every 2 milli secund
CY_ISR(WBO2_ISR_Function)
{
	temp_ulong++;
    
    // Increment the different counters used
    Ia_PID_Counter++;
	Heater_PID_Counter++;
	Heatup_Counter++;
	Vout_Lookup_Counter++;
  
    // This needs to be verified - WBO2_ADC_RESULT should hold all values needed - but needs testing
    // Get Ri_Min value
	Ri_Min_x1 = WBO2_ADC_RESULT[1]; 
	Ri_Min=IIR_Int(Ri_Min_x1*2,Ri_Min,Ri_Filter_Strength);

    // Get Ri_Max value
	Ri_Max_x1 = WBO2_ADC_RESULT[0];
	Ri_Max=IIR_Int(Ri_Max_x1*2,Ri_Max,Ri_Filter_Strength);
    
    // Calculate Ri_Delta and Ri_Mid
	Ri_Delta=Ri_Max-Ri_Min;
	Ri_Mid=(Ri_Max+Ri_Min)/2;

    // Get ip value - it should be in both WBO2_ADC_RESULT[2] and WBO2_ADC_RESULT[3]
    // If it makes sense we could use both to get a better filtering
	ip_x1 = WBO2_ADC_RESULT[3];
	ip=IIR_Int(ip_x1*2,ip,ip_Filter_Strength);
    
	if (Ia_PID_Counter>Ia_PID_Counter_Set)
	{
		Ia_PID_Counter=0;
		Ia_PID();
	}
    
    // If Heater_PID_Counter_Set continues to be one then remove this check to optimize speed!!
	if (Heater_PID_Counter>Heater_PID_Counter_Set)
	{
		Heater_PID_Counter=0;
		Heater_PID();
	}

// This could/needs to be moved to an function to get the LAMBDA or AFR value from the WBO2 class - current ip is only internal
//	if (Vout_Lookup_Counter>Vout_Lookup_Counter_Set)
//	{
//		Vout_Lookup_Counter=0;
//		temp_int=ip-ip_to_Vout_Lookup_Start;
//		if (temp_int<0)
//		{
//			temp_int=0;
//		}
//		if (temp_int>(ip_to_Vout_Lookup_Size-1))
//		{
//			temp_int=(ip_to_Vout_Lookup_Size-1);
//		}
//	}

	if (Heatup_Heater_Output<255)
	{   
		if (Heatup_Counter>Heatup_Counter_Set)
		{
			Heatup_Counter=0;
			Heatup_Heater_Output++;
		}
		if ((Ri_Min>50) && (Ri_Max<475) && (Ri_Delta<Ri_Delta_Target))
		{
			Heatup_Heater_Output=255;
			Ri_Delta_Error_Sum=0;
		}
	}
}

// Test function - can be removed when we have a functional WBO2 function using the LSU4.9 sensor
// Return ADC values
unsigned char WBO2_test( unsigned char array_index_nr )
{
    if (array_index_nr >= 0 || array_index_nr < 4)
    {
        return WBO2_ADC_RESULT[array_index_nr];
    }
    else
        return -1;
}

void WBO2_DMA_init() 
{
    /* Variable declarations for WBO2_DMA */
    uint8 WBO2_DMA_Chan;
    uint8 WBO2_DMA_TD[1];

    /* DMA Configuration for WBO2_DMA */
    /* Iniitialize DMA channel */
    WBO2_DMA_Chan = WBO2_DMA_DmaInitialize(WBO2_DMA_BYTES_PER_BURST, WBO2_DMA_REQUEST_PER_BURST, 
        HI16(WBO2_DMA_SRC_BASE), HI16(WBO2_DMA_DST_BASE));
    
    /* Allocate TD */
    WBO2_DMA_TD[0] = CyDmaTdAllocate();
    
    /* TD configuration setting */
    CyDmaTdSetConfiguration(WBO2_DMA_TD[0], 1u * NUMCHAN, WBO2_DMA_TD[0], CY_DMA_TD_INC_DST_ADR);
    
    // TD configuration with termial out - nrq
    //CyDmaTdSetConfiguration(WBO2_DMA_TD[0], 1u * NUMCHAN, WBO2_DMA_TD[0], WBO2_DMA__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    
    /* Set Source and Destination address */
    CyDmaTdSetAddress(WBO2_DMA_TD[0], LO16((uint32)WBO2_ADCINC_DEC_SAMP_PTR), LO16((uint32)WBO2_ADC_RESULT));
    
    /* TD initialization */
    CyDmaChSetInitialTd(WBO2_DMA_Chan, WBO2_DMA_TD[0]);
    
    /* Enable the DMA channel */
    CyDmaChEnable(WBO2_DMA_Chan, 1);
}

/* [] END OF FILE */
