/**
 * @file TimingConfig.hpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _TIMING_CONFIG_H_
#define _TIMING_CONFIG_H_

///< SoftTimer Timer minimum resolution in milli Seconds
#define SOFT_TIMER_RESOLUTION_MS                            (uint32_t)500

#define IPC_PACKET_TIMEOUT_PERIOD                           (uint32_t)(500/SOFT_TIMER_RESOLUTION_MS)        // 500 milli seconds

#define WIFI_RECONNECT_TIMEOUT_PERIOD                       (uint32_t)(2000/SOFT_TIMER_RESOLUTION_MS)        // 2000 milli seconds

#define MQTT_RECONNECT_TIMEOUT_PERIOD                       (uint32_t)(1000/SOFT_TIMER_RESOLUTION_MS)        // 1000 milli seconds

#endif /* _TIMING_CONFIG_H_ */