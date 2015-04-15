# Introduction #

Here I gather(still) useful tips with RPi. May be also for generic Linux stuff.


### Adding another user ###

to add another user, open a terminal, login in as default user pi

```
$ sudo adduser [newuser]
```

It'll ask new password and some stuffs like this.

```
pi@raspberrypi ~ $ sudo adduser xxxxxx
Adding user `xxxxx' ...
Adding new group `xxxxxx' (1002) ...
Adding new user `xxxxxx' (1001) with group `xxxxxx' ...
Creating home directory `/home/xxxxxx' ...
Copying files from `/etc/skel' ...
Enter new UNIX password:
Retype new UNIX password:
passwd: password updated successfully
Changing the user information for xxxxx
Enter the new value, or press ENTER for the default
        Full Name []:
        Room Number []:
        Work Phone []:
        Home Phone []:
        Other []:
Is the information correct? [Y/n]
```

where xxxxx should be your new user ID

### Giving the user su ability ###

To make that user do some su stuff with 'sudo'

```
$ sudo adduser [newuser] sudo
```

It'll show like this

```
pi@raspberrypi /etc $ sudo adduser xxxxx sudo
Adding user `xxxxx' to group `sudo' ...
Adding user xxxxx to group sudo
Done.
```


### Overclocking ###

  * login with ssh
  * remount /flash with rw
```
mount /flash -o remount,rw
```
  * edit file /flash/config.txt
```
vi /flash/config.txt
```
  * change overclock mode settings. you'll find where to change.
```
# Overclock mode settings.
#
# default recommended values are: arm_freq | core_freq | sdram_freq | over_voltage
# no overclocking               :    700   |    250    |    400     |      0
# mode 'Modest'                 :    800   |    300    |    400     |      0
# mode 'Medium'                 :    900   |    333    |    450     |      2
# mode 'High'                   :    950   |    450    |    450     |      6
# mode 'Turbo'                  :   1000   |    500    |    500     |      6

# arm_freq=700
# core_freq=250
# sdram_freq=400
# over_voltage=0
```
  * write sync twice
```
sync
sync
```
  * reboot and check cpuinfo
```
cat /proc/cpuinfo
```

  * My experience is that over clocking causes SD card write or read failure. I got my cheap SDHC card broken, may be it was too cheap :(
  * I'll write down what I get, first with only changing arm\_freq then only core\_freq and so on.
  * Got how to fix this SD Card corruption problem.
    * Before: I was using powered USB hub, and used this powered hub to power RPi.
    * What I guess: When downloading and decompressing files, CPU wanted more power. But since USB hub was giving the power and I think it had some limit. So RPi could'n power enough current to SD card.
    * After: I changed to feed the power with micro USB connector with 1A adapter. Seems OK!

  * good info : http://elinux.org/RPiconfig

### Temperature of CPU ###
```
cat /sys/class/thermal/thermal_zone0/temp
```
will show your RPis CPU temperature in milli-degree-C

### CPU clock info ###
  * Current working clock speed
```
cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq
```
  * Maximum
```
cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq
```
  * Minimum
```
cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq
```

### Other usages ###
  * Turn it to a low power storage http://www.howtogeek.com/139433/how-to-turn-a-raspberry-pi-into-a-low-power-network-storage-device/