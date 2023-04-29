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

u8 exFlag_HuoJia          = 0; // ȫ�ֵ�A,B,C,D����
u8 Flag_HuoJia_ShangXia = 0; // �������»���

u8 LunPan[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // ���̴�ŵĶ���
u8 LunPani    = 0;                              // ���̵��±�

u8 Tui[2][10];
u8 Tuii = 0;

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
            for (u8 it = 0; it < 52; it++)
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
            for (u8 it = 0; it < 52; it++)
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
    TIM_SetCompare3(TIM1, 700);
    while (PFin(9) == 1)
        ;
    delay_ms(500);
    while (PFin(9) == 0)
        ;
    TIM_SetCompare3(TIM1, 0); // ���̶��500��죬800��
    delay_ms(500);
    TIM_Cmd(TIM1, DISABLE);
}
void Zhua(u8 Flag_HuoJia)
{
    if (Flag_HuoJia == 'A') {
        memset(USART3_RX_BUF, 0, 10); // ��������0
        USART3_RX_STA = 0;
        delay_ms(10);
        Printf(USART3, "%c", 'A');
        while (1) {
            delay_ms(10);
            if (USART3_RX_STA & 0x8000) // �������
            {
                    delay_ms(10);
                if (Flag_HuoJia_ShangXia == 'X') {
                    for (u8 i = 0; i <= 5; i++) {
                        if (LunPan[i] == USART3_RX_BUF[1]) {
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
                            break;
                        }
                    }
                    break;
                }
                if (Flag_HuoJia_ShangXia == 'S') {
                    for (u8 i = 0; i <= 5; i++) {
                        if (LunPan[i] == USART3_RX_BUF[0]) {
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
                            break;
                        }
                    }
                    break;
                }
            }
        }
        stop();
    }
    if (Flag_HuoJia == 'B') {
        if (Flag_HuoJia_ShangXia == 'X') {
            delay_ms(100);
            Tuii=Tuii-1;
            delay_ms(100);
            LCD_CLS();
            sprintf(OLED_BUF, "%c %c %c %c %c %c", Tui[1][0], Tui[1][1], Tui[1][2], Tui[1][3], Tui[1][4], Tui[1][5]); // ��ʾ
            LCD_16_HanZi_ASCII(0, 4, OLED_BUF);
            sprintf(OLED_BUF, "%c %c %c %c %c %c", Tui[0][0], Tui[0][1], Tui[0][2], Tui[0][3], Tui[0][4], Tui[0][5]); // ��ʾ
            LCD_16_HanZi_ASCII(0, 2, OLED_BUF);
            sprintf(OLED_BUF, "%c %c", USART3_RX_BUF[0], USART3_RX_BUF[1]); // ��ʾ
            LCD_16_HanZi_ASCII(0, 0, OLED_BUF);
            sprintf(OLED_BUF, "%d %c %c", Tuii,Tui[0][Tuii],Tui[1][Tuii]); // ��ʾ
            LCD_16_HanZi_ASCII(6, 0, OLED_BUF);
            delay_ms(50);
            if(Tui[1][Tuii]!='o')
            {
            if (Tui[1][Tuii] == 'r')
                    BMQ_MOVE(0, 15, 0); // ������
            else if (Tui[1][Tuii] == 'l')
                    BMQ_MOVE(1, 15, 0); // ������
            Printf(USART2, "%s", zhiling[3]); // ���м�
            delay_ms(500);
            delay_ms(500);
            delay_ms(500);
            Printf(USART2, "%s", zhiling[2]); 
            }

        } else if (Flag_HuoJia_ShangXia == 'S') {
            if(Tui[0][Tuii]!='o')
            {
            if (Tui[0][Tuii] == 'r')
                BMQ_MOVE(0, 15, 0); // ������
            else if (Tui[0][Tuii] == 'l')
                BMQ_MOVE(1, 15, 0); // ������
            Printf(USART2, "%s", zhiling[3]); // ���м�
            delay_ms(500);
            delay_ms(500);
            delay_ms(500);
            Printf(USART2, "%s", zhiling[2]); // ���м�
            }
            Tuii++;
        }
        stop();
    }
}
void Nano_ChuLi(u8 Flag_HuoJia)
{
    if (Flag_HuoJia == 'A') {
        exFlag_HuoJia = 'A';
        memset(USART3_RX_BUF, 0, 10); // ��������0
        USART3_RX_STA = 0;
        delay_ms(500);
        USART3_Putc('A');
        while (1) {
            if (USART3_RX_STA & 0x8000) // �������
            {

                if (USART3_RX_BUF[0] != '1') // �ϲ�Ҫץ
                {
                    Printf(USART2, "%s", zhiling[4]); // ץ���м�ľ��
                    for (u8 t = 0; t < 10; t++)
                        delay_ms(1000);
                    Printf(USART2, "%s", zhiling[0]); // ��λ
                    LunPan[LunPani] = USART3_RX_BUF[0];
                    LunPani++;
                    if (LunPani == 6) LunPani = 0;
                    LunPan_Zhuan();
                } 
                if (USART3_RX_BUF[1] != '1') // �²�Ҫץ
                {
                    Printf(USART2, "%s", zhiling[5]); // ץ���м�ľ��
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
        delay_ms(100);
        Printf(USART3,"%c",'B');
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
    USART3_RX_STA = 0;
}
void HandInit()
{
    Printf(USART2, "%s", zhiling[0]); // ��λ
    memset(LunPan, 0, 10);
    memset(Tui, 0, 12);
    LunPani = 0;
    Tuii    = 0;
}