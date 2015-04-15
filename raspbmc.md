# Introduction #

Records of what happened while installing raspbmc


# Details #

### Use image file when first install ###

  * There's two types of image. One is small image that downloads from the server, which takes about 20~30 minutes, another with full image about 1.3G.
  * Visit http://www.raspbmc.com/download/
  * Author recommends the first but I recommend the second one.
  * After flashing to SD card, have to decide about over clocking in boot config.txt.
  * Initially clock is set to 800 MHz and force\_turbo=1.
  * My case, I had problems with higher than 700 MHz that made my SD card corrupt.
  * So, before inserting to RPi, decide edit or not.
  * This is my config.txt. Default GPU is 250, set to 350 for some video files had periodic short pausing and over clocking GPU solved the problem.
```
arm_freq=700
gpu_freq=350
sdram_freq=400
over_voltage=0

force_turbo=0
gpu_mem=128
disable_overscan=1
start_file=start_x.elf
fixup_file=fixup_x.dat
```
  * Update...
  * I've done some test with over clockings
    * Changed power line, previous was power from adaptor - USB Hub - RPi, this was not good.
    * USB hub, with 4 ports, consumed about 800mA
    * Power line now, removed USB Hub, gave power from 5V 1A adapter.
    * Seems OK in my computer room, over clocking to 1GHz, gpu 500MHz.
    * In my living room, under the LCD TV, works default 800MHz, but don't boot on overclocking !
    * Moved RPi away from LCD TV, works fine again !
  * So, conclusion,
    * Give power to RPi at least 1A to its micro USB power connector
    * Don't put RPi near TV. Seems affected by the Electromagnetic interference of the TV.
    * Maybe my TV is not so good.
    * my new config.txt
```
arm_freq=1000
gpu_freq=500
sdram_freq=500
over_voltage=6
disable_overscan=1
gpu_mem=128
start_file=start_x.elf
fixup_file=fixup_x.dat
```
  * and other stuffs what I was worried about,
    * Class 4 of SDHC card is OK. When I had problems with boot, one of my Class 6 SDHC card died.
    * I attached heat-sink in the first place. Broadcom SOC, LAN, and power regulator RG2.
    * What is RG1... do I have to put another to here?


### Power saving ###

  * I've attach Samsung 2T HDD and both consumes about 11W at normal and about 7W standby, where HDD is spin down.
  * Have to figure out how to power down RPi...

