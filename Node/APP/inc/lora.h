#ifndef LORA_H
#define LORA_H

#include "stm32f1xx_hal.h"   // or your device family

typedef struct 
{
    uint8_t Sender;
    uint8_t Reciever;
    uint8_t Dest;
    uint32_t Timestamp;
    char Data[20];
}Message_T;

void lora_init(void);
void lora_transmit(Message_T message);
void lora_recieve(void);
void lora_standby(void);
void lora_getStatus(void);
void dataDump(void);



#endif