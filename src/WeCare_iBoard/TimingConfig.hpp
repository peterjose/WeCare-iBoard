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
#define SOFT_TIMER_RESOLUTION_MS                            (uint32_t)5                                     // 5 milli second resolution

#define IPC_PACKET_TIMEOUT_PERIOD                           (uint32_t)(500/SOFT_TIMER_RESOLUTION_MS)        // 500 milli seconds

///< PERIODIC Timer timing
#define PERIODIC_TIMER_PERIOD                               (uint32_t)(10/SOFT_TIMER_RESOLUTION_MS)        // 10 miili seconds

#endif /* _TIMING_CONFIG_H_ */