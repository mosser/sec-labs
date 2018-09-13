# SEC-Lab1, Step #8

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2018.09
  * [Starter code](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step8)
  * Previous step: [Step #6](https://github.com/mosser/sec-labs/blob/master/lab_1/step_7.md)

## Objectives

  * Discover the principles associated to _Fluent APIs_;
  * Embed a language inside another one.

## The LED example

Instead of writing a new langage, we decide here to _hack_ an existing one (_e.g._, Java). The idea of a fluent interface is to support the definition of a new language by leveraging the available syntax in the host language. For example, the following code is a valid Java code, but is also understandable with respect to our FSM concepts.

```Java
application("theLed")
	.uses(actuator("led", 13))

	.hasForState("on")
		.setting("led").toHigh()
		.goingTo("off")

	.hasForState("off")
		.initial()
		.setting("led").toLow()
		.goingTo("on")

	.export("./output/fsm.h", "./output/main.c");
```

This approach relies on the definition of methods to support the fluent API. In our example, such elements are defined in the [`dsl`](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step7/src/main/java/io/github/mosser/arduinoml/ens/dsl) package. We use _static methods_ and _builders_ to support the API.

### Static methods

The application builder is designed to hide its constructor, thus the only way to create an instance of the builder is to call the `application(name: String)` method it provides. The same trick is used for the `actuator` method, supporting a user-friendly way of instantiating an actuator.

When creating an application, one import statically these methods (`import static AppBuilder.*`), and can use it directly in the code.

```Java
public static Actuator actuator(String name, int port) {
	if(name.isEmpty() || !Character.isLowerCase(name.charAt(0)))
		throw new IllegalArgumentException("Illegal brick name: ["+name+"]");
	if(port < 1 || port > 13)
		throw new IllegalArgumentException("Illegal brick port: ["+port+"]");
	Actuator result = new Actuator();
	result.setName(name);
	result.setPin(port);
	return result;
}
```

### Nested Builders

To control the way the API is used, we define intermediary object that expose the right interfaces. For example, inside a given state, calling the `setting` method yields an `InstructionBuilder` that only support the `toLow` or `toHigh` methods. When called, the method returns the parent `StateBuilder`, allowing one to add another instruction.

```Java
// class StateBuilder
public InstructionBuilder setting(String actuatorName) {
	return new InstructionBuilder(this, actuatorName);
}

// class InstructionBuilder
InstructionBuilder(StateBuilder parent, String target) {
	this.parent = parent;
	Optional<Actuator> opt = parent.parent.findActuator(target);
	Actuator act = opt.orElseThrow(() -> new IllegalArgumentException("Illegal actuator: ["+target+"]"));
	local.setActuator(act);
}

public StateBuilder toHigh() {
	local.setValue(SIGNAL.HIGH);
	parent.local.getActions().add(this.local);
	return parent;
}    
```
Using this programming style, we have a direct control on the language syntax, and one can rely on the code completion mechanism to write in the created language.

## Expected Work

  * Adapt the language to support sensors and transitions associated to sensors;
  * Identify the abstractions needed in the language to support the 7-segment display;
  * Adapt the language to support it.

## Feedback questions

  * How to chose between embedded or external?
  * What is the impact of the host language choice?
  * What about the maintainability of the concrete syntax?
  * Who is targeted as an audience by this class of languages?

## Documentation & Bibliography

  * [Domain Specific Languages](https://martinfowler.com/books/dsl.html), Martin Fowler (Part IV: _Internal DSL Topics_)
  * [ArduinoML syntax Zoo](https://github.com/mosser/ArduinoML-kernel/tree/master/embeddeds) (Embedded section)

  * Going to next step: [Step #7](https://github.com/mosser/sec-labs/blob/master/lab_1/step_7.md)
