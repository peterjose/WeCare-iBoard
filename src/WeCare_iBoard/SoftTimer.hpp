/**
 * @file SoftTimer.hpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _SOFT_TIMER_H_
#define _SOFT_TIMER_H_

/**
 * @brief Timer List
 * 
 */
typedef enum
{
    DUMMY_TIMER                      = 0,
    DUMMY_TIMER1                        ,
    /* ADD new timers Here */
    MAX_SOFT_TIMER_COUNT                , // TOTAL number of timers available
} SoftTimer_t;

void InitialiseSoftTimer(void);
void SoftTimerTaskRunner(void);
void SetSoftTimer(SoftTimer_t timer, uint32_t reloadTimerCount);
uint32_t GetSoftTimer(SoftTimer_t timer);

#endif /* _SOFT_TIMER_H_ */