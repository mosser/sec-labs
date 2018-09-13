# SEC-Lab1, Step 6

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2018.09
  * [Starter code](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step6)
  * Previous step: [Step #4](https://github.com/mosser/sec-labs/blob/master/lab_1/step_5.md)


## Objectives

  1. From FSM to a language that compiles to FSMs;
  2. Use the Lustre synchronous language and compiler to code the
  functionality;
  3. Abstract low level I/O through glue code;
  4. Abstract the FSM in a unique step function.


## Getting Started!

First launch the script to install Lustre, and play with the provided Lustre examples
and the luciole simulator:
```
luciole edge2.lus edge
```

In luciole, use "sim2chro" functionality to play with I/Os and draw
timing pictures.


## The LED example


* In Lustre, things are simple, we encode the sequence of values of
boolean or numerical variables into _nodes_. The compilation chain does the rest!

```
node cpt(reset:bool) returns  (led_on: bool) ;
let
   led_on = false -> not(pre(led_on));
tel
```

* Observe the  `glue_arduino.c` and `main.c` files. The main loop is
  still encoded by the user, but the rest of the functionnality: the
  `step()` function is not.

* After compilation, observe the automatically generated `cpt.c`
  file. The Lustre compiler (`lus2c`) has been invoked.


## Documentation & Bibliography

Lustre is a language that was designed for safety critical systems
(avionics, nuclear plants), in Grenoble, in the late 80s. Its
industrial version Scade is still used by Airbus.

* Have a look into the
[Lustre V6 official webpage](http://www-verimag.imag.fr/Lustre-V6.html?lang=fr)
We will use the V4 distribution but the language description is
accurate in the V6 documentation.

* Lustre Compilation Flow:
![Lustre compilation flow](figs/compil2.png)

* The Lustre compiler comes with some other tools like a simulator, and
 a model checker. If you have time, you can play with them and try to
 prove simple properties.

## Expected Work


* In the directory `LustreArduino`, modify the Lustre code to enable
the button (reset is true if the button has value 1). You will have to
modify `main.c` and the glue code.

* Modify the Lustre code  for the seven segment display. Compile,
test!

## Feedback Questions

  * Who is the intended user for such a language?
  * What is the cost of reusing this existing DSL for the developer in terms of code?
  * What is the cost of adding a new task of our domain?
  * Was is the cost of adding a new hardware target?
  * The Lustre language comes with its own ecosystem (test, formal verification), what are the generic properties we can imagine to prove from our domain?

* Going to next step: [Step #7](https://github.com/mosser/sec-labs/blob/master/lab_1/step_7.md)
