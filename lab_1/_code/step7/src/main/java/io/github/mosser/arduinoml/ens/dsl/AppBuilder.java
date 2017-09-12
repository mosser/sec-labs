package io.github.mosser.arduinoml.ens.dsl;


import io.github.mosser.arduinoml.ens.generator.ToC;
import io.github.mosser.arduinoml.ens.generator.Visitor;
import io.github.mosser.arduinoml.ens.model.*;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class AppBuilder {

    App theApp = null;

    public static AppBuilder application(String name) {
        AppBuilder inst = new AppBuilder();
        inst.theApp = new App();
        inst.theApp.setName(name);
        return inst;
    }

    private AppBuilder() { }

    Map<String, State> states = new HashMap<>();
    Map<State, String> transitions = new HashMap<>();

    public AppBuilder uses(Actuator b) {
        this.theApp.getActuators().add(b);
        return this;
    }

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


    public StateBuilder hasForState(String name) {
        return new StateBuilder(this, name);
    }


    public void export(String header, String code) {
        resolveTransitions();
        // Export code
        Visitor codeGenerator = new ToC();
        theApp.accept(codeGenerator);
        // Writing C files
        try {
            System.out.println("Generating C code: ./output/fsm.h");
            Files.write(Paths.get("./output/fsm.h"), codeGenerator.getHeaders().toString().getBytes());
            System.out.println("Generating C code: ./output/main.c");
            Files.write(Paths.get("./output/main.c"), codeGenerator.getCode().toString().getBytes());
            System.out.println("Code generation: done");
            System.out.println("Board upload : cd output && make upload && cd ..;");
        } catch (IOException e) {
            System.err.println(e);
        }
    }

    private void resolveTransitions() {
        this.transitions.forEach(((from, nextId) -> from.setNext(this.states.get(nextId)) ));
    }

    Optional<Actuator> findActuator(String name) {
        Optional<Actuator> b = theApp.getActuators()
                .stream()
                .filter( actuator -> actuator.getName().equals(name))
                .findFirst();
        return b.map(Optional::of).orElse(Optional.empty());
    }

}
