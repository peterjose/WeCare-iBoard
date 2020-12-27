/**
 * @file Sensor.cpp
 * @author Team Hugo
 * @brief Function to update the sensor inputs
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "CubeModule.hpp"
#include "arduino.h"

/**
 * @brief Function to update the sensor input details to the data points
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void UpdateSensorStatus(CubeModule_t interactiveBoard[], int pixelCount)
{
    bool state;
    for(int i = 0; i< pixelCount;i++)
    {
        // read the sensor and assign the state to the active or inactive
        state = (digitalRead(interactiveBoard[i].sensorPin) == SENSOR_TRIGGERED) ? SENSOR_ACTIVE : SENSOR_INACTIVE;
        // set the state update flag
        interactiveBoard[i].sensorStateUpdateFlag = (interactiveBoard[i].sensorStatus != state);
        // update the sensor state
        interactiveBoard[i].sensorStatus = state;
    }
}

/* EOF */