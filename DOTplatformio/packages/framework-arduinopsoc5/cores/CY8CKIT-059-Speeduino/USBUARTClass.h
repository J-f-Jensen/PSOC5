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

#ifndef _USBUART_CLASS_
#define _USBUART_CLASS_

#include "Stream.h"
#include <stdbool.h>
extern "C" {
#include <project.h>
}
  

class USBUARTClass : public Stream
{
  public:
    USBUARTClass(int);
    ~USBUARTClass(){};
    
    void begin(const uint32_t dwBaudRate);
    void end(void);
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    void flush(void);
    virtual uint8_t buffer(void);
    virtual size_t write(const uint8_t c);
    size_t write(unsigned long n)   { return write((uint8_t)n); }
	size_t write(long n)            { return write((uint8_t)n); }
	size_t write(unsigned int n)    { return write((uint8_t)n); }
	size_t write(int n)             { return write((uint8_t)n); }
	virtual size_t write(const uint8_t *buffer, size_t size)
					{ _usb_serial_write(buffer, size); return size; }
    virtual size_t write(const char *str)	{ size_t len = strlen(str);
					  _usb_serial_write((const uint8_t *)str, len);
					  return len; }
    using Print::write; // pull in write(str) and write(buf, size) from Print
    
    virtual size_t readBytes(const uint8_t *buffer, size_t length) {
			return _usb_serial_readBuffer(buffer, length);
	        }

    operator bool() { return 1; };

  private:
    uint32_t _baudRate;
    uint8_t _appBuffer[64];
    int8_t _appBuffSize;   
    int8_t _appBuffIndex;
    uint16_t _timeout;
    bool _enableUSBCDC(void);
    int16_t _usb_serial_CustomGetCount();
    size_t _usb_serial_readBuffer(const uint8_t* buffer, uint16_t size); // Read buffer methode
    size_t _usb_serial_write(const uint8_t* buffer, uint16_t size); // Write buffer methode
    
  protected:
    static bool _hasBegun;
};

extern USBUARTClass Serial; //USBUART

#endif // _USBUART_CLASS_
