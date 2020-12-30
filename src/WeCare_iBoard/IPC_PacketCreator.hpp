/**
 * @file IPC_PacketCreator.hpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _IPC_PACKET_CREATOR_H_
#define _IPC_PACKET_CREATOR_H_

#include "Arduino.h"

#define IPC_HEADER_BYTE1        0xA5
#define IPC_HEADER_BYTE2        0xEE
#define IPC_HEADER_BYTE3        0x5A

typedef struct IPC_Packet
{
    uint8_t HeaderByte1;
    uint8_t HeaderByte2;
    uint8_t HeaderByte3;
    uint8_t payloadByteCount;
    uint8_t *payload;
    uint8_t payload_CRC;
}IPC_Packet_t;

void InitialiseIPC_PacketCreator(int pixelCount);
void PacketCreator(CubeModule_t interactiveBoard[], int pixelCount);
void PacketParser(CubeModule_t interactiveBoard[], int pixelCount);

#endif /* _IPC_PACKET_CREATOR_H_ */