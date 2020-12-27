/**
 * @file CubeModule.h
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef CUBE_MODULE_H_
#define CUBE_MODULE_H_

// Macro definitions for Sensor state info
#define SENSOR_ACTIVE                   true
#define SENSOR_INACTIVE                 false

/**
 * @brief Data wrapper for the Modular cube  
 * 
 */
typedef struct cube
{
    // updated based on the sensor (reed switch)
    bool sensorStatus;
    // actuator calibration low state angle info
    int actuatorLowSetting;
    // actuator calibration high state angle info
    int actuatorHighSetting;
    // target setting on actuation
    int targetSetting;
    // led light colour on the cube
    int ledState;
} CubeModule_t;

#endif /* CUBE_MODULE_H_ */