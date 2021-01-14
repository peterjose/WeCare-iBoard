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

#include "CircularBuffer.hpp"
#include "CubeModule.hpp"
#include "IPC_PacketCreator.hpp"
#include "config.hpp"

#define F_CPU                       16000000UL
#define BAUD_PRESCALER              (((F_CPU / (BAUDRATE_NETWORK_SERIAL * 16UL))) - 1)

volatile CircularBuffer_t<uint8_t> RX_buffer(RX_BUFFER_SIZE);
volatile CircularBuffer_t<uint8_t> TX_buffer(TX_BUFFER_SIZE);


ISR(USART1_RX_vect)
{
    uint8_t val = UDR1;
    // Read the USART data register
    RX_buffer.pushByte(val);
}

ISR(USART1_TX_vect)
{

}

ISR(USART1_UDRE_vect)
{
	if (!TX_buffer.getByteCount())
	{
        uint8_t val;
        // get data from the circular buffer
        TX_buffer.popByte(&val);
		// Transmit data
		UDR1 = val;
	}
	else
	{
        cli();
		// Disable the interrupt.
		UCSR1B &= ~(1 << UDRIE1);
        sei();
	}
}

/**
 * @brief 
 * 
 */
void Rx_ISR_handler()
{
    // TODO: store the data from the RX Data register to the circular buffer
    uint8_t val;
    RX_buffer.pushByte(val);
}

/**
 * @brief 
 * 
 */
void InitialiseIPC_Communication()
{
    cli();
    // TODO: Intialise the UART and interrupts for the same
    UBRR1 = BAUD_PRESCALER;                                 // Set the baud rate prescale rate register
    UCSR1B = ((1<<RXEN1)|(1<<TXEN1)|(1 << RXCIE1));         // Enable receiver and transmitter and Rx interrupt
    UCSR1C = ((0<<USBS1)|(1 << UCSZ11)|(1<<UCSZ10));        // Set frame format: 8data, 1 stop bit
    sei();
}

/**
 * @brief 
 * 
 * @param IPC_packet 
 */
void Send_IPC_packet(IPC_Packet_t *IPC_packet)
{
    int headerSizeLen = (&(IPC_packet->HeaderByte1) - &(IPC_packet->payloadByteCount))/(sizeof(uint8_t));
    // to fix issues in the memory allocations
    headerSizeLen *= (headerSizeLen < 0) ? -1 :1; 
    RX_buffer.pushBytes((uint8_t*)IPC_packet,headerSizeLen);
    RX_buffer.pushBytes((uint8_t*)IPC_packet->payload,IPC_packet->payloadByteCount);
    RX_buffer.pushByte(IPC_packet->payload_CRC);
    cli();
    UCSR1B |= (1 << UDRIE1);
    sei();
}

/* EOF */