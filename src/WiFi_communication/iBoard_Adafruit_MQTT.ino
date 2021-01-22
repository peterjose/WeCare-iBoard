/**
 * @file iBoard_Adafruit_MQTT.ino 
 * @author Team Hugo
 * @WiFi Communication - Adafruit IO + MQTT
 * @version 0.1
 * @date 2021-01-22
 * 
 * @copyright Copyright (c) 2021 
 */

#include <ESP8266WiFi.h>
// #include <WiFi.h> // for esp32
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// WiFi Access Point
#define WLAN_SSID       "SSID"
#define WLAN_PASS       "password"

// Adafruit.io Setup

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "AIO username"
#define AIO_KEY         "AIO key"

// Global State

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiClientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Feeds
// Setup a feed called 'switchstat01' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish switchstat01 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/switchstat01");

// Setup a feed called 'switchstat02' for subscribing.
Adafruit_MQTT_Subscribe switchstat02 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/switchstat02");

// Switches Status
// Each bit shows the status of one switch
uint16_t switchStatus;

int newData = 0;
int r = 0;

// Sketch Code

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("iBoard Adafruit_MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for switchstat02 feed.
  mqtt.subscribe(&switchstat02);
}

uint32_t x=0;


void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).
  MQTT_connect();

  // wait for incoming subscription packets
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &switchstat02) {
      Serial.print(F("Got: "));
      Serial.println(*switchstat02.lastread);
    }
  }

  // publish stuff:
  recvBytes();
  
  // only if new switch status has received, send the data to server
  if (newData == 1){
    Serial.print(F("\nSending switch status "));
    Serial.print(switchStatus);
    Serial.print("...");
    if (! switchstat01.publish(switchStatus)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  }
  else if (newData == 0)
      asm("nop");
      
  // set newData flag to 0 again
  newData = 0;

  // ping the server to keep the mqtt connection alive
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to recieve data and set newData flag to 1
void recvBytes() {
  // read data from serial port
  if (Serial.available() > 0) {
    // read the incoming byte:
    switchStatus = Serial.read();
    newData = 1;}
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

// Tutorial could be found here: https://learn.adafruit.com/mqtt-adafruit-io-and-you/overview
/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
