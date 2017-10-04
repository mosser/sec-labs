# Data Sensor Simulation

  * Author: Sébastien Mosser
  * Revision: 17.10

## Context

The Gartner group’s forecasts predict up to 26 billions of things that could be connected to the Internet by 2020 forming the Internet of Things (IoT). Once measured, data gathered from IoT sensors are key enablers for next generation infrastructures such as Smart Cities or Smart Grid. In sensing infrastructures [1], sensor networks are responsible for measuring physical phenomena and sending values to a remote IoT middleware where the collected data can be retrieved by third-party applications. In addition, such middleware is also responsible for managing the devices deployed in the sensor networks [2]. 

## Problem Description

Developing a middleware for sensor network is a non-trivial task. Testing the system in real condition does not make sense, as one should be able to work without being connected to the 12,345 sensors deployed in a Smart City (or a Smart Campus [3]). But the test infrastructure must be as close to the real system as possible. It is then necessary to simulate the sensor network in a proper way. 

Sensor data can be simulated in different ways. On the one hand, the simplest way is to “replay” an existing dataset. However, one need to acquire such a dataset to be able to play it. On the other hand, it is possible to generate these data based on a law associated to the sensor. For example, considering a given set of reference points for a given sensor, one can interpolate an associated function using polynomial interpolation. This function can then be used to generate sensor data at any time. One can also rely on classical Markov chain to model a sensor behavior and then obtain sensor values [4]. Considering these different way to model sensors, one should then be able to replicate a sensor model and start a testbed. Finally, a simulation context can be defined by instantiating multiple sensors class in different contexts, and started in parallel on one or more physical machine to simulate the modelled sensors. A context can be used to generate dataset as static files, or to dynamically simulate sensors and push the data to a collector like real sensors.

### User Stories

  * As Bob, a researcher in transportation networks, I want to use a domain-specific language to model the mathematical law that rules a parking slot, so that this model can be used to simulate large parkings.
  * As Alice, a middleware designer, I want to instantiate 12,000 virtual parking sensors so that I can measure the robustness of my middleware. 

  
## Expected Work

  * Identify the concepts that are relevant for this domain, and define the associated class diagram;
  * Provide a concrete syntax associated to this language to declare sensors class and specify simulation contexts;
  * Identify the kind of code you want to target to support the (massively) parallel execution of a simulation context;
  * Implement a fully-fledged tool suite that goes from the concrete syntax (embedded or external) to the generated code;
  * Implement at least one of the following extensions:
    * Chaos Monkey: support the modelling of a chaos monkey, which will interact with the modelled sensors to alter data emission and simulate failures at runtime; 
    * Network data collection: make each sensor connected to a data collection middleware (e.g., influxdb, elasticsearch) and visualize the generated data (e.g., using kibana) in a configurable way;
    * Sensor network architecture: Model the way the different sensors are architectured together instead of considering a flat network;
    * Variability modelling: Organize the different class of sensors as a product line where a user can configure a sensor by selecting features;
    * Gossip propagation: Consider that sensors must transfer data to their immediate neighbor instead of  pushing it directly to the middleware; and only selected sensors can access the middleware;
    * Optimized compilation: optimize the generated code to address the massively parallel generation of data and satisfy the (soft) real-time constraint associated to the sensor data generation.

    
## References

  * A. H. Ngu, M. Gutierrez, V. Metsis, S. Nepal, Q. Z. Sheng, Iot middleware: A survey on issues and enabling technologies, IEEE Internet of Things Journal 4 (1) (2017) 1–20.
  * S. Bandyopadhyay, M. Sengupta, S. Maiti, S. Dutta, A survey of middleware for internet of things, in: Recent Trends in Wireless and Mobile Networks, Springer, 2011, pp. 288–296. 
  * Cyril Cecchinel, Matthieu Jimenez, Sébastien Mosser, Michel Riveill. “An Architecture to Support the Collection of Big Data in the Internet of Things” in Proceedings of the International Workshop on Ubiquitous Mobile cloud (UMC'14, co-located with SERVICES), IEEE, pages 1-8, Anchorage, Alaska, USA, 27-2 june 2014
  * "Predicting Parking Lot Occupancy in Vehicular Ad Hoc Networks" by Murat Caliskan, Andreas Barthels, Bjorn Scheuermann and Martin Mauve. 65th IEEE Vehicular Technology Conference, Dublin, Ireland, April 2007.
