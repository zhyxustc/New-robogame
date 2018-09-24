#include "brake.h"


int brake(){
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);  // 方向引脚GPIOE.3拉高;
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);   //使能GPIOE.4拉低;//
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);  // 方向引脚GPIOE.5拉高;
	GPIO_ResetBits(GPIOE,GPIO_Pin_6);   //使能GPIOE.6拉低;
	GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // 方向引脚GPIOE.7拉高;
	GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // 方向引脚GPIOE.8拉高;
	return	0;
}