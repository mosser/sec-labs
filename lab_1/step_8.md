# SEC-Lab1, Step #8

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2017.09
  * [Starter code](https://github.com/mosser/sec-labs/tree/master/lab_1/_code/step8)
  * Previous step: [Step #7](https://github.com/mosser/sec-labs/blob/master/lab_1/step_7.md)

## Objectives

  1. Use a DSL workbench to create a language ([MPS](https://confluence.jetbrains.com/display/MPS/Download+MPS)  2017.2)
  2. Uses a template-based code generation approach (TextGen)

## The LED example using MPS

### Creating a new project

We start by creating a new project for a language named ArduinoML, associated to a a _sandbox_ solution (to write programs in ArduinoML) and a _runtime_ solution (for test purpose).

<p align="center">
  <img src="https://raw.githubusercontent.com/mosser/sec-labs/master/lab_1/figs/mps/1_create_project.png" />
</p>

### Creating the Concepts

Each concept of the ArduinoML abstract syntax tree is modelled as a concept in MPS.

  * The `App`, `Actuator` and `State` concepts implements the `INamedConcept` interface as one can use their `name` to reference it;
  * The `App` concept is considered as a `root`, as it is the entry point of the language;
  * The `SIGNAL` concept is an Enumeration, containing the `HIGH` and `LOW` value. One can change the way the value are displayed using the _presentation_ field;
  * Modelling concepts in MPS:
    * Properties are used to model simple attributes (here the `SIGNAL` to send to a given actuator)
    * Children are used to model elements that are contained by the concept. An element can only be contained by a single container;
    * References are used to link an element to another one.

<p align="center">
  <img src="https://raw.githubusercontent.com/mosser/sec-labs/master/lab_1/figs/mps/2_concepts.png" />
</p>

Right-click on the project name and select `Make` to synchronise the language with the other solutions (and do this operation each time the tool underlines your models stating that "_generation is required_").

### Creating models 

Using these concepts, one can create a program in ArduinoML. Right-click on the _sandobox_ project and create a new `App` (proposed as it is defined as a _root concept_). In MPS, the syntax is made by _projecting_ the AST, and a default project does exists in the tool. 

<p align="center">
  <img src="https://raw.githubusercontent.com/mosser/sec-labs/master/lab_1/figs/mps/3_template.png" />
</p>

It is important to notice that you are not editing text, but directly the AST, using a _fill in the blanks_ (the red parts) approach. The LED example is modelled by filling these holes (we added an `isInitial` property in the `State` concept between the 2 screenshots).

<p align="center">
  <img src="https://raw.githubusercontent.com/mosser/sec-labs/master/lab_1/figs/mps/4_LED.png" />
</p>

### Modifying the projections

The default project has the advantage of existing for free, but is not really user-friendly. To create our own projects, we define _Editors_ associated to the concepts.

MPS provides a DSL to model _editors_. The DSL relies on the definition of collections (horizontal or vertical) to assemble the attributes associated to a given concept in the proper way. This is a tabular approach (which is arguable in terms of design choices and defined syntax) where you need to think of your projection as imbricated boxes. 

One must notice that the automatic completion is mandatory (using CRTL-space) to find the right symbol while defining the projection.

  * `[/` ... `/]`: vertical collection, all elements between these elements will be displayed on a vertical way;
  *  `[>` ... `<]`: horizontal collection;
  * `[-` ... `-]`: horizontal collection supporting indentation , using `--->` to specify the indentation level;
  * `{` x `}`: refers to the property `x` defined in the current concept;
  * `(/ %` x `%` ... `/)`: vertical collection of children nodes defined in `x`.
  * `empty`: an empty line

As we are defining a set of projections, building the language automatically update the `LED` model we defined previously.

<p align="center">
  <img src="https://raw.githubusercontent.com/mosser/sec-labs/master/lab_1/figs/mps/5_editor.png" />
</p>

### Specifying constraints


### Controlling Scope

### Generating code

## Expected Work

  * Adapt the language to support sensors and transitions associated to sensors;
  * Identify the abstractions needed in the language to support the 7-segment display;
  * Adapt the language to support it.

## Documentation & Bibliography

  * (other) Existing DSL workbenches
    * XText
    * Spoofax
    * MetaEdit 
    * Gemoc Studio
    * ...
  * [MPS documentation](https://confluence.jetbrains.com/display/MPSD20172/MPS+User%27s+Guide) 

  * Going to next step: _That's all folks!_