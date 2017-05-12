






![figs/arduino-uno-dip-rev3.jpg](Arduino Uno Platform)

# Pre-installation #

## Arduino stuff ##

You may have to install the following (Linux) packages: `arduino` ,
`gcc-avr` and avrdude (`avr-binutils` et `avr-libc` if they are not included)

`avrdude.conf` must be in `/usr/share/arduino/hardware/tools/` (if not you
have to modify Makefiles).

The user should have the right to write on  the USB port : 
`usermod -aG dialout <username>`

## ?? ##
