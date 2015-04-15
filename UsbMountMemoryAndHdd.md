# Introduction #

Mount as USB memory stick and use it to expand storage memory.


# Details #

I've followed http://raspi.tv/2012/mount-a-usb-flash-drive-on-raspberry-pi

1. USB memory

  * Plug your USB memory stick to USB port.
  * show dmesg
```
$ dmesg
...
[  346.689899] usb 1-1.3: new high-speed USB device number 4 using dwc_otg
[  346.791446] usb 1-1.3: New USB device found, idVendor=0781, idProduct=5572
[  346.791477] usb 1-1.3: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[  346.791493] usb 1-1.3: Product: Firebird USB Flash Drive
[  346.791506] usb 1-1.3: Manufacturer: SanDisk
[  346.791519] usb 1-1.3: SerialNumber: 4C532000011222106005
[  346.796904] scsi0 : usb-storage 1-1.3:1.0
[  347.791325] scsi 0:0:0:0: Direct-Access     SanDisk  Cruzer Switch    1.26 PQ: 0 ANSI: 5
[  347.794284] sd 0:0:0:0: [sda] 15633408 512-byte logical blocks: (8.00 GB/7.45 GiB)
[  347.795747] sd 0:0:0:0: [sda] Write Protect is off
[  347.795784] sd 0:0:0:0: [sda] Mode Sense: 43 00 00 00
[  347.796784] sd 0:0:0:0: [sda] Write cache: disabled, read cache: enabled, doesn't support DPO or FUA
[  347.813592]  sda: sda1
[  347.818970] sd 0:0:0:0: [sda] Attached SCSI removable disk
```
  * as shown above, sda1 is what you should mount
  * I'm expanding my web folder /var/www/data,
```
$ cd /var/www
$ mkdir data
$ sudo mount -t vfat -o uid=pi,gid=pi /dev/sda1 /var/www/data
```
  * when you're done, unmount then remove
```
$ sudo umount /var/www/data
```
  * now, another way. to auto mount at boot time, edit fstab file
```
$ sudo vi /etc/fstab
```
  * add at end of line
```
/dev/sda1       /var/www/data   vfat    defaults,uid=pi,gid=pi  0       0
```
  * mount it
```
$ sudo mount -a
```
  * now you'll have your usb memory on /var/www/data on boot.
  * 