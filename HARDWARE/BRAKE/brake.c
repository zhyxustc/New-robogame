#include "brake.h"


int brake(){
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);  // ��������GPIOE.3����;
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);   //ʹ��GPIOE.4����;//
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);  // ��������GPIOE.5����;
	GPIO_ResetBits(GPIOE,GPIO_Pin_6);   //ʹ��GPIOE.6����;
	GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // ��������GPIOE.7����;
	GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // ��������GPIOE.8����;
	return	0;
}