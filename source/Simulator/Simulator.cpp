/**
 * @file Simulator.cpp
 * @brief Implement the Simulation of the lunar Helium-4 space mining operation
 * @version 0.1
 * @date 2024-08-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./Simulator.h"

#include <iostream>

#include "../Sites/MiningSite.h"        // MiningSite class
#include "../Stations/UnloadStation.h"  // UnloadStation class
#include "../Trucks/MiningTruck.h"      // MiningTruck class

Simulator::Simulator()
{
}

Simulator::~Simulator()
{
    for (unsigned int ii = 0; ii < _truckCount; ii++)
    {
        // delete truck
        if (nullptr != _trucks[ii])
        {
            delete _trucks[ii];
            _trucks[ii] = nullptr;
        }
    }
    // clear trucks vector
    _trucks.clear();

    for (unsigned int ii = 0; ii < _miningSiteCount; ii++)
    {
        // delete site
        if (nullptr != _sites[ii])
        {
            delete _sites[ii];
            _sites[ii] = nullptr;
        }
    }
    // clear sites vector
    _sites.clear();

    for (unsigned int ii = 0; ii < _unloadStationCount; ii++)
    {
        // delete station
        if (nullptr != _unloadStations[ii])
        {
            delete _unloadStations[ii];
            _unloadStations[ii] = nullptr;
        }
    }
    // clear unload stations vector
    _unloadStations.clear();
}

void Simulator::Run()
{
    // Dispatch Trucks to available sites before starting the simulation
    DispatchTrucks();

    // Simulation main loop
    while (SIMULATION_DURATION > _time)
    {
        // Update Truck
        for (unsigned int ii = 0; ii < _truckCount; ii++)
        {
            if (nullptr != _trucks[ii])
            {
                _trucks[ii]->Update(_time, _unloadStations, _sites, _availableSite);
            }
        }

        // Update Unload Stations
        for (unsigned int ii = 0; ii < _unloadStationCount; ii++)
        {
            if (nullptr != _unloadStations[ii])
            {
                _unloadStations[ii]->Update();
            }
        }

        // Advance time
        _time++;
    }

    for (unsigned int ii = 0; ii < _truckCount; ii++)
    {
        std::cout << _trucks[ii]->GenerateStat() << std::endl;
    }
}

void Simulator::Initialize(unsigned int num_trucks, unsigned int num_sites, unsigned int num_stations)
{
    _truckCount = num_trucks;
    _miningSiteCount = num_sites;
    _unloadStationCount = num_stations;

    // Create Trucks
    for (unsigned int ii = 0; ii < _truckCount; ii++)
    {
        MiningTruck* truck = new MiningTruck(ii);
        _trucks.push_back(truck);
    }

    // Create Mining Sites
    for (unsigned int ii = 0; ii < _miningSiteCount; ii++)
    {
        MiningSite* site = new MiningSite(ii);
        _sites.push_back(site);

        // add site to list of available sites
        _availableSite.insert(ii);
    }

    // Create Unload Stations
    for (unsigned int ii = 0; ii < _unloadStationCount; ii++)
    {
        UnloadStation* station = new UnloadStation(ii);
        _unloadStations.push_back(station);
    }
}

void Simulator::DispatchTrucks()
{
    for (unsigned int ii = 0; ii < _truckCount; ii++)
    {
        // Get first available site
        std::unordered_set<unsigned int>::iterator it = _availableSite.begin();

        // check iterator
        if (it != _availableSite.end())
        {
            unsigned int site_id = *it;
            // remove site from list of available sites
            _availableSite.erase(it);

            // make sure we check for nullptr
            if ((nullptr != _sites[site_id]) && (nullptr != _trucks[ii]))
            {
                _trucks[ii]->AssignSite(*_sites[site_id]);
            }
        }
    }
}
