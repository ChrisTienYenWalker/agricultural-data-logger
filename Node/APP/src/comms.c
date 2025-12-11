#include "comms.h"
#include "main.h"
#include "stm32f1xx_hal_uart.h"

void Comms_SendHello(void)
{

    const char msg[] = "Hello World\r\n";
    HAL_UART_Transmit (&huart1, (uint8_t*)msg, sizeof(msg)-1, HAL_MAX_DELAY);
}

void Comms_SendMsg(char msg[])
{
    HAL_UART_Transmit (&huart1, (uint8_t*)msg, sizeof(msg)-1, HAL_MAX_DELAY);
}

