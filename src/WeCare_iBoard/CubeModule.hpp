/**
 * @file CubeModule.hpp
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
#define SENSOR_TRIGGERED                HIGH
#define SENSOR_ACTIVE                   true
#define SENSOR_INACTIVE                 false

/**
 * @brief Data wrapper for the Modular cube  
 * 
 */
typedef struct cube
{
    // pin details of the sensor
    int sensorPin;
    // updated based on the sensor (reed switch)
    bool sensorStatus;
    // flagged when a change in the state of the sensor is detected, 
    // so that it can be reported to server
    bool sensorStateUpdateFlag;
    // actuator calibration low state angle info
    int actuatorLowSetting;
    // actuator calibration high state angle info
    int actuatorHighSetting;
    // target setting on actuation
    int targetSetting;
    // led light colour on the cube
    int ledState;
} CubeModule_t;


// Function prototypes
void CubeTaskRunner(CubeModule_t interactiveBoard[], int pixelCount);

#endif /* CUBE_MODULE_H_ */