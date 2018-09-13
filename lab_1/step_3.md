# SEC-Lab1, Step 3

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2017.09
  * [Starter code](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step3)
  * Previous step: [Step #2](https://github.com/mosser/sec-labs/blob/master/lab_1/step_2.md)

## Objectives

  1. Introduce home-made abstraction in C code

## The LED example

The blinking LED example is a good example of a _finite state machine_. The LED goes from an _on_ state to an _off_ one, indefinitely.

<p align="center">
  <img src="https://raw.githubusercontent.com/mosser/sec-labs/master/lab_1/figs/fsm.png"/>
</p>

The idea is to reify in the host language the associated abstraction. We propose here a functional approach, where each state is designed as a function, and moving from one state to the other is modelled by a call to the associated function. The initial state is the one called by the `main` loop.

```C
void state_on() {
  digitalWrite(led, HIGH);
  _delay_ms(1000);
  state_off();
}

void state_off() {
  digitalWrite(led, LOW);
  _delay_ms(1000);
  state_on();
}
```

## Expected Work

  * Modify the given code to support an interaction with the button. Instead of blinking, the led will switch from one state to the other when the button is pressed.
  * Identify the right computation model associated to the 7-segment display use case.
  * Implement it in `main.c` (states signature are declared in `fsm.h`)

## Feedback Questions:

  - Does introducing a convention solve the readability issue?
  - How to extend an app with a new feature? Does the approach prevent one to perform invasive changes in the existing behavior to introduce a new one?
  - How to extend the code so that to support new features, e.g.,
memory-less tasks, state-full tasks, different frequencies?

## Documentation & Bibliography

  * [Domain Specific Languages](https://martinfowler.com/books/dsl.html), Martin Fowler (Chapter 7: _Alternative Computation Model_)

  * Going to next step: [Step #4](https://github.com/mosser/sec-labs/blob/master/lab_1/step_4.md)
