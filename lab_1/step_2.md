# SEC-Lab1, Step 2

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2017.09
  * [Starter code](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step2)
  * Previous step: [Step #1](https://github.com/mosser/sec-labs/blob/master/lab_1/step_1.md)

## Objectives

  1. Goes from plain C to library;
  2. Use the Arduino C/C++ library to code the feature;
  3. Abstracting low level I/O call through function calls.


## The LED example
* Include `Arduino.h` and link with the lib (the Makefile does this
job):
```C
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
```

* Now each pin has his own configuration and can be set independently
of the others:   `pinMode(led, OUTPUT);` for the led setup and
`digitalWrite(led, LOW);`,  `digitalWrite(led, HIGH);` to set the led
value.

* We had to store the led state in the `led_on` variable.


## Documentation & Bibliography

* The Arduino library
[reference](https://www.arduino.cc/en/Reference/HomePage). See
the `pinMode` and `digitalRead` documentation.


## Expected Work

* Implement the Button functionality. Test it!
* Implement the Seven Segment display functionnality: first implement `displayDigit`:
```C
void displayDigit(int digit)
{
  turnOff();
  //Conditions for displaying segment a
  if(digit!=1 && digit != 4)
    digitalWrite(a,HIGH);
	//continue
	}
```
and use it in the main. Test it!


## Feedback Questions

  - Is the readability problem solved?
  - What kind of parallelism can still be expressed?
  - Who is the public targeted by this “language”?
  - Is this language extensible enough to support new features?
  - What is the price for the developer?

  * Going to next step: [Step #3](https://github.com/mosser/sec-labs/blob/master/lab_1/step_3.md)
