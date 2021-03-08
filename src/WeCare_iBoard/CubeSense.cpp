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

// comment the following line to disable the Debug printing over the UART
#define DEBUG_ENABLE
#include "DebugPrint.hpp"

#include "CubeModule.hpp"
#include "arduino.h"

void InitialiseSensorModule(CubeModule_t interactiveBoard[], int pixelCount)
{
    for (int i = 0; i < pixelCount; i++)
    {
        pinMode(interactiveBoard[i].sensorPin, INPUT);
    }
    DBG_PRINT_LN(F("InitialiseSensorModule >> Sensor Intialised"));
}

/**
 * @brief Function to update the sensor input details to the data points
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void UpdateSensorStatus(CubeModule_t interactiveBoard[], int pixelCount)
{
    bool state;
    for (int i = 0; i < pixelCount; i++)
    {
        // read the sensor and assign the state to the active or inactive
        state = (digitalRead(interactiveBoard[i].sensorPin) == SENSOR_TRIGGERED) ? SENSOR_ACTIVE : SENSOR_INACTIVE;
        // set the state update flag
        interactiveBoard[i].sensorStateUpdateFlag = (interactiveBoard[i].sensorStatus != state) ? SENSOR_VALUE_UPDATED : SENSOR_VALUE_NOT_UPDATED;
        #ifdef DEBUG_ENABLE
        if(interactiveBoard[i].sensorStatus != state)
        {
            DBG_PRINT(F("UpdateSensorStatus >> Sensor state : "));
            DBG_PRINT(state);
            DBG_PRINT(F(" pin : "));
            DBG_PRINT(interactiveBoard[i].sensorPin);
            DBG_PRINT(F(", sensorStateUpdateFlag : "));
            DBG_PRINT_LN(interactiveBoard[i].sensorStateUpdateFlag);
        }
        #endif /* DEBUG_ENABLE */
        // update the sensor state
        interactiveBoard[i].sensorStatus = state;
    }
}

/* EOF */