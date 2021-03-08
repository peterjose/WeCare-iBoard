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

#include "config.hpp"

#ifdef NORMAL_SERVO
    #include <Servo.h>
#else
    #include <Adafruit_TiCoServo.h>
#endif /* NORMAL_SERVO */

/**
 * @brief 
 * 
 */
typedef enum
{
    NORMAL_MODE = 0,
    RAMP_MODE_UP,
    RAMP_MODE_DOWN,
    DEAD_LOW_MODE,
    ACTIVE_HIGH_MODE,
    IMMEDIATE_ACTIVE,
    NO_UPDATE_MODE,
    SENSOR_ACTIVE_MODE,
    DEACTIVE_MODE,
} ActuatorMode_t;

// Macro definitions for Sensor state info
#define SENSOR_TRIGGERED            HIGH
#define SENSOR_ACTIVE               true
#define SENSOR_INACTIVE             false

// Sensor value update flag values, 
// dont change these flag values, if did the update logic code has to be modified
#define SENSOR_VALUE_UPDATED        true
#define SENSOR_VALUE_NOT_UPDATED    false

/**
 * @brief Data wrapper for the Modular cube  
 * 
 */
typedef struct cube
{
    // Pin details of the sensor
    int sensorPin;
    // Pin details of the actuator
    int actuatorPin;

    // Updated based on the sensor (reed switch)
    bool sensorStatus;
    // Flagged when a change in the state of the sensor is detected,
    // so that it can be reported to server
    bool sensorStateUpdateFlag;

    // actuator corresponding to that cube
#ifdef NORMAL_SERVO
    Servo actuator;
#else
    Adafruit_TiCoServo actuator;
#endif /* NORMAL_SERVO */
    // Actuator calibration low state angle info
    int actuatorLowSetting;
    // Actuator calibration high state angle info
    int actuatorHighSetting;
    // Target setting on actuation
    bool actuationActivated;
    // The angle to which the actuator is activated
    int currentAngle;
    // The amount by which the actuator will be actuated
    int actuatorStepLevel;
    // actutor mode
    ActuatorMode_t actuatorMode;

    // Led light colour on the cube
    uint32_t ledColor;   // Format is 0x00RRGGBB
    // Led ledBrightness
    int ledBrightness;
} CubeModule_t;

// Function prototypes
void InitialiseCubeModule(CubeModule_t interactiveBoard[], int pixelCount);
void CubeTaskRunner(CubeModule_t interactiveBoard[], int pixelCount);

#endif /* CUBE_MODULE_H_ */