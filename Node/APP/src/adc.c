#include "adc.h"
#include "main.h"
#include "comms.h"
extern ADC_HandleTypeDef hadc1;

uint16_t sample_adc(GPIO_TypeDef *port, uint16_t pin){
    // uint32_t sum = 0;

    // for (int i = 0; i < 5; i++)
    // {
    //     HAL_ADC_Start(&hadc1);

    //     if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK)
    //     {
    //         sum += HAL_ADC_GetValue(&hadc1);
    //     }

    //     HAL_ADC_Stop(&hadc1);

    //     HAL_Delay(100);  // 100 ms between samples
    // }

    // return (uint16_t)(sum / 5);
}

uint8_t get_soilTemp(){

    uint8_t result = sample_adc(GPIOA, 1);
    //add proper pin to sample from 

    //write conversion here
    uint8_t conversion = result;

    return conversion; 
}