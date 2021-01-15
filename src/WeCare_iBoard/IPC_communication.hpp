/**
 * @file IPC_communication.hpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2021-01-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _IPC_COMMUNICATION_H_
#define _IPC_COMMUNICATION_H_

void InitialiseIPC_Communication(void);
void Send_IPC_packet(IPC_Packet_t* IPC_packet);
void Receive_IPC_packet();
int GetIPC_RX_ByteCount();
bool GetIPC_RX_HeaderBytes(IPC_Packet_t* IPC_packet);
bool GetIPC_RX_PacketBytes(IPC_Packet_t* IPC_packet);
void RemoveIPC_RX_Bytes(int size);

#endif /* _IPC_COMMUNICATION_H_ */