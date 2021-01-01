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
typedef class CircularBuffer
{
    uint8_t *buffer;
    int head;
    int tail;
    int maxSize; 
public:
    CircularBuffer(int bufferSize)
    {
        this->head = 0;
        this->tail = 0;
        this->maxSize = bufferSize;
        buffer = (uint8_t *)malloc(bufferSize);
    }
    bool pushByte(uint8_t val);
    bool pushBytes(uint8_t *elmArr,int elmCount);
    bool popBytes(uint8_t *elmStr,int elmCount);
    bool peekBytes(uint8_t *elmStr,int elmCount);
    int getByteCount(void);
    int getMaxBufferSize(void);
} CircularBuffer_t;

#endif /* _CIRCULAR_BUFFER_H_ */