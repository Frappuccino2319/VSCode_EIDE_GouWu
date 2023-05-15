#include "hand.h"
#include "timer.h"
#include "ui.h"
#include "math.h"
#include <stdlib.h>
#include "gpio.h"
#include "usart.h"
#include "moto.h"
#include "usart.h"
#include "delay.h"

u8 exFlag_HuoJia        = 0; // ȫ�ֵ�A,B,C,D����
u8 Flag_HuoJia_ShangXia = 0; // �������»���

u8 LuXian_DongTai[50][5];
u8 LuXian_DongTaii;

u8 Sum_Qian;

u8 LunPan[7];
u8 LunPani = 0;

u8 Tui[2][7];
u8 Tuii = 0;

u8 A_S[7];
u8 A_X[7];
u8 A_i;

u8 C_S[7];
u8 C_X[7];
u8 C_i;

u8 D_S[3][7];
u8 D_X[3][7];
u8 D_i;

void BuJin_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12; // ���������ת��־λ
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_SetBits(GPIOE, 12);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; // ��λ����7��8��9����
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
}

void BuJin_Zhuan(u8 flag)
{
    if (flag == 'I') {
        Flag_HuoJia_ShangXia = 0;
        PEout(12)            = 0; // ���¶���־λ��0Ϊ�£�
        TIM_Cmd(TIM1, ENABLE);
        TIM_SetCompare2(TIM1, 700);
        while (PFin(8) == 0) { // 7��8��
            ;
        }
        TIM_SetCompare2(TIM1, 0);
        TIM_Cmd(TIM1, DISABLE);
    }
    if (flag == 'S') {
        Flag_HuoJia_ShangXia = 'S';
        PEout(12)            = 1;
        TIM_Cmd(TIM1, ENABLE);
        TIM_SetCompare2(TIM1, 700);
        while (PFin(7) == 0) {
            ;
        }
        TIM_SetCompare2(TIM1, 0);
        TIM_Cmd(TIM1, DISABLE);
    }
    if (flag == 'X') {
        Flag_HuoJia_ShangXia = 'X';
        if (PFin(8) == 1) // ������
        {
            delay_ms(200);
            PEout(12) = 1;
            delay_ms(200);
            TIM_Cmd(TIM1, ENABLE);
            delay_ms(200);
            TIM_SetCompare2(TIM1, 700);
            delay_ms(200);
            for (u8 it = 0; it < 45; it++)
                delay_ms(100);
            TIM_SetCompare2(TIM1, 0);
            TIM_Cmd(TIM1, DISABLE);

        } else if (PFin(7) == 1) // ������
        {
            delay_ms(200); // ��ʱ�Ǳ�Ҫ��
            PEout(12) = 0;
            delay_ms(200);
            TIM_Cmd(TIM1, ENABLE);
            delay_ms(200);
            TIM_SetCompare2(TIM1, 700);
            delay_ms(200);
            for (u8 it = 0; it < 153; it++) delay_ms(100);
            TIM_SetCompare2(TIM1, 0);
            TIM_Cmd(TIM1, DISABLE);
        } else // �Ķ����ھ����º���
        {
            BuJin_Zhuan('I');
            Flag_HuoJia_ShangXia = 'X'; // ������I����Ҫ���¸�
            PEout(12)            = 1;
            delay_ms(200);
            TIM_Cmd(TIM1, ENABLE);
            delay_ms(200);
            TIM_SetCompare2(TIM1, 700);
            delay_ms(200);
            for (u8 it = 0; it < 45; it++)
                delay_ms(100);
            TIM_SetCompare2(TIM1, 0);
            TIM_Cmd(TIM1, DISABLE);
        }
    }
    if (flag == 'T') {
        TIM_SetCompare2(TIM1, 0);
        TIM_Cmd(TIM1, DISABLE);
    }
}
void LunPan_Zhuan()
{
    TIM_Cmd(TIM1, ENABLE);
    TIM_SetCompare3(TIM1, 680);
    while (PFin(9) == 1)
        ;
    delay_ms(500);
    while (PFin(9) == 0)
        ;
    TIM_SetCompare3(TIM1, 0); // ���̶��500��죬800��
    delay_ms(10);
    TIM_Cmd(TIM1, DISABLE);
}
void Zhua(u8 Flag_HuoJia)
{
    if (Flag_HuoJia == 'A') { 
        A_i             = 0;
        Sum_Qian        = 0;
        LuXian_DongTaii = 0;
        memset(LuXian_DongTai, 0, 100);
        if (Flag_HuoJia_ShangXia == 'X') {
            if (A_X[5] != 'r') {
                Routecpy(0, 2, 0, 'r', 0);
            }
            Sum_Qian++;
            if (A_X[4] != 'r') {
                Routecpy(Sum_Qian, 0, 0, 255, 0);
                Routecpy(0, 6, 0, 255, 10);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'r', 0);
            }
            Sum_Qian++;
            if (A_X[3] != 'g') {
                Routecpy(Sum_Qian, 0, 0, 255, 0);
                Routecpy(0, 6, 0, 255, 10);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'g', 0);
            }
            Sum_Qian++;
            if (A_X[2] != 'g') {
                Routecpy(Sum_Qian, 0, 0, 255, 0);
                Routecpy(0, 6, 0, 255, 10);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'g', 0);
            }
            Sum_Qian++;
            if (A_X[1] != 'b') {
                Routecpy(Sum_Qian, 0, 0, 255, 0);
                Routecpy(0, 6, 0, 255, 10);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'b', 0);
            }
            Sum_Qian++;
            if (A_X[0] != 'b') {
                Routecpy(Sum_Qian, 0, 0, 255, 0);
                Routecpy(0, 6, 0, 255, 10);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'b', 0);
            }
            Routecpy(Sum_Qian, 0, 0, 255, 0);
            Routecpy(0, 6, 0, 255, 10);
            Sum_Qian = 0;
            Routecpy(0, 0, 0, 0, 0);
            delay_ms(10);
            change_DongTai(LuXian_DongTai, 10);
        } else if (Flag_HuoJia_ShangXia == 'S') {
            if (A_S[0] != 'b') {
                Routecpy(0, 2, 0, 'b', 0);
            }
            Sum_Qian++;
            if (A_S[1] != 'b') {
                Routecpy(Sum_Qian, 1, 0, 255, 0);
                Routecpy(0, 6, 0, 255, 10);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'b', 0);
            }
            Sum_Qian++;
            if (A_S[2] != 'g') {
                Routecpy(Sum_Qian, 1, 0, 255, 0);
                Routecpy(0, 6, 0, 255, 10);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'g', 0);
            }
            Sum_Qian++;
            if (A_S[3] != 'g') {
                Routecpy(Sum_Qian, 1, 0, 255, 0);
                Routecpy(0, 6, 0, 255, 10);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'g', 0);
            }
            Sum_Qian++;
            if (A_S[4] != 'r') {
                Routecpy(Sum_Qian, 1, 0, 255, 0);
                Routecpy(0, 6, 0, 255, 10);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'r', 0);
            }
            Sum_Qian++;
            if (A_S[5] != 'r') {
                Routecpy(Sum_Qian, 1, 0, 255, 0);
                Routecpy(0, 6, 0, 255, 10);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'r', 0);
            }
            Routecpy(Sum_Qian, 1, 0, 255, 0);
            Routecpy(0, 6, 0, 255, 10);
            Sum_Qian = 0;
            Routecpy(0, 0, 0, 0, 0);
            delay_ms(10);
            change_DongTai(LuXian_DongTai, 10);
            LuXian_DongTaii = 0;
        }
    }
    if (Flag_HuoJia == 'B') {
        if (Flag_HuoJia_ShangXia == 'X') {
            Sum_Qian        = 0;
            LuXian_DongTaii = 0;
            memset(LuXian_DongTai, 0, 100);
            for (u8 i = 5; i >= 0 && i < 10; i--) {
                if(i!=5)
                  Sum_Qian++;
                if (Tui[1][i] != 'o') {
                    Routecpy(Sum_Qian, 0, 0, 255, 5);
                    Routecpy(0, 6, 0, 255, 15);
                    Sum_Qian = 0;
                    Routecpy(0, 2, 0, 20 + i, 0);
                }           
            }
            Routecpy(Sum_Qian, 0, 0, 255, 15);
            Routecpy(0, 0, 20, 255, 15);
            Routecpy(0, 10, 0, 255, 15);
            Routecpy(0, 6, 0, 255, 10);
            Routecpy(0, 0, 0, 0, 0);
            change_DongTai(LuXian_DongTai, 10);
        } else if (Flag_HuoJia_ShangXia == 'S') {
            Sum_Qian        = 0;
            LuXian_DongTaii = 0;
            memset(LuXian_DongTai, 0, 100);
            for (u8 i = 0; i <6; i++) {
                if(i!=0)
                Sum_Qian++;
                if (Tui[0][i] != 'o') {
                    Routecpy(Sum_Qian, 1, 0, 255,5);
                    Routecpy(0, 6, 0, 255, 15);
                    Sum_Qian=0;
                    Routecpy(0, 2, 0, 20 + i, 0);
                } 
            }
            Routecpy(Sum_Qian, 1, 0, 255, 5);
            Routecpy(0, 0, 0, 0, 0);
            change_DongTai(LuXian_DongTai, 10);
        }
    }
    if (Flag_HuoJia == 'C') {
        Sum_Qian        = 0;
        LuXian_DongTaii = 0;
        for (u8 i = 5; i >= 0 && i < 10; i--) {
            if (i != 5)
                Sum_Qian++;
            if (C_X[i] == 'm' || C_S[i] == 'm') {
                Routecpy(Sum_Qian, 1, 0, 255, 10);
                Routecpy(1, 8, 0, 255, 10);
                Routecpy(0, 6, 0, 255, 15);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 20 + i, 0);
                Routecpy(0, 0, 8, 255, 10);
            }
        }
        Routecpy(Sum_Qian, 1, 0, 255, 10);
        Sum_Qian=0;
        Routecpy(0, 2, 0, 'Z', 0);
        Routecpy(0, 2, 0, 'Z', 0);
        Routecpy(0, 2, 0, 'X', 0);
        for (u8 i = 0; i < 6; i++) {
            if (i != 0)
                Sum_Qian++;
            if (C_X[i] == 'k') {
                Routecpy(Sum_Qian, 0, 0, 255, 10);
                Routecpy(0, 6, 0, 255, 15);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'Z', 0);
                Routecpy(0, 2, 0, 1, 15);
                Routecpy(0, 2, 0, 2, 15);
            }
        }
        Routecpy(Sum_Qian, 0, 0, 255, 0); 
        Sum_Qian=0;
        Routecpy(0, 5, 0, 255, 10);
        Routecpy(0, 2, 0, 'S', 0);
        Routecpy(0, 6, 0, 255, 10);
        for (u8 i = 5; i >= 0 && i < 10; i--) {
            if (i != 5)
                Sum_Qian++;
            if (C_S[i] == 'k') {
                Routecpy(Sum_Qian, 1, 0, 255, 10);
                Routecpy(0, 6, 0, 255, 15);
                Sum_Qian = 0;
                Routecpy(0, 2, 0, 'Z', 0);
                Routecpy(0, 2, 0, 1, 15);
                Routecpy(0, 2, 0, 2, 15);
            }
        }
          Routecpy(0, 0, 0, 0, 0);
          change_DongTai(LuXian_DongTai,10);

    }
    if (Flag_HuoJia == 'D') {
        Sum_Qian        = 0;
        LuXian_DongTaii = 0;
        for (D_i = 5; D_i >= 0 && D_i < 10; D_i--) {
            if (D_i != 5)
                Sum_Qian++;
            for (u8 i = 0; i < 3; i++) {
                if (D_S[i][D_i] == 'z' || D_S[i][D_i] == 'h' || D_S[i][D_i] == 'j' || D_X[i][D_i] == 'z' || D_X[i][D_i] == 'h' || D_X[i][D_i] == 'j') {
                    Routecpy(Sum_Qian, 1, 0, 255, 10);
                    Sum_Qian = 0;
                    Routecpy(1, 8, 0, 255, 10);
                    Routecpy(0, 2, 0, D_i + 20, 0);
                    Routecpy(0, 0, 8, 255, 10);
                    break;
                }
            }
        }
        Routecpy(Sum_Qian, 1, 0, 255, 10);
        Routecpy(0, 0, 0, 0, 0);
        change_DongTai(LuXian_DongTai, 10);
        LuXian_DongTaii = 0;
    }
}
void Nano_ChuLi(u8 Flag_HuoJia)
{
    if (Flag_HuoJia == 'A') {
        exFlag_HuoJia = 'A';
        memset(USART3_RX_BUF, 0, 10); // ��������0
        USART3_RX_STA = 0;
        delay_ms(5);
        USART3_Putc('A');
        while (1) {
            if (USART3_RX_STA & 0x8000) // �������
            {
                A_S[A_i] = USART3_RX_BUF[0];
                A_X[A_i] = USART3_RX_BUF[1];
                A_i++;
                if (USART3_RX_BUF[2] == 's' || USART3_RX_BUF[2] == 'd') // �ϲ�Ҫץ
                {
                    Printf(USART2, "%s", zhiling[11]); // ץ���м�ľ��
                    for (u8 t = 0; t < 10; t++)
                        delay_ms(1000); 
                    Printf(USART2, "%s", zhiling[0]); // ��λ
                    LunPan[LunPani] = USART3_RX_BUF[0];
                    LunPani++;
                    if (LunPani == 6) LunPani = 0;
                    LunPan_Zhuan();
                }
                if (USART3_RX_BUF[2] == 'x' || USART3_RX_BUF[2] == 'd') // �²�Ҫץ
                {
                    Printf(USART2, "%s", zhiling[12]); // ץ���м�ľ��
                    for (u8 t = 0; t < 10; t++)
                        delay_ms(1000);
                    Printf(USART2, "%s", zhiling[0]); // ��λ
                    LunPan[LunPani] = USART3_RX_BUF[1];
                    LunPani++;
                    if (LunPani == 6) LunPani = 0;
                    LunPan_Zhuan();
                }
                USART3_RX_STA = 0;
                break;
            }
        }
    }
    if (Flag_HuoJia == 'B') {
        exFlag_HuoJia = 'B';
        memset(USART3_RX_BUF, 0, 10); // ��������0
        USART3_RX_STA = 0;
        delay_ms(5);
        Printf(USART3, "%c", 'B');
        while (1) {
            delay_ms(10);
            if (USART3_RX_STA & 0x8000) // �������
            {
                Tui[0][Tuii] = USART3_RX_BUF[0];
                Tui[1][Tuii] = USART3_RX_BUF[1];
                Tuii++;
                USART3_RX_STA = 0;
                break;
            }
        }
    }
    if (Flag_HuoJia == 'C') {
        exFlag_HuoJia = 'C';
        memset(USART3_RX_BUF, 0, 10); // ��������0
        USART3_RX_STA = 0;
        delay_ms(5);
        Printf(USART3, "%c", 'C');
        while (1) {
            delay_ms(10);
            if (USART3_RX_STA & 0x8000) // �������
            {
                C_S[C_i]      = USART3_RX_BUF[0];
                C_X[C_i]      = USART3_RX_BUF[1];
                C_i++;
                USART3_RX_STA = 0;
                break;
            }
        }
    }
    if (Flag_HuoJia == 'D') {
        exFlag_HuoJia = 'D';
        memset(USART3_RX_BUF, 0, 10); // ��������0
        USART3_RX_STA = 0;
        delay_ms(5);
        Printf(USART3, "%c", 'D');
        while (1) {
            delay_ms(10);
            if (USART3_RX_STA & 0x8000) // �������
            {
                for (u8 i = 0; i < 3; i++) {
                    D_S[i][D_i] = USART3_RX_BUF[i];
                }
                for (u8 i = 3; i < 6; i++) {
                    D_X[i - 3][D_i] = USART3_RX_BUF[i];
                }
                if (D_i == 1) {
                    D_i = 2;
                    for (u8 i = 0; i < 3; i++) {
                        D_S[i][D_i] = 'k';
                    }
                    for (u8 i = 3; i < 6; i++) {
                        D_X[i - 3][D_i] = 'k';
                    }
                    D_i = 3;
                    for (u8 i = 0; i < 3; i++) {
                        D_S[i][D_i] = 'k';
                    }
                    for (u8 i = 3; i < 6; i++) {
                        D_X[i - 3][D_i] = 'k';
                    }
                }
                D_i++;
                break;
            }
        }
    }
    USART3_RX_STA = 0;
}
void HandInit()
{
    Printf(USART2, "%s", zhiling[0]); // ��λ
    memset(A_S, 0, 7);
    memset(A_X, 0, 7);
    memset(LunPan, 0, 10);
    memset(Tui, 0, 12);
    memset(D_S, 0, 21);
    memset(D_X, 0, 21);
    Sum_Qian        = 0;
    LuXian_DongTaii = 0;
    LunPani         = 0;
    Tuii            = 0;
    A_i             = 0;
    C_i=0;
    D_i             = 0;
}
void LunPan_Zhao_Tui(u8 f)
{
    if (exFlag_HuoJia == 'A') { 
        for (u8 i = 0; i <= 5; i++) {
            if (LunPan[i] == f) { 
                LunPan[i] = 'k';
                while (LunPani != i) {
                    LunPan_Zhuan();
                    LunPani++;
                    if (LunPani == 6)
                        LunPani = 0;
                }
                Printf(USART2, zhiling[1]);
                delay_ms(500);
                delay_ms(500);
                delay_ms(500);
                Printf(USART2, zhiling[2]);
                delay_ms(500);
                delay_ms(500);
                delay_ms(500);
                break;
            }
        }
    }
    if (exFlag_HuoJia == 'D') {
        for (u8 i = 0; i <= 5; i++) { 
            if (LunPan[i] == f) {
                LunPan[i] = 'k';
                while (LunPani != i) {
                    LunPan_Zhuan();
                    LunPani++;
                    if (LunPani == 6)
                        LunPani = 0;
                }
                Printf(USART2, zhiling[4]);
                delay_ms(500);
                delay_ms(500);
                delay_ms(500);
                Printf(USART2, zhiling[2]);
                delay_ms(500);
                delay_ms(500);
                delay_ms(500);
                break;
            }
        }
    }
}

void Routecpy(u8 st1, u8 ed2, u8 rd3, u8 th4, u8 th5)
{
    LuXian_DongTai[LuXian_DongTaii][0] = st1;
    LuXian_DongTai[LuXian_DongTaii][1] = ed2;
    LuXian_DongTai[LuXian_DongTaii][2] = rd3;
    LuXian_DongTai[LuXian_DongTaii][3] = th4;
    LuXian_DongTai[LuXian_DongTaii][4] = th5;
    LuXian_DongTaii++;
}

void KaoBian_Zhua(u8 HuoJia_F, u8 HuoJia_i)
{
    if (HuoJia_F == 'C') {
        C_i = HuoJia_i - 20;
        if (C_X[C_i] == 'm') {
            Printf(USART2, zhiling[6]); // ץ����
            for (u8 i = 0; i < 12; i++)  
                delay_ms(1000);
            Printf(USART2, zhiling[0]);
            delay_ms(500);
            LunPan_Zhuan();
        }
        if (C_S[C_i] == 'm') {
            Printf(USART2, zhiling[5]); // ץ����
            for (u8 i = 0; i < 12; i++)
                delay_ms(1000);
            Printf(USART2, zhiling[0]);
            delay_ms(500);
            LunPan_Zhuan();
        }
    } else if (HuoJia_F == 'D') {
        D_i = HuoJia_i - 20;
        if (D_X[2][D_i] == 'h' || D_X[2][D_i] == 'z' || D_X[2][D_i] == 'j' ) {
            Printf(USART2, zhiling[7]); // ץ����
            for (u8 i = 0; i < 11; i++) 
                delay_ms(1000);
            Printf(USART2, zhiling[0]);
            delay_ms(500);
            LunPan[LunPani] = D_X[2][D_i];
            LunPani++;
            LunPan_Zhuan();
            if (LunPani == 6)
                LunPani = 0;
        }
        if (D_X[1][D_i] == 'h' || D_X[1][D_i] == 'z' || D_X[1][D_i] == 'j' ) {
            Printf(USART2, zhiling[6]); // ץ����
            for (u8 i = 0; i < 11; i++)
                delay_ms(1000);
            Printf(USART2, zhiling[0]);
            delay_ms(500);
            LunPan[LunPani] = D_X[1][D_i];
            LunPani++;
            LunPan_Zhuan();
            if (LunPani == 6)
                LunPani = 0;
        }
        if (D_X[0][D_i] == 'h' || D_X[0][D_i] == 'z' || D_X[0][D_i] == 'j' ) {
            Printf(USART2, zhiling[8]); // ץ����
            for (u8 i = 0; i < 11; i++)
                delay_ms(1000);
            Printf(USART2, zhiling[0]);
            delay_ms(500);
            LunPan[LunPani] = D_X[0][D_i];
            LunPani++;
            LunPan_Zhuan(); 
            if (LunPani == 6)
                LunPani = 0;
        }
        if (D_S[2][D_i] == 'h' || D_S[2][D_i] == 'z' || D_S[2][D_i] == 'j' ) {
            Printf(USART2, zhiling[10]); // ץ����
            for (u8 i = 0; i < 11; i++)
                delay_ms(1000);
            Printf(USART2, zhiling[0]);
            delay_ms(500);
            LunPan[LunPani] = D_S[2][D_i];
            LunPani++;
            LunPan_Zhuan();
            if (LunPani == 6)
                LunPani = 0;
        }
        if (D_S[1][D_i] == 'h' || D_S[1][D_i] == 'z' || D_S[1][D_i] == 'j' ) {
            Printf(USART2, zhiling[5]); // ץ����
            for (u8 i = 0; i < 11; i++)
                delay_ms(1000);
            Printf(USART2, zhiling[0]);
            delay_ms(500);
            LunPan[LunPani] = D_S[1][D_i];
            LunPani++;
            LunPan_Zhuan();
            if (LunPani == 6)
                LunPani = 0;
        }
        if (D_S[0][D_i] == 'h' || D_S[0][D_i] == 'z' || D_S[0][D_i] == 'j' ) {
            Printf(USART2, zhiling[9]); // ץ����
            for (u8 i = 0; i < 11; i++)
                delay_ms(1000);
            Printf(USART2, zhiling[0]);
            delay_ms(500);
            LunPan[LunPani] = D_S[0][D_i];
            LunPani++;
            LunPan_Zhuan();
            if (LunPani == 6)
                LunPani = 0;
        }
    }
}

void B_Tui(u8 HuoJia_i)
{
    if (Flag_HuoJia_ShangXia == 'X') {
        Tuii = HuoJia_i - 20;
        delay_us(100);
        if (Tui[1][Tuii] != 'o') {
            if (Tui[1][Tuii] == 'r')
                BMQ_MOVE(0, 17, 0); // ������
            else if (Tui[1][Tuii] == 'l')
                BMQ_MOVE(1, 17, 0);           // ������
            Printf(USART2, "%s", zhiling[3]); // ���м�
            delay_ms(500);
            delay_ms(500);
            delay_ms(500);
            Printf(USART2, "%s", zhiling[2]);
            delay_ms(500);
            delay_ms(500);
            delay_ms(500);
        }
    } else if (Flag_HuoJia_ShangXia == 'S') {
        Tuii = HuoJia_i - 20;
        delay_us(100);
        if (Tui[0][Tuii] != 'o') {
            if (Tui[0][Tuii] == 'r')
                BMQ_MOVE(0, 17, 0); // ������
            else if (Tui[0][Tuii] == 'l')
                BMQ_MOVE(1, 17, 0);           // ������
            Printf(USART2, "%s", zhiling[3]); // ���м�
            delay_ms(500);
            delay_ms(500);
            delay_ms(500);
            Printf(USART2, "%s", zhiling[2]);
            delay_ms(500);
            delay_ms(500);
            delay_ms(500);
        }
    }
}