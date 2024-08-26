/**
 * @file MiningTruck.cpp
 * @brief Implementation file for the MiningTruck class
 * @version 0.1
 * @date 2024-08-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../Trucks/MiningTruck.h"

#include <iostream>

#include "../Sites/MiningSite.h"
#include "../Stations/UnloadStation.h"

MiningTruck::MiningTruck(unsigned int truck_id): _truckId(truck_id)
{
}

MiningTruck::~MiningTruck()
{
}

void MiningTruck::AssignSite(MiningSite& site)
{
    _currentSite = &site;
}

void MiningTruck::Update(unsigned long time, std::vector<UnloadStation*>& stations, std::vector<MiningSite*>& sites,
                         std::unordered_set<unsigned int>& availableSites)
{
    switch (_status)
    {
        case TruckStatus_T::IDLE:
        {
            if (nullptr != _currentSite)
            {
                _status = TruckStatus_T::MINING;
                _miningStartTime = time;
            }
            else if (nullptr != _currentStation)
            {
                // if current truck is being processed
                if (_currentStation->GetCurrentTruck()->GetTruckId() == _truckId)
                {
                    _status = TruckStatus_T::UNLOADING;
                    _unloadStartTime = time;
                }
            }            
            _totalIdleTime++;

            break;
        }

        case TruckStatus_T::MINING:
        {
            if (nullptr != _currentSite)
            {
                bool mining_in_progress = _currentSite->MineSite();
                _totalMiningTime++;

                if (false == mining_in_progress)
                {
                    _totalResourcesMined++;
                    _status = TruckStatus_T::TRAVELING;
                    _travelStartTime = time;

                    // make site available
                    availableSites.insert(_currentSite->GetSiteId());
                    _currentSite = nullptr;

                    // find unload station with shortest wait time
                    _currentStation = FindBestUnloadStation(stations);
                }
            }
            break;
        }

        case TruckStatus_T::TRAVELING:
        {
            _totalTravelTime++;
            // not arrived to destination
            if (time - _travelStartTime >= TRAVEL_TIME)
            {
                // arrived at unload station
                if (nullptr != _currentStation)
                {
                    _currentStation->AcceptTrucks(*this);
                    _status = TruckStatus_T::IDLE;
                }
                // arrived at mining site
                else if (nullptr != _currentSite)
                {
                    _status = TruckStatus_T::IDLE;
                    _miningStartTime = time;
                }
            }
            break;
        }
        case TruckStatus_T::UNLOADING:
        {
            _totalUnloadTime++;

            if (time - _unloadStartTime >= UNLOAD_TIME)
            {
                _totalResourcesDelivered++;
                _status = TruckStatus_T::TRAVELING;
                _travelStartTime = time;
                _currentStation = nullptr;

                // find next available site
                FindAvailableSite(sites, availableSites);
            }
            break;
        }

        default:
        {
            break;
        }
    }
}

UnloadStation* MiningTruck::FindBestUnloadStation(std::vector<UnloadStation*>& stations)
{
    if (stations.size() == 0)
    {
        return nullptr;
    }
    else if (stations.size() == 1)
    {
        return stations[0];
    }

    UnloadStation* station_with_shortest_wait_time = stations[0];

    for (unsigned int ii = 0; ii < stations.size(); ii++)
    {
        if (false == stations[ii]->GetIsBusy())
        {
            station_with_shortest_wait_time = stations[ii];
            break;
        }
        
        // find unload station with shortest wait time
        if (stations[ii]->GetWaitTime() < station_with_shortest_wait_time->GetWaitTime())
        {
            station_with_shortest_wait_time = stations[ii];
        }
    }

    return station_with_shortest_wait_time;
}

void MiningTruck::FindAvailableSite(std::vector<MiningSite*>& sites, std::unordered_set<unsigned int>& availableSites)
{
    // Get first available site
    std::unordered_set<unsigned int>::iterator it = availableSites.begin();

    // check iterator
    if (it != availableSites.end())
    {
        unsigned int site_id = *it;
        // remove site from list of available sites
        availableSites.erase(it);

        // make sure we check for nullptr
        if (nullptr != sites[site_id])
        {
            AssignSite(*sites[site_id]);
        }
    }
}

std::string MiningTruck::GenerateStat()
{
    std::string result = "";

    result += "Truck [" + std::to_string(_truckId+1) + "] Statistics:\n";

    result += GeneratePerfomanceMetrics();
    result += GenerateEfficiencyMetrics();

    return result;
}

std::string MiningTruck::GeneratePerfomanceMetrics()
{
    std::string result = "";

    unsigned long total_resources_delivered = _totalResourcesDelivered;  // [T]
    unsigned long total_working_time = CalcTotalWorkingTime();           // [min]
    unsigned long total_idle_time = _totalIdleTime;                      // [min]
    unsigned long total_time = CalcTotalTime();                          // [min]

    result += "    Performance Metrics:\n";
    result += "        Total Resources Delivered: " + std::to_string(total_resources_delivered) + " T\n";
    result += "        Total Working Time: " + std::to_string(total_working_time) + " min\n";
    result += "        Total Idle Time: " + std::to_string(total_idle_time) + " min\n";
    result += "        Total Time: " + std::to_string(total_time) + " min\n";

    return result;
}

std::string MiningTruck::GenerateEfficiencyMetrics()
{
    std::string result = "";

    double resource_delivery_rate = CalcResourceDeliveryRate();  // [T/min]
    double utilization_rate = CalcUtilizationRate();             // [%]
    double idle_time_rate = CalcIdleTimeRate();                  // [%]

    result += "    Efficiency Metrics:\n";
    result += "        Resource Delivery Rate: " + std::to_string(resource_delivery_rate) + " T/min\n";
    result += "        Truck Utilization Rate: " + std::to_string(utilization_rate) + " %\n";
    result += "        Truck Idle Time Rate: " + std::to_string(idle_time_rate) + " %\n";

    return result;
}

unsigned long MiningTruck::CalcTotalTime()
{
    return _totalIdleTime + _totalMiningTime + _totalTravelTime + _totalUnloadTime;
}

double MiningTruck::CalcResourceDeliveryRate()
{
    double total_resource = static_cast<double>(_totalResourcesDelivered);
    double total_work_time = static_cast<double>(CalcTotalWorkingTime());
    double rate = total_resource / total_work_time;

    return rate;
}

double MiningTruck::CalcUtilizationRate()
{
    double total_work_time = static_cast<double>(CalcTotalWorkingTime());
    double total_time = static_cast<double>(CalcTotalTime());
    double rate = (total_work_time / total_time) * 100.0;

    return rate;
}

double MiningTruck::CalcIdleTimeRate()
{
    double total_idle_time = static_cast<double>(_totalIdleTime);
    double total_time = static_cast<double>(CalcTotalTime());
    double rate = (total_idle_time / total_time) * 100.0;

    return rate;
}

unsigned long MiningTruck::CalcTotalWorkingTime()
{
    return _totalMiningTime + _totalTravelTime + _totalUnloadTime;
}