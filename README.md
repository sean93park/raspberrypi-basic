*Automatically exported from code.google.com/p/raspberrypi-basic,2015-04-15*

### Welcome to Raspberry Pi Basic project for beginners

I'm writing down the steps I went with my Raspberry Pi.

Added Digital Clock project with 2 line LCD module with hardware circuit and source code.


### Sites to worth reading
* http://raspberrypi.stackexchange.com/questions/311/how-do-i-backup-my-raspberry-pi


### Current state of my RPi
```
pi@raspberrypi /var $ uname -a
Linux raspberrypi 3.6.11+ #371 PREEMPT Thu Feb 7 16:31:35 GMT 2013 armv6l GNU/Linux


pi@raspberrypi /var $ free
             total       used       free     shared    buffers     cached
Mem:        497544     224036     273508          0      21732     138528
-/+ buffers/cache:      63776     433768
Swap:       102396          0     102396


pi@raspberrypi /var $ df -H
Filesystem      Size  Used Avail Use% Mounted on
rootfs           16G  1.8G   14G  12% /
/dev/root        16G  1.8G   14G  12% /
devtmpfs        247M     0  247M   0% /dev
tmpfs            51M  230k   51M   1% /run
tmpfs           5.3M     0  5.3M   0% /run/lock
tmpfs           102M     0  102M   0% /run/shm
/dev/mmcblk0p1   59M   20M   40M  34% /boot


pi@raspberrypi /var $ cat /proc/cpuinfo
Processor       : ARMv6-compatible processor rev 7 (v6l)
BogoMIPS        : 464.48
Features        : swp half thumb fastmult vfp edsp java tls
CPU implementer : 0x41
CPU architecture: 7
CPU variant     : 0x0
CPU part        : 0xb76
CPU revision    : 7

Hardware        : BCM2708
Revision        : 000e

```
