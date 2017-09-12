# SEC-Lab1, Step 4

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2017.09
  * [Starter code](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step4)
  * Previous step: [Step #3](https://github.com/mosser/sec-labs/blob/master/lab_1/step_3.md)


## Objectives

  1. Create a meta model dedicated to a given problem;
  2. Tool the model with code generation capabilities;
  3. Reach an execution environment.

## The LED example

### Meta-model description

As stated in the previous step, a _finite state machine_ is a good abstraction for the blinking LED example. We define a meta-model to express such pieces of software, where an `App` contains several `State`s, and interact with `Actuator`s. In each state, a sequence of `Action`s identify which `SIGNAL` must be sent to the `Actuator`s for this very state. Finally, a `State` contains a single transition with the `next` one.

<p align="center">
  <img src="https://raw.githubusercontent.com/mosser/sec-labs/master/lab_1/_code/step4/model.png" />
</p>

The meta-model is implemented in Java, and available [here](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step4/src/main/java/io/github/mosser/arduinoml/ens/model)

### Model Instantiation

As the meta-model is naive in terms of implementation (plain Java classes with getters and setters), so creating a model conform to this meta-model (here objects instantiated from the classes) is quite verbose.

```Java
Actuator led = new Actuator();
led.setName("LED");
led.setPin(13);

// Declaring states
State on = new State();
on.setName("on");

State off = new State();
off.setName("off");

// Creating actions
Action switchTheLightOn = new Action();
switchTheLightOn.setActuator(led);
switchTheLightOn.setValue(SIGNAL.HIGH);

Action switchTheLightOff = new Action();
switchTheLightOff.setActuator(led);
switchTheLightOff.setValue(SIGNAL.LOW);

// Binding actions to states
on.setActions(Arrays.asList(switchTheLightOn));
off.setActions(Arrays.asList(switchTheLightOff));

// Binding transitions to states
on.setNext(off);
off.setNext(on);

// Building the App
App theApp = new App();
theApp.setName("Led!");
theApp.setBricks(Arrays.asList(led));
theApp.setStates(Arrays.asList(on, off));
theApp.setInitial(on);
```

### Code Generation

To generate the FSM code, we use the _Visitor_ design pattern. A Visitor is used to walk through a given model, externalising the behaviour associated to such a visit. Using this pattern, it is possible to implement several visitors for the same meta-model, meaning here different code generation for example.

For a meta-model element to be compatible with the visitor pattern, it must implements the `Visitable` interface. This is an invasive modification of the meta-model, but it actually help maintenance as to create a new visit, one simply extend a `Visitor` class and do not have to modify the meta-model again.

<p align="center">
  <img src="https://raw.githubusercontent.com/mosser/sec-labs/master/lab_1/_code/step4/visitable.png" />
</p>



## Expected Work


## Documentation & Bibliography

  * Going to next step: [Step #5](https://github.com/mosser/sec-labs/blob/master/lab_1/step_5.md)
