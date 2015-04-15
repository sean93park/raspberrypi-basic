# Introduction #

I'm using x86, actually dual core Atom, Linux box for cross compiling.
There are lots of sites about cross compile for RPi. I'm describing what I've got from many internet pages.


# Details #
1. get the tools
  * visit https://github.com/raspberrypi/tools
  * You've to get git tools before.
```
$ sudo apt-get install git
```
  * get the tools
```
$ mkdir ~/raspberrypi
$ cd ~/raspberrypi
$ git clone https://github.com/raspberrypi/tools.git
```
  * I'm using hard float version
  * edit .profile file and add to PATH
```
$ vi $HOME/.profile
```
  * add as,
```
export PATH=$PATH:$HOME/raspberrypi/tools/arm-bcm2708/arm-bcm2708hardfp-linux-gnueabi/bin
```
  * I've made a setenv file to set cross compile environment variables. there are lots of ways. this is my current choice.
```
$ cd ~/raspberry
$ vi setenv
```
  * set content as
```
TOOL_PREFIX=arm-bcm2708hardfp-linux-gnueabi
CXX=$TOOL_PREFIX-g++
AR=$TOOL_PREFIX-ar
RANLIB=$TOOL_PREFIX-ranlib
CC=$TOOL_PREFIX-gcc
LD=$TOOL_PREFIX-ld
CCFLAGS="-march=armv4 -mno-thumb-interwork"
```

2. simple test
  * create a test hello world source
```
$ cd ~/raspberry
$ source setenv
$ mkdir test
$ cd test
$ vi helloworld.c
```
  * set source as
```
#include <stdio.h>

int main ( int argc, char* argv[] )
{
        printf( "Hello World !\r\n" );
        return 0;
}
```
  * compile
```
  $ $CC helloworld.c -o helloworld
```
  * copy helloworld program to RPi, I've used FileZilla; http://filezilla-project.org/
  * run in your RPi