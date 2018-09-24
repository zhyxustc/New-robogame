#include "trace.h"



const u8 UID[2][4][2]={
	0x00,0x01,
	0x00,0x02,
	0x00,0x03,
	0x00,0x04,
	0x00,0x05,
	0x00,0x06,
	0x00,0x07,
	0x00,0x08
}; 
const u8 Parallel[2][2]={1,2,2,1};
u8 Stage1finish=FALSE;
u8 Stage2finish=FALSE;


int t_delta[2]={0},t_in=1;
int	side=0;//�߶�����
u8 dir=1;
u16 t_pwmval[3]={0};//ռ�ձ�
u16 up_pwmval=0;//ռ�ձ�
u16 dir_pwmval[3]={0};//ռ�ձ�
float distance_Data=30;//����
int stop_rot=0;
int bit[11]={0};//0������2��1������1��2�����У�3������1��4������2��5������1��6��ǰ����7��ǰ���У�8��ǰ����

u8 Rotationcheck=No;//�Ƿ���ת




void Trace_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIODʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9 |GPIO_Pin_10  ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	
	TIM2_Int_Init(50-1,8400-1);	//����Ѱ��
}



int Trace_Check(void){
	
	bit[0]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0);
	bit[1]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1);
	bit[2]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2);
	bit[3]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3);
	bit[4]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4);
	bit[5]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5);
	bit[6]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6);
	bit[7]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7);
	bit[8]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8);
	bit[9]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9);
	bit[10]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10);
	
	
	t_delta[0]=(bit[0]+bit[1]-bit[3]-bit[4]);
	t_delta[1]=4*(bit[5]+bit[8]*2-bit[6]-bit[10]*2);
	
	//printf("%d,%d,%d,%d     %d\n",bit[5],bit[8],bit[6],bit[10],t_delta[1]);
	
	if(Rotationcheck==Yes)
	{	
		if(bit[5]*bit[8]==1)
			Rotation(1);
		if(bit[1]*bit[3]==1)
			Rotation(0);
	}
	return 0;
}


int Direction(void){
	if(side==1){//����
		GPIO_SetBits(GPIOE,GPIO_Pin_3);  // ��������GPIOE.3����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_4);   //ʹ��GPIOE.4����;//
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);  // ��������GPIOE.5����;
		GPIO_SetBits(GPIOE,GPIO_Pin_6);   //ʹ��GPIOE.6����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // ��������GPIOE.7����;
		GPIO_SetBits(GPIOE,GPIO_Pin_8);  // ��������GPIOE.8����;
	}
	else if(side==2){//����
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);  // ��������GPIOE.3����;
		GPIO_SetBits(GPIOE,GPIO_Pin_4);   //ʹ��GPIOE.4����;//
		GPIO_SetBits(GPIOE,GPIO_Pin_5);  // ��������GPIOE.5����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);   //ʹ��GPIOE.6����;
		GPIO_SetBits(GPIOE,GPIO_Pin_7);  // ��������GPIOE.7����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // ��������GPIOE.8����;
	}
	else if(side==3){//ǰ��
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);  // ��������GPIOE.3����;
		GPIO_SetBits(GPIOE,GPIO_Pin_4);   //ʹ��GPIOE.4����;//
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);  // ��������GPIOE.5����;
		GPIO_SetBits(GPIOE,GPIO_Pin_6);   //ʹ��GPIOE.6����;
		//ǰ���������������
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // ��������GPIOE.7����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // ��������GPIOE.8����;	
	}		
	else if(side==4){//����
		GPIO_SetBits(GPIOE,GPIO_Pin_3);  // ��������GPIOE.3����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_4);   //ʹ��GPIOE.4����;//
		GPIO_SetBits(GPIOE,GPIO_Pin_5);  // ��������GPIOE.5����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);   //ʹ��GPIOE.6����;
		//ǰ���������������
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // ��������GPIOE.7����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // ��������GPIOE.8����;	
	}			
	return 1;
}

int TMoto_Control(void){
	/**������ͨ��ֱ�Ӳ����⺯���ķ�ʽʵ�ֳ��ֿ��ƣ�E3��4��t_pwmval[0]����ǰ���֣�E5��6��t_pwmval[1]����ǰ����**/	
/*	if(distance_Data<=20){
		t_pwmval[0]=0;
		t_pwmval[1]=0;
		t_pwmval[2]=0;
	}*/
	if((side==FORWARD)||(side==BACKWARD)){		
    t_pwmval[0]=10+t_delta[0]*3;	
		t_pwmval[1]=10-t_delta[0]*3;
		t_pwmval[2]=10;
	}
	else{
    t_pwmval[0]=10+t_delta[1]*1;	
    t_pwmval[1]=10-t_delta[1]*1;	
    t_pwmval[2]=20;			
	}

	TIM_SetCompare1(TIM4,100*200-t_pwmval[0]*200);
	TIM_SetCompare2(TIM4,100*200-t_pwmval[1]*200);
	TIM_SetCompare3(TIM4,100*200-t_pwmval[2]*200);
	return 0;
}


int Rotation(int rot){
	static int flag=0;
	if(rot==1&&flag==0){
		brake();
		delay_ms(5000);
		
		GPIO_SetBits(GPIOE,GPIO_Pin_3);  // ��������GPIOE.3����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_4);   //ʹ��GPIOE.4����;//
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);  // ��������GPIOE.5����;
		GPIO_SetBits(GPIOE,GPIO_Pin_6);   //ʹ��GPIOE.6����;
		GPIO_SetBits(GPIOE,GPIO_Pin_7);  // ��������GPIOE.7����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // ��������GPIOE.8����;
		t_delta[0]=0;
		flag=1;
		TMoto_Control();
		delay_ms(1000);
	}
	else if(rot==2&&flag==0){
		brake();
		delay_ms(5000);
		
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);  // ��������GPIOE.3����;
		GPIO_SetBits(GPIOE,GPIO_Pin_4);   //ʹ��GPIOE.4����;//
		GPIO_SetBits(GPIOE,GPIO_Pin_5);  // ��������GPIOE.5����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);   //ʹ��GPIOE.6����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // ��������GPIOE.7����;
		GPIO_SetBits(GPIOE,GPIO_Pin_8);  // ��������GPIOE.8����;

		t_delta[0]=0;
		flag=1;
	}
	else if(rot==0&&flag==1){
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);  // ��������GPIOE.3����;
		GPIO_SetBits(GPIOE,GPIO_Pin_4);   //ʹ��GPIOE.4����;//
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);  // ��������GPIOE.5����;
		GPIO_SetBits(GPIOE,GPIO_Pin_6);   //ʹ��GPIOE.6����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // ��������GPIOE.7����;
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // ��������GPIOE.8����;	

	}		
	return 0;
}





void forward(int turnto, u8 ifrotationcheck)
{//���߷���,��ת��⣬�������
	side=turnto;
	Rotationcheck=ifrotationcheck;
	Direction();
	Trace_Check();
	TMoto_Control();	
}

u8 Requirecheck(u8 rfiduid)
{//�������
	float distance=0;
	u8 uid[8]={0};	
  
	GET_UID(uid);
  distance=Hcsr04GetLength();	
	if(distance<=0.1)
	{
		if((uid[0]==UID[FLAGKIND][rfiduid][0])&&(uid[1]==UID[FLAGKIND][rfiduid][1]))
		{
			return Yes;
		}
		else{
			return No;
		}
	}
	return XXX;
}



//��ʱ��2�жϷ�����
void TIM2_IRQHandler(void){
	static u8 stage=SEARCH1;
	static u8 step=ZERO;
	static u8 rfiduid=ZERO;//ѡ����rfid	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
		if(stage==SEARCH1)
		{
			if(step==ZERO)
			{//ֱ��+���
				u8 check10;
				forward(FORWARD,No);					
				check10=Requirecheck(rfiduid);		
				if(check10==Yes)
				{
			    Take_Put(GRUB);					
					rfiduid=ONE;
					step=ONE;			
				}
			  else if(check10==No){
					step=ONE;
				}
			}
			if(step==ONE)
			{//����+���
				u8 check11;
				forward(Parallel[Position][RIGHT],No);					
				check11=Requirecheck(rfiduid);		
				if(check11==Yes)
				{
					Take_Put(GRUB);
					rfiduid=rfiduid+1;
					if(rfiduid==TWO)
					{
						step=THREE;
					}
					else{
						step=TWO;
					}
				}
			}
			
			if(step==THREE)
			{//����+˳ʱ����ת
				u8 check13;
				forward(BACKWARD,Yes);
				if(Stage1finish==SUCCESS)
				{
					stage=PLACE1;
					step=ZERO;
				}
			}
		}
		
		if(stage==PLACE1)
		{
			if(step==ZERO)
			{//ǰ��+������
				u8 check20;
				forward(FORWARD,No);
				check20=Requirecheck(rfiduid);
				if(check20==No)
				{
				  Take_Put(PUT);	
					step=ONE;
				}				
			}
			if(step==ONE)
			{//����+������
				u8 check21;
				forward(Parallel[Position][LEFT],No);					
				check21=Requirecheck(rfiduid);		
				if(check21==No)
				{
					step=TWO;
				}						
			}
			if(step==TWO)
			{//����+��ʱ����ת
				forward(BACKWARD,Yes);
				if(Stage2finish==SUCCESS)
				{
					stage=SEARCH2;
					step=ZERO;
				}
			}
		}
		if(stage==SEARCH2)
		{
			if(step==ZERO)
			{//ֱ��+���
				u8 check30;
				forward(FORWARD,No);					
				check30=Requirecheck(rfiduid);		
				if(check30==Yes)
				{
			    Take_Put(GRUB);					
					rfiduid=THREE;
					step=ONE;			
				}
			  else if(check30==No){
					step=ONE;
				}
			}
			if(step==ONE)
			{//����+���
				u8 check31;
				forward(Parallel[Position][LEFT],No);					
				check31=Requirecheck(rfiduid);		
				if(check31==Yes)
				{
					Take_Put(GRUB);
					rfiduid=rfiduid+1;
					if(rfiduid==FOUR)
					{
						step=TWO;
					}
					else{
						step=ONE;
					}
				}				
			}
			if(step==TWO)
			{//����+��ʱ����ת
				forward(BACKWARD,Yes);
				if(Stage2finish==SUCCESS)
				{
					stage=PLACE2;
					step=ZERO;
				}
			}
		}
		if(stage==PLACE2)//����������û�в��Թ������Ե�����Ϊֹ��
		{
			
		}		
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־λ
}
