#ifndef __WBO2_h_
#define __WBO2_h_
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
    

void WBO2_init( void );

unsigned char WBO2( void );

// Test function can be removed when we have a functional WBO2 function using the LSU4.9 sensor
unsigned char WBO2_test( unsigned char array_index_nr );
    
#endif
/* [] END OF FILE */
