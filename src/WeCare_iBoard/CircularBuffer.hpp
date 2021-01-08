/**
 * @file CircularBuffer.hpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

#include "Arduino.h"

#define CIRCULAR_BUFFER_MAX_SIZE            255

/**
 * @brief 
 * 
 */

template<typename T> class CircularBuffer_t
{
    // class Invalid{};
    T *buffer;
    int head;
    int tail;
    int maxSize; 
public:
    // Constructor
    CircularBuffer_t(int bufferSize)
    {
        this->head = 0;
        this->tail = 0;
        this->maxSize = bufferSize;
        buffer = (T *)malloc(bufferSize);
        if(buffer == NULL)
        {
            // commented out as arduino complier require to enable a flag to get exception working
            // throw Invalid();
        }
    }
    // Destructor
    ~CircularBuffer_t(){
        free(buffer);
    }
    // Memeber functions
    bool pushByte(T val);
    bool pushBytes(T *elmArr,int elmCount);
    bool popBytes(T *elmStr,int elmCount);
    bool peekBytes(T *elmStr,int elmCount);
    int getByteCount(void);
    int getMaxBufferSize(void);
};

#endif /* _CIRCULAR_BUFFER_H_ */