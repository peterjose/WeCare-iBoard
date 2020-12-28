/**
 * @file CubeSense.hpp
 * @author Team Hugo
 * @brief Provide functionalities for updating with the sensor inputs
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _CUBE_SENSE_H_
#define _CUBE_SENSE_H_

void InitialisedSensorModule(CubeModule_t interactiveBoard[], int pixelCount);
void UpdateSensorStatus(CubeModule_t interactiveBoard[], int pixelCount);

#endif /* _CUBE_SENSE_H_ */