# Arduino Lab

## How to compile?

```
azrael:step2 mosser$ make
avr-gcc -c -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  main.c -o main.o
avr-gcc -c -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  wiring.c -o wiring.o
avr-gcc -c -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  wiring_digital.c -o wiring_digital.o
avr-gcc -g -mmcu=atmega328p -lm -Wl,--gc-sections  -o led7seg.elf main.o wiring.o wiring_digital.o
avr-objcopy -j .text -j .data -O ihex led7seg.elf led7seg.hex
avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex led7seg.elf eeprom.hex
avr-objcopy: --change-section-lma .eeprom=0x0000000000000000 never used
```

## How to upload to the board?

```
azrael:step2 mosser$ make upload
stty -f /dev/tty.usbmodem* hupcl # reset
...
avrdude done.  Thank you.
```
