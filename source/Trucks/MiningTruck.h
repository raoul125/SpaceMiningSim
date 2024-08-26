/**
 * @file MiningTruck.h
 * @brief Class representing an Helium-3 space mining Truck
 * @version 0.1
 * @date 2024-08-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SOURCE_TRUCKS_MININGTRUCK_H
#define SOURCE_TRUCKS_MININGTRUCK_H
#include <unordered_set>
#include <vector>


// Forward declaration
class MiningSite;
class UnloadStation;

class MiningTruck
{
   public:
    /**
     * @brief Construct a new Mining Truck object
     *
     */
    MiningTruck();

    /**
     * @brief Destroy the Mining Truck object
     *
     */
    virtual ~MiningTruck();

    /**
     * @brief Get the Truck Id object
     *
     * @return unsigned int
     */
    unsigned int GetTruckId() const
    {
        return _truckId;
    }

    /**
     * @brief Assign site for this truck
     *
     * @param site_id
     */
    void AssignSite(MiningSite& site);

    /**
     * @brief Find the unload station with the shortest wait time
     *
     * @param station
     */
    UnloadStation* FindBestUnloadStation(std::vector<UnloadStation*>& stations);

    /**
     * @brief Find the next available site
     *
     * @param sites
     * @param availableSites
     * @return MiningSite*
     */
    MiningSite* FindAvailableSite(std::vector<MiningSite*>& sites, std::unordered_set<unsigned int>& availableSites);

    /**
     * @brief Update truck status
     *
     * @param time elapsed since the simulation started
     *
     */
    void Update(unsigned long time, std::vector<UnloadStation*>& stations, std::vector<MiningSite*>& sites,
                std::unordered_set<unsigned int>& availableSites);

   protected:
    // List of possible truck state
    enum class TruckStatus_T
    {
        IDLE = 0,
        MINING,
        TRAVELING,
        UNLOADING
    };

    // Constants
    static const unsigned int TRAVEL_TIME = 30;  //!< [min] travel time between site and unload station in minutes
    static const unsigned int UNLOAD_TIME = 5;   //!< [min] time it takes to unload the payload at an unload station

    // Members
    unsigned int _truckId = 0;                            //!< Truck Id
    TruckStatus_T _status = TruckStatus_T::IDLE;          //!< Truck current Status
    TruckStatus_T _previousStatus = TruckStatus_T::IDLE;  //!< Truck previous Status
    MiningSite* _currentSite = nullptr;                   //!< pointer to the site being mined by truck
    UnloadStation* _currentStation = nullptr;  //!< pointer to the unload station where the truck is unloading

    unsigned int _currentPayload = 0;        //!< [T] Current truck payload
    unsigned long _totalResourcesMined = 0;  //!< [T] Total resources mined by the truck
    unsigned long _totalIdleTime = 0;        //!< [min] Total idle time of the truck
    unsigned long _totalTravelTime = 0;      //!< [min] Total travel time of the truck
    unsigned long _totalUnloadTime = 0;      //!< [min] Total unload time of the truck
    unsigned long _totalMiningTime = 0;      //!< [min] Total mining time of the truck
    unsigned long _travelStartTime = 0;      //!< [min] Time at which the truck started traveling
    unsigned long _unloadStartTime = 0;      //!< [min] Time at which the truck started unloading
    unsigned long _miningStartTime = 0;      //!< [min] Time at which the truck started mining
};

#endif  // SOURCE_TRUCKS_MININGTRUCK_H