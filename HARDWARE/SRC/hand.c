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

u8 LunPan[10]           = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // ���̴�ŵĶ���
u8 LunPani              = 0;                              // ���̵��±�
u8 Flag_HuoJia          = 0;                              // A,B,C,D����
u8 Flag_HuoJia_ShangXia = 0;                              // �������»���

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
            for (u8 it = 0; it < 81; it++)
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
            for (u8 it = 0; it < 235; it++) delay_ms(100);
            TIM_SetCompare2(TIM1, 0);
            TIM_Cmd(TIM1, DISABLE);
        } else // �Ķ����ھ����º���
        {
            delay_ms(200);
            PEout(12) = 0;
            delay_ms(200);
            TIM_Cmd(TIM1, ENABLE);
            delay_ms(200);
            TIM_SetCompare2(TIM1, 700);
            while (PFin(8) == 0) {
                ;
            }
            delay_ms(200);
            TIM_SetCompare2(TIM1, 0);
            delay_ms(200);
            PEout(12) = 1;
            delay_ms(200);
            TIM_SetCompare2(TIM1, 700);
            delay_ms(200);
            for (u8 it = 0; it < 82; it++)
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
            delay_ms(100);
            if (USART3_RX_STA & 0x8000) // �������
            {
                LCD_CLS();
                sprintf(OLED_BUF, "%c %c!", USART3_RX_BUF[0], USART3_RX_BUF[1]); // ��ʾ
                LCD_16_HanZi_ASCII(0, 4, OLED_BUF);
                sprintf(OLED_BUF, "%c", Flag_HuoJia_ShangXia); // ��ʾ
                LCD_16_HanZi_ASCII(0, 2, OLED_BUF);
                if (Flag_HuoJia_ShangXia == 'X') {
                    if (USART3_RX_BUF[1] == 'r') // ����Ϊ�գ�Ҫ��
                    {
                        for (u8 i = 0; i <= 5; i++) {
                            if (LunPan[i] == 'r') {
                                LunPan[i] = 'k';
                                while (LunPani != i) {
                                    LunPan_Zhuan();
                                    LunPani++;
                                    if (LunPani == 6)
                                        LunPani = 0;
                                }
                                Printf(USART2, zhiling[1]);
                                break;
                            }
                        }
                        for (u8 itt = 0; itt < 15; itt++)
                            delay_ms(100);
                        break;
                    } else if (USART3_RX_BUF[1] == 'g') {
                        for (u8 i = 0; i <= 5; i++) {
                            if (LunPan[i] == 'g') {
                                LunPan[i] = 'k';
                                while (LunPani != i) {
                                    LunPan_Zhuan();
                                    LunPani++;
                                    if (LunPani == 6)
                                        LunPani = 0;
                                }
                                Printf(USART2, zhiling[1]);
                                break;
                            }
                        }
                        for (u8 itt = 0; itt < 15; itt++)
                            delay_ms(100);
                        break;
                    } else if (USART3_RX_BUF[1] == 'b') {
                        for (u8 i = 0; i <= 5; i++) {
                            if (LunPan[i] == 'b') {
                                LunPan[i] = 'k';
                                while (LunPani != i) {
                                    LunPan_Zhuan();
                                    LunPani++;
                                    if (LunPani == 6)
                                        LunPani = 0;
                                }
                                Printf(USART2, zhiling[1]);
                                break;
                            }
                        }
                        for (u8 itt = 0; itt < 15; itt++)
                            delay_ms(100);
                        break;
                    } else
                        break;
                }
                if (Flag_HuoJia_ShangXia == 'S') {
                    if (USART3_RX_BUF[0] == 'r') // ����Ϊ�գ�Ҫ��
                    {
                        for (u8 i = 0; i <= 5; i++) {
                            if (LunPan[i] == 'r') {
                                LunPan[i] = 'k';
                                while (LunPani != i) {
                                    LunPan_Zhuan();
                                    LunPani++;
                                    if (LunPani == 6)
                                        LunPani = 0;
                                }
                                Printf(USART2, zhiling[1]);
                                break;
                            }
                        }
                        for (u8 itt = 0; itt < 15; itt++)
                            delay_ms(100);
                        break;
                    } else if (USART3_RX_BUF[0] == 'g') {
                        for (u8 i = 0; i <= 5; i++) {
                            if (LunPan[i] == 'g') {
                                LunPan[i] = 'k';
                                while (LunPani != i) {
                                    LunPan_Zhuan();
                                    LunPani++;
                                    if (LunPani == 6)
                                        LunPani = 0;
                                }
                                Printf(USART2, zhiling[1]);
                                break;
                            }
                        }
                        for (u8 itt = 0; itt < 15; itt++)
                            delay_ms(100);
                        break;
                    } else if (USART3_RX_BUF[0] == 'b') {
                        for (u8 i = 0; i <= 5; i++) {
                            if (LunPan[i] == 'b') {
                                LunPan[i] = 'k';
                                while (LunPani != i) {
                                    LunPan_Zhuan();
                                    LunPani++;
                                    if (LunPani == 6)
                                        LunPani = 0;
                                }
                                Printf(USART2, zhiling[1]);
                                break;
                            }
                        }
                        for (u8 itt = 0; itt < 15; itt++)
                            delay_ms(100);
                        break;
                    } else
                        break;
                }
                break;
            }
        }
    }
}
void Nano_ChuLi(u8 Flag_HuoJia)
{
    if (Flag_HuoJia == 'A') {
        memset(USART3_RX_BUF, 0, 10); // ��������0
        USART3_RX_STA = 0;
        delay_ms(500);
        USART3_Putc('A');
        Flag_HuoJia = 'A';
        while (1) {
            if (USART3_RX_STA & 0x8000) // �������
            {

                switch (USART3_RX_BUF[0]) // �ϲ�
                {
                    case 'r':
                        Printf(USART2, "%s", zhiling[1]);
                        LunPan[LunPani] = 'r';
                        LunPani++;
                        if (LunPani == 6) LunPani = 0;
                        LunPan_Zhuan();
                        break;
                    case 'g':
                        Printf(USART2, "%s", zhiling[1]);
                        LunPan[LunPani] = 'g';
                        LunPani++;
                        if (LunPani == 6) LunPani = 0;
                        LunPan_Zhuan();
                        break;
                    case 'b':
                        Printf(USART2, "%s", zhiling[1]);
                        LunPan[LunPani] = 'b';
                        LunPani++;
                        if (LunPani == 6) LunPani = 0;
                        LunPan_Zhuan();
                        break;
                    default:
                        break;
                }
                switch (USART3_RX_BUF[1]) // �²�
                {
                    case 'r':
                        Printf(USART2, "%s", zhiling[1]);
                        LunPan[LunPani] = 'r';
                        LunPani++;
                        if (LunPani == 6) LunPani = 0;
                        LunPan_Zhuan();
                        break;
                    case 'g':
                        Printf(USART2, "%s", zhiling[1]);
                        LunPan[LunPani] = 'g';
                        LunPani++;
                        if (LunPani == 6) LunPani = 0;
                        LunPan_Zhuan();
                        break;
                    case 'b':
                        Printf(USART2, "%s", zhiling[1]);
                        LunPan[LunPani] = 'b';
                        LunPani++;
                        if (LunPani == 6) LunPani = 0;
                        LunPan_Zhuan();
                        break;
                    default:
                        break;
                }
                USART3_RX_STA = 0;
                break;
            }
        }
    }
}

void HandInit()
{
            memset(LunPan, 0, 10);
            LunPani = 0;
}