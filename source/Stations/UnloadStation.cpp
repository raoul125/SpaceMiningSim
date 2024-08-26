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

#include <iostream>

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
    _totalQueueTime += STANDARD_UNLOAD_TIME;
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
                _numberOfTruckProcessed++;
            }
        }
    }
    else
    {
        _isBusy = false;
        _waitTime = 0;
    }
}

std::string UnloadStation::GenerateStat()
{
    std::string result = "";

    result += "Unload Station [" + std::to_string(_stationId + 1) + "] Statistics:\n";

    result += GeneratePerfomanceMetrics();
    result += GenerateEfficiencyMetrics();

    return result;
}

std::string UnloadStation::GeneratePerfomanceMetrics()
{
    std::string result = "";

    unsigned long total_resources_processed = _totalResourcesProcessed;  // [T]
    unsigned long total_utilization_time = _totalUtilizationTime;        // [min]
    unsigned long total_queue_time = _totalQueueTime;                    // [min]
    unsigned int number_of_trucks_processed = _numberOfTruckProcessed;   // [trucks]
    unsigned long total_idle_time = CalcTotalIdleTime();                 // [min]

    result += "    Performance Metrics:\n";
    result += "        Total Resources Processed: " + std::to_string(total_resources_processed) + " T\n";
    result += "        Total Utilization Time: " + std::to_string(total_utilization_time) + " min\n";
    result += "        Total Queue Time: " + std::to_string(total_queue_time) + " min\n";
    result += "        Number of Trucks Processed: " + std::to_string(number_of_trucks_processed) + "\n";
    result += "        Total Idle Time: " + std::to_string(total_idle_time) + " min\n";

    return result;
}

std::string UnloadStation::GenerateEfficiencyMetrics()
{
    std::string result = "";
    double average_truck_processing_time = CalcAverageTruckProcessingTime();  // [min/truck]
    double station_utilization_rate = CalcStationUtilizationRate();           // [%]
    unsigned long average_queue_time = CalcAverageQueueTime();                // [min/truck]

    result += "    Efficiency Metrics:\n";
    result +=
        "        Average Truck Processing Time: " + std::to_string(average_truck_processing_time) + " min/truck\n";
    result += "        Station Utilization Rate: " + std::to_string(station_utilization_rate) + " %\n";
    result += "        Average Queue Time: " + std::to_string(average_queue_time) + " min/truck\n";

    return result;
}

unsigned long UnloadStation::CalcTotalIdleTime()
{
    // simulatioin duration - utilization time.
    unsigned long total_idle_time = SIMULATION_DURATION - _totalUtilizationTime;
    return total_idle_time;
}

double UnloadStation::CalcAverageTruckProcessingTime()
{
    double processing_time = 0.0;
    if (_numberOfTruckProcessed > 0)
    {
        processing_time = static_cast<double>(_totalUtilizationTime) / static_cast<double>(_numberOfTruckProcessed);
    }
    return processing_time;
}

double UnloadStation::CalcStationUtilizationRate()
{
    double utilization_rate = 0.0;
    if (SIMULATION_DURATION > 0)
    {
        utilization_rate =
            (static_cast<double>(_totalUtilizationTime) / static_cast<double>(SIMULATION_DURATION)) * 100.0;
    }

    return utilization_rate;
}

unsigned long UnloadStation::CalcAverageQueueTime()
{
    unsigned long average_queue_time = 0;
    if (_numberOfTruckProcessed > 0)
    {
        average_queue_time = _totalQueueTime / _numberOfTruckProcessed;
    }
    return average_queue_time;
}