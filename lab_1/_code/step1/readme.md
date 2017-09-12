# Arduino Lab

## How to compile?

```
azrael:step1 mosser$ make
avr-gcc -c  -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  main.c -o main.o
avr-gcc -g -mmcu=atmega328p -lm -Wl,--gc-sections  -o led7seg.elf main.o
avr-objcopy -j .text -j .data -O ihex led7seg.elf led7seg.hex
avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex led7seg.elf eeprom.hex
avr-objcopy: --change-section-lma .eeprom=0x0000000000000000 never used
```

## How to upload to the board?

```
azrael:step1 mosser$ make upload
```
