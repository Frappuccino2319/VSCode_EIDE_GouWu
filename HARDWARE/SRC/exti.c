#include "exti.h"
#include "timer.h"
#include "sys.h"
#include "st178.h"
#include "moto.h"
#include "ui.h"

char cunchu[4]={0,0,0,0};
char z_cha=0,y_cha=0,q_cha=0,h_cha=0;
u16 count_fz=0;
u8 fz_flag=0;

void fzopen()
{
	// cunchu[0] = zuo_sum;
	// cunchu[1] = you_sum;
	// cunchu[2] = qian_sum;
	// cunchu[3] = hou_sum;

	// Init_TIM6(99, 7199);
}

void fzclose()
{
	//TIM_Cmd(TIM6, DISABLE);
}

void Init_TIM6(u16 arr ,u16 psc)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��

	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
	
	 
	//�ж����ȼ�NVIC����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM7�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	
	TIM_Cmd(TIM6, ENABLE);
}

void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
		z_cha=zuo_sum-cunchu[0];
		if(z_cha<0)
			z_cha=-z_cha;
		y_cha=you_sum-cunchu[1];
		if(y_cha<0)
			y_cha=-y_cha;
		q_cha=qian_sum-cunchu[2];
		if(q_cha<0)
			q_cha=-q_cha;
		h_cha=hou_sum-cunchu[3];
		if(h_cha<0)
			h_cha=-h_cha;
		if(q_cha>0||h_cha>0 ||z_cha>0||y_cha>0)
		{
			count_fz=0;
			cunchu[0]=zuo_sum;
			cunchu[1]=you_sum;
			cunchu[2]=qian_sum;
			cunchu[3]=hou_sum;
		}
		else
		{
			count_fz++;
		}
		if(count_fz>=300)
		{
			fz_flag=1;
			stop();
			count_fz=0;
		}
		
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);	
	}

}



