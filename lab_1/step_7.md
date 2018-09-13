# SEC-Lab1, Step #7

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2018.09
  * [Starter code](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step7)

  * Previous step: [Step #5](https://github.com/mosser/sec-labs/blob/master/lab_1/step_6.md)

## Objectives

  1. Use a classical meta-compiler (antler) to define a grammar and implement a lexer/parser for our langage;
  2. Leverage the `Listener` pattern to build a model from a given word

## The LED example

For this example, we model the LED example using a textual syntax for the FSM

```
application led {

    actuator led: 13

    -> off {
        led is LOW
        goto on
    }

    on {
        led is HIGH
        goto off
    }
}
```

### Modelling the grammar

The associated grammar is implemented using ANTLR, in the [`ArduinoML.g4`](https://github.com/mosser/sec-labs/blob/master/lab_1/_code/step6/src/main/antlr4/io/github/mosser/arduinoml/external/ArduinoML.g4) file.

```antlr
app         :   'application' name=IDENTIFIER '{' actuator+ state+ '}';
actuator    :   'actuator' location ;
location    :   id=IDENTIFIER ':' port=PORT_NUMBER;
state       :   initial? name=IDENTIFIER '{'  action+ next '}';
action      :   receiver=IDENTIFIER 'is' value=SIGNAL;
next        :   'goto' target=IDENTIFIER ;
initial     :   '->';
```

### Instantiating models

When using maven to build the code, the `antlr` compiler is called on this grammar file, and generate the associated lexer and parser in `target/generated-sources/antlr4`. If you are using an IDE, do not forget to include this directory in your classpath.

The antlr tool supports two patterns to interact with the DSL code: a classical visitor or the listener pattern. As the visitor was previously described, we use here the listener one. By extending `ArduinoMLBaseListener`, one can implement a listener for a word conform to the `ArduinoML` grammar. For each rule `R` declared in the grammar, the listener provides two methods:

  * `enterR`: triggered each time the system enters in the `R` rule;
  * `exitR`: triggered each time the system enters in the `R` rule.

Using this pattern, we override several methods to implement a listener named [`ModelBuilder`](https://github.com/mosser/sec-labs/blob/master/lab_1/_code/step6/src/main/java/io/github/mosser/arduinoml/ens/compiler/ModelBuilder.java) that build instances of the previously defined meta-model (step 4). We rely on shared variable (_e.g._, a symbol table for states, the current application to build, the current state) to share information between method calls.

```Java
private App theApp = null;
private Map<String, State>    states  = new HashMap<>();
private State currentState = null;

// ...

@Override public void enterState(ArduinoMLParser.StateContext ctx) {
	State local = new State();
	local.setName(ctx.name.getText());
	this.currentState = local;
	this.states.put(local.getName(), local); // Symbol table for states
}

@Override public void exitState(ArduinoMLParser.StateContext ctx) {
	this.theApp.getStates().add(this.currentState);
	this.currentState = null;
}

//...
```  

### Calling the compiler

To call the compiler (see the [`Main`](https://github.com/mosser/sec-labs/blob/master/lab_1/_code/step6/src/main/java/Main.java) class), we bind the lexer and parser together, and associate our ModelBuilder as a parse tree walker.

```Java
private static App buildModel(CharStream stream) {
	ArduinoMLLexer    lexer   = new ArduinoMLLexer(stream);
	lexer.removeErrorListeners();
	lexer.addErrorListener(new StopErrorListener());

	ArduinoMLParser   parser  = new ArduinoMLParser(new CommonTokenStream(lexer));
	parser.removeErrorListeners();
	parser.addErrorListener(new StopErrorListener());

	ParseTreeWalker walker  = new ParseTreeWalker();
	ModelBuilder      builder = new ModelBuilder();

	// parser.app() is the entry point of the grammar
	walker.walk(builder, parser.app());
    return builder.retrieve();
}
```

## Expected Work

  * Adapt the language to support sensors and transitions associated to sensors;
  * Identify the abstractions needed in the language to support the 7-segment display;
  * Adapt the language to support it.

## Feedback Questions

  * Who is the intended user ? What about the tooling associated to the language?
  * More generally, what is the cost of such an approach?
  * To what extent is the language fragile to the introduction of new features?
  * What is the relationship between the meta-model and the grammar?
  * How to validate that the defined syntax is the right one?

## Documentation & Bibliography

  * [http://www.antlr.org/](http://www.antlr.org/)
  * The definitive ANTLR4 reference, Terence Parr
  * Language implementation patterns, Terence Parr

  * Going to next step: [Step #8](https://github.com/mosser/sec-labs/blob/master/lab_1/step_8.md)
