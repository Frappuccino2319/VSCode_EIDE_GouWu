#ifndef _HAND_H
#define _HAND_H

#include "sys.h"


//��̬·��
extern u8 LuXian_DongTai[50][5];
extern u8 LuXian_DongTaii;

//ͳ��ǰ���ĸ���
extern u8 Sum_Qian;

// A,B,C,D����
extern u8 exFlag_HuoJia;    

//��������ڵ���Ϣ
extern u8 LunPan[7];
extern u8 Tui[2][7];
extern u8 Tuii;
extern u8 LunPani;

//A��������
extern u8 A_S[7];
extern u8 A_X[7];
extern u8 A_i;

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
//�����Ҷ���Ȼ����(c/d ����/���� r/g/b)
void LunPan_Zhao_Tui(u8 f);
//����ά���鰴�з�ֵ
//��ά���飬��һ�У��������
void Routecpy(u8 st1,u8 ed2,u8 rd3,u8 th4,u8 th5);
//����ץCD����
void KaoBian_Zhua(u8 HuoJia_F,u8 HuoJia_i);
//B������
void B_Tui(u8 HuoJia_i);
#endif 

