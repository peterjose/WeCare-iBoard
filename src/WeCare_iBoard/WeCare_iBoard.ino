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

#include "CubeModule.hpp"
#include "NetworkCommunicationModule.hpp"
#include "SoftTimer.hpp"
#include "TimingConfig.hpp"

// Interactive Board
CubeModule_t interactiveBoard[1];

// pixel count of the interactive board
int pixelCount = sizeof(interactiveBoard) / sizeof(CubeModule_t);

/**
 * @brief 
 * 
 */
void DummyInitfn()
{
  interactiveBoard[0].actuatorPin = 3;
  interactiveBoard[0].sensorPin = 4;
}
/**
 * @brief 
 * 
 */
void DummyRunfn()
{
  static bool sensorVal = SENSOR_ACTIVE;
  if(!GetSoftTimer(DUMMY_TIMER1)){
    DBG_PRINT_LN(F("DummyRunfn >> Timer DUMMY_TIMER1 expired"));
    SetSoftTimer(DUMMY_TIMER1,DUMMY_TIMER_PERIOD);
    DBG_PRINT_LN(F("DummyRunfn >> Timer DUMMY_TIMER1, reloaded"));
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
  DummyInitfn();
  // Disabled watchdog timer for testing
  wdt_disable();
  // enable watchdog timer
  //wdt_enable(WDTO_8S);

  DBG_BEGIN(115200);
  DBG_PRINT_LN(F("Debug port opened"));
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
  DummyRunfn();
  // CubeTaskRunner(interactiveBoard, pixelCount);
  ConnectionTaskRunner(interactiveBoard, pixelCount);
  SoftTimerTaskRunner();
}
 
/* EOF */