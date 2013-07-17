/*
Copyright (c) 2013 sean93.park@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __RPI_I2C_HEADER__
#define __RPI_I2C_HEADER__

#include <linux/i2c.h> 
#include <linux/i2c-dev.h>

#include "rpi_types.h"

class rpi2c
{
public:
	rpi2c();
	virtual ~rpi2c();

public:
	int		open(const char* file, rpi_i2caddr addr);
	int		close();
	int		write(rpi_i2caddr reg_addr, rpi_byte data);
	int		read(rpi_i2caddr reg_addr, rpi_byte &data);

protected:
	char		m_device[250];
	int			m_fd;  
	rpi_i2caddr	m_addr; 
};

#endif // __RPI_I2C_HEADER__