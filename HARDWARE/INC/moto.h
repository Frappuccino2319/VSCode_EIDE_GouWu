#ifndef _MOTO_H
#define _MOTO_H

#include "sys.h"
#include "timer.h"
#include "usart.h"
#include "oled.h"
#include "st178.h"
#include "math.h"
#include "delay.h"

#include "gpio.h"
#include "ADC_Config.h"



//#define Distancenub   1024
#define   QIAN      1     
#define   HOU       0
#define   ZUO       3
#define   YOU   	4
//#define   TURN      5
//#define   UTURN     6
//#define   ADJUST    7

//�������ת��־λ
//Ϊ1���� Ϊ0 ��ת


//�ĸ�����pid�ṹ��
struct PID
{
	float kp;
	float ki;
	float kd;

	float det;
	float pre_det;	//ǰһ��������kd΢�ֲ���
	float last_det;

	s16   pwm;
	s16   wei_pwm;
	float set;	  	//���ƶ�����趨ֵ
	float sample; 	//���ƶ���ĵ�ǰ����ֵ
	float err;	   	//���С�ڱ�ֵʱ�����������㷨
}; 

extern float  KP,KI,KD;
extern struct PID Pid_fl;
extern struct PID Pid_fr;
extern struct PID Pid_br;
extern struct PID Pid_bl;
extern int speed;
extern u8 speed_carrage[10];

extern u8 velocity_PID_KP_qh[5];
extern u8 velocity_PID_KD_qh[5];

extern float velocity_KP;
extern float velocity_KI;
extern float velocity_KD;
extern s16 tt;//��ȡǰ���ѭ�������Ǿ����˼���·��

extern s8  aa;
extern u8 ZK;

extern u8 FX;
extern u8 Flag_PingYi;
extern u8 Flag_KaoBian;

void PWM_SET(void);

void DJ_MOVE(u8 t,u8 f,u8 sp,u8 dj_1,u8 dj_2,u8 dj_3,u8 dj_4,u8 YS);
//����ͣ��ǰ������
void DJ_MOVE_KaoBian(u8 t,u8 f,u8 sp);
void DJ_MOVE_YS(u8 t,u8 f,u8 sp,u16 tim);
void DJ_MOVE_ZHUAN(u8 r,u8 f);
u8 BMQ_MOVE(u8 f,u16 d,u8 mod);
//����/��(5/6)   ƽ��ʱ��
void DJ_MOVE_PingYi(u8 f,u8 t);


void stop(void);

void TIM7_BaseTime_Init(u16 arr,u16 psc);

void SentDateTo_usart(int16_t *wareaddr);


#endif

