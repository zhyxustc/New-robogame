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
int	side=0;//走动方向
u8 dir=1;
u16 t_pwmval[3]={0};//占空比
u16 up_pwmval=0;//占空比
u16 dir_pwmval[3]={0};//占空比
float distance_Data=30;//距离
int stop_rot=0;
int bit[11]={0};//0、后左2；1、后左1；2、后中；3、后右1；4、后右2；5、后右1；6、前左左；7、前左中；8、前左右

u8 Rotationcheck=No;//是否旋转




void Trace_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOD时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9 |GPIO_Pin_10  ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	
	TIM2_Int_Init(50-1,8400-1);	//控制寻迹
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
	if(side==1){//左走
		GPIO_SetBits(GPIOE,GPIO_Pin_3);  // 方向引脚GPIOE.3拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_4);   //使能GPIOE.4拉低;//
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);  // 方向引脚GPIOE.5拉高;
		GPIO_SetBits(GPIOE,GPIO_Pin_6);   //使能GPIOE.6拉低;
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // 方向引脚GPIOE.7拉高;
		GPIO_SetBits(GPIOE,GPIO_Pin_8);  // 方向引脚GPIOE.8拉高;
	}
	else if(side==2){//右走
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);  // 方向引脚GPIOE.3拉高;
		GPIO_SetBits(GPIOE,GPIO_Pin_4);   //使能GPIOE.4拉低;//
		GPIO_SetBits(GPIOE,GPIO_Pin_5);  // 方向引脚GPIOE.5拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);   //使能GPIOE.6拉低;
		GPIO_SetBits(GPIOE,GPIO_Pin_7);  // 方向引脚GPIOE.7拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // 方向引脚GPIOE.8拉高;
	}
	else if(side==3){//前进
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);  // 方向引脚GPIOE.3拉高;
		GPIO_SetBits(GPIOE,GPIO_Pin_4);   //使能GPIOE.4拉低;//
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);  // 方向引脚GPIOE.5拉高;
		GPIO_SetBits(GPIOE,GPIO_Pin_6);   //使能GPIOE.6拉低;
		//前面是左右两个电机
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // 方向引脚GPIOE.7拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // 方向引脚GPIOE.8拉高;	
	}		
	else if(side==4){//后退
		GPIO_SetBits(GPIOE,GPIO_Pin_3);  // 方向引脚GPIOE.3拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_4);   //使能GPIOE.4拉低;//
		GPIO_SetBits(GPIOE,GPIO_Pin_5);  // 方向引脚GPIOE.5拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);   //使能GPIOE.6拉低;
		//前面是左右两个电机
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // 方向引脚GPIOE.7拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // 方向引脚GPIOE.8拉高;	
	}			
	return 1;
}

int TMoto_Control(void){
	/**下面是通过直接操作库函数的方式实现车轮控制，E3、4、t_pwmval[0]控制前左轮：E5、6、t_pwmval[1]控制前右轮**/	
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
		
		GPIO_SetBits(GPIOE,GPIO_Pin_3);  // 方向引脚GPIOE.3拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_4);   //使能GPIOE.4拉低;//
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);  // 方向引脚GPIOE.5拉高;
		GPIO_SetBits(GPIOE,GPIO_Pin_6);   //使能GPIOE.6拉低;
		GPIO_SetBits(GPIOE,GPIO_Pin_7);  // 方向引脚GPIOE.7拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // 方向引脚GPIOE.8拉高;
		t_delta[0]=0;
		flag=1;
		TMoto_Control();
		delay_ms(1000);
	}
	else if(rot==2&&flag==0){
		brake();
		delay_ms(5000);
		
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);  // 方向引脚GPIOE.3拉高;
		GPIO_SetBits(GPIOE,GPIO_Pin_4);   //使能GPIOE.4拉低;//
		GPIO_SetBits(GPIOE,GPIO_Pin_5);  // 方向引脚GPIOE.5拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);   //使能GPIOE.6拉低;
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // 方向引脚GPIOE.7拉高;
		GPIO_SetBits(GPIOE,GPIO_Pin_8);  // 方向引脚GPIOE.8拉高;

		t_delta[0]=0;
		flag=1;
	}
	else if(rot==0&&flag==1){
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);  // 方向引脚GPIOE.3拉高;
		GPIO_SetBits(GPIOE,GPIO_Pin_4);   //使能GPIOE.4拉低;//
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);  // 方向引脚GPIOE.5拉高;
		GPIO_SetBits(GPIOE,GPIO_Pin_6);   //使能GPIOE.6拉低;
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);  // 方向引脚GPIOE.7拉高;
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);  // 方向引脚GPIOE.8拉高;	

	}		
	return 0;
}





void forward(int turnto, u8 ifrotationcheck)
{//行走方向,旋转检测，电机控制
	side=turnto;
	Rotationcheck=ifrotationcheck;
	Direction();
	Trace_Check();
	TMoto_Control();	
}

u8 Requirecheck(u8 rfiduid)
{//条件检测
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



//定时器2中断服务函数
void TIM2_IRQHandler(void){
	static u8 stage=SEARCH1;
	static u8 step=ZERO;
	static u8 rfiduid=ZERO;//选定的rfid	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
		if(stage==SEARCH1)
		{
			if(step==ZERO)
			{//直行+检测
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
			{//右行+检测
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
			{//后退+顺时针旋转
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
			{//前进+检测距离
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
			{//左行+检测距离
				u8 check21;
				forward(Parallel[Position][LEFT],No);					
				check21=Requirecheck(rfiduid);		
				if(check21==No)
				{
					step=TWO;
				}						
			}
			if(step==TWO)
			{//后退+逆时针旋转
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
			{//直行+检测
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
			{//左行+检测
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
			{//后退+逆时针旋转
				forward(BACKWARD,Yes);
				if(Stage2finish==SUCCESS)
				{
					stage=PLACE2;
					step=ZERO;
				}
			}
		}
		if(stage==PLACE2)//由于主动轮没有测试过，所以到这里为止了
		{
			
		}		
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}
