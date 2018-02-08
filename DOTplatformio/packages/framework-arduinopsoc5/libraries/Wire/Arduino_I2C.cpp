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


extern "C" {
#include <Project.h>
} 

#include "stdint.h"
#include "Arduino_I2C.h"
#include "Arduino_Pins.h"

#define BUS_CLOCK_RATE 24000000

TwoWire Wire = TwoWire();

void TwoWire::begin()
{

#if defined (CY8CKIT059)
    pinMode(22, PERIPHERAL_OD);
    pinMode(23, PERIPHERAL_OD);
#else
    pinMode(A4, PERIPHERAL_OD);
    pinMode(A5, PERIPHERAL_OD);
#endif
    i2cRXBufferSize = 0;
    i2cTXBufferSize = 0;
    
    I2C_Start();
}

void TwoWire::setClock(uint32_t newClockRate)
{
  uint32_t clockDivider = (1/BUS_CLOCK_RATE)*newClockRate;
  twiClock = newClockRate;
  *(uint8_t*)(CYREG_I2C_CLK_DIV1) = (uint8_t)clockDivider;
  *(uint8_t*)(CYREG_I2C_CLK_DIV1) = (uint8_t)((clockDivider>>8)&0x02);
}

void TwoWire::beginTransmission(uint8_t address)
{
    slaveAddress = address;
    i2cRXBufferSize = 0;
    i2cTXBufferSize = 0;
}

void TwoWire::beginTransmission(int address)
{
    slaveAddress = (uint8_t) address;
    i2cRXBufferSize = 0;
    i2cTXBufferSize = 0;
}

uint8_t TwoWire::checkTransmission()
{
    // Return 0 if transfeer not is in progress
    return (I2C_MasterStatus() & I2C_MSTAT_XFER_INP);
}

uint8_t TwoWire::endTransmission(enum XFER_MODE stop)
{
    uint16 internalTimeout = 100;
    uint8_t MasterWriteStatusUint8 = 0;
   
    if ( 0u != (I2C_MasterStatus() & I2C_MSTAT_XFER_INP) )
    {
        return 4;
    }
    
    if (stop == COMPLETE || stop == NO_BLOCK)
    {
        MasterWriteStatusUint8 = I2C_MasterWriteBuf(slaveAddress, i2cTXBuffer, i2cTXBufferSize, \
            I2C_MODE_COMPLETE_XFER);
    }
    else if (stop == REPEATED_START)
    {
        MasterWriteStatusUint8 = I2C_MasterWriteBuf(slaveAddress, i2cTXBuffer, i2cTXBufferSize, \
            I2C_MODE_REPEAT_START);
    }
    else
    {
        MasterWriteStatusUint8 = I2C_MasterWriteBuf(slaveAddress, i2cTXBuffer, i2cTXBufferSize, \
            I2C_MODE_NO_STOP);
    }
    
    if (MasterWriteStatusUint8 == I2C_MSTR_NO_ERROR)
    {
        if ( stop != NO_BLOCK ) // In no_block mode we don't wait to the transfeer is done. This have to be handled in the code
        {
            while (internalTimeout > 0)
            {
                if (0u != (I2C_MasterStatus() & I2C_MSTAT_XFER_INP))
                {
                  CyDelay(1);
                  --internalTimeout;
                  continue;
                }
                else
                {
                    i2cTXBufferSize = 0;
                    return 0;
                }
            }
        }
    }
    return 4; // Return with error 4
}

uint8_t TwoWire::endTransmission()
{
  return endTransmission(COMPLETE);
}
    
uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, \
    enum XFER_MODE stop)
{
    // If an transfer is in progress we cannot request new data
    // It have to be checked in the code if the requested bytes is send or a zero is returned
    if (0u != (I2C_MasterStatus() & I2C_MSTAT_XFER_INP))
    {
        return 0;
    }
    
    uint8_t MasterReadStatusUint8 = 0;
    
    // Max time we will wait for data
    uint16 internalTimeout = 100;
    
    // Reset buffer size and index
    i2cRXBufferSize = 0;
    i2cRXBufferIndex = 0;
    
    // Clear status register
    I2C_MasterClearStatus(); 
    
    // Clear read buffer
    I2C_MasterClearReadBuf(); 
    
    // Initiate read start
    if (stop == COMPLETE)
    {
        MasterReadStatusUint8 = I2C_MasterReadBuf(address, i2cRXBuffer, quantity, \
            I2C_MODE_COMPLETE_XFER);
    }
    else if (stop == REPEATED_START)
    {
        MasterReadStatusUint8 = I2C_MasterReadBuf(address, i2cRXBuffer, quantity, \
            I2C_MODE_REPEAT_START);
    }
    else
    {
        MasterReadStatusUint8 = I2C_MasterReadBuf(address, i2cRXBuffer, quantity, I2C_MODE_NO_STOP);
    }
    
    // Verify that the transfeer started without errors
    if (MasterReadStatusUint8 == I2C_MSTR_NO_ERROR)
    {
        while (internalTimeout > 0)
        {
            // Loop until all data are recived or timeout value is reached
            if (0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT))
            {
              CyDelay(1);
              --internalTimeout;
              continue;
            }
            else
            {
                // Verify that no xfer errors exist before releasing the buffer 
                if (0u == (I2C_MasterStatus() & I2C_MSTAT_ERR_XFER))
                {
                    i2cRXBufferSize = I2C_MasterGetReadBufSize();
                }
                
                // Exit while loop
                break;
            }
        }
    }
    else
    {
        return 0;
    }
    return i2cRXBufferSize;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  return requestFrom(address, quantity, COMPLETE);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (enum XFER_MODE)COMPLETE);
}
    
uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
  return requestFrom((uint8_t) address, (uint8_t) quantity, (enum XFER_MODE)sendStop);
}

size_t TwoWire::write(uint8_t *buffer, uint8_t length)
{
    uint8_t i;
    if (i2cTXBufferSize == 256)
    {
        txOverflow = 1;
        return 0;
    }
    for (i=0; i < length; i++)
    {
        i2cTXBuffer[i2cTXBufferSize+i] = buffer[i];
        if (++i2cTXBufferSize == 256)
        {
            txOverflow = 1;
            return i+1;
        }
    }
    return i;
}

size_t TwoWire::write(uint8_t buffer)
{
  return write((uint8_t *)&buffer, 1);
}

int TwoWire::available()
{
    return i2cRXBufferSize-i2cRXBufferIndex;
}

int TwoWire::read()
{
    if (i2cRXBufferSize > 0)
    {
        int temp = i2cRXBuffer[i2cRXBufferIndex++];
        if (i2cRXBufferSize == i2cRXBufferIndex)
        {
          i2cRXBufferSize = 0;
          i2cRXBufferSize = 0;
        }
        return temp;
    }
    else
    {
        return -1;
    }
}

int TwoWire::peek()
{
    if (i2cRXBufferSize == 0) return -1;
    return i2cRXBuffer[i2cRXBufferSize];
}

void TwoWire::flush()
{
}

/* [] END OF FILE */
