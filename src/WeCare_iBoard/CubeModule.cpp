/**
 * @file CubeModule.cpp
 * @author Team Hugo
 * @brief Provides all the functionalities needed to control the Interactive board based on the cube modules
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "CubeModule.hpp"
#include "CubeSense.hpp"
#include "LedControl.hpp"
#include "CubeActuate.hpp"

/**
 * @brief 
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void CubeModuleInitialise(CubeModule_t interactiveBoard[], int pixelCount)
{
    InitialisedSensorModule(interactiveBoard, pixelCount);
    LED_Intialise(pixelCount);
    InitialisedActuatorModule(interactiveBoard, pixelCount);
}

/**
 * @brief Function that handles the task corresponding to all the cubes
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void CubeTaskRunner(CubeModule_t interactiveBoard[], int pixelCount)
{
    UpdateSensorStatus(interactiveBoard, pixelCount);
    LED_updateTaskRunner(interactiveBoard, pixelCount);
    ActuatorTaskRunner(interactiveBoard, pixelCount);
}

/* EOF */