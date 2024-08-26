/**
 * @file Simulator.h
 * @brief Simulate the lunar Helium-4 space mining operation
 * @version 0.1
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SOURCE_SIMULATOR_HSIMULATOR_H
#define SOURCE_SIMULATOR_HSIMULATOR_H

#include <vector>
#include <unordered_set>
#include <unordered_map>

// Forward declaration
class MiningTruck;
class MiningSite;
class UnloadStation;

class Simulator
{
   public:
    /**
     * @brief Construct a new Simulator object
     *
     */
    Simulator();

    /**
     * @brief Destroy the Simulator object
     *
     */
    ~Simulator();

    /**
     * @brief Initialize the simulation with the specified number of trucks, mining sites, and unload stations
     *
     * @param num_trucks
     * @param num_sites
     * @param num_stations
     */
    void Initialize(unsigned int num_trucks, unsigned int num_sites, unsigned int num_stations);
    
    /**
     * @brief Assign trucks to available mining sites
     * 
     */
    void DispatchTrucks();

    /**
     * @brief Execute the simulation loop, advancing time and updating all components
     *
     */
    void Run();

    /**
     * @brief Generate and print the simulation statistics
     *
     */
    void GenerateStat();

   private:
    static const unsigned long SIMULATION_DURATION = 72 * 60;  //!< [min] Simulation duration in minutes
    static const unsigned int SIMULATION_TIME_STEP = 1;        //!< [min] Simulation step in minutes
    static const unsigned int STATISTIC_INTERVAL = 60;         //!< [min] Statistic interval in minutes
    unsigned int _time = 0;                                    //!< [min] current simulation time
    std::vector<MiningTruck*> _trucks;                         //!< List of trucks
    std::vector<MiningSite*> _sites;                           //!< List of mining sites
    std::vector<UnloadStation*> _unloadStations;               //!< List of unload stations
    std::unordered_set<unsigned int> _availableSite;           //!< List of available mining sites
    unsigned int _truckCount = 0;                              //!< Number of trucks in the simulations
    unsigned int _miningSiteCount = 0;                         //!< Number of mining sites in the simulations
    unsigned int _unloadStationCount = 0;                      //!< Number of unload Stations in the sumulation
    unsigned long _totalResourceMined = 0;                     //!< Total resources mined during by all Trucks
    unsigned long _totalIdleTime = 0;                          //!< Total idle time of all trucks
    unsigned long _totalTravelTime = 0;                        //!< Total travel time of all trucks
    unsigned long _totalUnloadTime = 0;                        //!< Total unload time of all trucks
    unsigned long _totalMiningTime = 0;                        //!< Total mining time of all trucks
};

#endif  // SOURCE_SIMULATOR_HSIMULATOR_H