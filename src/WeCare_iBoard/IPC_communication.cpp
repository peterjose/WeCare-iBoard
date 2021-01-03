/**
 * @file IPC_communication.cpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2021-01-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "CircularBuffer.hpp"
#include "config.hpp"

volatile CircularBuffer_t RX_buffer(RX_BUFFER_SIZE);
volatile CircularBuffer_t TX_buffer(TX_BUFFER_SIZE);

void Rx_ISR_handler()
{
    // TODO: store the data from the RX Data register to the circular buffer
    uint8_t val;
    RX_buffer.pushByte(val);
}

void InitialiseIPC_Communication()
{
    // TODO: Intialise the UART and interrupts for the same
}



/* EOF */