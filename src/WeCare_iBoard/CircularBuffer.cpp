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

// /**
//  * @brief 
//  * 
//  * @param val 
//  * @return true 
//  * @return false 
//  */
// template<typename T>
// bool CircularBuffer_t<T>::pushByte(T val) 
// {
//     if (this->getByteCount() != this->maxSize)
//     {
//         this->buffer[head] = val;
//         head = (head + 1) % this->maxSize;
//         return true;
//     }
//     return false;
// }

// /**
//  * @brief 
//  * 
//  * @param elmArr 
//  * @param elmCount 
//  * @return true 
//  * @return false 
//  */
// template<typename T>
// bool CircularBuffer_t<T>::pushBytes(T *elmArr,int elmCount)
// {
//     if (this->maxSize - this->getByteCount() >= elmCount)
//     {
//         for(int i =0; i < elmCount;i++)
//         {
//             this->buffer[this->head] = elmArr[i];
//             this->head = (this->head + 1) % this->maxSize;
//         }
//         return true;
//     }
//     return false;
// }

// /**
//  * @brief 
//  * 
//  * @param elmArr 
//  * @param elmCount 
//  * @return true 
//  * @return false 
//  */
// template<typename T>
// bool CircularBuffer_t<T>::popBytes(T *elmArr,int elmCount)
// {
//     if (this->getByteCount() >= elmCount)
//     {
//         for(int i =0; i < elmCount;i++)
//         {
//             elmArr[i] = this->buffer[this->tail];
//             this->tail = (this->tail + 1) % this->maxSize;
//         }
//         return true;
//     }
//     return false;
// }

// /**
//  * @brief 
//  * 
//  * @param elmArr 
//  * @param elmCount 
//  * @return true 
//  * @return false 
//  */
// template<typename T>
// bool CircularBuffer_t<T>::peekBytes(T *elmArr,int elmCount)
// {
//     int tailLoc = this->tail;
//     if (this->getByteCount() >= elmCount)
//     {
//         for(int i =0; i < elmCount;i++)
//         {
//             elmArr[i] = this->buffer[tailLoc];
//             tailLoc = (tailLoc + 1) % this->maxSize;
//         }
//         return true;
//     }
//     return false;
// }

// /**
//  * @brief 
//  * 
//  * @return int 
//  */
// template<typename T>
// inline int CircularBuffer_t<T>::getByteCount(void)
// {
//     return ((this->head >= this->tail) ? (this->head - this->tail) : ((CIRCULAR_BUFFER_MAX_SIZE - this->tail) + this->head + 1));
// }

// /**
//  * @brief 
//  * 
//  * @return int 
//  */
// template<typename T>
// inline int CircularBuffer_t<T>::getMaxBufferSize(void)
// {
//     return this->maxSize;
// }


/* EOF */