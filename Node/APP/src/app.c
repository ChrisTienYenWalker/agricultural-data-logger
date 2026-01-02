#include "app.h"
#include "comms.h"
#include "main.h"
#include "lora.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "sx126x_driver_version.h"
#include "sx126x.h"
// Change these to match your board
#define LED_GPIO_PORT GPIOC
#define LED_PIN       GPIO_PIN_13

static uint32_t lastToggle = 0;
void App_Init(void)
{
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);
    lora_init();
}

void App_Start(void)
{
    uint32_t now = HAL_GetTick(); 
    
    if ((now - lastToggle)%2500 == 1)  
    {
        Message_T LoraMsg = {
            .Sender = 0,
            .Reciever = 1,
            .Dest = 1,
            .Timestamp = now,
            .Data = "messageLora",
        };

        lora_transmit(LoraMsg);
    }

    if (now - lastToggle >= 5000)  
    {
        lastToggle = now;
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
        char msg[32];
        snprintf(msg, sizeof(msg), "%ld - Time Elapsed seconds\r\n", (now/1000)); 
        Comms_SendMsg( msg, sizeof(msg));
    }
}
