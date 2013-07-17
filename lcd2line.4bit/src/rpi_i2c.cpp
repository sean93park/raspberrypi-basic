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

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "rpi_i2c.h"

rpi2c::rpi2c()
{
	m_device[0] = 0;
	m_addr = 0;
	m_fd = -1;
}

rpi2c::~rpi2c()
{
	close();
}

int rpi2c::open ( const char* file, rpi_i2caddr addr )
{
	if ( !(file && *file ) )
	{
		fprintf( stderr, "rpi2c::open(), invalid file name\n" );
		return -1;
	}
	strcpy( m_device, file );
	m_addr = addr;
	m_fd = ::open( m_device, O_RDWR );
	if ( m_fd < 0 )
	{
		fprintf( stderr, "rpi2c::open(), Could not open file\n");
		return -1;
	}
	//fprintf( stderr, "rpi2c::openi2c() OK, [%s]:[0x%x] > fd(%d)\n", m_device, addr, m_fd );
	return m_fd;
}

int rpi2c::close ( void )
{
	int retval = -1;
	if ( m_fd > 0 )
	{
		retval = ::close( m_fd );
		if(retval < 0)
		{
			fprintf( stderr, "rpi2c::closei2c, close failed, %d\n", retval );
		}
	}
	m_device[0] = 0;
	m_addr = 0;
	m_fd = -1;
	return retval;
}

int rpi2c::write ( rpi_i2caddr reg_addr, rpi_byte data )
{
	if ( m_fd < 0 ) return -1;

	rpi_byte buff[2];
	int		retval = -1;
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages[1];

	buff[0] = reg_addr;
	buff[1] = data;

	messages[0].addr = m_addr;
	messages[0].flags = 0;
	messages[0].len = sizeof(buff);
	messages[0].buf = buff;

	packets.msgs  = messages;
	packets.nmsgs = 1;

	retval = ::ioctl( m_fd, I2C_RDWR, &packets );
	if ( retval < 0 )
		fprintf( stderr, "i2c8Bit::write(), write failed %d\n", retval );

	return retval;
}

int rpi2c::read ( rpi_i2caddr reg_addr, rpi_byte &data )
{
	if ( m_fd<0 ) return -1;

	rpi_byte *inbuff, outbuff;
	int retval = -1;
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages[2];

	outbuff = reg_addr;
	messages[0].addr = m_addr;
	messages[0].flags= 0;
	messages[0].len = sizeof(outbuff);
	messages[0].buf = &outbuff;

	inbuff = &data;
	messages[1].addr = m_addr;
	messages[1].flags = I2C_M_RD;
	messages[1].len = sizeof(inbuff);
	messages[1].buf = inbuff;

	packets.msgs = messages;
	packets.nmsgs = 2;

	retval = ioctl( m_fd, I2C_RDWR, &packets );
	if ( retval < 0 )
		fprintf( stderr, "rpi2c::read(), read failed %d\n", retval );

	return retval;
}