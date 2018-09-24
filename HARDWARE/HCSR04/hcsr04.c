#include "hcsr04.h"

#define HCSR04_PORT GPIOA
#define HCSR04_CLK  RCC_AHB1Periph_GPIOA
#define HCSR04_TRIG GPIO_Pin_1
#define HCSR04_ECHO GPIO_Pin_0

#define TRIG_Send PAout(1)
#define ECHO_Reci PAin(0)

u16 msHcCount=0;

//TIM5&&TIM9

void Hcsr04Init()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;    
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(HCSR04_CLK, ENABLE);
	//echo
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//trig
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
	TIM_DeInit(TIM5);
  TIM_TimeBaseStructure.TIM_Period = 5000-1; 	//自动重装载值
	TIM_TimeBaseStructure.TIM_Prescaler=8400-1;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//初始化TIM3
	TIM_ClearFlag(TIM5,TIM_FLAG_Update);
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	
	hcsr04_NVIC();
	
	TIM_Cmd(TIM5,ENABLE); //使能定时器5
}

void hcsr04_NVIC()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;             //
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //
  NVIC_Init(&NVIC_InitStructure);
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
		msHcCount++;
	}
}

static void OpenTimerForHc()        //
{
	TIM_SetCounter(TIM5,0);
	msHcCount=0;
	TIM_Cmd(TIM5,ENABLE);
}
 
static void CloseTimerForHc()        //
{
	TIM_Cmd(TIM5,DISABLE);
}

u32 GetEchoTimer(void)
{
	u32 t=0;
	t=msHcCount*1000;
	t+=TIM_GetCounter(TIM5);
	TIM5->CNT=0;
	delay_ms(50);
	return t;
}

float Hcsr04GetLength(void )
{
	u32 t=0;
	int i=0;
	float lengthTemp=0;
	float sum=0;
	while(i!=5)
	{
		TRIG_Send=1;
		delay_us(20);
		TRIG_Send=0;
		while(ECHO_Reci==0);
		OpenTimerForHc();
		while(ECHO_Reci==1);
		CloseTimerForHc();
		t=GetEchoTimer();
		lengthTemp=((float)t/58.0);
		sum=lengthTemp+sum;
		i=i+1;
	}
	lengthTemp=sum/5;
	return lengthTemp;
}

