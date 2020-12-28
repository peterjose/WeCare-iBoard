/**
 * @file LedControl.hpp
 * @author Team Hugo
 * @brief Gives functionlities for control of Neopixel LEDs
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _LED_CONTROL_H_
#define _LED_CONTROL_H_

void LED_Intialise(int pixelCount);
void LED_updateTaskRunner(CubeModule_t interactiveBoard[], int pixelCount);

#endif /* _LED_CONTROL_H_ */