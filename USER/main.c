#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "timer.h"

#include "hcsr04.h"//
#include "grub.h"//ץȡ
#include "capstan.h"//
#include "trace.h"//
#include "brake.h"//
#include "uart6.h"//rfid
#include "rfid.h"

int main(void)
{
	float distance=0;
	Gpio_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//
	delay_init(168);  //
	uart_init(115200);//
//  uart6_init(19200);//rfid
// RFID_Init();//rfid
	Hcsr04Init();//
	grub_init();//
	TIM4_PWM_Init(20000-1,84-1);	//
  //Trace_Init();

  //UMoto_Init();	//
  //UMoto_Control();
	while(1){
		Take_Put(1);
		distance=Hcsr04GetLength();
		printf("The first is :%f",distance);
		distance=Hcsr04GetLength_2();
		printf("The second is :%f\n",distance);
	}
}
