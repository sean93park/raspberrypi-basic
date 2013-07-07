#
# use build tools from https://github.com/raspberrypi/tools
# $ export PATH=$PATH:$HOME/raspberrypi/tools/arm-bcm2708/arm-bcm2708hardfp-linux-gnueabi/bin
# $ make
#

TOOL_PREFIX	= arm-bcm2708hardfp-linux-gnueabi

CXX		= $(TOOL_PREFIX)-g++
AR		= $(TOOL_PREFIX)-ar
RANLIB	= $(TOOL_PREFIX)-ranlib
CC		= $(TOOL_PREFIX)-gcc
LD		= $(TOOL_PREFIX)-ld

CXXFLAGS= -march=armv4 -mno-thumb-interwork
CFLAGS	= -Wall $(CXXFLAGS) -Iinc
LDFLAGS	= 

vpath %.cpp ./src

BUILDDIR = build
SOURCES = \
	rpi_i2c.cpp \
	rpi_lcd1602.cpp \
	main.cpp

OBJECTS 	= $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SOURCES))
EXECUTABLE 	= $(BUILDDIR)/rpilcd

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo Linking $@
	@$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILDDIR)/%.o : %.cpp
	@mkdir -p $(BUILDDIR)
	@echo Compiling $<
	@$(CXX) $(CFLAGS) -c $< -o $@
	
clean:
	rm -rf $(BUILDDIR)/*.o $(EXECUTABLE)
