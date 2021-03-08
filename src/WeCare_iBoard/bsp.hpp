/**
 * @file bsp.hpp
 * @author Team Hugo
 * @brief Contain all the information regarding the Hardware
 * @version 0.1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _BSP_H_
#define _BSP_H_

#define LED_SINGLE_WIRE_PIN               46
// Serial communication
#define DEBUG_RX                          0
#define DEBUG_TX                          1
#define NET_TX                            18
#define NET_RX                            19
// Switches
#define SWITCH01                          35
#define SWITCH02                          17
#define SWITCH03                          22
#define SWITCH04                          36
#define SWITCH05                          24
#define SWITCH06                          23
#define SWITCH07                          26
#define SWITCH08                          25
#define SWITCH09                          28
#define SWITCH10                          27
#define SWITCH11                          30
#define SWITCH12                          29
#define SWITCH13                          32
#define SWITCH14                          31
#define SWITCH15                          34
#define SWITCH16                          33
// Motors
#define MOTOR01                           4
#define MOTOR02                           9
#define MOTOR03                           14
#define MOTOR04                           15
#define MOTOR05                           16
#define MOTOR06                           2
#define MOTOR07                           3
#define MOTOR08                           5
#define MOTOR09                           6
#define MOTOR10                           7
#define MOTOR11                           8
#define MOTOR12                           11
#define MOTOR13                           12
#define MOTOR14                           13
#define MOTOR15                           44
#define MOTOR16                           45

// Free digital pins: 21,20 (I2C) 19~14 (UART) 8~2 (PWM)
// Free analog pins: A0~A15

#endif /* _BSP_H_ */
