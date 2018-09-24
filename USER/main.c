#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "timer.h"

#include "hcsr04.h"//����
#include "grub.h"//ץȡ
#include "capstan.h"//������
#include "trace.h"//Ѱ��
#include "brake.h"//ͣ��
#include "uart6.h"//rfidʹ��
#include "rfid.h"

int main(void)
{
	float distance=0;
	Gpio_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);//����
  uart6_init(19200);//rfid
  RFID_Init();//rfid
	Hcsr04Init();//������
  grub_init();//ץ��
	TIM4_PWM_Init(20000-1,84-1);	//��������
  //Trace_Init();

  //UMoto_Init();	//���������ڵ�Դδ������
  //UMoto_Control();
	while(1){
		printf(" Hello,World\n");
		printf("Why?\n");
		printf("new\n");
		Grab(3);//���뷽ʽע��һ��
	}
}
