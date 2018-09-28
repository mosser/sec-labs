# SEC-Lab1, Step 5

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2018.09
  * [Starter code](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step5)
  * Previous step: [Step #4](https://github.com/mosser/sec-labs/blob/master/lab_1/step_4.md)


## Objectives

  1. Moving from FSM to reactive system meta-model
  2. Compare the size of the obtained "product"

## Getting Started!

We give you another Meta Model, now for reactive systems. 

<p align="center">
  <img src="https://raw.githubusercontent.com/mosser/sec-labs/master/lab_1/_code/step5/reactive_model.png" />
</p>


## The LED example

Do the same as before: code generation from this meta-model, the
generated code should look like:


```C
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

int led = 13;
bool is_high = false;

void led_change_state() {
  if (is_high) { digitalWrite(led, LOW);  }
  else         { digitalWrite(led, HIGH); }
  is_high = !is_high;
}

int main(void) {
  pinMode(led, OUTPUT);
  while(1) {
    led_change_state(); _delay_ms(1000);
  }
  return 0;
}
```



## Documentation & Bibliography



## Feedback questions

* Compare how this modeling solution and the previous one
match the domain, especially regarding expressiveness and
scalability.

* What is the cost (e.g., modeling, code generation) of a new
feature for the developer?

* What about scalability of the modeling paradigm itself?



* Going to next step: [Step #6](https://github.com/mosser/sec-labs/blob/master/lab_1/step_6.md)
