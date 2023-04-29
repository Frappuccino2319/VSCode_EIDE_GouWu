#include "moto.h"
#include "exti.h"



int ii = 0;
u8 Flag_PingYi=0;

s16 tt;//��ȡǰ���ѭ�������Ǿ����˼���·��
s8  aa;//��ȡ����ѭ��ֵ�����Ƿ�ͣ��׼ȷ

u8 FX = 1;
u32 pwm_time=0;
u16 sum_flag=0;
/*�������ƶ���Ҫ�õ��Ĳ���*/
short int sum_value=0;
u8 pidflag=1;
short int sum_value1=0;
short int sum_value2=0;
short int sum_cha=0;

float KP=9.5;//80
float KI=10;//16
float KD=2;//1

u8 stop_TIM = 1;		//ͣ����־λ
u8 tim7_start=0;		//pid���ڱ�־λ

u8 velocity_PID_KP_qh[5] = {0,55,58,59,91};
u8 velocity_PID_KD_qh[5] = {0,55,69,75,118};

/*----------------------------��������--------------------------*/

u8 g_nInterrupt_Count=0;   //10ms

float velocity_KP=56;
float velocity_KI=0;
float velocity_KD=50;//32

float Encoder_Integral;

struct PID Pid_fl={0,0,0,0,0,0,0,0,0,0,0};
struct PID Pid_fr={0,0,0,0,0,0,0,0,0,0,0};
struct PID Pid_br={0,0,0,0,0,0,0,0,0,0,0};
struct PID Pid_bl={0,0,0,0,0,0,0,0,0,0,0};

int ll_PWM = 0;
int lr_PWM = 0;
int bl_PWM = 0;
int br_PWM = 0;

int speed=0;
u8 speed_carrage[10]={0,25,20,25,25,25,10};

int16_t a_pwm[6];

///*/////////////////////////////////////////

//  FL            FR


//         ��

//  BL            BR

///*/////////////////////////////////////////*/

void stop(void)
{	
	
//	printf("%d\n",pwm_time);

	tim7_start = 0;
	
	tt = 0;
	aa = 0;
	
	pwm_time = 0;
	
	stop_TIM = 0;
	
	Pid_fl.set=0;
	Pid_fr.set=0;	
	Pid_bl.set=0;
	Pid_br.set=0;

	TIM_SetCompare1(TIM8,0);
	TIM_SetCompare2(TIM8,0);
	TIM_SetCompare3(TIM8,0);
	TIM_SetCompare4(TIM8,0);
	
	bxcls();	
	TIM_Cmd(TIM7, DISABLE);
	fzclose();                    //��ײ�ر�
	
	
	
	
}
	
void PWM_PID(struct PID *pid_s)
{
	(*pid_s).det=(*pid_s).set-(*pid_s).sample;
	(*pid_s).pwm=(*pid_s).pwm+(*pid_s).kp*((*pid_s).det-(*pid_s).pre_det)+(*pid_s).ki*(*pid_s).det+(*pid_s).kd*((*pid_s).det-2*(*pid_s).pre_det+(*pid_s).last_det);
	(*pid_s).last_det=(*pid_s).pre_det;
	(*pid_s).pre_det=(*pid_s).det;
	
	if((*pid_s).pwm>=830)
	{
		(*pid_s).pwm=830;
	}
	if((*pid_s).pwm<=-830)
	{
		(*pid_s).pwm=-830; 
	}
}

void XIANFU(struct PID *pid_s)
{
	
	if((*pid_s).pwm>=850)
	{
		(*pid_s).pwm=850;
	}
	if((*pid_s).pwm<=-850)
	{
		(*pid_s).pwm=-850; 
	}
}

int WEI_PID(void)     //΢��PWM����
{
	static float Encoder_Least,Encoder;
	int pwm;
	
	if(BX_FLAGE == 1)   //����flag
		return 0;

	if(FX == 1)
	{
		velocity_KP = velocity_PID_KP_qh[speed];
		velocity_KD = velocity_PID_KD_qh[speed];
		
		Encoder_Least =(qian_sum+0)-0;
		
		chazhi_qh = -chazhi_qh;
		
		if(Encoder_Least>=1||Encoder_Least<-1)
		{
			Encoder *= 0.8;		                                                //===һ�׵�ͨ�˲���       
			Encoder += Encoder_Least*0.2;	                                    //===һ�׵�ͨ�˲���    
		}
		else if(Encoder_Least>=-1 && Encoder_Least<1)
		{
			Encoder = 0;
			Encoder_Integral = 0;
			chazhi_qh = 0;
		}
		pwm = Encoder*velocity_KP+Encoder_Integral*velocity_KI+chazhi_qh*velocity_KD;        //===�ٶȿ���	
		pwm = pwm/20;
		
	}
	else if(0 == FX)
	{
		velocity_KP = velocity_PID_KP_qh[speed];
		velocity_KD = velocity_PID_KD_qh[speed];
		
		Encoder_Least =(0+hou_sum)-0;
		
		chazhi_qh = -chazhi_qh;
		
		if(Encoder_Least>=3||Encoder_Least<=-3)
		{
			Encoder *= 0.8;		                                                //===һ�׵�ͨ�˲���       
			Encoder += Encoder_Least*0.2;	                                    //===һ�׵�ͨ�˲���    
		}
		else if(Encoder_Least>-3 && Encoder_Least<3)
		{
			Encoder = 0;
			Encoder_Integral = 0;
			chazhi_qh = 0;
		}
		pwm = Encoder*velocity_KP+Encoder_Integral*velocity_KI+chazhi_qh*velocity_KD;        //===�ٶȿ���	
		pwm = pwm/20;
	}
	
/*˫���洢���ݡ���������*/
//		a_pwm[0]=hou_sum*100;
//		a_pwm[1]=qian_sum*100;
//		a_pwm[2]=chazhi_qh*100;
//		a_pwm[4]=pwm;

//		SentDateTo_usart(a_pwm);
	
	return pwm;
}


void SentDateTo_usart(int16_t *wareaddr)
{
  	u8 i;
   u8 DB[2]={0x03,0xFC};
   u8 DB1[2]={0XFC,0X03};
  for(i=0;i<2;i++)
  {
			 USART2->DR=DB[i];
		 while((USART2->SR&0x40)==0);	 
  }
			USART2->DR =wareaddr[0];
  	  while((USART2->SR&0x40)==0);
				USART2->DR =wareaddr[0]>>8;
  	  while((USART2->SR&0x40)==0);
				USART2->DR =wareaddr[1];
  	  while((USART2->SR&0x40)==0);
				USART2->DR =wareaddr[1]>>8;
  	  while((USART2->SR&0x40)==0);
	
			USART2->DR =wareaddr[2];
  	  while((USART2->SR&0x40)==0);
				USART2->DR =wareaddr[2]>>8;
  	  while((USART2->SR&0x40)==0);

			USART2->DR =wareaddr[3];
  	  while((USART2->SR&0x40)==0);
				USART2->DR =wareaddr[3]>>8;
  	  while((USART2->SR&0x40)==0);
	
			USART2->DR =wareaddr[4];
  	  while((USART2->SR&0x40)==0);
				USART2->DR =wareaddr[4]>>8;
  	  while((USART2->SR&0x40)==0);
			
						USART2->DR =wareaddr[5];
  	  while((USART2->SR&0x40)==0);
				USART2->DR =wareaddr[5]>>8;
  	  while((USART2->SR&0x40)==0);

   for(i=0;i<2;i++)
  {
			 USART2->DR=DB1[i];
		 while((USART2->SR&0x40)==0);	 
  }

}
void TIM7_BaseTime_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //ʱ��ʹ��

	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
	
	TIM_Cmd(TIM7, ENABLE); 
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM7�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

 //ʹ��TIMx					
	
}

void TIM7_IRQHandler(void)      //��������PID��PWM��ʱ��7�жϺ���
{
	
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{		
		//AD_AnJian();		
		if(tim7_start)
		{
			/*��ȡ�ĸ����ӵ�ʱ��PID�ο�ֵ*/
			Pid_fl.sample =((s16)TIM3->CNT);//5
			Pid_bl.sample =((s16)TIM2->CNT);
			Pid_fr.sample =((s16)TIM5->CNT);
			Pid_br.sample =-((s16)TIM4->CNT);
			if(sum_flag)                    //������ת�����
			{
				sum_value+=Pid_fr.sample;
				sum_value1+=Pid_fl.sample;//
				sum_value2+=Pid_bl.sample;//
				sum_cha=abs(sum_value1)-abs(sum_value2);
			}

            // sprintf(OLED_BUF,"%.0f 	",Pid_bl.sample);//��ʾ
            // LCD_16_HanZi_ASCII(0,6,OLED_BUF);
            // sprintf(OLED_BUF,"%.0f  ",Pid_br.sample);
            // LCD_16_HanZi_ASCII(8,6,OLED_BUF);
            // sprintf(OLED_BUF,"%.0f  ",Pid_fl.sample);
            // LCD_16_HanZi_ASCII(0,4,OLED_BUF);
            // sprintf(OLED_BUF,"%.0f  ",Pid_fr.sample);
            // LCD_16_HanZi_ASCII(8,4,OLED_BUF);

            TIM2->CNT=0;
			TIM3->CNT=0;
			TIM4->CNT=0;
			TIM5->CNT=0;
					

			
//			sprintf(OLED_BUF,"%d  %d  ",aa,speed);
//			LCD_16_HanZi_ASCII(0,4,OLED_BUF);
			
			if(FX == 1)				//ֱ��
			{
				aa = St178_Scanf(1);
				tt = St188_Scanf(1);
				/*�趨�ĸ�����PID�ο�ֵ*/
				Pid_fl.set=speed_carrage[speed]; 
				Pid_bl.set=speed_carrage[speed];
				Pid_fr.set=speed_carrage[speed];
				Pid_br.set=speed_carrage[speed];
				
				
//				sprintf(OLED_BUF,"%.0f 	",Pid_fl.set);
//				LCD_16_HanZi_ASCII(0,4,OLED_BUF);	
//				sprintf(OLED_BUF,"%.0f  ",Pid_fr.set);
//				LCD_16_HanZi_ASCII(8,4,OLED_BUF);				
//				sprintf(OLED_BUF,"%.0f  ",Pid_bl.set);
//				LCD_16_HanZi_ASCII(0,6,OLED_BUF);				
//				sprintf(OLED_BUF,"%.0f  ",Pid_br.set);
//				LCD_16_HanZi_ASCII(8,6,OLED_BUF);	
			/*�����õ�PWM��*/
				Pid_fl.wei_pwm = WEI_PID();
				Pid_bl.wei_pwm = Pid_fl.wei_pwm ;
				Pid_fr.wei_pwm = Pid_fl.wei_pwm ;
				Pid_br.wei_pwm = Pid_fl.wei_pwm ;
				
				PWM_PID(&Pid_fl);
				PWM_PID(&Pid_fr);
				PWM_PID(&Pid_bl);
				PWM_PID(&Pid_br);
				
				if(pidflag)//�Ƿ��ñ�������־λ
				{
					Pid_fl.pwm = Pid_fl.pwm - Pid_fl.wei_pwm;
					Pid_bl.pwm = Pid_bl.pwm - Pid_bl.wei_pwm;
					Pid_fr.pwm = Pid_fr.pwm + Pid_fr.wei_pwm;
					Pid_br.pwm = Pid_br.pwm + Pid_br.wei_pwm;
				}
				else
				{
					Pid_fl.pwm = Pid_fl.pwm - sum_cha*0.1;
					Pid_bl.pwm = Pid_bl.pwm - sum_cha*0.1;
					Pid_fr.pwm = Pid_fr.pwm + sum_cha*0.1;
					Pid_br.pwm = Pid_br.pwm + sum_cha*0.1;
				}


//				sprintf(OLED_BUF,"%d 	",Pid_fl.pwm);
//				LCD_16_HanZi_ASCII(0,4,OLED_BUF);	
//				sprintf(OLED_BUF,"%d  ",Pid_fr.pwm);
//				LCD_16_HanZi_ASCII(8,4,OLED_BUF);				
//				sprintf(OLED_BUF,"%d  ",Pid_bl.pwm);
//				LCD_16_HanZi_ASCII(0,6,OLED_BUF);				
//				sprintf(OLED_BUF,"%d  %d",Pid_br.pwm,speed);
//				LCD_16_HanZi_ASCII(8,6,OLED_BUF);	

//				if(Pid_fl.pwm<0)	Pid_fl.pwm = 0;
//				if(Pid_bl.pwm<0)	Pid_bl.pwm = 0;
//				if(Pid_fr.pwm<0)	Pid_fr.pwm = 0;
//				if(Pid_br.pwm<0)	Pid_br.pwm = 0;

				
			}
			else if(FX == 0)		//����
			{
				aa = St178_Scanf(1);
				tt = St188_Scanf(1);
				Pid_fl.set=-speed_carrage[speed]; 
				Pid_bl.set=-speed_carrage[speed];
				Pid_fr.set=-speed_carrage[speed];
				Pid_br.set=-speed_carrage[speed];
								
				Pid_fl.wei_pwm = WEI_PID();
				Pid_bl.wei_pwm = Pid_fl.wei_pwm ;
				Pid_fr.wei_pwm = Pid_fl.wei_pwm ;
				Pid_br.wei_pwm = Pid_fl.wei_pwm ;

				PWM_PID(&Pid_fl);
				PWM_PID(&Pid_fr);
				PWM_PID(&Pid_bl);
				PWM_PID(&Pid_br);
					
				if(pidflag)
				{
					Pid_fl.pwm = Pid_fl.pwm - Pid_fl.wei_pwm;
					Pid_bl.pwm = Pid_bl.pwm - Pid_bl.wei_pwm;
					Pid_fr.pwm = Pid_fr.pwm + Pid_fr.wei_pwm;
					Pid_br.pwm = Pid_br.pwm + Pid_br.wei_pwm;
				}
				else
				{
					Pid_fl.pwm = Pid_fl.pwm - sum_cha*0.1;
					Pid_bl.pwm = Pid_bl.pwm - sum_cha*0.1;
					Pid_fr.pwm = Pid_fr.pwm + sum_cha*0.1;
					Pid_br.pwm = Pid_br.pwm + sum_cha*0.1;
				}
				
//				if(Pid_fl.pwm>0)	Pid_fl.pwm = 0;
//				if(Pid_bl.pwm>0)	Pid_bl.pwm = 0;
//				if(Pid_fr.pwm>0)	Pid_fr.pwm = 0;
//				if(Pid_br.pwm>0)	Pid_br.pwm = 0;
			}
			else if(FX == 2)		//��ת
			{
				Pid_fl.set=-speed_carrage[speed]; 
				Pid_bl.set=-speed_carrage[speed];
				Pid_fr.set=speed_carrage[speed];
				Pid_br.set=speed_carrage[speed];
			
				Pid_fl.wei_pwm = 0;
				Pid_bl.wei_pwm = 0;
				Pid_fr.wei_pwm = 0;
				Pid_br.wei_pwm = 0;
				
				PWM_PID(&Pid_fl);
				PWM_PID(&Pid_fr);
				PWM_PID(&Pid_bl);
				PWM_PID(&Pid_br);
				
				Pid_fl.pwm = Pid_fl.pwm - Pid_fl.wei_pwm;
				Pid_bl.pwm = Pid_bl.pwm - Pid_bl.wei_pwm;
				Pid_fr.pwm = Pid_fr.pwm + Pid_fr.wei_pwm;
				Pid_br.pwm = Pid_br.pwm + Pid_br.wei_pwm;
			}
			else if(FX == 3)		//��ת
			{
				Pid_fl.set=speed_carrage[speed]; 
				Pid_bl.set=speed_carrage[speed];
				Pid_fr.set=-speed_carrage[speed];
				Pid_br.set=-speed_carrage[speed];
			
				Pid_fl.wei_pwm = 0;
				Pid_bl.wei_pwm = 0;
				Pid_fr.wei_pwm = 0;
				Pid_br.wei_pwm = 0;
				
				PWM_PID(&Pid_fl);
				PWM_PID(&Pid_fr);
				PWM_PID(&Pid_bl);
				PWM_PID(&Pid_br);
				
				Pid_fl.pwm = Pid_fl.pwm - Pid_fl.wei_pwm;
				Pid_bl.pwm = Pid_bl.pwm - Pid_bl.wei_pwm;
				Pid_fr.pwm = Pid_fr.pwm + Pid_fr.wei_pwm;
				Pid_br.pwm = Pid_br.pwm + Pid_br.wei_pwm;
			}
			pwm_time++;
			
			/*��PWM����850ʱ��Ϊ850��С��0ʱΪ0*/
			XIANFU(&Pid_fl);
			XIANFU(&Pid_fr);
			XIANFU(&Pid_bl);
			XIANFU(&Pid_br);
			
			/*
			t8pwm_1ǰ��
			t8pwm_2����
			t8pwm_3����
			t8pwm_4ǰ��
			*/
			if(Pid_fl.pwm>=0){CAR_FL=0;TIM_SetCompare4(TIM8,Pid_fl.pwm);}  //ǰ��   
			else{CAR_FL=1;TIM_SetCompare4(TIM8,-Pid_fl.pwm);}
			if(Pid_fr.pwm>=0){CAR_FR=0;TIM_SetCompare3(TIM8,Pid_fr.pwm);}	 //ǰ��		
			else{CAR_FR=1;TIM_SetCompare3(TIM8,-Pid_fr.pwm);}
			if(Pid_bl.pwm>=0){CAR_BL=1;TIM_SetCompare1(TIM8,Pid_bl.pwm);}  //����  
			else{CAR_BL=0;TIM_SetCompare1(TIM8,-Pid_bl.pwm);}
			if(Pid_br.pwm>=0){CAR_BR=1;TIM_SetCompare2(TIM8,Pid_br.pwm);}	 //����		
			else{CAR_BR=0;TIM_SetCompare2(TIM8,-Pid_br.pwm);}
			
		}	
		
		
		/*˫��ʱ�������ݻ���ط�*/
//		a_pwm[0]=qian_sum*10;
//		a_pwm[1]=hou_sum*10;
//		a_pwm[2]=chazhi_qh*10;
//		a_pwm[3]=Pid_br.sample*100;
//		a_pwm[4]=Pid_fr.pwm;
//		a_pwm[5]=Pid_fl.pwm;
//		SentDateTo_usart(a_pwm);//˫���������ݺ���
		
		//pwm_time--;
//		printf("%d",pwm_time);
				
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update);		
	}

}

void PWM_SET(void)      //������ʱ��7���ҽ���һЩPID��������
{
	aa=0;
	tt=0;
	
	pwm_time = 0;
	
	stop_TIM = 1;
	
	Pid_fl.kp=KP;
	Pid_fr.kp=KP;
	Pid_bl.kp=KP;
	Pid_br.kp=KP;

	Pid_fl.ki=KI;
	Pid_fr.ki=KI;
	Pid_bl.ki=KI;
	Pid_br.ki=KI;

	Pid_fl.kd=KD;
	Pid_fr.kd=KD;
	Pid_bl.kd=KD;
	Pid_br.kd=KD;

	Pid_fl.pwm=0;
	Pid_fr.pwm=0;
	Pid_bl.pwm=0;
	Pid_br.pwm=0;

	Pid_fl.pre_det=0;
	Pid_fr.pre_det=0;
	Pid_bl.pre_det=0;
	Pid_br.pre_det=0;
	
	Encoder_Integral = 0;

	Pid_fl.last_det=0;
	Pid_fr.last_det=0;
	Pid_bl.last_det=0;
	Pid_br.last_det=0;
	
	tim7_start = 1;
	
	TIM7_BaseTime_Init(2000,720-1);		//100 	
	fzopen();                         //��ײ��
}



//��t��f 1ǰ��0����

void DJ_MOVE(u8 t,u8 f,u8 sp,u8 dj_1,u8 dj_2,u8 dj_3,u8 dj_4,u8 YS)		
{
//	printf("����%d���ߣ�%d���ٶȣ�%d��ʱ�䣺",f,t,sp);
	u8 at = 0;		
	speed=sp;	
	FX = f;	
	if(t == 1)//����Ҫ��һ��ʱ
	{
		at = 0;
		speed=1;
		PWM_SET();			
		while(t > tt && stop_TIM)	       //�ȴ����߹��趨����
		{		
			;
		}	
		
		aa = St178_Scanf(1);		
		if(aa == 0)          //ֱ��������ʱ
		{		
			while(aa == 0 && stop_TIM)
			{
				;
			}
		}
		
		
		/*�ж�ͣ��ʱ�Ƿ��м���������ʮ�֣�������ڵ���*/
		if(aa == 1)	         //����ת��
		{		
			stop();
		}
		else if(aa == 3)     //���ڿ���
		{
//			FX = 1;
			while(1)
			{
				if(aa == 1 && stop_TIM)
					break;
			}
			stop();
		}
		else if(aa == 4)     //���ڿ�ǰ
		{
//			FX = 0;
			while(1)
			{
				if(aa == 1 && stop_TIM)
					break;
			}
			stop();
		}
		else
		{
			stop();
		}		
	}	
	else if(t == 2)        //����Ҫ������ʱ
	{
		speed=2;
		PWM_SET();
		while(t-1 > tt && stop_TIM)	//���һ��ǰ��·����2��
		{
			;			
		}				
		
		speed=1;		
		while(t > tt && stop_TIM)	  //���һ���·����1��
		{		
			;
		}

		aa = St178_Scanf(1);		
		if(aa == 0)
		{		
			while(aa == 0 && stop_TIM)
			{
				;
			}
		}	
		if(aa == 1)	
		{		
			stop();
		}
		else if(aa == 3)
		{
//			FX = 1;			
			while(1)
			{
				if(aa == 1 && stop_TIM)
					break;
			}
			stop();
		}
		else if(aa == 4)
		{
//			FX = 0;			
			while(1)
			{
				if(aa == 1 && stop_TIM)
					break;
			}
			stop();
		}
		else
		{
			stop();
		}	
	}
	else if(t >= 3)          //����Ҫ����������ʱ
	{
		speed = 2;	
		PWM_SET();
		while(tt < 1 && stop_TIM)	//��һ����2���ٶ�
		{		
			;
		}
		
		speed = sp;		
		while(t-1 > tt && stop_TIM)	//�м����趨�ٶ�
		{
			;
		}
	
		speed=1;
		while(t > tt && stop_TIM)	  //���һ����1���ٶ�
		{		
			;
		}

		aa = St178_Scanf(1);	
		if(aa == 0)
		{		
			while(aa == 0 && stop_TIM)
			{
				;
			}
		}
		if(aa == 1)	
		{		
			stop();
		}
		else if(aa == 3)
		{
			FX = 1;		
			while(1)
			{
				if(aa == 1 && stop_TIM)
					break;
			}
			stop();
		}
		else if(aa == 4)
		{
//			FX = 0;			
			while(1)
			{
				if(aa == 1 && stop_TIM)
					break;
			}
			stop();
		}
		else
		{
			stop();
		}	
	}
	tt=0;
	bxcls();	
	
}

u8 BMQ_MOVE(u8 f,u16 d,u8 mod)        //���������ߺ���
{
	speed=1;
	pidflag=0;
	if(f==1)//ǰ��
	{
		FX=1;
		PWM_SET();
		sum_value1=0;
		sum_value2=0;
		sum_flag=1;
		
		if(mod==1)
		{
			while(1)
			{
				if((abs(sum_value1)>(d-4)*56)&&(abs(sum_value1)<(d+6)*56)) {tt=0;bxcls();pidflag=1;return 1;}
				else if(abs(sum_value1)>(d+6)*56) {tt=0;bxcls();pidflag=1;return 0;}//��ֹ�ܳ�
				
			}
		}
		else
			while(abs(sum_value1)<d*56||abs(sum_value2)<d*56);     //57����1cm��ֵ���޸����ֵ���Ըı���1cm�ľ���
		sum_flag=0;
	}
	
	if(f==0)//����
	{
		FX=0;
		PWM_SET();
		sum_value1=0;
		sum_value2=0;
		sum_flag=1;

		if(mod==1)
		{
				while(1)
			{
				if((abs(sum_value1)>(d-4)*56)&&(abs(sum_value1)<(d+6)*56)) {tt=0;bxcls();pidflag=1;return 1;}
				else if(abs(sum_value1)>(d+6)*56) {tt=0;bxcls();pidflag=1;return 0;}//��ֹ�ܳ�
			}
		}
		else
			while(abs(sum_value1)<d*56||abs(sum_value2)<d*56);
		sum_flag=0;
	}
		tt=0;
		bxcls();	
	stop();
		pidflag=1;
}

void DJ_MOVE_ZHUAN(u8 r,u8 f)		//r3��ת4��ת,f1ǰ��0����
{
//	
//	printf("ת�䷽��%d,ʱ�䣺",r);
	/*ѭ����ʱת��*/
//	speed=1;
//	if(r == 3)
//	{
//		FX = 2;			
//		PWM_SET();
//		delay_ms(300);
//		while(1)	
//		{
//			if((q_q_q>=2&&q_q_q<=4&&h_h_h<=4&&h_h_h>=2||pwm_time>=80|| stop_TIM == 0))//60
//			break;
//		}
//	}
//	if(r == 4)
//	{
//		FX = 3;			
//		PWM_SET();
//		delay_ms(300);
//		while(1)	
//		{
//			if((q_q_q>=2&&q_q_q<=4&&h_h_h<=4&&h_h_h>=2||pwm_time>=80||stop_TIM == 0))//60
//			break;
//		}
//	}
	/*������ת��*/
	speed=1;
	if (r == 3)
	{
		float angle1 = 0;
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // �������ڽ����ж�
		USART_Cmd(USART1, ENABLE);
		angle_6 = 0;					   // ʹ�ܴ���1
		while (angle_6 == 0)						   // �ȴ�����
			;
		angle1 = angle_6;
		angle1 += 93; // ����Ҽ�����360��0��ת����������Ŀ��ֵ
		if (angle1 >= 360)
			angle1 -= 360;
		FX = 2;
		PWM_SET();		
		while (abs(angle1 - angle_6) >= 5) // ��ǰֵ��Ŀ��ֵ�����С��ĳ��ֵ����Ϊת����
			;
		sum_flag = 0;
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); // �������ڽ����ж�
		USART_Cmd(USART1, DISABLE);						// ʹ�ܴ���1
		angle_6 = 0;
	}
	if (r == 4)
	{
		float angle1 = 0;
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // �������ڽ����ж�
		USART_Cmd(USART1, ENABLE);					   // ʹ�ܴ���1
		angle_6 == 0;
		while (angle_6 == 0)						   // �ȴ�����
			;
		angle1 = angle_6;
		angle1 -= 93;
		if (angle1 <= 0)
			angle1 += 360;
		FX = 3;
		PWM_SET();	
		while (abs(angle1 - angle_6) >= 5)
			;
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); // �������ڽ����ж�
		USART_Cmd(USART1, DISABLE);						// ʹ�ܴ���1
		angle_6 = 0;
	}
	
	else if(r==5)    //��ƫ
	{
		FX =2;
		PWM_SET();
		sum_value=0;
		sum_flag=1;//��������־λ
		while(abs(sum_value)<100);       //�����ֵ���Ըı�ת��ĽǶ�
		sum_flag=0;
	}
	else if(r==6)    //��ƫ
	{
		FX =2;
		PWM_SET();
		sum_value=0;
		sum_flag=1;//��������־λ
		while(abs(sum_value)<400);       //�����ֵ���Ըı�ת��ĽǶ�
		sum_flag=0;
	}
	else if(r==7)    //��ƫ΢��
	{
		FX =3;
		PWM_SET();
		sum_value=0;
		sum_flag=1;//��������־λ
		while(abs(sum_value)<180);       //�����ֵ���Ըı�ת��ĽǶ�
		sum_flag=0;
	}
	else if(r==8)    //��ƫ΢��
	{
		FX =2;
		PWM_SET();
		sum_value=0;
		sum_flag=1;//��������־λ
		while(abs(sum_value)<100);       //�����ֵ���Ըı�ת��ĽǶ�
		sum_flag=0;
	}
	else if(r==9)    //��ƫ΢��
	{
		FX =3;
		PWM_SET();
		sum_value=0;
		sum_flag=1;//��������־λ
		while(abs(sum_value)<100);       //�����ֵ���Ըı�ת��ĽǶ�
		sum_flag=0;
	}
	bxcls();	
	stop();
	tt=0;
}


void DJ_MOVE_YS(u8 t,u8 f,u8 sp,u16 tim)	//��ʱͣ��
{
	speed=1;
	
	FX = f;
	PWM_SET();		
	if(t > 1)
	{
		while(t-1 > tt && stop_TIM)	
		{		
			;
		}
		aa = St178_Scanf(1);	
		if(aa == 0)
		{		
			while(aa == 0 && stop_TIM)
			{
				;
			}
		}
		if(aa == 1)	
		{		
		}
		else if(aa == 3)
		{		
			while(1)
			{
				if(aa == 1 && stop_TIM)
					break;
			}
		}
		else if(aa == 4)
		{	
			while(1)
			{
				if(aa == 1 && stop_TIM)
					break;
			}
		}
	}	
	
	
	speed=1;
	pwm_time = 0;	
	while(pwm_time<tim)			//�ٶ�1��һ��67
	{		
		;
	}	
	
//	stop();
	tt=0;
	bxcls();	
}


void DJ_MOVE_PingYi(u8 f, u8 t)
{
	u32 yanshi = t * 50000;
	PWM_SET();
	if (f == 5)
	{
		//Flag_PingYi=1;
		// aa = St178_Scanf(1);
		while (yanshi >= 5)
		{
			CAR_FL = 1;
			TIM_SetCompare4(TIM8, 470);
			CAR_FR = 0;
			TIM_SetCompare3(TIM8, 450);
			CAR_BL = 1;
			TIM_SetCompare1(TIM8, 450);
			CAR_BR = 0;
			TIM_SetCompare2(TIM8, 450);
			yanshi--;
		}
		TIM_SetCompare4(TIM8, 0);
		TIM_SetCompare3(TIM8, 0);
		TIM_SetCompare1(TIM8, 0);
		TIM_SetCompare2(TIM8, 0);
	}
	if (f == 6)
	{
		u8 aax=0;
		Flag_PingYi=1;
		while (yanshi >= 5)
		{
			CAR_FL = 0;
			TIM_SetCompare4(TIM8, 470);
			CAR_FR = 1;
			TIM_SetCompare3(TIM8, 450);
			CAR_BL = 0;
			TIM_SetCompare1(TIM8, 450);
			CAR_BR = 1;
			TIM_SetCompare2(TIM8, 450);
			yanshi--;
		}
		TIM_SetCompare4(TIM8, 0);
        TIM_SetCompare3(TIM8, 0);
        TIM_SetCompare1(TIM8, 0);
        TIM_SetCompare2(TIM8, 0);
        delay_ms(50);
        if (t>=30) {
            CAR_FL = 1;
            CAR_FR = 1;
            CAR_BL = 0;
            CAR_BR = 0;
            TIM_SetCompare4(TIM8, 430);
            TIM_SetCompare3(TIM8, 390);
            TIM_SetCompare1(TIM8, 390);
            TIM_SetCompare2(TIM8, 390); // ǰ��,����һһ��Ӧ
            delay_ms(200);
            aax = St178_Scanf(1);
            while (!aax) {
                aax = St178_Scanf(1);
            }
        }
        stop();
        Flag_PingYi = 0;
    }
	stop();
}



