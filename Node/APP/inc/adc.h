#ifndef ADC_H
#define ADC_H

#include "stm32f1xx_hal.h"   

uint16_t sample_adc(GPIO_TypeDef *port, uint16_t pin);
uint8_t get_soilTemp(void);


#endif