/**
 * @file WeCare_iBoard.ino
 * @author Team Hugo
 * @brief WeCare_iBoard is a project developed for remote interaction between two or more people using 
 * a interactive board.
 * 
 * Software Modules used:
 * DebugPrint : For debug related functionalities
 * CubeModule : Provide a single point data point for all the info related to modular peice designed
 * Sensor : 
 * 
 * Libraries used:
 * Servo by Michael Margolis, Arduino version 1.1.7
 * Adafruit NeoPixel version 1.7.0
 * Adafruit TiCoServo version 1.0.4
 * 
 * 
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*
TODO: 
  Additional Serial connector for ESP communication
  Packet Creator
  Backup - Use of CBOR for data transfer or Custom protocol (bit map)
  MQTT feasiblity - ESP
  EEPROM module for the actuator calibration information
  Make interactiveBoard Dynamic
*/

#include <avr/wdt.h>

// comment the following line to disable the Debug printing over the UART
#define DEBUG_ENABLE
#include "DebugPrint.hpp"

#include "config.hpp"
#include "bsp.hpp"
#include "CubeModule.hpp"
#include "NetworkCommunicationModule.hpp"
#include "SoftTimer.hpp"
#include "TimingConfig.hpp"

// Interactive Board
CubeModule_t interactiveBoard[16];

// pixel count of the interactive board
int pixelCount = sizeof(interactiveBoard) / sizeof(CubeModule_t);

/**
 * @brief 
 * 
 */
void DummyInitfn()
{
  interactiveBoard[0].sensorPin = SWITCH01;
  interactiveBoard[0].actuatorPin = MOTOR01;
  interactiveBoard[0].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[0].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[0].actuatorHighSetting  = MAX_POSITION_DEFAULT;
#ifdef NORMAL_SERVO
  interactiveBoard[0].actuatorMode = NO_UPDATE_MODE;
#else
  interactiveBoard[0].actuatorMode = DEACTIVE_MODE;
#endif /* NORMAL_SERVO */

  interactiveBoard[1].sensorPin = SWITCH02;
  interactiveBoard[1].actuatorPin = MOTOR02;
  interactiveBoard[1].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[1].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[1].actuatorHighSetting  = MAX_POSITION_DEFAULT;
#ifdef NORMAL_SERVO
  interactiveBoard[1].actuatorMode = NO_UPDATE_MODE;
#else
  interactiveBoard[1].actuatorMode = DEACTIVE_MODE;
#endif /* NORMAL_SERVO */

  interactiveBoard[2].sensorPin = SWITCH03;
  interactiveBoard[2].actuatorPin = MOTOR03;
  interactiveBoard[2].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[2].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[2].actuatorHighSetting  = MAX_POSITION_DEFAULT;
#ifdef NORMAL_SERVO
  interactiveBoard[2].actuatorMode = NO_UPDATE_MODE;
#else
  interactiveBoard[2].actuatorMode = DEACTIVE_MODE;
#endif /* NORMAL_SERVO */

  interactiveBoard[3].sensorPin = SWITCH04;
  interactiveBoard[3].actuatorPin = MOTOR04;
  interactiveBoard[3].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[3].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[3].actuatorHighSetting  = MAX_POSITION_DEFAULT;
#ifdef NORMAL_SERVO
  interactiveBoard[3].actuatorMode = NO_UPDATE_MODE;
#else
  interactiveBoard[3].actuatorMode = DEACTIVE_MODE;
#endif /* NORMAL_SERVO */

  interactiveBoard[4].sensorPin = SWITCH05;
  interactiveBoard[4].actuatorPin = MOTOR05;
  interactiveBoard[4].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[4].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[4].actuatorHighSetting  = MAX_POSITION_DEFAULT;
#ifdef NORMAL_SERVO
  interactiveBoard[4].actuatorMode = NO_UPDATE_MODE;
#else
  interactiveBoard[4].actuatorMode = DEACTIVE_MODE;
#endif /* NORMAL_SERVO */

  interactiveBoard[5].sensorPin = SWITCH06;
  interactiveBoard[5].actuatorPin = MOTOR06;
  interactiveBoard[5].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[5].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[5].actuatorHighSetting  = MAX_POSITION_DEFAULT;
#ifdef NORMAL_SERVO
  interactiveBoard[5].actuatorMode = NO_UPDATE_MODE;
#else
  interactiveBoard[5].actuatorMode = DEACTIVE_MODE;
#endif /* NORMAL_SERVO */

  interactiveBoard[6].sensorPin = SWITCH07;
  interactiveBoard[6].actuatorPin = MOTOR07;
  interactiveBoard[6].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[6].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[6].actuatorHighSetting  = MAX_POSITION_DEFAULT;
  interactiveBoard[6].actuatorMode = NO_UPDATE_MODE;

  interactiveBoard[7].sensorPin = SWITCH08;
  interactiveBoard[7].actuatorPin = MOTOR08;
  interactiveBoard[7].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[7].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[7].actuatorHighSetting  = MAX_POSITION_DEFAULT;
  interactiveBoard[7].actuatorMode = NO_UPDATE_MODE;

  interactiveBoard[8].sensorPin = SWITCH09;
  interactiveBoard[8].actuatorPin = MOTOR09;
  interactiveBoard[8].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[8].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[8].actuatorHighSetting  = MAX_POSITION_DEFAULT;
  interactiveBoard[8].actuatorMode = NO_UPDATE_MODE;

  interactiveBoard[9].sensorPin = SWITCH10;
  interactiveBoard[9].actuatorPin = MOTOR10;
  interactiveBoard[9].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[9].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[9].actuatorHighSetting  = MAX_POSITION_DEFAULT;
  interactiveBoard[9].actuatorMode = NO_UPDATE_MODE;

  interactiveBoard[10].sensorPin = SWITCH11;
  interactiveBoard[10].actuatorPin = MOTOR11;
  interactiveBoard[10].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[10].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[10].actuatorHighSetting  = MAX_POSITION_DEFAULT;
  interactiveBoard[10].actuatorMode = NO_UPDATE_MODE;

  interactiveBoard[11].sensorPin = SWITCH12;
  interactiveBoard[11].actuatorPin = MOTOR12;
  interactiveBoard[11].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[11].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[11].actuatorHighSetting  = MAX_POSITION_DEFAULT;
  interactiveBoard[11].actuatorMode = NO_UPDATE_MODE;

  interactiveBoard[12].sensorPin = SWITCH13;
  interactiveBoard[12].actuatorPin = MOTOR13;
  interactiveBoard[12].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[12].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[12].actuatorHighSetting  = MAX_POSITION_DEFAULT;
  interactiveBoard[12].actuatorMode = NO_UPDATE_MODE;

  interactiveBoard[13].sensorPin = SWITCH14;
  interactiveBoard[13].actuatorPin = MOTOR14;
  interactiveBoard[13].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[13].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[13].actuatorHighSetting  = MAX_POSITION_DEFAULT;
  interactiveBoard[13].actuatorMode = NO_UPDATE_MODE;

  interactiveBoard[14].sensorPin = SWITCH15;
  interactiveBoard[14].actuatorPin = MOTOR15;
  interactiveBoard[14].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[14].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[14].actuatorHighSetting  = MAX_POSITION_DEFAULT;
  interactiveBoard[14].actuatorMode = NO_UPDATE_MODE;

  interactiveBoard[15].sensorPin = SWITCH16;
  interactiveBoard[15].actuatorPin = MOTOR16;
  interactiveBoard[15].actuationActivated = SENSOR_INACTIVE;
  interactiveBoard[15].actuatorLowSetting = MIN_POSITION_DEFAULT;
  interactiveBoard[15].actuatorHighSetting  = MAX_POSITION_DEFAULT;
  interactiveBoard[15].actuatorMode = NO_UPDATE_MODE;
  DBG_PRINT_LN(F("Dummy Init done"));
}
/**
 * @brief 
 * 
 */
void DummyRunfn()
{
  static bool sensorVal = SENSOR_ACTIVE;
  if(!GetSoftTimer(PERIODIC_TIMER1)){
    // DBG_PRINT_LN(F("DummyRunfn >> Timer DUMMY_TIMER1 expired"));
    SetSoftTimer(PERIODIC_TIMER1,PERIODIC_TIMER_PERIOD);
    // DBG_PRINT_LN(F("DummyRunfn >> Timer DUMMY_TIMER1, reloaded"));
    interactiveBoard[0].sensorStateUpdateFlag = SENSOR_VALUE_UPDATED;
    interactiveBoard[0].sensorStatus = sensorVal;
    sensorVal = !sensorVal;
  }
}

/**
 * @brief setup function to intialise all the components
 * 
 */
void setup()
{
  // Disabled watchdog timer for testing
  wdt_disable();
  // enable watchdog timer
  //wdt_enable(WDTO_8S);

  DBG_BEGIN(115200);
  DBG_PRINT_LN(F("Debug port opened"));
  DummyInitfn();
  InitialiseCubeModule(interactiveBoard, pixelCount);
  EstablishedInterBoardConnection(pixelCount);
  InitialiseSoftTimer();
  DBG_PRINT(F("WeCare-iBoard Intialised with "));
  DBG_PRINT(pixelCount);
  DBG_PRINT_LN(F(" pixels"));
}

/**
 * @brief loop function
 * 
 */
void loop()
{
  // DummyRunfn();
  SoftTimerTaskRunner();
  if(!GetSoftTimer(PERIODIC_TIMER)){
    SetSoftTimer(PERIODIC_TIMER,PERIODIC_TIMER_PERIOD);
    CubeTaskRunner(interactiveBoard, pixelCount);
    ConnectionTaskRunner(interactiveBoard, pixelCount);
  }
}
 
/* EOF */
