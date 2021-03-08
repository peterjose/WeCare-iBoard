/**
 * @file config.hpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2021-01-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#define ALGORITHM_1
#define ALGORITHM_2

#define NORMAL_SERVO

// SERIAL COMMUNICATION
#define RX_BUFFER_SIZE              255
#define TX_BUFFER_SIZE              255

#define BAUDRATE_NETWORK_SERIAL     9600

// LED Brightness Info
#define LED_MIN_BRIGHTNESS          0
#define LED_MAX_BRIGHTNESS          255

// Actuator 
#define ACTUATOR_MAX_CHANGE         125

#define MIN_POSITION_DEFAULT        125
#define MAX_POSITION_DEFAULT        0

#endif /* _CONFIG_H_ */