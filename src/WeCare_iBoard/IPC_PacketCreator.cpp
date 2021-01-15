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

// comment the following line to disable the Debug printing over the UART
#define DEBUG_ENABLE
#include "DebugPrint.hpp"

#include "CubeModule.hpp"
#include "IPC_PacketCreator.hpp"
#include "IPC_communication.hpp"
#include "MessageCreator.hpp"
#include "TimingConfig.hpp"
#include "SoftTimer.hpp"

IPC_Packet_t IPC_packetOutgoing;
uint8_t *OutgoingMsg;
int headerSizeLen;
uint16_t corruptedByteCount = 0;
bool Incomming_IPC_packetFlag  = false;

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
bool InitialiseIPC_PacketCreator(int pixelCount)
{
    InitialiseMessageModule(pixelCount);
    IPC_packetOutgoing.HeaderByte1 = IPC_HEADER_BYTE1;
    IPC_packetOutgoing.HeaderByte2 = IPC_HEADER_BYTE2;
    IPC_packetOutgoing.HeaderByte3 = IPC_HEADER_BYTE3;
    IPC_packetOutgoing.packetNumber = INITIAL_PACKET_NO;
    headerSizeLen = ((&(IPC_packetOutgoing.payloadByteCount) - &(IPC_packetOutgoing.HeaderByte1))
                            /(sizeof(uint8_t)))+1;
    OutgoingMsg = (uint8_t *)malloc(GetMessageLength());
    SetSoftTimer(IPC_PACKET_TIMEOUT_TIMER,IPC_PACKET_TIMEOUT_PERIOD);
    if(OutgoingMsg != NULL)
    {
        DBG_PRINT_LN(F("InitialiseIPC_PacketCreator >> Initialised"));
        return true;
    }
    DBG_PRINT_LN(F("InitialiseIPC_PacketCreator >> Initialisation Failed"));
    return false;
    
}

/**
 * @brief 
 * 
 */
void DeinitialiseIPC_PacketCreator(void)
{
    free(OutgoingMsg);
    DBG_PRINT_LN(F("DeinitialiseIPC_PacketCreator >> Done"));
}

static void printCreatedMsg()
{
    for (size_t i = 0; i < GetMessageLength(); i++)
    {
        DBG_PRINT_HEX(OutgoingMsg[i]);
    }
    
}

/**
 * @brief 
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
bool PacketCreator(CubeModule_t interactiveBoard[], int pixelCount)
{
    if (CreateMessage(interactiveBoard, pixelCount, OutgoingMsg))
    {
        DBG_PRINT(F("PacketCreator >> New Pkt created with payload len "));
        DBG_PRINT(GetMessageLength());
        DBG_PRINT(F(" msg as "));
        #ifdef DEBUG_ENABLE
        printCreatedMsg();
        #endif /* DEBUG_ENABLE */
        DBG_PRINT_LN();
        IPC_packetOutgoing.packetNumber = (IPC_packetOutgoing.packetNumber + 1) % MAX_PACKET_NO;
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
void GetOutgoingPacketCreated(IPC_Packet_t** IPC_packet_ref)
{
    *IPC_packet_ref = &IPC_packetOutgoing;
}

/**
 * @brief 
 * 
 * @param interactiveBoard 
 * @param pixelCount 
 */
void PacketParser(CubeModule_t interactiveBoard[], int pixelCount)
{
    if(!Incomming_IPC_packetFlag)
    {
        SetSoftTimer(IPC_PACKET_TIMEOUT_TIMER,IPC_PACKET_TIMEOUT_PERIOD);
    }
    IPC_Packet_t IPC_RX_packet;
    if(GetIPC_RX_ByteCount() > headerSizeLen)
    {
        Incomming_IPC_packetFlag = true;
        if(GetIPC_RX_HeaderBytes(&IPC_RX_packet))
        {
            if((IPC_RX_packet.HeaderByte1 == IPC_HEADER_BYTE1) &&
                (IPC_RX_packet.HeaderByte2 == IPC_HEADER_BYTE2) &&
                (IPC_RX_packet.HeaderByte3 == IPC_HEADER_BYTE3))
            {
                if(!GetSoftTimer(IPC_PACKET_TIMEOUT_TIMER) && 
                GetIPC_RX_ByteCount() < (headerSizeLen + IPC_RX_packet.payloadByteCount +1) )
                {
                    corruptedByteCount++;
                    RemoveIPC_RX_Bytes(1);
                    Incomming_IPC_packetFlag = false;
                    DBG_PRINT_LN(F("PacketParser >> Pkt time out"));
                    return;
                }
                if(GetIPC_RX_ByteCount() >= (headerSizeLen + IPC_RX_packet.payloadByteCount +1)){
                    IPC_RX_packet.payload = NULL;
                    if(GetIPC_RX_PacketBytes(&IPC_RX_packet))
                    {
                        if(getCRC(IPC_RX_packet.payload,IPC_RX_packet.payloadByteCount) == IPC_RX_packet.payload_CRC)
                        {
                            ParseMessage(interactiveBoard,pixelCount,IPC_RX_packet.payload,IPC_RX_packet.payloadByteCount);
                            DBG_PRINT(F("PacketParser >> PKT parsed is "));
                            DBG_PRINT_LN(IPC_RX_packet.packetNumber);
                        }
                        else
                        {
                            DBG_PRINT_LN(F("PacketParser >> CRC error"));
                        }
                        
                    }
                    if(IPC_RX_packet.payload != NULL)
                    {
                        free(IPC_RX_packet.payload);
                    }
                    Incomming_IPC_packetFlag = false;
                }
            }
            else
            {
                corruptedByteCount++;
                RemoveIPC_RX_Bytes(1);
                Incomming_IPC_packetFlag = false;
                DBG_PRINT_LN(F("PacketParser >> Pkt Corrupted"));
            }       
        }  
    }
}


/* EOF */