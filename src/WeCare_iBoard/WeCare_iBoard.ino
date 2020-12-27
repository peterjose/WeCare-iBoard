/**
 * @file WeCare_iBoard.ino
 * @author Team Hugo
 * @brief WeCare_iBoard is a project developed for remote interaction between two or more people using 
 * a interactive board.
 * 
 * Software Modules used:
 * DebugPrint : For debug related functionalities
 * CubeModule : Provide a single point data point for all the info related to modular peice designed
 * 
 * 
 * Libraries used:
 * Servo
 * 
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
  Reschedule watchdog
  Additional serial for ESP communication
  Use of CBOR for data transfer or custom protocol
  MQTT feasiblity
  EEPROM module for the actuator calibration information
  NEOPIXEL module
*/

// comment the following line to disable the Debug printing over the UART
#define DEBUG_ENABLE
#include "DebugPrint.h"

#include "CubeModule.h"

CubeModule_t interactiveBoard[16];

/**
 * @brief setup function to intialise all the components
 * 
 */
void setup() {
  DBG_BEGIN(115200);

}

/**
 * @brief loop function
 * 
 */
void loop() {

}


/* EOF */