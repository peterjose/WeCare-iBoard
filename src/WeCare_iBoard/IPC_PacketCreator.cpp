/**
 * @file IPC_PacketCreator.cpp
 * @author Team Hugo
 * @brief Provides necessary information regarding 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "CubeModule.hpp"
#include "IPC_PacketCreator.hpp"
#include "MessageCreator.hpp"

IPC_Packet_t IPC_packetOutgoing;
uint8_t *OutgoingMsg;

/**
 * @brief 
 * 
 * @param data 
 * @param len 
 * @return uint8_t 
 */
static uint8_t getCRC(uint8_t *data, int len)
{
    uint8_t CRC_val = 0;
    if (len != 0)
    {
        CRC_val = data[0];
        for (int i = 1; i < len; i++)
        {
            CRC_val ^= data[i];
        }
    }
    return CRC_val;
}

/**
 * @brief 
 * 
 * @param pixelCount 
 */
void InitialiseIPC_PacketCreator(int pixelCount)
{
    InitialiseMessageModule(pixelCount);
    IPC_packetOutgoing.HeaderByte1 = IPC_HEADER_BYTE1;
    IPC_packetOutgoing.HeaderByte2 = IPC_HEADER_BYTE2;
    IPC_packetOutgoing.HeaderByte3 = IPC_HEADER_BYTE3;
    OutgoingMsg = (uint8_t *)malloc(GetMessageLength());
}

/**
 * @brief 
 * 
 */
void DeinitialiseIPC_PacketCreator(void)
{
    free(OutgoingMsg);
}


/**
 * @brief 
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
bool PacketCreator(CubeModule_t interactiveBoard[], int pixelCount)
{
    char msgStr[GetMessageLength()];
    if (CreateMessage(interactiveBoard, pixelCount, OutgoingMsg))
    {
        IPC_packetOutgoing.payloadByteCount = GetMessageLength();
        IPC_packetOutgoing.payload = OutgoingMsg;
        IPC_packetOutgoing.payload_CRC =getCRC(OutgoingMsg,GetMessageLength());
        return true;
    }
    return false;
}

/**
 * @brief Get the Outgoing Packet Created object
 * 
 * @param IPC_packet_ref 
 */
void GetOutgoingPacketCreated(IPC_Packet_t *IPC_packet_ref)
{
    IPC_packet_ref = &IPC_packetOutgoing;
}

/**
 * @brief 
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void PacketParser(CubeModule_t interactiveBoard[], int pixelCount)
{

}


/* EOF */