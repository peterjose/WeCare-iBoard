/**
 * @file NetworkCommunicationModule.cpp
 * @author Team Hugo
 * @brief Function for handling connection between two boards
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "CubeModule.hpp"
#include "NetworkCommunicationModule.hpp"
#include "IPC_PacketCreator.hpp"
#include "IPC_communication.hpp"

/**
 * @brief 
 * 
 */
void EstablishedInterBoardConnection(int pixelCount)
{
    InitialiseIPC_PacketCreator(pixelCount);
}

/**
 * @brief 
 * 
 */
void ConnectionTaskRunner(CubeModule_t interactiveBoard[], int pixelCount)
{
    if(PacketCreator(interactiveBoard,pixelCount)){
        IPC_Packet_t *IPC_packet_ref;
        GetOutgoingPacketCreated(IPC_packet_ref);
        Send_IPC_packet(IPC_packet_ref);
    }
    PacketParser(interactiveBoard,pixelCount);
}

/* EOF */