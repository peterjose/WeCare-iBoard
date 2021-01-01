/**
 * @file CircularBuffer.cpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "CircularBuffer.hpp"

/**
 * @brief 
 * 
 * @param val 
 * @return true 
 * @return false 
 */
bool CircularBuffer_t::pushByte(uint8_t val)
{
    if (this->getByteCount() != this->maxSize)
    {
        this->buffer[head] = val;
        head = (head + 1) % this->maxSize;
        return true;
    }
    return false;
}

/**
 * @brief 
 * 
 * @param elmArr 
 * @param elmCount 
 * @return true 
 * @return false 
 */
bool CircularBuffer_t::pushBytes(uint8_t *elmArr,int elmCount)
{
    if (this->maxSize - this->getByteCount() >= elmCount)
    {
        for(int i =0; i < elmCount;i++)
        {
            this->buffer[this->head] = elmArr[i];
            this->head = (this->head + 1) % this->maxSize;
        }
        return true;
    }
    return false;
}

/**
 * @brief 
 * 
 * @param elmArr 
 * @param elmCount 
 * @return true 
 * @return false 
 */
bool CircularBuffer_t::popBytes(uint8_t *elmArr,int elmCount)
{
    if (this->getByteCount() >= elmCount)
    {
        for(int i =0; i < elmCount;i++)
        {
            elmArr[i] = this->buffer[this->tail];
            this->tail = (this->tail + 1) % this->maxSize;
        }
        return true;
    }
    return false;
}

/**
 * @brief 
 * 
 * @param elmArr 
 * @param elmCount 
 * @return true 
 * @return false 
 */
bool CircularBuffer_t::peekBytes(uint8_t *elmArr,int elmCount)
{
    int tailLoc = this->tail;
    if (this->getByteCount() >= elmCount)
    {
        for(int i =0; i < elmCount;i++)
        {
            elmArr[i] = this->buffer[tailLoc];
            tailLoc = (tailLoc + 1) % this->maxSize;
        }
        return true;
    }
    return false;
}

/**
 * @brief 
 * 
 * @return int 
 */
inline int CircularBuffer_t::getByteCount(void)
{
    return ((this->head >= this->tail) ? (this->head - this->tail) : ((CIRCULAR_BUFFER_MAX_SIZE - this->tail) + this->head + 1));
}

/**
 * @brief 
 * 
 * @return int 
 */
inline int CircularBuffer_t::getMaxBufferSize(void)
{
    return this->maxSize;
}


/* EOF */