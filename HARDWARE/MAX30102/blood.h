#ifndef _BLOOD_H
#define _BLOOD_H
#include "stm32f10x.h"                  // Device header
#include "MAX30102.h"
#include "algorithm.h"
#include "math.h"
//#include "oled.h"
typedef enum
{
	BLD_NORMAL,		//正常
	BLD_ERROR,		//侦测错误
	
}BloodState;//血液状态

typedef struct
{
	int 		heart;		//心率数据
	float 			SpO2;			//血氧数据
}BloodData;


void blood_data_translate(void);
void blood_data_update(void);
void heart_blood(void);//显示心率血氧状态
void heart_Loop(void);//显示心率状态
void blood_Loop(void);//显示血氧状态

#endif


