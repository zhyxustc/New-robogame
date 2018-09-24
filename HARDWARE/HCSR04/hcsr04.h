#ifndef _HCSR04_H_
#define _HCSR04_H_

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "delay.h"
#include "usart.h"


void Hcsr04Init();
void hcsr04_NVIC();
void TIM5_IRQHandler(void);
u32 GetEchoTimer(void);
float Hcsr04GetLength(void);
float Hcsr04GetLength_2(void);

#endif