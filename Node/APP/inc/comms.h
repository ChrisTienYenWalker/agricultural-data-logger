#ifndef COMMS_H
#define COMMS_H

#include "stm32f1xx_hal.h"   // Change if you use a different family

void Comms_SendHello(void);
void Comms_SendMsg(char msg[]);

#endif
