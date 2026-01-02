#include "lora.h"
#include "main.h"
#include "comms.h"
#include "stdio.h"

void lora_init(void){
    
}

void lora_transmit(Message_T message){
    Comms_SendMsg(message.Data, sizeof(message.Data));
}

void lora_recieve(void){

}

void lora_standby(void){

}

void lora_getStatus(void){

}

void dataDump(void){
    
}