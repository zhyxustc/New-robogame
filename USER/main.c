#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "timer.h"

#include "hcsr04.h"//测距
#include "grub.h"//抓取
#include "capstan.h"//主动轮
#include "trace.h"//寻迹
#include "brake.h"//停车
#include "uart6.h"//rfid使用
#include "rfid.h"

int main(void)
{ 
	float distance=0;
	Gpio_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);//蓝牙
  uart6_init(19200);//rfid
  RFID_Init();//rfid	
	Hcsr04Init();//超声波	
  grub_init();//抓手
	TIM4_PWM_Init(20000-1,84-1);	//步进电机 
  //Trace_Init();	
	
  //UMoto_Init();	//主动轮由于电源未到搁置
  //UMoto_Control();
	while(1){
		//printf("ok\n");
		Grab(3);
	}	
}
