package io.github.mosser.arduinoml.ens.generator;

import io.github.mosser.arduinoml.ens.model.*;

public abstract class Visitor<T> {

	public abstract void visit(App app);
	public abstract void visit(State state);
	public abstract void visit(Action action);
	public abstract void visit(Actuator actuator);

	/***********************
	 ** Helper mechanisms **
	 ***********************/

	T code;
	T headers;

	public T getCode() {
		return code;
	}
	public T getHeaders() {
		return headers;
	}

}

