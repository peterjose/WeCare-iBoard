/**
 * @file WIFI_connector.cpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define ENABLE_DEBUG
#include "DebugPrint.hpp"

#include <ESP8266WiFi.h>
#include "WirelessConfig.hpp"
#include "WIFI_connector.hpp"


static bool WIFI_Status = false;

/**
   @brief

*/
static void printWIFI_ConnectionStatus(void)
{
  DBG_PRINT_LN(F(""));
  DBG_PRINT(F("Connected to "));
  DBG_PRINT_LN(WIFI_SSID);
  DBG_PRINT_LN(F(""));
  DBG_PRINT_LN(F("IP address: "));
  DBG_PRINT_LN(WiFi.localIP());
}


/**
   @brief Function to check the WIFI connection

   @return true, If WIFI connected
   @return false, If not connected
*/
bool CheckWIFI_ConnectionStatus(void)
{
  if (WiFi.status() == WL_CONNECTED)
  {
    if (!WIFI_Status)
    {
      printWIFI_ConnectionStatus();
      WIFI_Status = true;
    }
    return true;
  }
  else
  {
    if (WIFI_Status)
    {
      DBG_PRINT_LN(F(""));
      DBG_PRINT_LN(F("WIFI Disconnected"));
    }
    WIFI_Status = false;
    return false;
  }
}

/**
   @brief Set the up WIFI object

*/
void Setup_WIFI(void)
{

  // We start by connecting to a WiFi network

  DBG_PRINT_LN();
  DBG_PRINT_LN(F("**** WeCare iBoard Network Adaptor ****"));
  DBG_PRINT(F("Connecting to "));
  DBG_PRINT(WIFI_SSID);

  // Connected to WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  if (WiFi.status() == WL_CONNECTED)
  {
    printWIFI_ConnectionStatus();
    WIFI_Status = true;
  }
}
