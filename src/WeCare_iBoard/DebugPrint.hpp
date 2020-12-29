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
    #define DBG_PRINT_LN(x)     Serial.println(x);
    #define DBG_PRINT_HEX(x)    Serial.print(x,HEX);
#else
    #define DBG_BEGIN(x)
    #define DBG_PRINT(x)
    #define DBG_PRINT_LN(x)
    #define DBG_PRINT_HEX(x)
#endif /* DEBUG_ENABLE */

#endif /* _DEBUG_PRINT_H_ */
