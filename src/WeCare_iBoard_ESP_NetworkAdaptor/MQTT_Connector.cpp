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

#define ENABLE_DEBUG
#include "DebugPrint.hpp"

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "SoftTimer.hpp"
#include "TimingConfig.hpp"
#include "WirelessConfig.hpp"
#include "MQTT_Connector.hpp"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish board1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Board1");

Adafruit_MQTT_Subscribe board2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Board2");

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
    if (!GetSoftTimer(MQTT_TIMEOUT_TIMER))
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
    mqtt.subscribe(&board2);
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
    MQTT_connect();

    // this is our 'wait for incoming subscription packets' busy subloop
    // try to spend your time here

    // Adafruit_MQTT_Subscribe *subscription;
    // while ((subscription = mqtt.readSubscription(5000)))
    // {
    //     if (subscription == &onoffbutton)
    //     {
    //         DBG_PRINT(F("Got: "));
    //         DBG_PRINT_LN((char *)onoffbutton.lastread);
    //     }
    // }

    // // Now we can publish stuff!
    // Serial.print(F("\nSending photocell val "));
    // Serial.print(x);
    // Serial.print("...");
    // if (!photocell.publish(x++))
    // {
    //     DBG_PRINT_LN(F("Failed"));
    // }
    // else
    // {
    //     DBG_PRINT_LN(F("OK!"));
    // }

    // ping the server to keep the mqtt connection alive
    // NOT required if you are publishing once every KEEPALIVE seconds

    if (!mqtt.ping())
    {
        mqtt.disconnect();
    }
}


/* EOF */