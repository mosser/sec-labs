##################
# general options

export CC = avr-gcc
export MCU = atmega328p
export TARGET_ARCH = -mmcu=$(MCU)

TARGET = led7seg


#######################
# Setting up tool paths
UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Darwin) # If you're a darwin user, you should have arduino installed cause we point to it :)
ARDUINO_HW_ROOT = /Applications/Arduino.app/Contents/Java/hardware/arduino/avr
TERM = /dev/tty.usbmodem*
STTY_OPT = -f
AVRDUDE_PATH = /opt/local/bin/
AVRDUDECONF_PATH = /opt/local/etc/
else # only linux is supported, haven't checked for varieties here
ARDUINO_HW_ROOT = /usr/share/arduino/hardware/arduino/
TERM = /dev/ttyACM0
STTY_OPT = -F
AVRDUDE_PATH = /usr/bin/
AVRDUDECONF_PATH = /usr/share/arduino/hardware/tools/
endif

####################
# ARDUINO libs setup
ARDUINO_H = $(ARDUINO_HW_ROOT)/cores/arduino
ARDUINO_STD = $(ARDUINO_HW_ROOT)/variants/standard


###########################
# compiler and linker flags
export CFLAGS = -mmcu=$(MCU) -Wall -I. -I$(ARDUINO_H) -I$(ARDUINO_STD) -DF_CPU=16000000 -Os #-g
export LDFLAGS = -g $(TARGET_ARCH) -lm -Wl,--gc-sections #	-Os


#################
# AVRDUDE options
PGMER = -c arduino -b 57600 -P $(TERM)
PGMERISP = -c arduino -b 115200 -P $(TERM)
ARVDUDECONF= -C $(AVRDUDECONF_LOC)/avrdude.conf
export DUDE = $(AVRDUDE_PATH)/avrdude -F -v -p $(MCU) $(AVRDUDECONF)


### OBJS
C_SRC = $(wildcard *.c)
OBJS = $(C_SRC:.c=.o)


all: $(TARGET).hex

%.o:%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex $(TARGET).elf eeprom.hex

upload: $(TARGET).hex
	stty $(STTY_OPT) $(TERM) hupcl # reset
	$(DUDE) $(PGMERISP) -U flash:w:$(TARGET).hex

size: $(TARGET).elf
	avr-size --format=avr --mcu=$(MCU) $(TARGET).elf


clean:
	rm -f *.o *~ *.hex *.elf
