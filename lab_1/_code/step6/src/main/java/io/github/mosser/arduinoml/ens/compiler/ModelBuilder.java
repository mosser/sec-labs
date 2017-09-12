package io.github.mosser.arduinoml.ens.compiler;

import io.github.mosser.arduinoml.external.*;
import io.github.mosser.arduinoml.ens.model.*;
import org.antlr.v4.runtime.ParserRuleContext;
import org.antlr.v4.runtime.tree.ErrorNode;
import org.antlr.v4.runtime.tree.TerminalNode;

import java.util.HashMap;
import java.util.Map;

public class ModelBuilder extends ArduinoMLBaseListener {

    /********************
     ** Business Logic **
     ********************/

    private App theApp = null;
    private boolean built = false;

    public App retrieve() {
        if (built) { return theApp; }
        throw new RuntimeException("Cannot retrieve a model that was not created!");
    }

    /*******************
     ** Symbol tables **
     *******************/

    private Map<String, Actuator> actuators = new HashMap<>();
    private Map<String, State>    states  = new HashMap<>();
    private Map<State, String>  transitions  = new HashMap<>();

    private State currentState = null;

    /**************************
     ** Listening mechanisms **
     **************************/


    @Override
    public void enterApp(ArduinoMLParser.AppContext ctx) {
        this.built = false;
        this.theApp = new App();
        this.theApp.setName(ctx.name.getText());
    }

    @Override
    public void exitApp(ArduinoMLParser.AppContext ctx) {
        // Resolving transitions
        this.transitions.forEach( (from, nextId) -> from.setNext(this.states.get(nextId)) );
        this.built = true;
    }

    @Override
    public void enterActuator(ArduinoMLParser.ActuatorContext ctx) {
        Actuator act = new Actuator();
        act.setName(ctx.location().id.getText());
        act.setPin(Integer.parseInt(ctx.location().port.getText()));
        this.theApp.getActuators().add(act);
        this.actuators.put(act.getName(), act); // Symbol table for actuators
    }

    @Override
    public void enterState(ArduinoMLParser.StateContext ctx) {
        State local = new State();
        local.setName(ctx.name.getText());
        this.currentState = local;
        this.states.put(local.getName(), local); // Symbol table for states
    }

    @Override
    public void exitState(ArduinoMLParser.StateContext ctx) {
        this.theApp.getStates().add(this.currentState);
        this.currentState = null;
    }

    @Override
    public void enterAction(ArduinoMLParser.ActionContext ctx) {
        Action action = new Action();
        action.setActuator(actuators.get(ctx.receiver.getText()));
        action.setValue(SIGNAL.valueOf(ctx.value.getText()));
        currentState.getActions().add(action);
    }


    @Override
    public void enterNext(ArduinoMLParser.NextContext ctx) {
        this.transitions.put(this.currentState, ctx.target.getText());
    }


    @Override
    public void enterInitial(ArduinoMLParser.InitialContext ctx) {
        this.theApp.setInitial(this.currentState);
    }

}