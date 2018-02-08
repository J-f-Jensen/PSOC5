/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "USBUARTClass.h"
extern "C" {
#include <project.h>
}

// Wait for PC to configure USB for CONFIG_DELAY * CONFIG_LOOPS milliseconds
#define CONFIG_DELAY 10
#define CONFIG_LOOPS 200

bool USBUARTClass::_hasBegun = false;

//Required to load the class
USBUARTClass Serial(1);

// Public Methods //////////////////////////////////////////////////////////////

USBUARTClass::USBUARTClass(int)
{
}

void USBUARTClass::begin(const uint32_t dwBaudRate)
{
  if (_hasBegun)
  {
    return;
  }

  _hasBegun = true;
  
  _enableUSBCDC();
}

void USBUARTClass::end( void )
{
  //Not implemented
}

int USBUARTClass::available( void )
{
  buffer();
  return _appBuffSize;
}

int USBUARTClass::peek( void )
{
  buffer();
  if (_appBuffSize > 0)
  {
    return _appBuffer[_appBuffIndex];
  }
  else
  {
    return -1;
  }
}

int USBUARTClass::read( void )
{
  buffer();
  if (_appBuffSize > 0)
  {
    int temp = _appBuffer[_appBuffIndex++];
    if (_appBuffIndex == _appBuffSize)
    {
      _appBuffIndex = 0;
      _appBuffSize = 0;
    }
    return temp;
  }
  else
  {
    return -1;
  }
}

void USBUARTClass::flush( void )
{
  // Not implemented
}

uint8_t USBUARTClass::buffer( void )
{
  uint8_t dataBufferSize = _usb_serial_CustomGetCount();

  if (dataBufferSize > 0)
  {
    // We need to check if there is space in the buffer to recive data, if not then we have to wait until the buffer is read
    if ((_appBuffSize + dataBufferSize) < 63)
    {
        USBUART_GetData((_appBuffer+_appBuffSize), dataBufferSize);
        _appBuffSize += dataBufferSize;
    }
  }
  return _appBuffSize;
}

size_t USBUARTClass::write( const uint8_t uc_data )
{
  uint8_t delayCounter = 0;
  
  /* wait for the port to be ready */   
  while (USBUART_CDCIsReady() == 0)
  {  
    CyDelay(1);
    delayCounter++;
    if (delayCounter > 2000)
    {
      return 0;
    }
  }
  
  /* Send data */
  USBUART_PutChar(uc_data);
  return 1;
}


// Private Methods //////////////////////////////////////////////////////////////

bool USBUARTClass::_enableUSBCDC()
{
  _appBuffSize = 0;
  _appBuffIndex = 0;
  _timeout = 10;
  
  USBUART_Start(0, USBUART_5V_OPERATION);
  uint8_t delayCounter = 0;
  /* It's important that we not loop forever here, or we'll never leave in
   * cases where the device isn't plugged into a PC. We do, however, want to
   * provide enough time for the PC to do its thing. */  
  while(USBUART_GetConfiguration() == 0)
  {  
    CyDelay(100);
    delayCounter++;
    if (delayCounter > 20)
    {
      return false;
    }
  }
  USBUART_CDC_Init();
  return true;
}

size_t USBUARTClass::_usb_serial_readBuffer(const uint8_t* buffer, uint16_t size) // Read buffer methode
{
  return 1; 
}

size_t USBUARTClass::_usb_serial_write( const uint8_t* buffer, uint16_t size )
{
  uint8_t retVal = 0;

  uint16 internalTimeout = 2000;
  uint8 packetsSent = 0;
  uint8 numPackets = size/64;
  uint8 lastPacketSize = size%64;
  /* The sending loop. There are two limits on this:
   1. We can't send data until the prior data transmission is done, so we have
      to wait until USBUART_CDCIsReady() returns a non-zero value.
   2. We can only send 64 bytes at a go.
  */
  while (internalTimeout > 0)
  {
    if (USBUART_CDCIsReady() == 0)
    {
      CyDelay(1);
      --internalTimeout;
      continue;
    }
    /* Once here, we can send out our packets one at a time. There are three
       cases:
     1. More than 64 bytes to send, so do numPackets of 64 bytes followed by one
        packet of lastPacketSize bytes.
     2. 64 bytes to send, so do one packet of 64 bytes, then one packet of zero.
     3. Less than 64 bytes, so do one packet of lastPacketSize bytes.
    */
    else
    {
      if (numPackets > 0)
      {
        USBUART_PutData((buffer+(packetsSent*64)), 64);
        ++packetsSent;
        --numPackets;
      }
      else if (numPackets == 0)
      {
        USBUART_PutData((buffer+(packetsSent*64)), lastPacketSize);
        retVal = 1;
        break;
      }
    }
  }
  return retVal;
}

int16_t USBUARTClass::_usb_serial_CustomGetCount()
{
  uint16 internalTimeout = 15;
  
  // loop to check for data more than once
  while (internalTimeout > 0)
  {
    if (USBUART_DataIsReady() == 0)
    {
      CyDelay(1);
      --internalTimeout;
      continue;
    }
    else
    {
      return USBUART_GetCount();
    }
  }
  // If we reach this then no data where recived
  return 0;
}