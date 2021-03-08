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

// To disable any Debug comment the following line 
// #define DEBUG_ALLOWED

#ifdef DEBUG_ALLOWED
    #ifdef DEBUG_ENABLE
        #define DBG_BEGIN(x)        Serial.begin(x);
        #define DBG_PRINT(x)        Serial.print(x);
        #define DBG_PRINT_LN(x)     Serial.println(x);
        #define DBG_PRINT_HEX(x)    Serial.print(x,HEX);
        #define DBG_WRITE(x)        Serial.write(x);
    #else
        #define DBG_BEGIN(x)
        #define DBG_PRINT(x)
        #define DBG_PRINT_LN(x)
        #define DBG_PRINT_HEX(x)
        #define DBG_WRITE(x)
    #endif /* DEBUG_ENABLE */
#else
    #define DBG_BEGIN(x)
    #define DBG_PRINT(x)
    #define DBG_PRINT_LN(x)
    #define DBG_PRINT_HEX(x)
    #define DBG_WRITE(x)
#endif /* DEBUG_ALLOWED */

#endif /* _DEBUG_PRINT_H_ */
