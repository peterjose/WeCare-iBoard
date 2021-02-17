/**
 * @file WeCare_iBoard_ESP_NetworkAdaptor.ino
 * @author Team Hugo
 * @brief The following project is a part of WeCare iBoard.
 * This specific project provides the wireless connectivity of the boards
 * @version 0.1
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <ESP8266WiFi.h>

#define DEBUG_ENABLE
#include "DebugPrint.hpp"

#include "WIFI_connector.hpp"
#include "SoftTimer.hpp"
#include "MQTT_Connector.hpp"

/**
 * @brief 
 * 
 */
void setup()
{

  ESP.wdtDisable();
  DBG_BEGIN(115200);
  delay(100);

  Setup_WIFI();
  Initialise_MQTT();
  InitialiseSoftTimer();
  DBG_PRINT_LN(F("Board Init OK"));
}

/**
 * @brief 
 * 
 */
void loop()
{
  SoftTimerTaskRunner();
  if (CheckWIFI_ConnectionStatus())
  {
    MQTT_TaskRunner();
  }
}

/* EOF */