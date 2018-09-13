## How to start the Lustre environment?

```
azrael:step5 mosser$ ./lance_lustre.sh macosx
############################################################
Some Examples
   cd /Users/mosser/work/ens/sec-labs/lab_1/_code/step5/lustre-v4-III-c-macosx/examples/     # Official Lustre tests
   # Simulate a node
   luciole filename.lus node
   # Compile (see the provided makefile)
############################################################
For the arduino led
   cd /Users/mosser/work/ens/sec-labs/lab_1/_code/step5/Arduino7seg
   make all upload
############################################################
If you quit this shell, you quit the Lustre environment.
############################################################

###LUSTRE###$
```

## How to compile?

```
###LUSTRE###$ cd /Users/mosser/work/ens/sec-labs/lab_1/_code/step5/LustreArduino/
###LUSTRE###$ make all
lus2c led7seg.lus cpt
--Pollux Version 2.4
--ec2c cpt.ec
avr-gcc -c -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  cpt.c -o cpt.o
avr-gcc -c -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  glue_arduino.c -o glue_arduino.o
avr-gcc -c -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  main.c -o main.o
avr-gcc -c -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  wiring.c -o wiring.o
avr-gcc -c -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  wiring_digital.c -o wiring_digital.o
avr-gcc -g -mmcu=atmega328p -lm -Wl,--gc-sections  -o led7seg.elf cpt.o glue_arduino.o main.o wiring.o wiring_digital.o
avr-objcopy -j .text -j .data -O ihex led7seg.elf led7seg.hex
avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex led7seg.elf eeprom.hex
avr-objcopy: --change-section-lma .eeprom=0x0000000000000000 never used
```

## How to upload to the board?

```
###LUSTRE###$ make upload
```
