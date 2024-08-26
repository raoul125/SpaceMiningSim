/**
 * @file MiningSite.h
 * @brief classing representing a Mining Site
 * @version 0.1
 * @date 2024-08-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SOURCE_SITES_MININGSITE_H
#define SOURCE_SITES_MININGSITE_H

// Forward declaration
class MiningTruck;

class MiningSite
{
   public:
    /**
     * @brief Construct a new Mining Site object
     *
     */
    MiningSite(unsigned long side_id);

    /**
     * @brief Destroy the Mining Site object
     *
     */
    ~MiningSite();

    /**
     * @brief Get the Site Id
     *
     * @return Site Id
     */
    unsigned long GetSiteId() const
    {
        return _siteId;
    }

    /**
     * @brief Assign a truck to the mining site
     *
     */
    bool MineSite();

   protected:
    static const unsigned long MAX_RESOURCES = 50000;    //!< [T] Max possible resources available for mining in tons
    static const unsigned int MINIMUM_MINING_TIME = 60;  //!< [min] Minimum mining time in minutes
    static const unsigned int MAXIMUM_MINING_TIME = 60 * 5;  //!< [min] Maximum mining time in minutes

    unsigned long _siteId = 0;                         //!< Mining Site Id
    unsigned long _availableResource = MAX_RESOURCES;  //!< [T] Available resources in the site in tons
    bool _isBeingMined = false;                        //!< a flag indicating if the site is currently being mined
    unsigned int _miningTimeLeft = 0;                  //!< how much time has passed since mining started

    /**
     * @brief Compute a random mining time between 1 to 5 hours
     *
     * @return time number between 60 and 300 mins
     */
    virtual unsigned int CalcMiningTime();
};

#endif  // SOURCE_SITES_MININGSITE_H