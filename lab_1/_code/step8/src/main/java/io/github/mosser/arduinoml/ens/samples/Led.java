package io.github.mosser.arduinoml.ens.samples;

import static io.github.mosser.arduinoml.ens.dsl.AppBuilder.*;

public class Led {

	public static void main(String[] args) {

		application("theLed")
				.uses(actuator("led", 13))

                .hasForState("on")
                    .setting("led").toHigh()
                    .goingTo("off")

                .hasForState("off")
                    .initial()
                    .setting("led").toLow()
                    .goingTo("on")

		.export("./output/fsm.h",
                "./output/main.c");


	}

}
