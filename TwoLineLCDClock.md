### Introduction ###

This is a study project to use I2C with Raspberry Pi.
It uses MCP23017 a 16 Bit I/O expander with I2C and
16 character 2 line Hitachi HD44780 compatible
JS-SCB16202S-BW6T-LW two line LCD module.


### Source code ###

Source code;
  * clone the this project source
  * cd to lcd2line sub-directory
  * make and copy executable to your RPi

Or view source from browser
  * https://code.google.com/p/raspberrypi-basic/source/browse/#git%2Flcd2line

4Bit control mode with IR receiver
  * https://code.google.com/p/raspberrypi-basic/source/browse/#git%2Flcd2line.4bit


### Hardware Curcuit ###

8Bit control

![https://raspberrypi-basic.googlecode.com/git/lcd2line/circuit_rpi_i2d_mcp23017_lcd2line.png](https://raspberrypi-basic.googlecode.com/git/lcd2line/circuit_rpi_i2d_mcp23017_lcd2line.png)

4Bit control with Backlight control and IR receiver

![https://raspberrypi-basic.googlecode.com/git/lcd2line.4bit/circuit_rpi_lcd2_ir.png](https://raspberrypi-basic.googlecode.com/git/lcd2line.4bit/circuit_rpi_lcd2_ir.png)



### Running on bread board ###

Power to LCD is given with separate +5V Adapter for power safety.

![https://raspberrypi-basic.googlecode.com/git/lcd2line/capture_01_rpi_i2d_mcp23017_lcd2line.png](https://raspberrypi-basic.googlecode.com/git/lcd2line/capture_01_rpi_i2d_mcp23017_lcd2line.png)

![https://raspberrypi-basic.googlecode.com/git/lcd2line/capture_02_rpi_i2d_mcp23017_lcd2line.png](https://raspberrypi-basic.googlecode.com/git/lcd2line/capture_02_rpi_i2d_mcp23017_lcd2line.png)

![https://raspberrypi-basic.googlecode.com/git/lcd2line.4bit/capture_03_rpi_lcd2_ir.png](https://raspberrypi-basic.googlecode.com/git/lcd2line.4bit/capture_03_rpi_lcd2_ir.png)