/**
 * @file MiningSite.cpp
 * @brief Implement the Mining Site class
 * @version 0.1
 * @date 2024-08-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../Sites/MiningSite.h"
#include "../Trucks/MiningTruck.h"
#include "cstdlib" // rand()

MiningSite::MiningSite(unsigned long site_id) : _siteId(site_id)
{
}

MiningSite::~MiningSite()
{
}

bool MiningSite::MineSite()
{
    if (false == _isBeingMined)
    {
        _miningTimeLeft = CalcMiningTime();
        _isBeingMined = true;
    }
    else
    {
        _miningTimeLeft--;

        if (0 == _miningTimeLeft)
        {
            _isBeingMined = false;
            _availableResource--;
        }
    }

    return _isBeingMined;
}

unsigned int MiningSite::CalcMiningTime()
{
    unsigned int time = MINIMUM_MINING_TIME + std::rand() % (MAXIMUM_MINING_TIME + 1);

    return time;
}