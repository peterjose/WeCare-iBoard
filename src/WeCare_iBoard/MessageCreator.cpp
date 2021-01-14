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
int GetMessageLength()
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
 * @return true if a new message is created
 * @return false if no new message is created
 */
bool CreateMessage(CubeModule_t interactiveBoard[], int pixelCount, uint8_t msgPayload[])
{
    bool reportMessageFlag = false;
    if (msgStrByteCount != 0)
    {
        for (int i = 0; i < pixelCount; i++)
        {
            if (interactiveBoard[i].sensorStatus == SENSOR_ACTIVE)
            {
                bitSet(msgPayload[i / 8], 7 - i % 8);
            }
            else
            {
                bitClear(msgPayload[i / 8], 7 - i % 8);
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
 * @param msgPayload 
 */
void ParseMessage(CubeModule_t interactiveBoard[], int pixelCount,uint8_t msgPayload[])
{
    bool bitInfo = true;
    for (int i = 0; i < pixelCount; i++)
    {
        bitInfo = (bitRead(msgPayload[i / 8], 7 - i % 8) == 1);
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