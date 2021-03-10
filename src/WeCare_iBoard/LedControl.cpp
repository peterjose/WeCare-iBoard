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

// API information used for the algorithm is available
// https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html#aa05f7d37828c43fef00e6242dcf75959

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif                 /* __AVR__ */

// comment the following line to disable the Debug printing over the UART
// #define DEBUG_ENABLE
#include "DebugPrint.hpp"

#include "bsp.hpp"
#include "config.hpp"
#include "CubeModule.hpp"
#include "LedControl.hpp"

// Number of LED pixels
#define DEFAULT_PIXEL_COUNT 16
#define PIXELS_PER_BLOCK 2

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel LED_pixels(DEFAULT_PIXEL_COUNT, LED_SINGLE_WIRE_PIN, NEO_GRB + NEO_KHZ800);

#ifdef ALGORITHM_1
/**
 * @brief Algorithm 1
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void LED_updateTaskRunner(CubeModule_t interactiveBoard[], int pixelCount)
{
    for (int i = 0; i < pixelCount; i++)
    {
        int brightness = map(interactiveBoard[i].currentAngle, interactiveBoard[i].actuatorLowSetting, interactiveBoard[i].actuatorHighSetting,
                             LED_MIN_BRIGHTNESS, LED_MAX_BRIGHTNESS);
        // (((interactiveBoard[i].actuatorLowSetting - interactiveBoard[i].currentAngle) * LED_MAX_BRIGHTNESS)
        //                     / ACTUATOR_MAX_CHANGE);
        // TEMPORARY logic for testing
        // if reed switch sensor is active then apply this
        if (interactiveBoard[i].sensorStatus == SENSOR_ACTIVE)
        {
            LED_pixels.fill(LED_pixels.Color(0, 255, 0, 255), PIXELS_PER_BLOCK * i, PIXELS_PER_BLOCK);
        }
        // if actuation is intended then apply this.
        else if (interactiveBoard[i].actuationActivated == true)
        {
            LED_pixels.fill(LED_pixels.Color(brightness , 0, 0, 255), PIXELS_PER_BLOCK * i, PIXELS_PER_BLOCK);
            DBG_PRINT(F("LED_updateTaskRunner >> brightness "));
            DBG_PRINT(interactiveBoard[i].actuatorLowSetting);
            DBG_PRINT(" ");
            DBG_PRINT(interactiveBoard[i].currentAngle);
            DBG_PRINT(" ");
            DBG_PRINT_LN(brightness);
        }
        else
        {
            LED_pixels.fill(LED_pixels.Color(5, 5, 5, 0), PIXELS_PER_BLOCK * i, PIXELS_PER_BLOCK);
        }
    }
    LED_pixels.show(); // Send the updated pixel colors to the hardware.
}

#elif defined (ALGORITHM_2)
/**
 * @brief Algorithm 2
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void LED_updateTaskRunner(CubeModule_t interactiveBoard[], int pixelCount)
{
    for (int i = 0; i < pixelCount; i++)
    {
        int brightness = map(interactiveBoard[i].currentAngle, interactiveBoard[i].actuatorLowSetting, interactiveBoard[i].actuatorHighSetting,
                             LED_MIN_BRIGHTNESS, LED_MAX_BRIGHTNESS);
        // (((interactiveBoard[i].actuatorLowSetting - interactiveBoard[i].currentAngle) * LED_MAX_BRIGHTNESS)
        //                     / ACTUATOR_MAX_CHANGE);
        // TEMPORARY logic for testing
        // if reed switch sensor is active then apply this
        if (interactiveBoard[i].sensorStatus == SENSOR_ACTIVE)
        {
            LED_pixels.fill(LED_pixels.Color(0, 255, 0, 255), PIXELS_PER_BLOCK * i, PIXELS_PER_BLOCK);
        }
        // if actuation is intended then apply this.
        else if (interactiveBoard[i].actuationActivated == true)
        {
            LED_pixels.fill(LED_pixels.Color(brightness , 0, 0, 255), PIXELS_PER_BLOCK * i, PIXELS_PER_BLOCK);
            DBG_PRINT(F("LED_updateTaskRunner >> brightness "));
            DBG_PRINT(interactiveBoard[i].actuatorLowSetting);
            DBG_PRINT(" ");
            DBG_PRINT(interactiveBoard[i].currentAngle);
            DBG_PRINT(" ");
            DBG_PRINT_LN(brightness);
        }
        else
        {
            LED_pixels.fill(LED_pixels.Color(5, 5, 5, 0), PIXELS_PER_BLOCK * i, PIXELS_PER_BLOCK);
        }
    }
    LED_pixels.show(); // Send the updated pixel colors to the hardware.
}

#endif /* ALGORITHM_1 */
/**
 * @brief 
 * 
 * @param pixelCount 
 */
static void defaultBrightness(int pixelCount)
{
    LED_pixels.fill(LED_pixels.Color(130, 130, 130, 255), 0, pixelCount * PIXELS_PER_BLOCK);
}

/**
 * @brief 
 * 
 * @param pixelCount 
 */
static void printWelcomNote(int pixelCount)
{
    defaultBrightness(pixelCount);
    // print H
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 0,  PIXELS_PER_BLOCK);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 3 * PIXELS_PER_BLOCK,  PIXELS_PER_BLOCK * 2);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 7 * PIXELS_PER_BLOCK,  PIXELS_PER_BLOCK * 6);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 15 * PIXELS_PER_BLOCK,  PIXELS_PER_BLOCK);
    LED_pixels.show();
    delay(1000);
    // print U
    LED_pixels.clear();
    defaultBrightness(pixelCount);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 0,  PIXELS_PER_BLOCK*5);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 7 * PIXELS_PER_BLOCK,  PIXELS_PER_BLOCK * 2);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 11 * PIXELS_PER_BLOCK,  PIXELS_PER_BLOCK * 2);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 15 * PIXELS_PER_BLOCK,  PIXELS_PER_BLOCK);
    LED_pixels.show();
    delay(1000);
    // Print G
    LED_pixels.clear();
    defaultBrightness(pixelCount);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 0,  PIXELS_PER_BLOCK * 5);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 6 * PIXELS_PER_BLOCK,  PIXELS_PER_BLOCK * 3);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 12 * PIXELS_PER_BLOCK,  PIXELS_PER_BLOCK * 5);
    LED_pixels.show();
    delay(1000);
    // print O
    LED_pixels.clear();
    defaultBrightness(pixelCount);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 0,  PIXELS_PER_BLOCK*5);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 7 * PIXELS_PER_BLOCK,  PIXELS_PER_BLOCK * 2);
    LED_pixels.fill(LED_pixels.Color(255, 0, 0, 255), 11 * PIXELS_PER_BLOCK,  PIXELS_PER_BLOCK * 5);
    LED_pixels.show();
    delay(1000);
    LED_pixels.clear();

}

/**
 * @brief 
 * 
 * @param pixelCount 
 */
void LED_Intialise(int pixelCount)
{
    LED_pixels.updateLength(pixelCount * PIXELS_PER_BLOCK);
    LED_pixels.begin();
    LED_pixels.clear();
    printWelcomNote(pixelCount);
}


/* EOF */