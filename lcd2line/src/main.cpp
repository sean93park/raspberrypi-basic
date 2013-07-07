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

#include "rpi_lcd1602.h"

int main ( void )
{
	lcd2line	lcd2;
	time_t 		t;
	struct tm 	ts;
	struct tm 	to;
	char		buffd[128];
	char		bufft[128];

	if ( !lcd2.initdevice() )
		exit(-1);

	lcd2.ctrlfunctionset( LC_FUNCTIONSET_8BIT | LC_FUNCTIONSET_2LINE | LC_FUNCTIONSET_5x8 );
	lcd2.ctrldisplay( LC_DISPLAY_ON );//| LC_DISPLAY_CURSOR_ON | LC_DISPLAY_BLINK_ON );
	lcd2.ctrlcleardisplay();
	lcd2.ctrlentrymode( LC_ENTRYMODE_INC );
	
	lcd2.displaytextpos( 0, 0, "RPi" );
	lcd2.displaytextpos( 1, 0, "Time" );

	memset( &to, 0, sizeof(to) );
	
	while ( 1 )
	{
		t  = time(NULL);
		ts = *localtime(&t);
		
		if ( ts.tm_sec != to.tm_sec )
		{
			// display current time in text only the string has changed.
			to = ts;
			
			strftime( buffd, sizeof(buffd), "%Y-%m-%d", &ts );
			strftime( bufft, sizeof(bufft), "%X", &ts );
							
			lcd2.displaytextpos( 0, 4, buffd );
			lcd2.displaytextpos( 1, 6, bufft );
		}
		usleep( 100000 );	// wait 100 msecs
	}

	return 0;           
}