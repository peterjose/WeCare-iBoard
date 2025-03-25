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
    /**
     * @brief 
     * 
     */
    void flushBuffer()
    {
        this->head = 0;
        this->tail = 0;
    }

    /**
     * @brief 
     * 
     * @param val 
     * @return true 
     * @return false 
     */
    bool pushByte(T val) 
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
    bool pushBytes(T *elmArr,int elmCount)
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
    bool popByte(T *element)
    {
        if (this->getByteCount() != 0)
        {
            *element = this->buffer[this->tail];
            this->tail = (this->tail + 1) % this->maxSize;
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
    bool popBytes(T *elmArr,int elmCount)
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
    bool peekByte(T *element)
    {
        int tailLoc = this->tail;
        if(this->getByteCount() != 0){
            element = this->buffer[tailLoc];
            tailLoc = (tailLoc + 1) % this->maxSize;
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
    bool peekBytes(T *elmArr,int elmCount)
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
     * @brief Get the Byte Count object
     * 
     * @return int 
     */
    int getByteCount(void)
    {
        return ((this->head >= this->tail) ? (this->head - this->tail) : ((CIRCULAR_BUFFER_MAX_SIZE - this->tail) + this->head));
    }

    /**
     * @brief Get the Max Buffer Size object
     * 
     * @return int 
     */
    int getMaxBufferSize(void)
    {
        return this->maxSize;
    }

};

#endif /* _CIRCULAR_BUFFER_H_ */
