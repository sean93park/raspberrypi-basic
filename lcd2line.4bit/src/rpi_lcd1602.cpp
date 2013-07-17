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

#include "rpi_lcd1602.h"

lcd2line::lcd2line (  )
{
	m_lcd_cmd = 0x00;
}

lcd2line::~lcd2line()
{
}

void lcd2line::send_nibble ( rpi_byte data )
{
	// turn on E
	m_lcd_cmd |= LCD2L_CTRL_E;
	m_mcp23017.write( MCP23017_OLATA, m_lcd_cmd );

	// set DATA
	m_lcd_cmd |= data;
	m_mcp23017.write( MCP23017_OLATA, m_lcd_cmd );

	// wait for 200usec(depends on model) and turn off E
	usleep( 200 );
	m_lcd_cmd &= ~LCD2L_CTRL_E;
	m_mcp23017.write( MCP23017_OLATA, m_lcd_cmd );

	// wait for 10usec
	usleep( 10 );
	
	m_lcd_cmd &= 0xf0;	// clear data nibble, not necessary but just in case.
	//m_mcp23017.write( MCP23017_OLATA, m_lcd_cmd );
}

void lcd2line::send_data ( rpi_byte data )
{
	rpi_byte	datah, datal;
	
	datah = (data & 0xf0)>>4;
	datal = (data & 0x0f);

	send_nibble( datah );
	//usleep(10);
	send_nibble( datal );
	//usleep(10);
}

void lcd2line::ctrl ( rpi_byte cmd )
{
	m_lcd_cmd &= ~LCD2L_CTRL_RS;	// clear RS --> instruction mode.
	m_lcd_cmd &= ~LCD2L_CTRL_RW;	// clear RW --> write mode

	send_data( cmd );

	m_lcd_cmd |= LCD2L_CTRL_RW;
	m_lcd_cmd |= LCD2L_CTRL_RS;
}

void lcd2line::text ( rpi_byte text )
{
	m_lcd_cmd |=  LCD2L_CTRL_RS;	// data mode
	m_lcd_cmd &= ~LCD2L_CTRL_RW;	// clear RW --> write mode

	send_data( text );

	m_lcd_cmd |= LCD2L_CTRL_RS;		// to data mode
	m_lcd_cmd |= LCD2L_CTRL_RW;		// to read mode

	usleep(50);
}

bool lcd2line::initdevice ( void )
{
	if ( m_mcp23017.open( "/dev/i2c-1", MCP23017_ADDR ) < 0 )
	{
		fprintf( stderr, "lcd2line::init(), failed to open device '/dev/i2c-1'\n" );
		return false;
	}
	// port A to write mode
	if ( 0 > m_mcp23017.write( MCP23017_IODIRA, 0x00 ) ) return false;
	// port B to write mode
	if ( 0 > m_mcp23017.write( MCP23017_IODIRB, 0x00 ) ) return false;
	
	if ( 0 > m_mcp23017.write( MCP23017_OLATA, 0 ) ) return false;
	if ( 0 > m_mcp23017.write( MCP23017_OLATB, 0 ) ) return false;

	// spec says send "8bit" 3 times then 
	// send one "4bit" nibble without low nibble.
	usleep(4000);
	send_nibble( 0b0011 );
	usleep(1000);
	send_nibble( 0b0011 );
	usleep(1000);
	send_nibble( 0b0011 );
	usleep(1000);
	send_nibble( 0b0010 );
	usleep(1000);
	
	return true;
}

void lcd2line::ctrlcleardisplay ( void )
{
	ctrl( LCD2L_CMD_CLEAR );
	usleep(1700);
}

void lcd2line::ctrlreturnhome ( void )
{
	ctrl( LCD2L_CMD_RETURNHOME );
	usleep(1700);
}

void lcd2line::ctrlfunctionset ( rpi_byte param )
{
	ctrl( LCD2L_CMD_FUNCTIONSET | (param & 0b00011100) );
	usleep(50);
}

void lcd2line::ctrldisplay ( rpi_byte param )
{
	ctrl( LCD2L_CMD_DISPLAY | (param & 0b00000111) );
	usleep(50);
}

void lcd2line::ctrlentrymode ( rpi_byte param )
{
	ctrl( LCD2L_CMD_ENTRYMODE | (param & 0b00000011) );
	usleep(50);
}

void lcd2line::ctrlmovecursorleft ( void )
{
	ctrl( LCD2L_CMD_CURSOR | LC_CURSOR_POSLEFT );
	usleep(50);
}

void lcd2line::ctrlmovecursorright ( void )
{
	ctrl( LCD2L_CMD_CURSOR | LC_CURSOR_POSRIGHT );
	usleep(50);
}

void lcd2line::ctrlmovedisplayleft ( void )
{
	ctrl( LCD2L_CMD_CURSOR | LC_CURSOR_ENTLEFT );
	usleep(50);
}

void lcd2line::ctrlmovedisplayright ( void )
{
	ctrl( LCD2L_CMD_CURSOR | LC_CURSOR_ENTRIGHT );
	usleep(50);
}

void lcd2line::ctrlbacklight ( rpi_byte blon )
{
	if ( blon )
	{
		m_lcd_cmd |= LCD2L_CTRL_BL;
		m_mcp23017.write( MCP23017_OLATA, m_lcd_cmd );
	}
	else
	{
		m_lcd_cmd &= ~LCD2L_CTRL_BL;
		m_mcp23017.write( MCP23017_OLATA, m_lcd_cmd );
	}
}

void lcd2line::setdisplaypos ( rpi_byte line, rpi_byte pos )
{
	rpi_byte	addr;
	addr = line ? 0x40 : 0x00;
	addr = addr + (pos);
	ctrl( LCD2L_CMD_DDRAMADDR | addr );
	usleep(50);
}

void lcd2line::displaytext ( const char* sztext )
{
	int			i, leng;
	rpi_byte	onechar;

	leng = strlen(sztext);
	for (i=0; i<leng; i++ )
	{
		onechar = (rpi_byte)(*(sztext+i));
		text( onechar );
	}
}

void lcd2line::displaytextpos ( rpi_byte line, rpi_byte pos, const char* sztext )
{
	setdisplaypos( line, pos );
	displaytext( sztext );
}
