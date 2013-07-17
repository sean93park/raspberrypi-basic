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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h> 

#include <fcntl.h>
#include <termios.h>

#include "rpi_serir.h"

rpiserir::rpiserir()
{
	m_uart0_fd = 0;
	m_rdmode = 0;
}

rpiserir::~rpiserir()
{
	close();
}

bool rpiserir::open ( void )
{
	if ( m_uart0_fd > 0 )
		::close( m_uart0_fd );
	m_uart0_fd = ::open( "/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY );
	if (m_uart0_fd == -1)
	{
		fprintf( stderr, "Error: Unable to open /dev/ttyAMA0. Ensure it is not in use by another application\n" );
		return false;
	}
	struct termios options;
	
	if ( tcgetattr(m_uart0_fd, &options) < 0 ) 
		return false;
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR | ICRNL;
	options.c_oflag = 0;
	options.c_lflag = 0;
	if ( tcflush(m_uart0_fd, TCIFLUSH) < 0 )
		return false;
	if ( tcsetattr(m_uart0_fd, TCSANOW, &options) < 0 )
		return false;
	
	return true;
}

void rpiserir::close ( void )
{
	if ( m_uart0_fd > 0 )
		::close( m_uart0_fd );
	m_uart0_fd = 0;
}

int rpiserir::check ( void )
{
	//----- CHECK FOR ANY RX BYTES -----
	if (m_uart0_fd != -1)
	{
		unsigned char	buffer[4];
		int rx_length = read(m_uart0_fd, (void*)buffer, 1);
		if (rx_length <= 0)
			return IR_EMPTY;

		switch ( m_rdmode )
		{
		case RDM_NONE : 
			if ( buffer[0] == 'R' )
				m_rdmode = RDM_R;
			break;

		case RDM_R :
			if ( buffer[0] == 'M' )
				m_rdmode = RDM_M;
			else
				m_rdmode = RDM_NONE;
			break;

		case RDM_M :
			m_rdmode = RDM_NONE;
			//printf( "-- 0x%02x\n", buffer[0]+0x80 );
			return buffer[0] + 0x80;
		}
		return IR_CONT;
	}
	return IR_EMPTY;
}


