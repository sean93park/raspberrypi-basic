# Introduction #

I'll try to explain how to use RPi's GPIO and some digital control. Most will be from other internet documents and sources so this maybe a gathering of those information.


### GPIO ###

What's a GPIO ?
  * read http://en.wikipedia.org/wiki/General_Purpose_Input/Output
  * general purpose, it can be used as input or output or both by software control
  * if you've not seen this, please do; http://www.raspberrypi.org/archives/1417

What's provided by Raspberry Pi?
  * I2C
  * SPI
  * UART
  * 8 I/O pins
  * http://elinux.org/RPi_Low-level_peripherals

About I2C and SPI
  * http://quick2wire.com/articles/i2c-and-spi/

How to understand
  * I2C
    * http://www.skpang.co.uk/blog/archives/575
    * http://www.skpang.co.uk/blog/archives/454
    * http://www.adafruit.com/blog/2013/04/05/interfacing-an-i2c-gpio-expander-mcp23017-to-the-raspberry-pi-using-c-sysfs/
    * http://raspberrypi.citrusperl.com/perl_on_raspberry_pi/2013/02/enabling-i2c-and-spi.html
  * SPI
    * http://www.brianhensley.net/2012/07/getting-spi-working-on-raspberry-pi.html
  * UART
    * 
  * 8 I/O
    * http://www.airspayce.com/mikem/bcm2835/

### Enable I2C and SPI ###

You've to upgrade the system. It'll take a while. Grad a coffee.
```
$ sudo apt-get update
$ sudo apt-get upgrade
```

I2C and SPI needs to be enable before use. Edit /etc/modprobe.d/raspi-blacklist.conf file and comment out blacklist as below.
```
$ sudo vi /etc/modprobe.d/raspi-blacklist.conf
```
```
# blacklist spi and i2c by default (many users don't need them)

#blacklist spi-bcm2708
#blacklist i2c-bcm2708
```

Edit /etc/modules file and add 'i2c-dev' item
```
$ sudo vi /etc/modules
```
```
# /etc/modules: kernel modules to load at boot time.
#
# This file contains the names of kernel modules that should be loaded
# at boot time, one per line. Lines beginning with "#" are ignored.
# Parameters can be specified after the module name.

snd-bcm2835

# enable i2c
i2c-dev
```

Install i2c-tools package
```
$ sudo apt-get install i2c-tools
```
there will be a new 'i2c' group added.

Add your user account to i2c, for example default 'pi' account
```
$ sudo adduser pi i2c
```

Now reboot.
```
$ sudo reboot now
```

Test and device is connected (for [revision 2](https://code.google.com/p/raspberrypi-basic/source/detail?r=2))
```
$ sudo i2cdetect -y 1
```
(for [revision 1](https://code.google.com/p/raspberrypi-basic/source/detail?r=1))
```
$ sudo i2cdetect -y 0
```

It'll show you something like this,
```
$ sudo i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: 20 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --
```

### GPIO control with C ###

There are lots of examples written in C to control GPIO.
What I've found actually working and understandable is from http://www.airspayce.com/mikem/bcm2835/.
This too I could not compile with cross compiling what I wrote in **CrossCompileForRPi** page.
But using the source code in **src** folder I could do basic testing.

These are the steps I've done.

1) download bcm2835-1.25.tar.gz from http://www.airspayce.com/mikem/bcm2835/bcm2835-1.25.tar.gz

2) extract it
```
tar xvf bcm2835-1.25.tar.gz
```

3) copy core files
```
cp bcm2835-1.25/src/bcm2835.c .
cp bcm2835-1.25/src/bcm2835.h .
cp bcm2835-1.25/examples/blink/blink.c .
```

4) build blink example
```
$CC -I . blink.c bcm2835.c -o blink
```

5) connect GPIO17 to a LED

6) copy blink to RPi, I use filezilla.

7) run in RPi
```
sudo ./blink
```


### Expanding GPIO ###

1) There are lots of I2C to GPIO chips, one of it is MCP23017

2) It provides 16 bit or 2x8 bit I/O
  * http://www.alldatasheet.com/datasheet-pdf/pdf/195324/MICROCHIP/MCP23017.html

3) Testing

  * connect GPA0 and GPA1 pin of MCP23017 to two LED with 330 ohm resistor.
  * something like http://www.skpang.co.uk/blog/wp-content/uploads/2012/06/io_rev_A.pdf
  * send commands and see the LED turns on
```
$ i2cset -y 1 0x20 0 0
$ i2cset -y 1 0x20 1 0
$ i2cset -y 1 0x20 0x12 0
$ i2cset -y 1 0x20 0x12 1
$ i2cset -y 1 0x20 0x12 2
$ i2cset -y 1 0x20 0x12 3
```


4) How to Program
...

### Controlling 2 Line LCD display ###

Moved to separate wiki page.