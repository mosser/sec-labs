# Arduino Lab

## How to compile?

```
azrael:step6 mosser$ mvn clean package
[INFO] Scanning for projects...
[INFO]
[INFO] ------------------------------------------------------------------------
[INFO] Building AntLR implementation of ArduinoML syntax 1.0
[INFO] ------------------------------------------------------------------------
[INFO]
[INFO] --- maven-clean-plugin:2.5:clean (default-clean) @ kernel-antlr ---
[INFO]
[INFO] --- antlr4-maven-plugin:4.7:antlr4 (antlr) @ kernel-antlr ---
[INFO] ANTLR 4: Processing source directory /Users/mosser/work/ens/sec-labs/lab_1/_code/step6/src/main/antlr4
[INFO] Processing grammar: io/github/mosser/arduinoml/external/ArduinoML.g4
[INFO]
[INFO] --- maven-resources-plugin:2.6:resources (default-resources) @ kernel-antlr ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] Copying 1 resource
[INFO]
[INFO] --- maven-compiler-plugin:3.6.1:compile (default-compile) @ kernel-antlr ---
[INFO] Changes detected - recompiling the module!
[INFO] Compiling 16 source files to /Users/mosser/work/ens/sec-labs/lab_1/_code/step6/target/classes
[INFO]
[INFO] --- maven-resources-plugin:2.6:testResources (default-testResources) @ kernel-antlr ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] skip non existing resourceDirectory /Users/mosser/work/ens/sec-labs/lab_1/_code/step6/src/test/resources
[INFO]
[INFO] --- maven-compiler-plugin:3.6.1:testCompile (default-testCompile) @ kernel-antlr ---
[INFO] No sources to compile
[INFO]
[INFO] --- maven-surefire-plugin:2.12.4:test (default-test) @ kernel-antlr ---
[INFO] No tests to run.
[INFO]
[INFO] --- maven-jar-plugin:2.4:jar (default-jar) @ kernel-antlr ---
[INFO] Building jar: /Users/mosser/work/ens/sec-labs/lab_1/_code/step6/target/kernel-antlr-1.0.jar
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time: 4.536 s
[INFO] Finished at: 2017-09-12T10:52:33+02:00
[INFO] Final Memory: 24M/308M
[INFO] ------------------------------------------------------------------------
```

## How to generate the code from the model?

```
azrael:step6 mosser$ mvn -q exec:java -Dexec.args="src/main/resources/led.arduinoml"

Running the ANTLR compiler for ArduinoML
Using input file: /Users/mosser/work/ens/sec-labs/lab_1/_code/step6/src/main/resources/led.arduinoml
Generating C code: ./output/fsm.h
Generating C code: ./output/main.c
Code generation: done
Board upload : cd output && make upload && cd ..;
```

## How to upload to the board?

```
azrael:step6 mosser$ cd output && make upload && cd ..;
avr-gcc -c -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  main.c -o main.o
...
avrdude done.  Thank you.
```
