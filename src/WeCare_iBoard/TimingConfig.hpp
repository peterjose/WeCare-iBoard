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

///< Dummy Timinig
#define DUMMY_TIMER_PERIOD                                  (uint32_t)(10000/SOFT_TIMER_RESOLUTION_MS)        // 10 seconds

#endif /* _TIMING_CONFIG_H_ */