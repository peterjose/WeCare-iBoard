/**
 * @file IPC_communication.cpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2021-01-03
 * 
 * @copyright Copyright (c) 2021
 * 
 * CODE in reference to the data sheet :
 * https://ww1.microchip.com/downloads/en/devicedoc/atmel-2549-8-bit-avr-microcontroller-atmega640-1280-1281-2560-2561_datasheet.pdf
 * 
 */

// comment the following line to disable the Debug printing over the UART
// #define DEBUG_ENABLE
#include "DebugPrint.hpp"

#include "CircularBuffer.hpp"
#include "CubeModule.hpp"
#include "IPC_PacketCreator.hpp"
#include "config.hpp"

#define F_CPU                       16000000UL
#define BAUD_PRESCALER              (((F_CPU / (BAUDRATE_NETWORK_SERIAL * 16UL))) - 1)

volatile CircularBuffer_t<uint8_t> RX_buffer(RX_BUFFER_SIZE);
volatile CircularBuffer_t<uint8_t> TX_buffer(TX_BUFFER_SIZE);

/**
 * @brief Construct a new ISR object
 * 
 */
ISR(USART1_RX_vect)
{
    uint8_t val = UDR1;
    // Read the USART data register
    RX_buffer.pushByte(val);
}

/**
 * @brief Construct a new ISR object
 * 
 */
ISR(USART1_TX_vect)
{

}

/**
 * @brief Construct a new ISR object
 * 
 */
ISR(USART1_UDRE_vect)
{
    uint8_t val;
    // get data from the circular buffer
	if (TX_buffer.popByte(&val)){
        // Transmit data
        UDR1 = val;
	}
	else{
        cli();
		// Disable the interrupt.
		UCSR1B &= ~(1 << UDRIE1);
        sei();
	}
}


/**
 * @brief Initialise the IPC communication
 * 
 */
void InitialiseIPC_Communication(void)
{
    // Disable interrupts
    cli();
    UBRR1 = BAUD_PRESCALER;                                 // Set the baud rate prescale rate register
    UCSR1B = ((1<<RXEN1)|(1<<TXEN1)|(1 << RXCIE1));         // Enable receiver and transmitter and Rx interrupt
    UCSR1C = ((0<<USBS1)|(1 << UCSZ11)|(1<<UCSZ10));        // Set frame format: 8data, 1 stop bit
    // enable back interrupts
    sei();
}


/**
 * @brief 
 * 
 * @param IPC_packet 
 */
void Send_IPC_packet(IPC_Packet_t* IPC_packet)
{
    int headerSizeLen = ((&(IPC_packet->payloadByteCount) - &(IPC_packet->HeaderByte1))/(sizeof(uint8_t)))+1;
    // to fix issues in the memory allocations
    headerSizeLen *= (headerSizeLen < 0) ? -1 :1; 
    TX_buffer.pushBytes((uint8_t*)&(IPC_packet->HeaderByte1),headerSizeLen);
    TX_buffer.pushBytes((uint8_t*)(IPC_packet)->payload,IPC_packet->payloadByteCount);
    TX_buffer.pushByte(IPC_packet->payload_CRC);
    cli();
    UCSR1B |= (1 << UDRIE1);
    sei();
    DBG_PRINT_LN(F("Send_IPC_packet >> Added to buffer"));
    DBG_PRINT(F("TX buffer size "));
    DBG_PRINT_LN(TX_buffer.getByteCount());
}

void Receive_IPC_packet()
{
    uint8_t val;
    if(RX_buffer.popByte(&val))
    {
        DBG_WRITE(val);
    }
}

/**
 * @brief 
 * 
 * @return int 
 */
int GetIPC_RX_ByteCount()
{
    return RX_buffer.getByteCount();
}

/**
 * @brief 
 * 
 * @param IPC_packet 
 * @return true 
 * @return false 
 */
bool GetIPC_RX_HeaderBytes(IPC_Packet_t* IPC_packet)
{
    int headerSizeLen = ((&(IPC_packet->payloadByteCount) - &(IPC_packet->HeaderByte1))/(sizeof(uint8_t)))+1;
    // to fix issues in the memory allocations
    headerSizeLen *= (headerSizeLen < 0) ? -1 :1; 
    return RX_buffer.peekBytes((uint8_t*)&(IPC_packet->HeaderByte1),headerSizeLen);
}

/**
 * @brief 
 * 
 * @param IPC_packet 
 * @return true 
 * @return false 
 */
bool GetIPC_RX_PacketBytes(IPC_Packet_t* IPC_packet)
{
    int headerSizeLen = ((&(IPC_packet->payloadByteCount) - &(IPC_packet->HeaderByte1))/(sizeof(uint8_t)))+1;
    // to fix issues in the memory allocations
    headerSizeLen *= (headerSizeLen < 0) ? -1 :1; 
    if(RX_buffer.popBytes((uint8_t*)&(IPC_packet->HeaderByte1),headerSizeLen))
    {
        if(RX_buffer.getByteCount() >= IPC_packet->payloadByteCount +1)
        {
            IPC_packet->payload = (uint8_t *)malloc(IPC_packet->payloadByteCount);
            if(IPC_packet->payload != NULL)
            {
                bool flag = false;
                flag = RX_buffer.popBytes((uint8_t*)(IPC_packet->payload),IPC_packet->payloadByteCount);
                return (flag & RX_buffer.popByte((uint8_t*)&(IPC_packet->payload_CRC)));
            }
        }
    }
    return false;
}

/**
 * @brief 
 * 
 * @param size 
 */
void RemoveIPC_RX_Bytes(int size)
{
    uint8_t val = 0;
    if(RX_buffer.getByteCount() >= size){
        RX_buffer.popByte(&val);
    }
}
/* EOF */