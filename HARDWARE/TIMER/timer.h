#ifndef _TIMER_
#define _TIMER_

#include "sys.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"
#include "usart.h"

#include "stm32f4xx_tim.h"
#include "misc.h"
#include "stm32f4xx_rcc.h"

void TIM2_Int_Init(u16 arr,u16 psc);
void TIM5_Int_Init(u16 arr,u16 psc);

#endif