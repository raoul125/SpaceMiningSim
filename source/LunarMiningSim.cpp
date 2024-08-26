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

int main()
{
    Simulator lunar_sim;
    // Initialize the simulation with 1 truck, 3 mining sites, and 1 unload station
    lunar_sim.Initialize(1, 2, 2);
    lunar_sim.Run();

    std::cout << "Done Running" << std::endl;

    return 0;
}