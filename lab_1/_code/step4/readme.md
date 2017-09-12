# Arduino Lab

## How to compile?

```
azrael:step4 mosser$ mvn clean package
[INFO] Scanning for projects...
[INFO]
[INFO] ------------------------------------------------------------------------
[INFO] Building Java implementation of ArduinoML abstract syntax 1.0
[INFO] ------------------------------------------------------------------------
[INFO]
[INFO] --- maven-clean-plugin:2.5:clean (default-clean) @ kernel-jvm ---
[INFO] Deleting /Users/mosser/work/ens/sec-labs/lab_1/_code/step4/target
[INFO]
[INFO] --- maven-resources-plugin:2.6:resources (default-resources) @ kernel-jvm ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] skip non existing resourceDirectory /Users/mosser/work/ens/sec-labs/lab_1/_code/step4/src/main/resources
[INFO]
[INFO] --- maven-compiler-plugin:3.6.1:compile (default-compile) @ kernel-jvm ---
[INFO] Changes detected - recompiling the module!
[INFO] Compiling 10 source files to /Users/mosser/work/ens/sec-labs/lab_1/_code/step4/target/classes
[INFO]
[INFO] --- maven-resources-plugin:2.6:testResources (default-testResources) @ kernel-jvm ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] skip non existing resourceDirectory /Users/mosser/work/ens/sec-labs/lab_1/_code/step4/src/test/resources
[INFO]
[INFO] --- maven-compiler-plugin:3.6.1:testCompile (default-testCompile) @ kernel-jvm ---
[INFO] No sources to compile
[INFO]
[INFO] --- maven-surefire-plugin:2.12.4:test (default-test) @ kernel-jvm ---
[INFO] No tests to run.
[INFO]
[INFO] --- maven-jar-plugin:2.4:jar (default-jar) @ kernel-jvm ---
[INFO] Building jar: /Users/mosser/work/ens/sec-labs/lab_1/_code/step4/target/kernel-jvm-1.0.jar
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time: 3.735 s
[INFO] Finished at: 2017-09-12T10:46:30+02:00
[INFO] Final Memory: 17M/211M
[INFO] ------------------------------------------------------------------------
```

## How to generate the code from the model?

```
azrael:step4 mosser$ mvn -q exec:java
Generating C code: ./output/fsm.h
Generating C code: ./output/main.c
Code generation: done
Board upload : cd output && make upload && cd ..;
```

## How to upload to the board?

```
azrael:step4 mosser$ cd output && make upload && cd ..;
avr-gcc -c -mmcu=atmega328p -Wall -I. -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -DF_CPU=16000000 -Os  main.c -o main.o
...
avrdude done.  Thank you.
```
