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

   protected:
    static const unsigned int STANDARD_UNLOAD_TIME = 5;  //!< [min] Standard unload time in minutes
    std::queue<MiningTruck*> _truckQueue;                //!< Queue of trucks waiting to unload at the station
    MiningTruck* _currentTruck = nullptr;                //!< Pointer to the truck currently unloading at the station
    unsigned long _currentTruckTime = 0;                 //!< Time left to process current truck
    unsigned long _stationId = 0;                        //!< Station Id
    bool _isBusy = false;                                //!< indicated is station is currently occupied
    unsigned long _totalResourcesProcessed = 0;          //!< [T] Total resources processed by the station in tons
    unsigned long _totalUtilizationTime = 0;             //!< [min] Total utilization time of the station in minutes
    unsigned long _waitTime = 0;                         //!< [min] Total unload wait time of the station in minutes
};
#endif  // SOURCE_STATIONS_UNLOADSTATION_H