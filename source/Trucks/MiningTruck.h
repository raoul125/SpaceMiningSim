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
#include <string>
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
    MiningTruck(unsigned int truck_id);

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
    void AssignSite(MiningSite &site);

    /**
     * @brief Find the unload station with the shortest wait time
     *
     * @param station
     */
    UnloadStation *FindBestUnloadStation(std::vector<UnloadStation *> &stations);

    /**
     * @brief  Generate and print the truck statistics
     *
     */
    std::string GenerateStat();

    /**
     * @brief Calculate and return the following performance metrics:
     *     1. Total Resources Delivered [T]
     *     2. Total Working time [min]
     *     3. Total Idle time. [min]
     *     4. Total time [min]
     *
     * @return std::string
     */
    std::string GeneratePerfomanceMetrics();

    /**
     * @brief Calculate and return the following Efficiency Metrics:
     *     1. Resource delivery Rate [T/mins]
     *     2. Truck's utilization rate [%]
     *     3. Truck's idle Time rate [%]
     *
     * @return std::string
     */
    std::string GenerateEfficiencyMetrics();

    /**
     * @brief Duration of the simulation till now
     *  total time = total_idle + total_mining + total_travel + total_unload
     *
     * @return unsigned long
     */
    unsigned long CalcTotalTime();

    /**
     * @brief How efficient this truck is delivering resources relative to time it spends working.
     *        It reflect the average rate at which the truck delivers resources per minute of work.
     *        DeliveryRate = Total Resource delivered / Total working time
     * @return int
     */
    double CalcResourceDeliveryRate();

    /**
     * @brief How much of the truck's total time is spend on productive tasks.
     *       A higher utilization rate means the truck is being use more
     *       efficently, with less idle time.
     *
     *       Utilization rate = 100% * Total Working Time / Total Time
     *
     * @return int
     */
    double CalcUtilizationRate();

    /**
     * @brief  shows the percentage of time the truck spends waiting.
     *         High queue time can indicate bottlenecks at the unload stations.
     *
     *        Idle Rate = 100% * total idle time / total time.
     *
     * @return int
     */
    double CalcIdleTimeRate();

    /**
     * @brief Total Working time of the truck =
     *       Totoal mining time + total travel time + total unload time
     *
     * @return unsigned long
     */
    unsigned long CalcTotalWorkingTime();

    /**
     * @brief Find the next available site
     *
     * @param sites
     * @param availableSites
     */
    void FindAvailableSite(std::vector<MiningSite *> &sites, std::unordered_set<unsigned int> &availableSites);

    /**
     * @brief Update truck status based on current time and simulation state.
     *
     * This function updates the truck's status (IDLE, MINING, TRAVELING, UNLOADING) based on the current simulation
     * time and the state of the mining sites, unload stations, and available sites.
     *
     * The function handles the following scenarios:
     *
     * - **IDLE:** If the truck is idle and has a current site assigned, it transitions to MINING.
     *   If the truck is idle and is currently being processed at an unload station, it transitions to UNLOADING.
     * - **MINING:** If the truck is mining and the current site is not depleted, it continues mining.
     *   If the current site is depleted, the truck transitions to TRAVELING, making the site available for other
     * trucks.
     * - **TRAVELING:** If the truck is traveling and has reached its destination (either an unload station or a mining
     * site), it transitions to IDLE.
     * - **UNLOADING:** If the truck is unloading and has finished unloading, it transitions to TRAVELING and searches
     * for a new available mining site.
     *
     * @param time Elapsed time since the simulation started.
     * @param stations Vector of unload stations in the simulation.
     * @param sites Vector of mining sites in the simulation.
     * @param availableSites Set of available mining sites.
     * */
    void Update(unsigned long time, std::vector<UnloadStation *> &stations, std::vector<MiningSite *> &sites,
                std::unordered_set<unsigned int> &availableSites);

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
    MiningSite *_currentSite = nullptr;                   //!< pointer to the site being mined by truck
    UnloadStation *_currentStation = nullptr;  //!< pointer to the unload station where the truck is unloading

    unsigned int _currentPayload = 0;            //!< [T] Current truck payload
    unsigned long _totalResourcesMined = 0;      //!< [T] Total resources mined by the truck
    unsigned long _totalResourcesDelivered = 0;  //!< [T] Total resources delivered by the truck
    unsigned long _totalIdleTime = 0;            //!< [min] Total idle time of the truck
    unsigned long _totalTravelTime = 0;          //!< [min] Total travel time of the truck
    unsigned long _totalUnloadTime = 0;          //!< [min] Total unload time of the truck
    unsigned long _totalMiningTime = 0;          //!< [min] Total mining time of the truck
    unsigned long _travelStartTime = 0;          //!< [min] Time at which the truck started traveling
    unsigned long _unloadStartTime = 0;          //!< [min] Time at which the truck started unloading
    unsigned long _miningStartTime = 0;          //!< [min] Time at which the truck started mining
};

#endif  // SOURCE_TRUCKS_MININGTRUCK_H