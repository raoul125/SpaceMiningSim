/**
 * @file UnloadStation.h
 * @brief Class Representing an Unload Station
 * @version 0.1
 * @date 2024-08-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SOURCE_STATIONS_UNLOADSTATION_H
#define SOURCE_STATIONS_UNLOADSTATION_H

#include <queue>
#include <string>

// Forward declaration
class MiningTruck;

class UnloadStation
{
   public:
    /**
     * @brief Construct a new Unload Station object
     *
     */
    UnloadStation(unsigned long station_id);

    /**
     * @brief Destroy the Unload Station object
     *
     */
    virtual ~UnloadStation();

    /**
     * @brief Accept a truck at the unload station
     *
     * @param truck
     */
    void AcceptTrucks(MiningTruck& truck);

    /**
     * @brief Process the truck queue
     *
     */
    void ProcessTruckQueue();

    /**
     * @brief Get the wait time of this station
     *
     * @return unsigned long
     */
    unsigned long GetWaitTime() const
    {
        return _waitTime;
    }

    MiningTruck* GetCurrentTruck() const
    {
        return _currentTruck;
    }

    /**
     * @brief Update the unload station status
     *
     * @param time elapsed since the simulation started
     */
    void Update();

    /**
     * @brief Generate and print station statistics
     *
     */
    std::string GenerateStat();

    /**
     * @brief Calculate and return the following performance metrics:
     *     1. Total Resources Processed [T]
     *     2. Total Utilization Time [min]
     *     3. Total Queue Time [min]
     *     4. Number of Trucks Processed
     *     5. Total Idle time
     *
     * @return std::string
     */
    std::string GeneratePerfomanceMetrics();

    /**
     * @brief Calculate and return the following Efficiency Metrics:
     *     1. Average Truck Processing Time [min/truck]
     *     2. Station Utilization Rate [%]
     *     3. Average Queue Time [min/truck]
     *
     * @return std::string
     */
    std::string GenerateEfficiencyMetrics();

    /**
     * @brief Calculate total time station stay idle
     *
     *
     * @return unsigned long
     */
    unsigned long CalcTotalIdleTime();

    /**
     * @brief Calculate average truck processing time
     *
     * @return double
     */
    double CalcAverageTruckProcessingTime();

    /**
     * @brief Calculate station utilization rate
     *
     *
     * @return double
     */
    double CalcStationUtilizationRate();

    /**
     * @brief Calculate average queue time
     *
     *
     * @return unsigned long
     */
    unsigned long CalcAverageQueueTime();

    /**
     * @brief Get the unload station busy status
     * 
     * @return true 
     * @return false 
     */
    bool GetIsBusy() const
    {
        return _isBusy;
    }

   protected:
    static const unsigned int STANDARD_UNLOAD_TIME = 5;        //!< [min] Standard unload time in minutes
    static const unsigned long SIMULATION_DURATION = 72 * 60;  //!< [min] Simulation duration in minutes
    std::queue<MiningTruck*> _truckQueue;                      //!< Queue of trucks waiting to unload at the station
    MiningTruck* _currentTruck = nullptr;        //!< Pointer to the truck currently unloading at the station
    unsigned long _currentTruckTime = 0;         //!< Time left to process current truck
    unsigned long _stationId = 0;                //!< Station Id
    bool _isBusy = false;                        //!< indicated is station is currently occupied
    unsigned long _totalResourcesProcessed = 0;  //!< [T] Total resources processed by the station in tons
    unsigned long _totalUtilizationTime = 0;     //!< [min] Total utilization time of the station in minutes
    unsigned long _waitTime = 0;                 //!< [min] Total unload wait time of the station in minutes
    unsigned int _numberOfTruckProcessed = 0;    //!< Number of trucks processed at the station
    unsigned int _totalQueueTime = 0;            //!< [min] Total queue time of the station in minutes
};
#endif  // SOURCE_STATIONS_UNLOADSTATION_H