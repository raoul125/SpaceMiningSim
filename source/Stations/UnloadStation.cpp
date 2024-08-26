/**
 * @file UnloadStation.cpp
 * @brief Implement Unload Station class
 * @version 0.1
 * @date 2024-08-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../Stations/UnloadStation.h"

#include "../Trucks/MiningTruck.h"


UnloadStation::UnloadStation(unsigned long station_id) : _stationId(station_id)
{
}

UnloadStation::~UnloadStation()
{
}

void UnloadStation::AcceptTrucks(MiningTruck& truck)
{
    // Add Truck To queue
    _truckQueue.push(&truck);
    _waitTime += STANDARD_UNLOAD_TIME;
}

void UnloadStation::Update()
{
    ProcessTruckQueue();
}

void UnloadStation::ProcessTruckQueue()
{
    if (_truckQueue.size() > 0)
    {
        _isBusy = true;
        _waitTime--;
        _totalUtilizationTime++;
        if (_currentTruckTime == 0)
        {
            _currentTruck = _truckQueue.front();
            _truckQueue.pop();
            _currentTruckTime = STANDARD_UNLOAD_TIME;
        }
        else
        {
            _currentTruckTime--;
            if (_currentTruckTime == 0)
            {
                _totalResourcesProcessed++;
                _currentTruck = nullptr;
            }
        }
    }
    else
    {
        _isBusy = false;
        _waitTime = 0;
    }
}