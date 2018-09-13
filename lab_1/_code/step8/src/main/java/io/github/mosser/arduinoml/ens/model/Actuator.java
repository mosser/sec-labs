package io.github.mosser.arduinoml.ens.model;


import io.github.mosser.arduinoml.ens.generator.Visitable;
import io.github.mosser.arduinoml.ens.generator.Visitor;

public class Actuator implements NamedElement, Visitable {

    private int pin;
    private String name;

    public int getPin() {
        return pin;
    }
    public void setPin(int pin) {
        this.pin = pin;
    }

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }


    @Override
    public String getName() {
        return name;
    }

    @Override
    public void setName(String name) {
        this.name = name;
    }


}
