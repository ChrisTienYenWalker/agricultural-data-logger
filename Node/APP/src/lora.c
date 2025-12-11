#include "lora.h"
#include "main.h"
#include "comms.h"
#include "stdio.h"

void lora_readRegister8(int regAddr, uint8_t *value)
{
    uint8_t cmd = 0x1D;
    uint8_t addr[1] = {regAddr };

    uint8_t reg_value = 0x00;               
    HAL_GPIO_WritePin(CS_Lora_GPIO_Port, CS_Lora_Pin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, addr, 2, HAL_MAX_DELAY);

    HAL_SPI_Receive(&hspi1, &reg_value, 1, HAL_MAX_DELAY);
    
    char msg[32];
    snprintf(msg, sizeof(msg), "LoraReg Read: 0x%04X\r\n", reg_value);
    HAL_UART_Transmit (&huart1,  (uint8_t*)msg, sizeof(msg)-1, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(CS_Lora_GPIO_Port, CS_Lora_Pin, GPIO_PIN_SET);
}

void lora_readRegister16(uint16_t regAddr, uint16_t *value)
{
    uint8_t cmd = 0x1D;
    uint8_t addr[2] = { (uint8_t)(regAddr >> 8), (uint8_t)(regAddr & 0xFF) };
    uint8_t data[2];           
    uint8_t dummy = 0x00;

    // Wait for BUSY pin low if you have one
    //SX_WaitBusy(); 

    HAL_GPIO_WritePin(CS_Lora_GPIO_Port, CS_Lora_Pin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);       
    HAL_SPI_Transmit(&hspi1, addr, 2, HAL_MAX_DELAY);       
    //HAL_SPI_Transmit(&hspi1, &dummy, 1, HAL_MAX_DELAY);     
    HAL_SPI_Receive(&hspi1, data, 2, HAL_MAX_DELAY);        

    HAL_GPIO_WritePin(CS_Lora_GPIO_Port, CS_Lora_Pin, GPIO_PIN_SET);

    // Combine MSB + LSB
    *value = ((uint16_t)data[0] << 8) | data[1];

    // Print for debug
    char msg[32];
    snprintf(msg, sizeof(msg), "LoraReg Read: 0x%04X\r\n", *value);
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, sizeof(msg)-1, HAL_MAX_DELAY);
}

void lora_writeRegister(int regAddr, uint8_t value){
    uint8_t cmd = 0x0D;

    HAL_GPIO_WritePin(CS_Lora_GPIO_Port, CS_Lora_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, &value, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(CS_Lora_GPIO_Port, CS_Lora_Pin, GPIO_PIN_SET);

    //check(uint8_t*)
    lora_readRegister16(regAddr, NULL);
}