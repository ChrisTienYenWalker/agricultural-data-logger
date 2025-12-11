#include "sx126x_hal.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;

// Change these to your actual pins
#define SX126X_NSS_PORT   GPIOA
#define SX126X_NSS_PIN    GPIO_PIN_4

#define SX126X_BUSY_PORT  GPIOB
#define SX126X_BUSY_PIN   GPIO_PIN_3

#define SX126X_RESET_PORT GPIOB
#define SX126X_RESET_PIN  GPIO_PIN_4

static inline void nss_low(void)  { HAL_GPIO_WritePin(SX126X_NSS_PORT, SX126X_NSS_PIN, GPIO_PIN_RESET); }
static inline void nss_high(void) { HAL_GPIO_WritePin(SX126X_NSS_PORT, SX126X_NSS_PIN, GPIO_PIN_SET); }

sx126x_hal_status_t sx126x_hal_read( const void* context,
                                     const uint8_t* command, uint16_t command_length,
                                     uint8_t* data,    uint16_t data_length )
{
    nss_low();
    HAL_SPI_Transmit(&hspi1, (uint8_t*)command, command_length, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi1, data, data_length, HAL_MAX_DELAY);
    nss_high();

    return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_write( const void* context,
                                      const uint8_t* command, uint16_t command_length,
                                      const uint8_t* data,   uint16_t data_length )
{
    nss_low();
    HAL_SPI_Transmit(&hspi1, (uint8_t*)command, command_length, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, (uint8_t*)data,    data_length,   HAL_MAX_DELAY);
    nss_high();

    return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_reset( const void* context )
{
    HAL_GPIO_WritePin(SX126X_RESET_PORT, SX126X_RESET_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(SX126X_RESET_PORT, SX126X_RESET_PIN, GPIO_PIN_SET);
    HAL_Delay(6);
    return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_wakeup( const void* context )
{
    uint8_t c = 0x00;

    nss_low();
    HAL_SPI_Transmit(&hspi1, &c, 1, HAL_MAX_DELAY);
    nss_high();

    HAL_Delay(3);
    return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_wait_on_busy( const void* context, uint32_t timeout_ms )
{
    uint32_t start = HAL_GetTick();

    while (HAL_GPIO_ReadPin(SX126X_BUSY_PORT, SX126X_BUSY_PIN) == GPIO_PIN_SET)
    {
        if ((HAL_GetTick() - start) > timeout_ms)
            return SX126X_HAL_STATUS_ERROR;
    }
    return SX126X_HAL_STATUS_OK;
}
