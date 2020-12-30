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
#include "MessageCreator.hpp"

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
void ConnectionTaskRunner()
{
}

/* EOF */