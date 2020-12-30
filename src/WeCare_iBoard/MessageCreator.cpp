/**
 * @file MessageCreator.cpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2020-12-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "CubeModule.hpp"
#include "Arduino.h"

int msgStrByteCount = 0;

/**
 * @brief 
 * 
 * @param pixelCount 
 */
void InitialiseMessageModule(int pixelCount)
{
    msgStrByteCount = (pixelCount / 8) + ((pixelCount % 8) == 0 ? 0 : 1);
}

/**
 * @brief Get the Message Length object
 * 
 * @return int 
 */
int getMessageLength()
{
    return msgStrByteCount;
}

/**
 * @brief Create a Message object
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 * @param msgStr 
 * @param msgStrByteCount 
 * @return true 
 * @return false 
 */
bool CreateMessage(CubeModule_t interactiveBoard[], int pixelCount, char msgStr[])
{
    bool reportMessageFlag = false;
    if (msgStrByteCount != 0)
    {
        for (int i = 0; i < pixelCount; i++)
        {
            if (interactiveBoard[i].sensorStatus == SENSOR_ACTIVE)
            {
                bitSet(msgStr[i / 8], 7 - i % 8);
            }
            else
            {
                bitClear(msgStr[i / 8], 7 - i % 8);
            }            
            reportMessageFlag |= interactiveBoard[i].sensorStateUpdateFlag;
            interactiveBoard[i].sensorStateUpdateFlag = SENSOR_VALUE_NOT_UPDATED;
        }
    }
    return (reportMessageFlag == SENSOR_VALUE_UPDATED);
}

/**
 * @brief 
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 * @param msgStr 
 */
void parseMessage(CubeModule_t interactiveBoard[], int pixelCount,char msgStr[])
{
    bool bitInfo = true;
    for (int i = 0; i < pixelCount; i++)
    {
        bitInfo = (bitRead(msgStr[i / 8], 7 - i % 8) == 1);
        if( interactiveBoard[i].actuationActivated != bitInfo)
        {
            interactiveBoard[i].actuationActivated = bitInfo;
            if(interactiveBoard[i].actuationActivated == false)
            {
                interactiveBoard[i].actuatorMode = DEAD_LOW_MODE;
            }
            else
            {
                interactiveBoard[i].actuatorMode = RAMP_MODE_UP;
            }            
        }    
    }
}

/* EOF */