## Introduction ##

How to install OpenELEC, a quite good home living room media player.


## Reference Sites ##

Turn your RPi into a media box !
  * http://wiki.openelec.tv/index.php?title=Installing_OpenELEC_on_Raspberry_Pi

Make OpenElec SD Card from Windows
  * http://squirrelhosting.co.uk/hosting-blog/hosting-blog-info.php?id=9

How to enable Korean
  * http://blog.naver.com/PostView.nhn?blogId=kyb016&logNo=60171977936

Remote control application; Android and iOS
  * http://wiki.xbmc.org/index.php?title=Official_XBMC_Remote

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
  * made mine to
```
arm_freq=1000
core_freq=500
sdram_freq=500
over_voltage=6
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

### Expanding storage partition ###

Default storage partition size is fixed to some low amount.
To expand to use full size of it, I've done like below.

  1. insert SD card to any Linux machine
  1. run parted, where sdb is SD card device in my case.
```
sudo parted /dev/sdb
```
  1. edit as, where 258048 is the number of second partition start number.
```
unit s
p
```
  1. where it'll show like, (this is actually result after expand)
```
Model: USB Mass  Storage Device (scsi)
Disk /dev/sdb: 15771648s
Sector size (logical/physical): 512B/512B
Partition Table: msdos

Number  Start    End        Size       Type     File system  Flags
 1      2048s    258047s    256000s    primary  fat16        boot, lba
 2      258048s  15771647s  15513600s  primary  ext4
```
  1. continue editing...
```
rm 2
mkpart primary 258048 -1
quit
```
  1. check and resize
```
sudo e2fsck -f /dev/sdb2
sudo resize2fs /dev/sdb2
```