# SEC-Lab 1: ArduinoML

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2018.09

## Problem Description

In this lab, you will implement the very same (simple) behavior, at different levels of abstraction. This journey through abstraction levels will help you to identify the pros and cons of each level, and the importance of model-driven engineering and domain-specific languages to reason about domains.


For each lab, you'll have to implement two simple behaviors, and then compose them:

  1. Building a application that switch on or off a LED based on a button sensor;
  2. Building a simple counter using a 7-segment display;
  3. Compose the two apps so that the button control both the display and the LED.

<p align="center">
  <img src="https://raw.githubusercontent.com/mosser/sec-labs/master/lab_1/figs/montage.jpg"/>
</p>

You will be given a whole platform with an Arduino UNO, some leds, a breadboard, wires ...  **You will be responsible for them for the duration of this lab** On the breadboards, all points in a given supply line (blue/black, read) are connected. Same for the columns. More details about the experimental setup are available here: [Board details](https://github.com/mosser/sec-labs/blob/master/lab_1/_board.md)

## Steps

We decomposed this lab into 8 steps, from a low level of abstraction (plain old C code) to high level meta-programming environments (DSL workbench). At each step, the lab describe how to model/implement the "LED" example. You'll have to adapt this example to fit the "counter" example, and the composition.

  1. [Plain old C code](https://github.com/mosser/sec-labs/blob/master/lab_1/step_1.md)
  2. [Using the ArduinoLib](https://github.com/mosser/sec-labs/blob/master/lab_1/step_2.md)
  3. [Implementing a Finite State Machine](https://github.com/mosser/sec-labs/blob/master/lab_1/step_3.md)
  4. [Modelling a Finite state machine](https://github.com/mosser/sec-labs/blob/master/lab_1/step_4.md)
  5. [Re-modelling the domain](https://github.com/mosser/sec-labs/blob/master/lab_1/step_5.md)
  6. [Using an existing language: Lustre](https://github.com/mosser/sec-labs/blob/master/lab_1/step_6.md)
  7. [Implementing an external compiler](https://github.com/mosser/sec-labs/blob/master/lab_1/step_7.md)
  8. [Embedding inside an host language](https://github.com/mosser/sec-labs/blob/master/lab_1/step_8.md)
  9. [Using a DSL workbench](https://github.com/mosser/sec-labs/blob/master/lab_1/step_9.md)

For each step, the kick-off code is available under the [code directory](https://github.com/mosser/sec-labs/tree/master/lab_1/_code). Use it as a starter to support the LED case study and to be adapted for the counter one.
