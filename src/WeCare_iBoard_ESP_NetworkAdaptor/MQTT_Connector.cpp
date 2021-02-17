/**
 * @file MQTT_Connector.cpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define DEBUG_ENABLE
#include "DebugPrint.hpp"

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "SoftTimer.hpp"
#include "TimingConfig.hpp"
#include "WirelessConfig.hpp"
#include "MQTT_Connector.hpp"


#define DEVICE_BOARD(x)     (x == BOARD1_MAC) ?"Board1":"Board2"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish Board_self = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/BoardX" );

Adafruit_MQTT_Subscribe Board_other = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/BoardX");

static void processingIncomingPacket(char *data, uint16_t len)
{
    // TODO: set the data for processing and then send to the device
    DBG_PRINT(F("Data rcvd for board : "))
    DBG_PRINT_LN(data);
}

/**
 * @brief Function to connect and reconnect as necessary to the MQTT server.
 * Should be called in the loop function and it will take care if connecting.
 * @return true, if connection is proper 
 * @return false, if connection is not proper 
 */
static bool MQTT_connect()
{
    static int retries = 0;
    int8_t ret = 0;
    // Stop if already connected.
    if (mqtt.connected())
    { 
        // reset the timer for MQTT reconnect timer since connection is proper
        SetSoftTimer(MQTT_TIMEOUT_TIMER, MQTT_RECONNECT_TIMEOUT_PERIOD);
        retries = 0;
        return true;
    }

    // wait till timer expires
    if (GetSoftTimer(MQTT_TIMEOUT_TIMER))
    {
        return false;
    }
    // reset the timer back for next retry
    SetSoftTimer(MQTT_TIMEOUT_TIMER, MQTT_RECONNECT_TIMEOUT_PERIOD);
    retries++;
    DBG_PRINT(F("MQTT reconnect: try no "));
    DBG_PRINT_LN(retries);

    if ((ret = mqtt.connect()) != 0)
    {
        // connect will return 0 for connected
        DBG_PRINT_LN(mqtt.connectErrorString(ret));
        mqtt.disconnect();
        return false;
    }
    DBG_PRINT_LN(F("MQTT Connected!"));
    return true;
}

/**
 * @brief 
 * 
 */
void Initialise_MQTT(void)
{
    Board_self = Adafruit_MQTT_Publish(&mqtt,  ((WiFi.macAddress() == BOARD1_MAC) ? (AIO_USERNAME "/feeds/Board1") : (AIO_USERNAME "/feeds/Board2")));
    Board_other = Adafruit_MQTT_Subscribe(&mqtt, ((WiFi.macAddress() == BOARD1_MAC) ? (AIO_USERNAME "/feeds/Board2") : (AIO_USERNAME "/feeds/Board1")));

    Board_other.setCallback(processingIncomingPacket);
    mqtt.subscribe(&Board_other);
    SetSoftTimer(MQTT_TIMEOUT_TIMER, MQTT_RECONNECT_TIMEOUT_PERIOD);
}

/**
 * @brief 
 * 
 */
void MQTT_TaskRunner(void)
{
    // Ensure the connection to the MQTT server is alive (this will make the first
    // connection and automatically reconnect when disconnected).  See the MQTT_connect
    // function definition further below.
    if(MQTT_connect())
    {
        mqtt.processPackets(1);

        // ping the server to keep the mqtt connection alive
        // NOT required if you are publishing once every KEEPALIVE seconds

        if (!mqtt.ping())
        {
            mqtt.disconnect();
        }
    }
}


/* EOF */