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

#ifndef __RPI_SERIAL_IR_HEADER__
#define __RPI_SERIAL_IR_HEADER__

#include "rpi_types.h"

class rpiserir
{
public:
	rpiserir();
	virtual ~rpiserir();

public:
	bool	open( void );
	void	close( void );
	int		check( void );

protected:
	int				m_uart0_fd; 
	int				m_rdmode;

	enum { RDM_NONE = 0, RDM_R, RDM_M, RDM_CODE };

public:
	
	enum { 
		IR_EMPTY = 0, IR_CONT, 
		IR_CODE_CHNUP	= 0x80,
		IR_CODE_CHNDN	= 0x81,
		IR_CODE_VOLUP	= 0x82,
		IR_CODE_VOLDN	= 0x83,
		IR_CODE_FPLUS	= 0x84,
		IR_CODE_FMINUS	= 0x85,

		IR_CODE_POWER	= 0x88,
		IR_CODE_MUTE	= 0x89,
		IR_CODE_MULAUD	= 0x8a,
		IR_CODE_INPUT	= 0x8b,

		IR_CODE_00		= 0x90, IR_CODE_01, IR_CODE_02, IR_CODE_03, IR_CODE_04, IR_CODE_05, IR_CODE_06, IR_CODE_07, IR_CODE_08, IR_CODE_09, 

		IR_CODE_SUBTIT	= 0xb9,
		IR_CODE_FUNC	= 0xc3,
		IR_CODE_OK		= 0xc4,
		IR_CODE_AUTO	= 0xcd,
	};
};

#endif // __RPI_SERIAL_IR_HEADER__