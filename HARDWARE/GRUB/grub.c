#include "grub.h"





int Grab(int flag){
  float ang_pwmval[4];
	if(flag==0){
		ang_pwmval[0]=3.5;
		ang_pwmval[1]=9.5;//��1
		ang_pwmval[2]=4;
		ang_pwmval[3]=5;
	}//
	if(flag==1)
	{
		ang_pwmval[0]=6.8;
		ang_pwmval[1]=9.5;
		ang_pwmval[2]=6.8;
		ang_pwmval[3]=5;
	}		
	if(flag==2)
	{
		ang_pwmval[0]=6.8;
		ang_pwmval[1]=13;
		ang_pwmval[2]=6.8;
		ang_pwmval[3]=1.5;
	}
	if(flag==3)
	{
    ang_pwmval[0]=4;
		ang_pwmval[1]=13;
		ang_pwmval[2]=4;
		ang_pwmval[3]=1.5;
	}	
	
	TIM_SetCompare1(TIM3,(100-ang_pwmval[0])*200);//ץ��
	delay_us(50);
	TIM_SetCompare2(TIM3,(100-ang_pwmval[1])*200);
	delay_us(50);
	TIM_SetCompare3(TIM3,(100-ang_pwmval[2])*200);//ץ��
	delay_us(50);
	TIM_SetCompare4(TIM3,(100-ang_pwmval[3])*200);
	
	return 0;
}

int Take_Put(int k){
	if(k==1){
		StepMoto_Control(1);
		delay_ms(2000);
		Grab(3);
		delay_ms(2000);
		Grab(0);
		delay_ms(2000);
		Grab(1);
		delay_ms(2000);
		Grab(2);
		delay_ms(2000);
		StepMoto_Control(0);
	}
	else{
		Grab(1);
		delay_ms(2000);
		StepMoto_Control(1);
		delay_ms(2000);
		Grab(0);
		delay_ms(2000);
		Grab(3);
		delay_ms(2000);	
		StepMoto_Control(0);
	}
	return 1;
}


int StepMoto_Control(int v){
	/**������ͨ��ֱ�Ӳ����⺯���ķ�ʽʵ��IO����**/		
	u16 step_pwmval=50;
	if(v==1){	//˳ʱ��
		GPIO_SetBits(GPIOE,GPIO_Pin_9);	
		delay_ms(10);
		
		GPIO_SetBits(GPIOE,GPIO_Pin_10);	//��ʼת��
		delay_ms(4000);
	
		GPIO_ResetBits(GPIOE,GPIO_Pin_10);
	}
	else{//��ʱ��
		GPIO_ResetBits(GPIOE,GPIO_Pin_9);		//��ת
		delay_ms(10);
	
		GPIO_SetBits(GPIOE,GPIO_Pin_10);	//��ʼת��
		delay_ms(4000);
		GPIO_ResetBits(GPIOE,GPIO_Pin_10);
	}
		//StepMoto
	TIM_SetCompare4(TIM4,100*200-step_pwmval*200);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	return 0;
}

void grub_init()
{
	TIM3_PWM_Init(20000-1,84-1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.
}