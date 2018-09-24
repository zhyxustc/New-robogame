#ifndef __USART6_H
#define __USART6_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h"



#define USART6_REC_LEN      200

extern u8 USART6_RX_BUF[USART6_REC_LEN];
extern u16 USART6_RX_STA;

void uart6_init(u32 bound);

#endif