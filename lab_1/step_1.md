# SEC-Lab1, Step 1

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * [Starter code](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step1)
  * Version: 2017.09

## Objectives

  1. Understand the execution semantics associated to the board;
  2. Use the `avr` standard C library to code the feature;
  3. Use `make` to automate compilation & upload the program on the board.

## Arduino programming style

Here is the pattern we will use to program the Arduino :

```C
#include <avr/io.h>
#include <util/delay.h>

void setup(void) {}

int main(void)
{
  setup();
  while(1)
  {
    // Business code goes here
    _delay_ms(1000);
  }
}
```

The program to embed on the board implements an infinite loop, where the main behavior will be called. The `setup` procedure is used to initialize the board, //e.g.//, specify which pin is used as input or output.

### Controlling the LED

To switch a led on or off on a Arduino, we need to
* configure the port/pin where the led is connected into
  _reading mode_ (in the setup procedure)
* write a 0 (off) or a 1 (on) into the same port when required.

We give you the LED example, and here are some information:
* As the led is linked to digital pin 13, the port to be manipulated
  is DDRB, here every single pin from 8 to 13 is set to "input" (0)
  excepting bit 5 which gives an "output" access to the led (1).

* The instruction `PORTB ^= 0b00100000;` makes the led blink, as the xor
  operator permits to toggle the 5th bit from 0 to 1 or 1 to 0 each
  time we enter a different loop.



### Additional documentation

Other links:
* [port manipulation](https://www.arduino.cc/en/Reference/PortManipulation). Warning,
the documentation is for the Arduino Lib format. In raw C, you should use
`0b11111110` (rather than `B11111110`).
* [Boolean operators](http://playground.arduino.cc/Code/BitMath),
* [AVR libc doc for delays](http://www.nongnu.org/avr-libc/user-manual/group__util__delay.html).



## Expected Work

* Add functionality for the button: write a `int get_reset_value()`
  function that reads on digital 10 (use `PINB` value and some boolean
  operators). Use it in the `main` to control the led (switch it on to
  off or off to on if the button is pressed). Do not forget to update
  the `setup` function if required. Test.

* Add functionality for the seven-segment display: write a `void
display_7seg(int value)` function to display a given number.
As an
  example, our version begins with:
```C
void display_7seg(int value){
  switch (value) {
  case 0: //a,b,c,d,e,f
    PORTD = 0b01111110;
    break;
	//todo: implement the rest!
}
```

And use it to increment the 7 segment value each time you enter the
  loop. If the button is pressed, the 7-segment should reset
  to 0. Test.


## Feedback questions

  - What can we say about readability of this code? What are the skills required to write such a program?
  - Regarding the application domain, could you characterize the expressivity?
  The configurability of the code to change pins or behavior? Its debugging capabilities?
  - Regarding the performance of the output code, what kind of parallelism is expressed by the use of the DDRx registers?
  - What if we add additional tasks in the micro-controller code, with the same frequency? With a different frequency?

  * Going to next step: [Step #2](https://github.com/mosser/sec-labs/blob/master/lab_1/step_2.md)
