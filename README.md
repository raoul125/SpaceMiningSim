# Lunar Helium-3 Mining Simulation

This project simulates a lunar Helium-3 mining operation, modeling the interactions between mining trucks, mining sites, and unload stations.

## Project Structure

The project is organized as follows:

- **Simulator:**
    - `Simulator.cpp`: Contains the main simulation loop, managing the interaction between trucks, sites, and stations.
    - `Simulator.h`: Header file for the Simulator class.
- **Trucks:**
    - `MiningTruck.cpp`: Implementation of the MiningTruck class, representing a mining truck.
    - `MiningTruck.h`: Header file for the MiningTruck class.
- **Sites:**
    - `MiningSite.cpp`: Implementation of the MiningSite class, representing a mining site.
    - `MiningSite.h`: Header file for the MiningSite class.
- **Stations:**
    - `UnloadStation.cpp`: Implementation of the UnloadStation class, representing an unload station.
    - `UnloadStation.h`: Header file for the UnloadStation class.

## Simulation Logic

The simulation operates in discrete time steps, with each step representing a unit of time (e.g., minutes). The simulation logic is as follows:

1. **Initialization:**
    - The simulation is initialized with a specified number of trucks, mining sites, and unload stations.
    - Trucks are initially assigned to available mining sites.
2. **Main Loop:**
    - The simulation loop iterates through time steps, updating the state of each component:
        - **Trucks:**
            - Trucks mine resources at their assigned sites.
            - Once a site is depleted, trucks travel to the nearest unload station with the shortest wait time.
            - At the unload station, trucks unload their resources and wait for processing.
            - After unloading, trucks find the next available mining site and repeat the process.
        - **Mining Sites:**
            - Mining sites are depleted as trucks mine resources.
            - Depleted sites become available for other trucks.
        - **Unload Stations:**
            - Unload stations process resources from arriving trucks.
            - Trucks wait in a queue at the station until they are processed.
3. **Statistics:**
    - The simulation tracks various statistics, including:
        - Total resources mined and delivered.
        - Total working time, idle time, travel time, and unload time for each truck.
        - Resource delivery rate, truck utilization rate, and truck idle time rate.

## Running the Simulation

To run the simulation, compile the source code and execute the compiled executable. The simulation parameters (number of trucks, sites, and stations) can be adjusted in the `Simulator.cpp` file.

## Future Enhancements

- **Resource Management:** Implement a more sophisticated resource management system, including resource storage and consumption.
- **Dynamic Site Allocation:** Allow trucks to dynamically choose mining sites based on factors like resource availability and distance.
- **Advanced Station Logic:** Implement more complex station logic, such as multiple processing stages or priority queues.
- **Visualization:** Create a visual representation of the simulation, showing the movement of trucks, resource extraction, and station activity.
