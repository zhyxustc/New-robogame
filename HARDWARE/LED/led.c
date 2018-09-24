#include "led.h"  



//初始化PE5、6、7、8为输出口.并使能这两个口的时钟		    
//GPIO IO初始化

void Gpio_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  //输出口GPIOE初始化设置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10);//GPIOE9,E10设置高，灯灭
	
}
