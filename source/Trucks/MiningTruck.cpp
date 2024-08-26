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

#include "../Sites/MiningSite.h"
#include "../Stations/UnloadStation.h"

MiningTruck::MiningTruck()
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
            else
            {
                _totalIdleTime++;
            }
            break;
        }

        case TruckStatus_T::MINING:
        {
            if (nullptr != _currentSite)
            {
                bool is_mining_done = _currentSite->MineSite();

                if (false == is_mining_done)
                {
                    _totalMiningTime++;
                }
                else
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
            // not arrived to destination
            if (time - _travelStartTime < TRAVEL_TIME)
            {
                _totalTravelTime++;
            }
            else
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
                    _status = TruckStatus_T::MINING;
                    _miningStartTime = time;
                }
            }
            break;
        }
        case TruckStatus_T::UNLOADING:
        {
            if (time - _unloadStartTime < UNLOAD_TIME)
            {
                _totalUnloadTime++;
            }
            else
            {
                _status = TruckStatus_T::TRAVELING;
                _travelStartTime = time;
                _currentStation = nullptr;

                // find next available site
                _currentSite = FindAvailableSite(sites, availableSites);
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

    for (size_t ii = 1; ii < stations.size(); ii++)
    {
        if (stations[ii]->GetWaitTime() < station_with_shortest_wait_time->GetWaitTime())
        {
            station_with_shortest_wait_time = stations[ii];
        }
    }

    return station_with_shortest_wait_time;
}

MiningSite* MiningTruck::FindAvailableSite(std::vector<MiningSite*>& sites,
                                           std::unordered_set<unsigned int>& availableSites)
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