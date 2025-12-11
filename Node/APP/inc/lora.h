#ifndef LORA_H
#define LORA_H

#include "stm32f1xx_hal.h"   // or your device family

void lora_init(void);
void lora_writeRegister(int regAddr, uint8_t value);
void lora_readRegister8(int regAddr, uint8_t *value);
void lora_readRegister16(uint16_t regAddr, uint16_t *value);
void lora_transmit(void);
void lora_recieve(void);
void lora_standby(void);
void lora_getStatus(void);


//define preset values for the module

// IRQs and DIOs
#define SetDioIrqParams           
#define SetDioIrqParams_Hex        0x08

#define GetIrqStatus             
#define GetIrqStatus_Hex           0x12

#define ClearIrqStatus            
#define ClearIrqStatus_Hex         0x02

#define SetDIO2AsRfSwitchCtrl     
#define SetDIO2AsRfSwitchCtrl_Hex  0x9D

#define SetDIO3AsTcxoCtrl         
#define SetDIO3AsTcxoCtrl_Hex      0x97

// rf modulation and packets
#define SetRfFrequency            
#define SetRfFrequency_Hex         0x86

#define SetPacketType            
#define SetPacketType_Hex          0x8A

#define GetPacketType            
#define GetPacketType_Hex          0x11

#define SetTxParams               
#define SetTxParams_Hex            0x8E

#define SetModulationParams       
#define SetModulationParams_Hex    0x8B

#define SetPacketParams           
#define SetPacketParams_Hex        0x8C

#define SetCadParams              
#define SetCadParams_Hex           0x88

#define SetBufferBaseAddress      
#define SetBufferBaseAddress_Hex   0x8F

#define SetLoRaSymbNumTimeout     
#define SetLoRaSymbNumTimeout_Hex  0xA0




#endif