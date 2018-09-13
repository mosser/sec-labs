package io.github.mosser.arduinoml.ens.dsl;


import io.github.mosser.arduinoml.ens.model.*;
import java.util.Optional;

public class InstructionBuilder {

    private StateBuilder parent;

    private Action local =  new Action();

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

    public StateBuilder toLow() {
        local.setValue(SIGNAL.LOW);
        parent.local.getActions().add(this.local);
        return parent;
    }

}
