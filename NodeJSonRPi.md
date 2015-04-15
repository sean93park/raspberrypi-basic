# Introduction #

This document will explain how to run node.js on RaspBerry Pi.

# Details #

### 1. install with apt-get ###
  * simple. in your RPi terminal,
```
$ sudo apt-get install nodejs
```
  * as for 1 March, 2013, I've got node version 0.6.19.
  * too old. try with build from source.

### 2. build from source ###
  * I'm trying on my x86 machine, cross compiling.
  * following https://gist.github.com/adammw/3245130
  * prepare cross compile tools
  * download 'cross-compile helper script' from https://gist.github.com/raw/3246346/crosscompile.sh
```
#!/bin/sh -e
if [ -z "$HOST" ]; then
  HOST=arm-bcm2708hardfp-linux-gnueabi
fi

export CPP="${HOST}-gcc -E"
export STRIP="${HOST}-strip"
export OBJCOPY="${HOST}-objcopy"
export AR="${HOST}-ar"
export RANLIB="${HOST}-ranlib"
export LD="${HOST}-ld"
export OBJDUMP="${HOST}-objdump"
export CC="${HOST}-gcc"
export CXX="${HOST}-g++"
export NM="${HOST}-nm"
export AS="${HOST}-as"
export PS1="[${HOST}] \w$ "
bash --norc
```
  * download nodejs. I've got 0.8.20 stable, which is e10c75579b536581ddd7ae4e2c3bf8a9d550d343
```
$ cd ~/raspberrypi
$ git clone git://github.com/joyent/node.git
$ cd node
$ git reset --hard e10c75579b536581ddd7ae4e2c3bf8a9d550d343
```
  * @update 2013-05-12, node version 0.10.5. get the source from download page http://www.nodejs.org/download/
  * enter to cross compile shell
```
$ ./crosscompile.sh
```
  * print $HOST, if it's empty, do as (I'm using hard float)
```
$ export HOST=arm-bcm2708hardfp-linux-gnueabi
```
  * have to edit LD
```
$ export LD="$CXX"
```
  * configure and build
```
$ ./configure --without-snapshot
$ make
```
  * copy node file to target RPi: I used filezilla.
  * out/Release/node binary to /usr/local/bin

### 3. install npm ###
  * in RPi terminal, install npm
```
$ cd ~
$ export NODE_PATH=/usr/local/lib/node_modules
$ wget http://npmjs.org/install.sh
$ sudo install.sh
```
  * it'll take a while to finish this job.
  * add node\_modules path to environment
```
$ export NODE_PATH=/usr/local/lib/node_modules
```
  * add to /etc/profile.d/node.sh so it's always added at boot time
```
$ sudo vi /etc/profile.d/node.sh
```
  * with content,
```
# for node.js npm
export NODE_PATH=/usr/local/lib/node_modules
```
  * //
  * original try for npm. not correct. leaving this for history.
    * deps/npm to /usr/local/share
    * if copy fails, add pi user to 'staff' group. you'll find in another wiki page.
    * create npm symbolic
```
$ cd /usr/local/bin
$ ln -s ../share/npm/bin/npm-cli.js npm
$ chmod 750 /usr/local/share/npm/bin/npm-cli.js
```
  * //

### 4. test node ###
  * create a sample js file, testnodehttp.js
```
var http = require('http');

var server = http.createServer(function (request, response) {
  response.writeHead(200, {"Content-Type": "text/plain"});
  response.end("Hello World\n");
});

server.listen(8080);
console.log("Server running at port 8080");
```
  * run the file
```
$ node testnodehttp.js
```
  * if all is ok, it'll show like
```
Server running at port 8080
```
  * with your browser, open your RPi address with port 8080
```
http://192.168.1.31:8080/
```
  * if 'hello world' message shown, every things ok.
  * CTRL+C to quit test

### 5. test with express ###
  * now, install famous express
```
$ sudo npm install -g express
```
  * test with express
```
$ vi testexpress.js
```
  * with content,
```
var express = require('express');
var app = express();

app.get('/', function(req, res){
  res.send('hello world express');
});
app.listen(8080);
console.log("Server with express running at port 8080");
```
  * now, run server
```
$ node testexpress.js
```
  * if ok, it'll show
```
Server with express running at port 8080
```
  * again, with your browser, open your RPi address with port 8080
```
http://192.168.1.31:8080/
```
  * if 'hello world express' message shown, every things ok.
  * CTRL+C to quit test


### x. historical record of bad tries ###

build from source old try; for previous recordings so I don't do this again. don't follow this.
  * I'm trying on my x86 machine
  * following http://n8.io/cross-compiling-nodejs-v0.8/ and...
```
$ cd ~/raspberrypi
$ source setenv
$ git clone git://github.com/joyent/node.git
$ cd node
$ git checkout v0.8.10
$ ./configure --without-snapshot --dest-cpu=arm --dest-os=linux
$ make
```
  * got error, maybe try later with more googling.
```
arm-bcm2708hardfp-linux-gnueabi-ld: bad -rpath option
```
  * maybe I've to build in RPi...
  * http://jeelabs.org/2013/01/06/node-js-on-raspberry-pi/
  * I must try https://gist.github.com/adammw/3245130