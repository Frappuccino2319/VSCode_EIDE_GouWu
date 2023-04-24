#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "oled.h"
#include "oled2.h"
#include "timer.h"
#include "gpio.h"
#include "ADC_Config.h"
#include "moto.h"
#include "move.h"
#include "st178.h"
#include "ui.h"
#include "stmflash.h"
#include "hand.h"

int AD_test = 0;
int tx_qian = 0;
int tx_hou  = 0;

int main(void)
{

    int tx_flag = 0;
    delay_init(); // ��ʱ��ʼ��
    OLED_Init();  // OLED��ʼ��
    LCD_CLS();    // OLED����
    //	TZXH_LOGO();//̨��ѧԺlogo��ʾ
    All_GPIO_Init(); // �õ���IO�ڳ�ʼ��
    SHOP_GPIO_init();
    BuJin_GPIO_Init();
    uart1_init(115200); // ����1
    uart2_init(9600);   // ����2
    uart3_init(9600);   // ����3

    Init_BMQ();               // ��������ʼ��
    Init_TIM1_PWM(1499, 109); // �������1499,69Ϊ600HZ,����Խ��Խ��
    ADC_DMA_Configuration();  // ADC1��ʼ��(��֪����û���õ����ϳ�����)
    ADKey_Init();             // ACD3��ʼ��(�õ�)

    Init_TIM8_PWM(899, 7); // ���PWM��
    //	Init_TIM1_PWM(19999,71);//PE11 PE13���(Ԥ��)

    read_from_flash(); // ��flash�ж�ȡ����

    LCD_CLS();
    // BuJin_Zhuan('S');
    delay_ms(100);
    BuJin_Zhuan('I');
    delay_ms(100);
    LunPan_Zhuan();
    delay_ms(100);
        delay_ms(100);
    Printf(USART2, "%s\r\n", "tlcdb");
     Printf(USART3, "%s\r\n", "tlcdb");
    while (1) {
        // Printf(USART1, "%s\r\n", "TLCDB1!");
        // delay_ms(500);
        // Printf(USART2, "%s\r\n", "TLCDB2!");
        // delay_ms(500);
        // Printf(USART3, "%s\r\n", "TLCDB3!");
        // sprintf(OLED_BUF, "E7=%d", 1);
        // LCD_16_HanZi_ASCII(10, 6, OLED_BUF);

        // delay_ms(500);
        MenuOperate();
    }
}
