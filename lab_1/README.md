







![figs/arduino-uno-dip-rev3.jpg](Arduino Uno Platform)

# Pre-installation #

## Arduino stuff ##

You may have to install the following (Linux) packages: `arduino` ,
`gcc-avr` and avrdude (`avr-binutils` et `avr-libc` if they are not included)

`avrdude.conf` must be in `/usr/share/arduino/hardware/tools/` (if not you
have to modify Makefiles).

The user should have the right to write on  the USB port : 
`usermod -aG dialout <username>`



# SEC-Lab 1: ArduinoML

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](laure.gonnord@ens-lyon.fr)
  * Version: 2017.05

## Problem Description

## Domain Description

## Example Applications

### Switch the light on!

### Count to 9

### The all together


## Steps

In this lab, you will implement the very same (simple) piece of software, at different levels of abstraction. This journey through abstraction levels will help you to identify the pros and cons of each level, and the importance of model-driven engineering and domain-specific languages to reason about domains.

  1. [Plain old C code](https://github.com/mosser/sec-labs/lab_1/step_1.md)
  2. [Using the ArduinoLib](https://github.com/mosser/sec-labs/lab_1/step_2.md)
  3. [Implemeting a Finite State Machine](https://github.com/mosser/sec-labs/lab_1/step_3.md)
  4. [Modelling a Finite state machine](https://github.com/mosser/sec-labs/lab_1/step_4.md)
  5. [Using an existing language: Lustre](https://github.com/mosser/sec-labs/lab_1/step_5.md)
  6. [Implementing an external compiler](https://github.com/mosser/sec-labs/lab_1/step_6.md)
  7. [Embedding inside an host language](https://github.com/mosser/sec-labs/lab_1/step_7.md)
  8. [Using a DSL workbench](https://github.com/mosser/sec-labs/lab_1/step_8.md)

