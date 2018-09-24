#ifndef _GRUB_H
#define _GRUB_H


#include "sys.h"
#include "delay.h"
#include "pwm.h"
#include "led.h"

void grub_init();
int Grab(int flag);
int Take_Put(int k);
int StepMoto_Control(int v);

#endif