
# Lunar Helium-3 Mining Simulation

This project simulates a lunar Helium-3 mining operation, modeling the interactions between mining trucks, mining sites, and unload stations.

## Project Structure

The project is organized as follows:
├── source 
│ ├── Simulator 
│ │ ├── Simulator.cpp 
│ │ └── Simulator.h 
│ ├── Trucks 
│ │ ├── MiningTruck.cpp 
│ │ └── MiningTruck.h 
│ ├── Sites 
│ │ ├── MiningSite.cpp 
│ │ └── MiningSite.h 
│ ├── Stations 
│ │ ├── UnloadStation.cpp 
│ │ └── UnloadStation.h 
│ └── LunarMiningSim.cpp 
├── CMakeLists.txt 
├── build.sh 
├── run.sh 
├── .clang-format 
├── .gitignore 
├── README.md

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

### Requirements

- **Linux:**
    - CMake
    - g++ compiler
    - gdb
- **Windows:**
    - CMake
    - Visual Studio (with C++ compiler)

### Compilation

1. **Navigate to the project directory:**
   ```bash
   cd SpaceMiningSim
2. **Compile the project using the provided script:**
    ```bash
   ./build.sh

### Execution
1. **Run the simulation with the desired parameters**
    ```bash
    ./run.sh <numtrucks> <numSites> <numStations>
- Replace numtrucks, numSites, and numStations with the desired number of trucks, mining sites, and unload stations, respectively.

## Future Enhancements

- **Resource Management:** Implement a more sophisticated resource management system, including resource storage and consumption.

- **Visualization:** Create a visual representation of the simulation, showing the movement of trucks, resource extraction, and station activity.

- **Unit Tests:** Implement a comprehensive suite of unit tests to ensure the correctness and robustness of the simulation code using Google Test Framework.

- **Code Coverage** Utilize a tool like VectorCast or LDRA to ensure MC/DC code coverage

