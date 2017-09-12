package io.github.mosser.arduinoml.ens.dsl;

import io.github.mosser.arduinoml.ens.model.State;


public class StateBuilder {

    AppBuilder parent;
    State local = new State();

    StateBuilder(AppBuilder parent, String name) {
        this.parent = parent;
        this.parent.states.put(name, this.local);
        local.setName(name);
    }

    public StateBuilder initial() { parent.theApp.setInitial(this.local); return this; }

    public AppBuilder goingTo(String next) {
        this.parent.transitions.put(local, next);
        parent.theApp.getStates().add(this.local);
        return parent;
    }

    public InstructionBuilder setting(String actuatorName) {
        return new InstructionBuilder(this, actuatorName);
    }


}
