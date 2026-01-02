#include "RTC.h"
#include "main.h"
#include "comms.h"


/*
set the time for the RTC

date is in format DDMMYYYY
time is in the format HHMMSS
*/
void set_RTC(int date, int time){
    
    // Parse input
    int day   = date / 1000000;
    int month = (date / 10000) % 100;
    int year  = date % 100; // last two digits only
    int hour  = time / 10000;
    int min   = (time / 100) % 100;
    int sec   = time % 100;

    // Convert to BCD
    uint8_t sec_bcd  = TO_BCD(sec) | 0x80;      // ST = bit7 = 1
    uint8_t min_bcd  = TO_BCD(min);
    uint8_t hour_bcd = TO_BCD(hour);            // 24H format → bit6=0 already
    uint8_t date_bcd = TO_BCD(day);
    uint8_t month_bcd= TO_BCD(month);
    uint8_t year_bcd = TO_BCD(year % 100);

    // SPI writes
    RTC_WriteReg(RTC_ADDR_SEC,  sec_bcd);
    RTC_WriteReg(RTC_ADDR_MIN,  min_bcd);
    RTC_WriteReg(RTC_ADDR_HOUR, hour_bcd);
    RTC_WriteReg(RTC_ADDR_DATE, date_bcd);
    RTC_WriteReg(RTC_ADDR_MON,  month_bcd);
    RTC_WriteReg(RTC_ADDR_YEAR, year_bcd);
}

/*
read the time for the RTC

format is HHMMSS
*/
int read_RTC_Time(void)
{
    uint8_t sec_bcd  = RTC_ReadReg(0x01) & 0x7F; // strip ST bit
    uint8_t min_bcd  = RTC_ReadReg(0x02);
    uint8_t hour_bcd = RTC_ReadReg(0x03) & 0x3F; // 24h mode mask

    int sec  = FROM_BCD(sec_bcd);
    int min  = FROM_BCD(min_bcd);
    int hour = FROM_BCD(hour_bcd);

    return (hour * 10000) + (min * 100) + sec; // HHMMSS
}

/*
read the date for the RTC

format is DDMMYYYY
*/
int read_RTC_Date(void)
{
    uint8_t date_bcd = RTC_ReadReg(0x05);
    uint8_t mon_bcd  = RTC_ReadReg(0x06) & 0x1F; // mask LPYR bit
    uint8_t year_bcd = RTC_ReadReg(0x07);

    int day   = FROM_BCD(date_bcd);
    int month = FROM_BCD(mon_bcd);
    int year  = FROM_BCD(year_bcd); // 0-99 only

    return (day * 10000) + (month * 100) + year;  // DDMMYY
}

/*
set the RTC alarm time
format is HHMMSS
*/
void set_RTC_Alarm(uint8_t interval){
    uint8_t hour = (interval / 10000) % 100;
    uint8_t min  = (interval / 100)   % 100;
    uint8_t sec  =  interval          % 100;

    uint8_t reg;

    reg = RTC_ReadReg(RTC_CONTROL);
    reg &= ~(1 << 6);               // SQWEN = 0
    RTC_WriteReg(RTC_CONTROL, reg);

    RTC_WriteReg(ALM0SEC,  TO_BCD(sec));
    RTC_WriteReg(ALM0MIN,  TO_BCD(min));
    RTC_WriteReg(ALM0HOUR, TO_BCD(hour));

    /* Required valid values even if masked */
    RTC_WriteReg(ALM0DATE, TO_BCD(1));
    RTC_WriteReg(ALM0MTH,  TO_BCD(1));

    reg  = (0b111 << 4);             
    reg &= ~(1 << 3);                
    reg |= 0x01;                     
    RTC_WriteReg(ALM0WKDAY, reg);

    //enable alarm
    reg = RTC_ReadReg(RTC_CONTROL);
    reg |= (1 << 4);           // ALM0EN = 1
    RTC_WriteReg(RTC_CONTROL, reg);
}


void RTC_WriteReg(uint8_t addr, uint8_t data)
{
    uint8_t buf[3];
    buf[0] = 0x12; // WRITE opcode
    buf[1] = addr;
    buf[2] = data;

    // HAL_GPIO_WritePin(RTC_CS_GPIO_Port, RTC_CS_Pin, GPIO_PIN_RESET);
    // HAL_SPI_Transmit(&hspi1, buf, 3, HAL_MAX_DELAY);
    // HAL_GPIO_WritePin(RTC_CS_GPIO_Port, RTC_CS_Pin, GPIO_PIN_SET);
}

uint8_t RTC_ReadReg(uint8_t addr)
{
    uint8_t tx[2] = {0x13, addr}; // READ opcode + address
    uint8_t rx[2];

    // HAL_GPIO_WritePin(RTC_CS_GPIO_Port, RTC_CS_Pin, GPIO_PIN_RESET);
    // HAL_SPI_Transmit(&hspi1, tx, 2, HAL_MAX_DELAY);
    // HAL_SPI_Receive(&hspi1, rx, 1, HAL_MAX_DELAY);
    // HAL_GPIO_WritePin(RTC_CS_GPIO_Port, RTC_CS_Pin, GPIO_PIN_SET);

    return rx[0];
}