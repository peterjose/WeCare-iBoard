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


/**
 * @brief Function that handles the task corresponding to all the cubes
 * 
 */
void CubeTaskRunner(CubeModule_t interactiveBoard[], int pixelCount)
{
    UpdateSensorStatus(interactiveBoard,pixelCount);
    LED_updateTaskRunner(interactiveBoard,pixelCount);
    
}

/* EOF */