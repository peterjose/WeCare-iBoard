/**
 * @file DebugPrint.hpp
 * @author Team Hugo
 * @brief File contains the necessary functions and defintions 
 * debug printing
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _DEBUG_PRINT_H_
#define _DEBUG_PRINT_H_

#ifdef DEBUG_ENABLE
    #define DBG_BEGIN(x)        Serial.begin(x);
    #define DBG_PRINT(x)        Serial.print(x);
#else
    #define DBG_BEGIN(x)
    #define DBG_PRINT(x)
#endif /* DEBUG_ENABLE */

#endif /* _DEBUG_PRINT_H_ */
