#include "capstan.h"


//PE11,12,13,14
//TIM12 PB14,PB15
void UMoto_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  //输出口GPIOE初始化设置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14);//GPIOE9,E10设置高，灯灭
	
	TIM12_PWM_Init(20000-1,84-1);	//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.
}



int UMoto_Control(void){
	
	float up_pwmval;
	
	GPIO_SetBits(GPIOE,GPIO_Pin_11 |GPIO_Pin_13	);  // 方向引脚GPIOE.1\2拉高;
	delay_ms(2000);//
	
	up_pwmval=100;

	TIM_SetCompare1(TIM12,100*200-up_pwmval*200);	//修改比较值，修改占空比			
	TIM_SetCompare2(TIM12,100*200-up_pwmval*200);//PB14,PB15

	return 0;
}