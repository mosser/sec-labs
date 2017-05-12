# SEC-Lab 1: ArduinoML

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2017.05

## Problem Description

![Expected behavior](figs/demochrono.png)

** TODO : change the fig! **

## Domain Description

### Pre-installation (Arduino stuff)

![Arduino Uno Platform](figs/arduino-uno-dip-rev3.jpg)

  * You may have to install the following (Linux) packages: `arduino` ,
`gcc-avr` and `avrdude` (`avr-binutils` et `avr-libc` if they are not included)
  * `avrdude.conf` must be in `/usr/share/arduino/hardware/tools/` (if not you have to modify Makefiles).
  * The user should have the right to write on  the USB port : 
`usermod -aG dialout <username>`

### A traduire 

Les cartes Arduino / Guenuino sont des cartes matériellement libres
architecturées autour d'un micro-contrôleur de la famille AVR
d'Atmel. Pour ce TP nous utiliserons des Arduino UNO (atmega328p)
comme celui de la Figure, qui fournissent un certain
nombre d'entrées sorties numériques et analogiques sur lesquelles nous
pourrons connecter des LEDs, des boutons poussoir, un afficheur 7
segment.


Le micro-contrôleur est
programmé avec un bootloader de façon à ce qu'un programmateur
  dédié ne soit pas nécessaire. Les Makefile fournis utiliseront
  `avrdude` [doc](http://www.nongnu.org/avrdude/)
  pour charger les binaires dans la mémoire du  micro-contrôleur.


On vous fournit par trinôme une plateforme de TP comportant 1 arduino
Uno, un cable USB, une plateforme ``breadboard'', un écran LCD 2
lignes, deux LEDs (une rouge, une jaune), trois résistances 220 ohm,
et une vingtaine de fils. ** Ils seront sous votre responsabilité
durant 2 semaines **

*  On utilise une plaque d'essai *breadboard* sans
  soudure. Dans cette plaque, 
  tous les points d'une même ligne d'alimentation (horizontales sur le
  schéma) et tous les points d'une même colonne (numérotées 20, 30,
  ... sur le schéma) sont connectés entre eux.

* La grande patte de la LED est connectée au port Analog 13 de
  l'Arduino via une resistance 220 ohm. 

* Le circuit est fermé en reliant la petite patte de la LED à la
  masse, via la ligne noire (ou bleue) du *breadboard*.


## Example Applications

![Arduino Uno Platform](figs/montage.jpg)


### Switch the light on!

![Arduino Uno + Led on Port Digital 13](figs/led_schema1_port13_cut.jpg)

### Count to 9

![Arduino Uno + 7 seg Common Cathode](figs/7SegmentCC_bb.png)
![Arduino Uno + 7 seg Common Anode](figs/7SegmentAC_bb.png)

![7 seg Common Cathode interface](figs/numerotation_7segvertical_CC.png)
![7 seg Common Anode interface](figs/numerotation_7seghorizontal_AC.jpg)

** TODO ajouter les résistances **

### The all together

## Steps

In this lab, you will implement the very same (simple) piece of software, at different levels of abstraction. This journey through abstraction levels will help you to identify the pros and cons of each level, and the importance of model-driven engineering and domain-specific languages to reason about domains.

  1. [Plain old C code](https://github.com/mosser/sec-labs/blob/master/lab_1/step_1.md)
  2. [Using the ArduinoLib](https://github.com/mosser/sec-labs/blob/master/lab_1/step_2.md)
  3. [Implemeting a Finite State Machine](https://github.com/mosser/sec-labs/blob/master/lab_1/step_3.md)
  4. [Modelling a Finite state machine](https://github.com/mosser/sec-labs/blob/master/lab_1/step_4.md)
  5. [Using an existing language: Lustre](https://github.com/mosser/sec-labs/blob/master/lab_1/step_5.md)
  6. [Implementing an external compiler](https://github.com/mosser/sec-labs/blob/master/lab_1/step_6.md)
  7. [Embedding inside an host language](https://github.com/mosser/sec-labs/blob/master/lab_1/step_7.md)
  8. [Using a DSL workbench](https://github.com/mosser/sec-labs/blob/master/lab_1/step_8.md)
