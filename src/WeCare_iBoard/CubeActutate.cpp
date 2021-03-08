/**
 * @file CubeActutate.cpp
 * @author Team Hugo
 * @brief Provides functionalities for controlling the cube actuation
 * @version 0.1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// comment the following line to disable the Debug printing over the UART
#define DEBUG_ENABLE
#include "DebugPrint.hpp"

#include "config.hpp"
#include "arduino.h"
#include "CubeModule.hpp"

#define ACTUATOR_STEP_SIZE              1

#ifdef ALGORITHM_1

/**
 * @brief 
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void InitialiseActuatorModule(CubeModule_t interactiveBoard[], int pixelCount)
{
    for (int i = 0; i < pixelCount; i++)
    {
        if(interactiveBoard[i].actuatorMode != DEACTIVE_MODE)
        {
            interactiveBoard[i].actuator.attach(interactiveBoard[i].actuatorPin);
            interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorLowSetting;
            interactiveBoard[i].actuator.write(interactiveBoard[i].actuatorLowSetting);
            interactiveBoard[i].actuatorStepLevel = ACTUATOR_STEP_SIZE;
            // interactiveBoard[i].actuatorMode = NO_UPDATE_MODE;
        }
    }
}

/**
 * @brief 
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void ActuatorTaskRunner(CubeModule_t interactiveBoard[], int pixelCount)
{
    // TODO: timer based actuation
    ActuatorMode_t mode;
    for (int i = 0; i < pixelCount; i++)
    {
        mode = interactiveBoard[i].actuatorMode;
        if(interactiveBoard[i].sensorStatus == SENSOR_ACTIVE)
        {
         mode = SENSOR_ACTIVE_MODE;   
        }
        switch (mode)
        {
        case NORMAL_MODE:
            interactiveBoard[i].currentAngle = (interactiveBoard[i].actuationActivated ? interactiveBoard[i].actuatorHighSetting : interactiveBoard[i].actuatorLowSetting);
            interactiveBoard[i].actuatorMode = NO_UPDATE_MODE;
            break;
        case RAMP_MODE_DOWN:
            interactiveBoard[i].currentAngle += interactiveBoard[i].actuatorStepLevel;
            if (interactiveBoard[i].currentAngle >= interactiveBoard[i].actuatorLowSetting)
            {
                interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorLowSetting;
                interactiveBoard[i].actuatorMode = RAMP_MODE_UP;
            }
            DBG_PRINT(F("Ramp down "));
            DBG_PRINT(i);
            DBG_PRINT(F(" :"));
            DBG_PRINT_LN(interactiveBoard[i].currentAngle);
            break;
        case RAMP_MODE_UP:
            interactiveBoard[i].currentAngle -= interactiveBoard[i].actuatorStepLevel;
            if (interactiveBoard[i].currentAngle <= interactiveBoard[i].actuatorHighSetting)
            {
                interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorHighSetting;
                interactiveBoard[i].actuatorMode = RAMP_MODE_DOWN;
            }
            DBG_PRINT(F("Ramp up "));
            DBG_PRINT(i);
            DBG_PRINT(F(" :"));
            DBG_PRINT_LN(interactiveBoard[i].currentAngle);
            break;
        case DEAD_LOW_MODE:
            interactiveBoard[i].currentAngle += interactiveBoard[i].actuatorStepLevel;
            if (interactiveBoard[i].currentAngle >= interactiveBoard[i].actuatorLowSetting)
            {
                interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorLowSetting;
                interactiveBoard[i].actuatorMode = NO_UPDATE_MODE;
            }
            break;
        case ACTIVE_HIGH_MODE:
            interactiveBoard[i].currentAngle -= interactiveBoard[i].actuatorStepLevel;
            if (interactiveBoard[i].currentAngle <= interactiveBoard[i].actuatorHighSetting)
            {
                interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorHighSetting;
                interactiveBoard[i].actuatorMode = NO_UPDATE_MODE;
            }
            break;
        case SENSOR_ACTIVE_MODE:
            interactiveBoard[i].currentAngle += interactiveBoard[i].actuatorStepLevel;
            if (interactiveBoard[i].currentAngle >= interactiveBoard[i].actuatorLowSetting)
            {
                interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorLowSetting;
            }
            break;
        case IMMEDIATE_ACTIVE:
            interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorHighSetting;
            break;
        case NO_UPDATE_MODE:
            break;
        default:
            break;
        }
        if(interactiveBoard[i].actuatorMode != DEACTIVE_MODE)
        {
            if (interactiveBoard[i].actuator.read() != interactiveBoard[i].currentAngle)
            {
                interactiveBoard[i].actuator.write(interactiveBoard[i].currentAngle);
                DBG_PRINT(F("setting actuation "));
                DBG_PRINT(interactiveBoard[i].currentAngle);
                DBG_PRINT(F(" curr angle "));
                DBG_PRINT_LN(interactiveBoard[i].actuator.read());
            }
        }
        // else
        // {
        //     DBG_PRINT_LN(F("Actuator is deactivated"));
        // }
        
    }
}

#elif defined (ALGORITHM_2)

/**
 * @brief 
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void InitialiseActuatorModule(CubeModule_t interactiveBoard[], int pixelCount)
{
    for (int i = 0; i < pixelCount; i++)
    {
        interactiveBoard[i].actuator.attach(interactiveBoard[i].actuatorPin);
        interactiveBoard[i].currentAngle = (interactiveBoard[i].actuatorLowSetting - interactiveBoard[i].actuatorHighSetting)/2;
        interactiveBoard[i].actuator.write(interactiveBoard[i].currentAngle);
        interactiveBoard[i].actuatorStepLevel = ACTUATOR_STEP_SIZE;
        interactiveBoard[i].actuatorMode = NO_UPDATE_MODE;
    }
}

/**
 * @brief Algorithm 2 of Actutator
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void ActuatorTaskRunner(CubeModule_t interactiveBoard[], int pixelCount)
{
    // TODO: timer based actuation
    ActuatorMode_t mode;
    for (int i = 0; i < pixelCount; i++)
    {
        mode = interactiveBoard[i].actuatorMode;
        switch (mode)
        {
        case NORMAL_MODE:
            interactiveBoard[i].currentAngle = (interactiveBoard[i].actuationActivated ? interactiveBoard[i].actuatorHighSetting : interactiveBoard[i].actuatorLowSetting);
            interactiveBoard[i].actuatorMode = NO_UPDATE_MODE;
            break;
        case RAMP_MODE_DOWN:
            if (interactiveBoard[i].actuationActivated)
            {
                interactiveBoard[i].currentAngle += interactiveBoard[i].actuatorStepLevel;
                if (interactiveBoard[i].currentAngle >= interactiveBoard[i].actuatorLowSetting)
                {
                    interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorLowSetting;
                    interactiveBoard[i].actuatorMode = RAMP_MODE_UP;
                }
            }
            break;
        case RAMP_MODE_UP:
            if (interactiveBoard[i].actuationActivated)
            {
                interactiveBoard[i].currentAngle -= interactiveBoard[i].actuatorStepLevel;
                if (interactiveBoard[i].currentAngle <= interactiveBoard[i].actuatorHighSetting)
                {
                    interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorHighSetting;
                    interactiveBoard[i].actuatorMode = RAMP_MODE_DOWN;
                }
            }
            break;
        case DEAD_LOW_MODE:
            interactiveBoard[i].currentAngle += interactiveBoard[i].actuatorStepLevel;
            if (interactiveBoard[i].currentAngle >= interactiveBoard[i].actuatorLowSetting)
            {
                interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorLowSetting;
                interactiveBoard[i].actuatorMode = NO_UPDATE_MODE;
            }
            break;
        case ACTIVE_HIGH_MODE:
            if (interactiveBoard[i].actuationActivated)
            {
                interactiveBoard[i].currentAngle -= interactiveBoard[i].actuatorStepLevel;
                if (interactiveBoard[i].currentAngle <= interactiveBoard[i].actuatorHighSetting)
                {
                    interactiveBoard[i].currentAngle = interactiveBoard[i].actuatorHighSetting;
                    interactiveBoard[i].actuatorMode = NO_UPDATE_MODE;
                }
            }
            break;
        case NO_UPDATE_MODE:
            break;
        default:
            break;
        }

        if (interactiveBoard[i].actuator.read() != interactiveBoard[i].currentAngle)
        {
            interactiveBoard[i].actuator.write(interactiveBoard[i].currentAngle);
            DBG_PRINT(F("setting actuation"));
            DBG_PRINT_LN(interactiveBoard[i].currentAngle);
        }
    }
}

#endif /* ALGORITHM_1 */


/* EOF */