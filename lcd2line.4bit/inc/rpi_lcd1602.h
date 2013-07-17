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

#ifndef __RPI_LCD_HEADER__
#define __RPI_LCD_HEADER__

#include <string>
#include <linux/i2c.h> 
#include <linux/i2c-dev.h>

#include "rpi_i2c.h"
#include "mcp23017.h"
#include "rpi_types.h"

// theres are the commands for 2Line LCD (http://www.eleparts.co.kr/EPX4P4YG)

// Signal control from MCP23017 to LCD
#define LCD2L_CTRL_BL				0b10000000	// GPA7 is connected to LCD Backlight
#define	LCD2L_CTRL_RS				0b01000000	// GPA6 is connected to RS
#define	LCD2L_CTRL_RW				0b00100000	// GPA5 is connected to RW
#define	LCD2L_CTRL_E				0b00010000	// GPA4 is connected to E

// LCD control commands and parameters
#define	LCD2L_CMD_CLEAR				0b00000001

#define	LCD2L_CMD_RETURNHOME		0b00000010

#define LCD2L_CMD_ENTRYMODE			0b00000100
#define	LC_ENTRYMODE_INC			0b00000010
#define	LC_ENTRYMODE_SHIFT			0b00000001

#define LCD2L_CMD_DISPLAY			0b00001000
#define LC_DISPLAY_ON				0b00000100
#define LC_DISPLAY_CURSOR_ON		0b00000010
#define	LC_DISPLAY_BLINK_ON			0b00000001

#define	LCD2L_CMD_CURSOR			0b00010000
#define	LC_CURSOR_POSLEFT			0b00000000
#define	LC_CURSOR_POSRIGHT			0b00000100
#define	LC_CURSOR_ENTLEFT			0b00001000
#define	LC_CURSOR_ENTRIGHT			0b00001100

#define	LCD2L_CMD_FUNCTIONSET		0b00100000		// function set cmd
#define	LC_FUNCTIONSET_8BIT			0b00010000		// 8 bit or 4bit
#define LC_FUNCTIONSET_4BIT			0b00000000
#define	LC_FUNCTIONSET_2LINE		0b00001000		// 2 line or 1 line
#define	LC_FUNCTIONSET_1LINE		0b00000000
#define	LC_FUNCTIONSET_5x10			0b00000100		// 5x10 dot or 5x8 dot
#define	LC_FUNCTIONSET_5x8			0b00000000

#define	LCD2L_CMD_DDRAMADDR			0b10000000

class lcd2line
{
public:
	lcd2line();
	virtual ~lcd2line();

protected:
	rpi2c		m_mcp23017;
	rpi_byte	m_lcd_cmd;

protected:
	void		send_nibble( rpi_byte data );
	void		send_data( rpi_byte data );
	void		ctrl( rpi_byte cmd );
	void		text( rpi_byte text );

public:
	bool		initdevice( void );

	void		ctrlcleardisplay( void );
	void		ctrlreturnhome( void );
	void		ctrlfunctionset( rpi_byte cmd );
	void		ctrldisplay( rpi_byte param );
	void		ctrlentrymode( rpi_byte param );
	void		ctrlmovecursorleft( void );
	void		ctrlmovecursorright( void );
	void		ctrlmovedisplayleft( void );
	void		ctrlmovedisplayright( void );
	void		ctrlbacklight( rpi_byte blon );
	
	void		setdisplaypos( rpi_byte line, rpi_byte pos );
	void		displaytext( const char* text );
	void 		displaytextpos( rpi_byte line, rpi_byte pos, const char* sztext );
};

#endif // __RPI_LCD_HEADER__