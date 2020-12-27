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

extern CubeModule_t interactiveBoard[16];
extern int pixelCount;

/**
 * @brief 
 * 
 */
void updateSensorStatus(void)
{
    for(int i; i< pixelCount;i++)
    {
        interactiveBoard[i].sensorStatus = digitalRead(interactiveBoard[i].sensorPin);
    }
}

/* EOF */