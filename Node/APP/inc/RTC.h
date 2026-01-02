#ifndef RTC_H
#define RTC_H

#include "stm32f1xx_hal.h"  
#include "lora.h"


#define RTC_ADDR_SEC   0x01
#define RTC_ADDR_MIN   0x02
#define RTC_ADDR_HOUR  0x03
#define RTC_ADDR_WDAY  0x04
#define RTC_ADDR_DATE  0x05
#define RTC_ADDR_MON   0x06
#define RTC_ADDR_YEAR  0x07

#define ALM0SEC     0x0C
#define ALM0MIN     0x0D
#define ALM0HOUR    0x0E
#define ALM0WKDAY   0x0F
#define ALM0DATE    0x10
#define ALM0MTH     0x11

#define RTC_CONTROL 0x08


#define TO_BCD(x)  ( ((x/10) << 4) | (x%10) )
#define FROM_BCD(x)  ( ((x >> 4) * 10) + (x & 0x0F) )

void set_RTC(int date, int time);
void read_RTC(void);
void RTC_WriteReg(uint8_t addr, uint8_t data);
void set_RTC_Alarm(uint8_t interval);
uint8_t RTC_ReadReg(uint8_t addr);

#endif