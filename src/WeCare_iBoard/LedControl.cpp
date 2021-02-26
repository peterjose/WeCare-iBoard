/**
 * @file LedControl.cpp
 * @author Team Hugo
 * @brief Gives functionlities for control of Neopixel LEDs
 * @version 0.1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include "bsp.hpp"
#include "CubeModule.hpp"
#include "LedControl.hpp"

// Number of LED pixels
#define DEFAULT_PIXEL_COUNT             16
#define PIXELS_PER_BLOCK                2

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel LED_pixels(DEFAULT_PIXEL_COUNT, LED_SINGLE_WIRE_PIN, NEO_GRB + NEO_KHZ800);

/**
 * @brief 
 * 
 * @param pixelCount 
 */
void LED_Intialise(int pixelCount)
{
    LED_pixels.updateLength(pixelCount*PIXELS_PER_BLOCK);
    LED_pixels.begin();
    LED_pixels.clear();
}

/**
 * @brief 
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void LED_updateTaskRunner(CubeModule_t interactiveBoard[], int pixelCount)
{
    for (int i = 0; i < pixelCount; i++)
    {
        // TEMPORARY logic for testing
        // if reed switch sensor is active then apply this 
        if(interactiveBoard[i].sensorStatus == SENSOR_ACTIVE)
        {
            LED_pixels.fill(LED_pixels.Color(0, 255, 0, 255),PIXELS_PER_BLOCK * i, PIXELS_PER_BLOCK);
        }
        // if actuation is intended then apply this.
        else if(interactiveBoard[i].actuationActivated == true)
        {
            LED_pixels.fill(LED_pixels.Color(0, 0, 255, 255),PIXELS_PER_BLOCK * i, PIXELS_PER_BLOCK);
        }
        else
        {
            LED_pixels.fill(LED_pixels.Color(0, 0, 0, 255),PIXELS_PER_BLOCK * i, PIXELS_PER_BLOCK);
        }
        
    }
    LED_pixels.show(); // Send the updated pixel colors to the hardware.
}

/* EOF */