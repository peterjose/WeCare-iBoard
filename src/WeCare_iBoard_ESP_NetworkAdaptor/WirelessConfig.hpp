/**
 * @file WirelessConfig.hpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _WIRELESS_CONFIG_H_
#define _WIRELESS_CONFIG_H_

/************************* WiFi Access Point *********************************/

#define WIFI_SSID       "...your SSID..."
#define WIFI_PASSWORD   "...your password..."

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "...your AIO username (see https://accounts.adafruit.com)..."
#define AIO_KEY         "...your AIO key..."


// fill in the MAC address of the boards
#define BOARD1_MAC      "XX:XX:XX:XX:XX:XX"
// #define BOARD2_MAC      "XX:XX:XX:XX:XX:XX"


#endif /* _WIRELESS_CONFIG_H_ */