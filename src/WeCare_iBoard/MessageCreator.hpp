/**
 * @file MessageCreator.hpp
 * @author Team Hugo
 * @brief 
 * @version 0.1
 * @date 2020-12-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _MESSAGE_CREATOR_H_
#define _MESSAGE_CREATOR_H_

void InitialiseMessageModule(int pixelCount);
int GetMessageLength();
bool CreateMessage(CubeModule_t interactiveBoard[], int pixelCount, uint8_t msgPayload[]);
void ParseMessage(CubeModule_t interactiveBoard[], int pixelCount,uint8_t msgPayload[],int size);


#endif /* _MESSAGE_CREATOR_H_ */