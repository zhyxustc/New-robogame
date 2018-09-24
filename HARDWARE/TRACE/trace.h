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
//左右场地

#define Position LEFT_LAND
//左场地

#define RED  0
#define Li   1

#define FLAGKIND RED
//红专还是理实


#define SEARCH1  0
#define PLACE1   1
#define SEARCH2  2
#define PLACE2   3
//搜索过程

#define FORWARD 4
#define BACKWARD 3
#define LEFT 0
#define RIGHT 1
//前进后退，左走右走

#define ZERO  0
#define ONE   1
#define TWO   2
#define THREE  3
#define FOUR   4

//抓取旗帜数目

#define SUCCESS 1
#define FALSE 0

//阶段完成情况判定


#define  No   0
#define  Yes  1
#define  XXX  -1
//是否检测到RFID标志


#define GRUB  1
#define PUT   0
//抓取还是放下

#define LEFT_HAND 0
#define RIGHT_HAND 1
//左手还是右手





void Trace_Init(void);
int TMoto_Control(void);//控制底部轮子运动
int Trace_Check(void);//寻迹
int Rotation(int rot);//根据测到的数据转动90度
int Direction(void);//左走还是右走


#endif
