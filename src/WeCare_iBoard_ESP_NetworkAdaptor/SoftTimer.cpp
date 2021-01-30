/**
 * @file SoftTimer.cpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Arduino.h"
#include "TimingConfig.hpp"
#include "SoftTimer.hpp"

uint32_t lastMillis = 0;

// Create the timers
uint32_t SoftTimerCounter[MAX_SOFT_TIMER_COUNT] = {0};

/**
 * @brief Timer call back function
 * 
 */
static void softTimerCallback(void)
{
    for (uint8_t i = 0; i < MAX_SOFT_TIMER_COUNT; i++)
    {
        if (SoftTimerCounter[i])
        {
            SoftTimerCounter[i]--;
        }
    }
}

/**
 * @brief Soft Timer periodic timer 
 * 
 */
void SoftTimerTaskRunner(void)
{
    if ((millis() / SOFT_TIMER_RESOLUTION_MS) != lastMillis)
    {
        softTimerCallback();
        lastMillis = millis() / SOFT_TIMER_RESOLUTION_MS;
    }
}

/**
 * @brief Initialise the soft Timers
 * 
 */
void InitialiseSoftTimer(void)
{
    lastMillis = millis() / SOFT_TIMER_RESOLUTION_MS;
}

/**
 * @brief Set the Soft Timer object
 * 
 * @param timer 
 * @param reloadTimerCount 
 */
void SetSoftTimer(SoftTimer_t timer, uint32_t reloadTimerCount)
{
    SoftTimerCounter[timer] = reloadTimerCount;
}

/**
 * @brief Get the Soft Timer object
 * 
 * @param timer 
 * @return uint32_t 
 */
uint32_t GetSoftTimer(SoftTimer_t timer)
{
    return SoftTimerCounter[timer];
}

/* EOF */