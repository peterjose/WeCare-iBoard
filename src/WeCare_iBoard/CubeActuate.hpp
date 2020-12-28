/**
 * @file CubeActuate.hpp
 * @author Team Hugo
 * @brief Provide actuator related functionality
 * @version 0.1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _CUBE_ACTUATE_H_
#define _CUBE_ACTUATE_H_

void InitialisedActuatorModule(CubeModule_t interactiveBoard[],int pixelCount);
void ActuatorTaskRunner(CubeModule_t interactiveBoard[],int pixelCount);

#endif /* _CUBE_ACTUATE_H_ */