#ifndef _HAND_H
#define _HAND_H

#include "sys.h"

// A,B,C,D����
extern u8 exFlag_HuoJia;    
//��������ڵ���Ϣ
extern u8 LunPan[7];
extern u8 Tui[2][7];
extern u8 Tuii;
//D���������
extern u8 D_S[3][7];
extern u8 D_X[3][7];
extern u8 D_i;

//void CSD(void);

//����ץ�ĺ������������
void Zhua(u8 Flag_HuoJia);
void BuJin_GPIO_Init();
//�����������������I��ͳ�ʼ����XΪ�²���ܣ�SΪ�ϲ����
void BuJin_Zhuan(u8 flag);
//����ת������
void LunPan_Zhuan();
void Nano_ChuLi(u8 Flag_HuoJia);
//��ʼ��һЩ����
void HandInit();
#endif 

