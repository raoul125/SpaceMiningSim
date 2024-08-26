/**
 * @file SpaceMining.cpp
 * @brief Entry point of the simulation for the lunar Helium-3 space mining operation.
 * @version 0.1
 * @date 2024-08-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Simulator/Simulator.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    // Check if the correct number of arguments is provided
    if (argc != 4) {
        std::cerr << "Usage: LunarMiningSim <num_trucks> <num_mining_sites> <num_unload_stations>" << std::endl;
        return 1;
    }

    // Parse the arguments
    int num_trucks = std::stoi(argv[1]);
    int num_mining_sites = std::stoi(argv[2]);
    int num_unload_stations = std::stoi(argv[3]);
    
    // Make sure all input are valid
    if (num_trucks <= 0 || num_mining_sites <= 0 || num_unload_stations <= 0)
    {
        std::cerr << "Invalid arguments. All arguments must be positive integers." << std::endl;
        return 1;
    }

    // number of sites must be greater than number of trucks and unload_stations
    if (num_mining_sites < num_trucks)
    {
        std::cerr << "Invalid arguments. Number of mining sites must be greater than number of trucks and unload stations." << std::endl;
        return 1;
    }

    Simulator lunar_sim;
    // Initialize the simulation with the provided parameters
    lunar_sim.Initialize(num_trucks, num_mining_sites, num_unload_stations);
    lunar_sim.Run();

    // ask user to press any key to continue
    std::cout << "Simulation Complete. Please press any key to exit..." << std::endl;
    std::cin.get();

    return 0;
}
