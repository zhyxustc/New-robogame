#ifndef __TRACE_H
#define __TRACE_H

#include "stm32f4xx_gpio.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "brake.h"
#include "pwm.h"
#include "timer.h"
#include "rfid.h"
#include "grub.h"
#include "hcsr04.h"


#define LEFT_LAND 0
#define RIGHT_LAND 1
//���ҳ���

#define Position LEFT_LAND
//�󳡵�

#define RED  0
#define Li   1

#define FLAGKIND RED
//��ר������ʵ


#define SEARCH1  0
#define PLACE1   1
#define SEARCH2  2
#define PLACE2   3
//��������

#define FORWARD 4
#define BACKWARD 3
#define LEFT 0
#define RIGHT 1
//ǰ�����ˣ���������

#define ZERO  0
#define ONE   1
#define TWO   2
#define THREE  3
#define FOUR   4

//ץȡ������Ŀ

#define SUCCESS 1
#define FALSE 0

//�׶��������ж�


#define  No   0
#define  Yes  1
#define  XXX  -1
//�Ƿ��⵽RFID��־


#define GRUB  1
#define PUT   0
//ץȡ���Ƿ���

#define LEFT_HAND 0
#define RIGHT_HAND 1
//���ֻ�������





void Trace_Init(void);
int TMoto_Control(void);//���Ƶײ������˶�
int Trace_Check(void);//Ѱ��
int Rotation(int rot);//���ݲ⵽������ת��90��
int Direction(void);//���߻�������


#endif
