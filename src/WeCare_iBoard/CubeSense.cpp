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
    for(int i; i< pixelCount;i++)
    {
        interactiveBoard[i].sensorStatus = digitalRead(interactiveBoard[i].sensorPin);
    }
}

/* EOF */