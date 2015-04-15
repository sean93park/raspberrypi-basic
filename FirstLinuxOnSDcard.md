# Introduction #

Please read http://www.raspberrypi.org/downloads for detailed information.

my environment
  * I'm using a Windows 7 host on a private network with ipTime 804T.
  * I've a linux box for cross compile if needed

# Details #

1. Download Image writer on Windows
  * download win32diskimager from http://sourceforge.net/projects/win32diskimager/
  * extract it and you'll get Win32DiskImager.exe file
2. Prepare the Raspberry Pi disk image
  * I've used Wheezy Raspbian, hard floating point.
  * extract to your working folder
  * Read http://elinux.org/RPi_Easy_SD_Card_Setup#Copying_the_image_to_an_SD_card_on_Windows for more details
  * plug your SD card. I've used 16G SDHC card and amount seems ok.
  * remember the driver letter when it's attached.
  * run Win32DiskImager.exe. it takes some time to showup.
  * select the image file, in my case, it's 2013-02-09-wheezy-raspbian.img
  * change the device; drive letter to the one mounted
  * click "Write" button and wait till it's finished.
  * Unmount the SDCard and insert to your RPi.
3. Turn on your RPi
  * Connect power and Ethernet. I didn't use any keyboard or mouse.
  * Wait for a moment and connect to RPi with something like putty.
  * RPi is DHCP client enabled. You've to get the IP Address to connect
  * I used my router to get the MAC and IP and registered to static IP table.
  * Connect to RPi. Default user id and password are pi/raspberry
  * First thing is to do configure your RPi
  * run raspi-config
```
$ sudo raspi-config
```
  * I've selected "expand\_rootfs", "change\_pass", "change\_locale", "change\_timezone". use down arrow to move.
  * You MUST change to password.
  * use TAB to change focus to **Finish** and press ENTER
  * to cancel operation, press ESC.
  * It'll reboot. wait and reconnect.

4. Installing services
  * Read http://www.instructables.com/id/Raspberry-Pi-Web-Server/
  * There are lots of steps. Click on the "Next >>" orange button to move to next step.
  * These are what I executed
```
$ sudo apt-get update
$ sudo apt-get install mysql-server
(set root passwrod)
$ sudo apt-get install mysql-client apache2 php5 libapache2-mod-php5 php5-mysql
```
  * for vsftpd
```
$ sudo apt-get install vsftpd
$ sudo vi /etc/vsftpd.conf
```
  * change as,
```
anonymous_enable=YES Change To anonymous_enable=NO
#local_enable=YES Change To local_enable=YES
#write_enable=YES Change To write_enable=YES
add line 'force_dot_files=YES'
```
  * restart vsftpd service
```
$ sudo service vsftpd restart
```
  * change owner of web root
```
$ sudo chown -R pi /var/www
```
  * to test php is working, try this.
```
  $ cd /var/www
  $ vi phpinfo.php
```
  * and type like this
```
  <? phpinfo(); ?>
```
  * run web browser and open that page, something like, http://192.168.1.31/phpinfo.php
  * install PhpMyAdmin
  * first, read http://www.phpmyadmin.net/home_page/index.php
  * download and extract to /var/www
  * I've renamed the folder to phpmyadmin
```
  $ tar xvf phpMyAdmin-3.5.7-english.tar.gz
  $ mv phpMyAdmin-3.5.7-english phpmyadmin
```
  * run web browser and open, like, http://192.168.1.31/phpmyadmin


5. samba settings
  * http://simonthepiman.com/how_to_setup_windows_file_server.php