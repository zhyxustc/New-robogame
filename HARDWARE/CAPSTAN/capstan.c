#include "capstan.h"


//PE11,12,13,14
//TIM12 PB14,PB15
void UMoto_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  //�����GPIOE��ʼ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14);//GPIOE9,E10���øߣ�����
	
	TIM12_PWM_Init(20000-1,84-1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.
}



int UMoto_Control(void){
	
	float up_pwmval;
	
	GPIO_SetBits(GPIOE,GPIO_Pin_11 |GPIO_Pin_13	);  // ��������GPIOE.1\2����;
	delay_ms(2000);//
	
	up_pwmval=100;

	TIM_SetCompare1(TIM12,100*200-up_pwmval*200);	//�޸ıȽ�ֵ���޸�ռ�ձ�			
	TIM_SetCompare2(TIM12,100*200-up_pwmval*200);//PB14,PB15

	return 0;
}