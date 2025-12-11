#include "app.h"
#include "comms.h"
#include "main.h"
#include "lora.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>
#include "sx126x_driver_version.h"
#include "sx126x.h"
// Change these to match your board
#define LED_GPIO_PORT GPIOC
#define LED_PIN       GPIO_PIN_13

static uint32_t lastToggle = 0;
void App_Init(void)
{
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);
}

void App_Tick(void)
{
    uint32_t now = HAL_GetTick();

 
    if (now - lastToggle >= 1000)  
    {
        lastToggle = now;
        uint8_t value;

        sx126x_status_t status = sx126x_read_register(
            &hspi1,     // your HAL context
            0x0740,         // register address
            &value,         // buffer to store result
            1               // number of bytes to read
        );
        //lora_readRegister16(reg, &value);
        //lora_writeRegister(0x96, 1);
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
        Comms_SendHello();     
    }
}
