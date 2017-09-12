package io.github.mosser.arduinoml.ens.model;

import io.github.mosser.arduinoml.ens.generator.*;

import java.util.ArrayList;
import java.util.List;

public class App implements NamedElement, Visitable {

	private String name;
	private List<Actuator> actuators = new ArrayList<Actuator>();
	private List<State> states = new ArrayList<State>();
	private State initial;

	@Override
	public String getName() {
		return name;
	}

	@Override
	public void setName(String name) {
		this.name = name;
	}

	public List<Actuator> getActuators() {
		return actuators;
	}

	public void setBricks(List<Actuator> actuators) {
		this.actuators = actuators;
	}

	public List<State> getStates() {
		return states;
	}

	public void setStates(List<State> states) {
		this.states = states;
	}

	public State getInitial() {
		return initial;
	}

	public void setInitial(State initial) {
		this.initial = initial;
	}

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}
}
