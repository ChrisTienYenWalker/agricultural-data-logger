#include "comms.h"
#include "main.h"
#include "stm32f1xx_hal_uart.h"

void Comms_SendMsg(char *msg, uint16_t len)
{
    HAL_UART_Transmit (&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
}

