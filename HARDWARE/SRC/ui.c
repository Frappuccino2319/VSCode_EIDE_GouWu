
#include "ui.h"

#define MENU_SIZE 40 // 菜单长度
#define uchar     unsigned char
#define uint      unsigned int

extern short int sum_value1, sum_value2;
extern u16 sum_flag;
u8 j                    = 0;
u8 Infoflag                = 0; // 现存信息
unsigned char hou[30][5]   = {{1, 0, 0, 255, 0}, {0, 3, 0, 255, 0}, {1, 1, 140, 68, 1}, {1, 0, 0, 255, 0}, {0, 4, 0, 255, 0}};
unsigned char qian[30][5]  = {{1, 1, 0, 255, 0}, {0, 3, 0, 255, 0}, {1, 1, 140, 68, 1}, {1, 0, 0, 255, 0}, {0, 4, 0, 255, 0}};
unsigned char xiacsd[3][5] = {{0, 5, 0, 254, 0}, {0, 0, 0, 0, 0}};

char zhiling[][20] = {
    // 机械臂动作
    "$DGT:1-1,1!",   // 所有复位 							0
    "$DGT:2-2,1!",   // 轮盘舵机推   					    1
    "$DGT:3-3,1!",   // 轮盘舵机收    					    2
    "$DGT:4-4,1!",   // 推饮料    		                   3
    "$DGT:6-13,1!",  // 上中抓方块    		                4
    "$DGT:14-21,1!", // 下中抓方块    		                5
};

// 方向0后退1前进2无3左4右5左移6右移
// 指令组下标为A,B,C,D对应各个区域，255为空,S为上，X为下，I为初始位置，1为轮盘复位
// 五个一组分别表示格数，方向，延时停车的延时时长ms，指令数组下标，等待机械臂延时s
unsigned char a[][5] = {
    // {0, 1, 30, 255, 0},
    // {0, 6, 0, 255, 80},
    // {0, 2, 0, 255, 10}, // 平移出去等一会儿
    // {0, 2, 0, 'A', 0},  // 发A拍照
    // {0, 2, 0, 255, 10}, // 停一会儿
    // {1, 1, 0, 255, 0},  // 前移一格
    // {0, 6, 0, 255, 5},  // 平移一点
    // {0, 2, 0, 'A', 0},  // 发A拍照
    // {0, 2, 0, 255, 10}, // 停一会儿
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'A', 0},
    // {0, 2, 0, 255, 20},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'A', 0},
    // {0, 2, 0, 255, 20},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'A', 0},
    // {0, 2, 0, 255, 20},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'A', 0},
    // {0, 2, 0, 255, 20},
    // {0, 2, 0, 'Z', 2}, // 因为抓的是1位置，所以要转一下才正确
    // {0, 2, 0, 'X', 1}, // 轮盘到下层
    // {0, 2, 0, 'P', 10},
    // {1, 0, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'P', 10},
    // {1, 0, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'P', 10},
    // {1, 0, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'P', 10},
    // {1, 0, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'P', 10},
    // {1, 0, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'P', 10},
    // {0, 5, 0, 255, 5},  // 退一下
    // {0, 2, 0, 'S', 10}, // 升
    // {0, 6, 0, 255, 5},  // 进去
    // {0, 2, 0, 'P', 10},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'P', 10},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'P', 10},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'P', 10},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'P', 10},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'P', 10},//A OK!

    // {1, 1, 0, 255, 0}, // i==1略过
    // {1, 1, 0, 255, 0},
    // {1, 1, 0, 255, 0},
    // {1, 1, 0, 255, 0},
    // {0, 3, 0, 255, 0},
    // {0, 6, 0, 255, 40},
    // {0, 2, 0, 'B', 0},
    // {0, 2, 0, 255, 5}, // 停一会儿
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'B', 0},
    // {0, 2, 0, 255, 5}, // 停一会儿
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'B', 0},
    // {0, 2, 0, 255, 5}, // 停一会儿
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'B', 0},
    // {0, 2, 0, 255, 5}, // 停一会儿
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'B', 0},
    // {0, 2, 0, 255, 5}, // 停一会儿
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 5},
    // {0, 2, 0, 'B', 0},
    // {0, 2, 0, 255, 5}, // 停一会儿
    // {0, 2, 0, 'X', 1}, // 轮盘到下层
    // {0, 2, 0, 'P', 10},
    // {1, 0, 0, 255, 0},
    // {0, 6, 0, 255, 10},
    // {0, 2, 0, 'P', 10},
    // {1, 0, 0, 255, 0},
    // {0, 6, 0, 255, 10},
    // {0, 2, 0, 'P', 10},
    // {1, 0, 0, 255, 0},
    // {0, 6, 0, 255, 10},
    // {0, 2, 0, 'P', 10},
    // {1, 0, 0, 255, 0},
    // {0, 6, 0, 255, 10},
    // {0, 2, 0, 'P', 10},
    // {1, 0, 0, 255, 0},
    // {0, 6, 0, 255, 10},
    // {0, 2, 0, 'P', 10},
    // {0, 5, 0, 255, 10}, // 退一下
    // {0, 2, 0, 'S', 10}, // 升
    // {0, 6, 0, 255, 10}, // 进去
    // {0, 2, 0, 'P', 10},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 10},
    // {0, 2, 0, 'P', 10},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 10},
    // {0, 2, 0, 'P', 10},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 10},
    // {0, 2, 0, 'P', 10},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 10},
    // {0, 2, 0, 'P', 10},
    // {1, 1, 0, 255, 0},
    // {0, 6, 0, 255, 10},
    // {0, 2, 0, 'P', 10},//BOK！

    {1, 1, 0, 255, 0}, // i==1略过
    {0, 5, 0, 255, 29},
    {0, 4, 0, 255, 0},
    {0, 0, 50, 255, 0},
    {0, 0, 50, 255, 0},
    {0, 6, 0, 255, 8},
    {1, 0, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'C', 5},
    {1, 0, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'C', 5},
    {1, 0, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'C', 5},
    {1, 0, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'C', 5},
    {1, 0, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'C', 5},
    {1, 0, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'C', 5},
    {0, 2, 0, 'X', 1}, // 轮盘到下层
    {0, 2, 0, 'P', 10},
    {1, 1, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'P', 10},
    {1, 1, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'P', 10},
    {1, 1, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'P', 10},
    {1, 1, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'P', 10},
    {1, 1, 0, 255, 0},
    {0, 6, 0, 255, 5},
    {0, 2, 0, 'P', 10},
    {0, 0, 0, 0, 0}};

unsigned char b[][5] = {

    {0, 0, 0, 0, 0}};

unsigned char c[][5] = {

    {0, 0, 0, 0, 0}};

unsigned char d[][5] = {

    {0, 0, 0, 0, 0}};

unsigned char e[][5] = {

    {0, 0, 0, 0, 0}};

// 中键
unsigned char a1[][5] = {

    {0, 0, 0, 0, 0}};

unsigned char b1[][5] = {

    {0, 0, 0, 0, 0}};

unsigned char c1[][5] = {
    {0, 0, 0, 0, 0}};

unsigned char d1[][5] = {

    {0, 0, 0, 0, 0}};

unsigned char e1[][5] = {

    {0, 0, 0, 0, 0}};
// 重启路线
unsigned char a2[][5] = {
    {0, 0, 0, 0, 0}};

unsigned char c2[][5] = {

    {0, 0, 0, 0, 0}};

unsigned char d2[][5] = {
    {0, 0, 0, 0, 0}};

unsigned char e2[][5] = {

    {0, 0, 0, 0, 0}};

unsigned char paizhao[][5] = {{1, 1, 0, 255, 0}};

typedef struct
{
    unsigned char KeyStatusIndex; // 当前的状态索引号
    unsigned char KeyOKStatus;    // 按下确认键时的状态索引号
    unsigned char KeyUpStatus;    // 按下向上键时的状态索引号
    unsigned char KeyDownStatus;  // 按下向下键时的状态索引号
    unsigned char KeyYou;
    unsigned char KeyBackStatus;  // 按下返回键时的状态索引号
    void (*CurrentOperate)(void); // 当前状态应该执行的功能操作
} StatusTab;
///////////////////////////////////////////////////////////////////////////

u8 move_flag  = 0; // 显示
u8 move_flag1 = 0; // 复制
u8 move_flag2 = 0;
u8 move_flag3 = 0;

extern u8 gImage_set[];
extern u8 gImage_timer[];
extern u8 gImage_Internet[];
extern u8 gImage_Tem[];
extern u8 gImage_benz[];

extern byte xinghao[];
extern byte xinghao2[];
extern byte xinghao3[];
extern byte xinghao4[];

#define UIMAX 7 // 调试界面总数-1

u8 KeyFuncIndex = 2; // 存放当前的菜单索引

void (*KeyFuncPtr)(void); // 定义按键功能指针

#define Picture_X      2
#define Picture_Y      19
#define Picture_HIGH   24
#define Picture_SIZE   72
#define Picture_OFFSET 24

// KeyStatusIndex;   //当前的状态索引号
// KeyOKStatus;      //按下确认键时的状态索引号
// KeyUpStatus;      //按下向上键时的状态索引号
// KeyDownStatus;    //按下向下键时的状态索引号
// KeyYou            //按下 右键时的状态索引号
// KeyBackStatus;    //按下返回键时的状态索引号
//(*CurrentOperate)(void);      //当前状态应该执行的功能操作
//////////////////////////////////////////////////////////////////////////////////
// 定义菜单切换链表
StatusTab KeyTab[MENU_SIZE] =
    {
        /*当前索引号 确认 上 下 右 左  */
        {0, 5, 4, 1, 1, 4, (*Debug)},         // 选中：设置
        {1, 21, 0, 2, 2, 0, (*Internet_Set)}, // 选中：路线
        {2, 24, 1, 3, 3, 1, (*Temp_Set)},     // 选中：开车
        {3, 17, 2, 4, 4, 2, (*Clock)},        // 选中：路线设置
        {4, 15, 3, 0, 0, 3, (*Drive)},        // 选中：舵机

        {5, 7, 13, 6, 0, 0, (*Debug_Set)},      // 设置1
        {6, 0, 5, 13, 0, 0, (*Set_a)},          // 设置2
        {7, 10, 9, 8, 0, 5, (*Set_b)},          // 设置1-调1
        {8, 11, 7, 9, 0, 5, (*Set_c)},          // 设置1-调2
        {9, 12, 8, 7, 0, 5, (*Set_d)},          // 设置1-调3
        {10, 0, 0, 0, 0, 7, (*Set_e)},          // 设置1-调1-1
        {11, 0, 0, 0, 0, 8, (*Set_f)},          // 设置1-调2-1
        {12, 0, 0, 0, 0, 9, (*Set_g)},          // 设置1-调3-1
        {13, 14, 6, 5, 14, 0, (*Set_188)},      // 设置3
        {14, 13, 14, 14, 14, 13, (*Set_188_a)}, // 显示1循迹

        {15, 15, 0, 0, 0, 4, (*Drive_a)}, // 舵机动作

        {16, 16, 0, 0, 0, 20, (*Clock_a)},   // 路线设置
        {17, 20, 19, 18, 20, 3, (*Clock_b)}, // 自设1
        {18, 20, 17, 19, 20, 3, (*Clock_c)}, // 自设2
        {19, 20, 18, 17, 20, 3, (*Clock_d)}, // 自设3
        {20, 0, 20, 20, 16, 17, (*Clock_e)}, // 路线观看

        {21, 0, 23, 22, 0, 1, (*Net_a)}, // 初启_路线_双
        {22, 0, 21, 23, 0, 1, (*Net_b)}, // 重启_路线_双
        {23, 0, 22, 21, 0, 1, (*Net_c)}, // 再启_路线_双

        {24, 0, 26, 25, 0, 2, (*Net_d)}, // 初启_路线
        {25, 0, 24, 26, 0, 2, (*Net_e)}, // 重启_路线
        {26, 0, 25, 24, 0, 2, (*Net_f)}, // 再启_路线
};
// 运行路线数组函数，写路线数组时要数数组个数写进这个函数第二个变量中
// 路线数组五个一组分别表示格数，方向，延时停车的延时时长ms，指令数组下标，等待机械臂延时s
void change(unsigned char (*a)[5], unsigned char len)
{
    uchar i, j, pinf_qian = 0, num = 0, relen = 0, index = 0, ret = 1;
    int pinf       = 0;
    u8 dist[9]     = {0};
    char s[100]    = "";
    int breakcnt   = 0;
    int real_dis_x = 0;
    int xx         = 0;
    int count_once = 0;

    // printf("$DGT:11-11,1!");
    for (i = 0; a[i][0] + a[i][1] + a[i][2] + a[i][3] + a[i][4] > 0; i++) {
        xx  = 0;
        LED = 0;
        if (i == 0) {
            // 			printf("$DGT:10-10,1!");
            // 			delay_ms(1000);
            // 			printf("$DGT:10-10,1!");
            // 			delay_ms(1000);
            // //			for(j=0;j<10;j++)//开车延时，正式比赛时解开注释
            // //			delay_ms(1000);
            HandInit();
            BMQ_MOVE(a[i][1], a[i][2], 0);
        } else {
            if (a[i][2] != 0) {
                if (a[i][2] > 58)
                    DJ_MOVE_YS(a[i][0], a[i][1], 1, a[i][2]);
                else {
                    BMQ_MOVE(a[i][1], a[i][2], 0);
                    xx = a[i][2];
                }

            } else if (a[i][1] != 2)               
                DJ_MOVE_BUFF_SET(a[i][0], a[i][1], a[i][4]); // 循迹移动函数   格数  方向  平移延时
            if (a[i][3] != 255) {
                stop();
                if (a[i][3] == 'I' || a[i][3] == 'S' || a[i][3] == 'X') {//步进电机
                    BuJin_Zhuan(a[i][3]);
                    for (u8 it = 0; it < a[i][4]; it++)
                        delay_ms(100);
                } else if (a[i][3] == 'Z') { // 轮盘转
                    LunPan_Zhuan();
                    for (u8 it = 0; it < a[i][4]; it++)
                        delay_ms(100);
                } else if (a[i][3] == 'P') // 算法
                {
                    Zhua(exFlag_HuoJia);
                    for (u8 it = 0; it < a[i][4]; it++)
                        delay_ms(100);
                } else if (a[i][3] == 'A' || a[i][3] == 'B' || a[i][3] == 'C' || a[i][3] == 'D') { // 给nano发数据
                    Nano_ChuLi(a[i][3]);
                    for (u8 it = 0; it < a[i][4]; it++)
                        delay_ms(100);
                }
            }
            if (a[i][1] == 2 && a[i][4] != 0 && a[i][3] == 255) // 啥都不做时延时
            {
                for (u8 it = 0; it <= a[i][4]; it++) {
                    delay_ms(100);
                }
            }
            stop();

        }
    }
}
void change_uart(unsigned char (*a)[5], unsigned char len)
{
    ;
}

void OLED_tou(void)
{
    static u8 a = 0;
    a++;
    if (a >= 100) a = 0;
    if (a == 0) LCD_CLS_06();

    if (Bluetooth2 == 1 && Bluetooth3 == 1) {
        Draw_BMP(0, 0, 23, 1, xinghao3);
        Draw_BMP(24, 0, 40, 1, xinghao4);
    } else if (Bluetooth2 == 1 || Bluetooth3 == 1) {
        Draw_BMP(0, 0, 23, 1, xinghao3);
    }

    else
        Draw_BMP(0, 0, 31, 1, xinghao2);

    Draw_Power(750, 0);

    switch (KeyTab[KeyFuncIndex].KeyStatusIndex) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            LCD_16_HanZi_ASCII(6, 0, "底车");
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            LCD_16_HanZi_ASCII(6, 0, "设置");
            break;
        case 15:
            LCD_16_HanZi_ASCII(6, 0, "舵机");
            break;
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            LCD_16_HanZi_ASCII(6, 0, "路线");
            break;
        case 21:
        case 22:
        case 23:
            LCD_16_HanZi_ASCII(6, 0, "双车");
            break;
        case 24:
        case 25:
        case 26:
            LCD_16_HanZi_ASCII(6, 0, "开车");
            break;

        default:
            break;
    }
    //	if(Bluetooth2 == 0)
    //	{
    //		SHAUNG_FLAG = 0;
    //	}
    //
    //	if(SHAUNG_FLAG == 1)
    //	{
    //		S_D_LED = 0;
    //	}
    //	else
    //		S_D_LED = 1;
}
void Debug(void)
{
    OLED_tou();

    OLED_CLS(0);
    OLED_DrawPicture(Picture_X + 0 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_set, 0);
    OLED_DrawPicture(Picture_X + 1 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_Internet, 1);
    OLED_DrawPicture(Picture_X + 2 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_benz, 1);
    OLED_DrawPicture(Picture_X + 3 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_timer, 1);
    OLED_DrawPicture(Picture_X + 4 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_Tem, 1);
    OLED_DrawHanzi(47, 47, "设置", 1);

    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            break;
            //			MenuOperate();
        }
    }
}
void Internet_Set(void)
{
    OLED_tou();

    OLED_CLS(0);
    OLED_DrawPicture(Picture_X + 0 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_set, 1);
    OLED_DrawPicture(Picture_X + 1 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_Internet, 0);
    OLED_DrawPicture(Picture_X + 2 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_benz, 1);
    OLED_DrawPicture(Picture_X + 3 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_timer, 1);
    OLED_DrawPicture(Picture_X + 4 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_Tem, 1);

    OLED_DrawHanzi(47, 47, "双车", 1);

    OLED_Refresh();

    printf("DAN\r\n");

    while (1) {

        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            break;
            //			MenuOperate();
        }
    }
}
void Temp_Set()
{
    OLED_tou();

    OLED_CLS(0);
    OLED_DrawPicture(Picture_X + 0 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_set, 1);
    OLED_DrawPicture(Picture_X + 1 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_Internet, 1);
    OLED_DrawPicture(Picture_X + 2 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_benz, 0);
    OLED_DrawPicture(Picture_X + 3 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_timer, 1);
    OLED_DrawPicture(Picture_X + 4 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_Tem, 1);
    OLED_DrawHanzi(47, 47, "开车", 1);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            break;
            //			MenuOperate();
        }
    }
}
void Clock()
{
    OLED_tou();

    OLED_CLS(0);
    OLED_DrawPicture(Picture_X + 0 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_set, 1);
    OLED_DrawPicture(Picture_X + 1 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_Internet, 1);
    OLED_DrawPicture(Picture_X + 2 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_benz, 1);
    OLED_DrawPicture(Picture_X + 3 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_timer, 0);
    OLED_DrawPicture(Picture_X + 4 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_Tem, 1);
    OLED_DrawHanzi(31, 47, "路线设置", 1);
    OLED_Refresh();
    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            break;
            //			MenuOperate();
        }
    }
}

void Drive(void)
{
    OLED_tou();

    OLED_CLS(0);
    OLED_DrawPicture(Picture_X + 0 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_set, 1);
    OLED_DrawPicture(Picture_X + 1 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_Internet, 1);
    OLED_DrawPicture(Picture_X + 2 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_benz, 1);
    OLED_DrawPicture(Picture_X + 3 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_timer, 1);
    OLED_DrawPicture(Picture_X + 4 * Picture_OFFSET, Picture_Y, Picture_HIGH, Picture_SIZE, gImage_Tem, 0);
    OLED_DrawHanzi(31, 47, "舵机调节", 1);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            break;
            //			MenuOperate();
        }
    }
}

void Debug_Set(void)
{

    ce_move2_BUFF[0][2] = ce_move1_BUFF[0][2];
    ce_move2_BUFF[1][2] = ce_move1_BUFF[0][2] - 1;
    if (ce_move2_BUFF[1][2] <= 1)
        ce_move2_BUFF[1][2] = 1;
    ce_move2_BUFF[2][2] = ce_move1_BUFF[0][2];
    ce_move2_BUFF[3][2] = ce_move1_BUFF[0][2] - 1;
    if (ce_move2_BUFF[3][2] <= 1)
        ce_move2_BUFF[3][2] = 1;

    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "路线", 0);
    OLED_ShowxcString(32, 16, "5x0", 16, 0);
    OLED_DrawHanzi(0, 32, "路线", 1);
    OLED_ShowxcString(32, 32, "5x2", 16, 1);
    OLED_DrawHanzi(0, 48, "循迹", 1);
    OLED_ShowxcString(32, 48, "ST188", 16, 1);
    OLED_ShowxcNum(96, 16, speed_carrage[ce_move1_BUFF[0][2]], 2, 16, 0);
    OLED_ShowxcNum(96, 32, speed_carrage[ce_move2_BUFF[0][2]], 2, 16, 1);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            if (KEY_TYPE == 'y') {
                LCD_16_HanZi_ASCII(10, 6, "go");
                ce_1();
                LCD_16_HanZi_ASCII(10, 6, "  ");
            } else
                break;
        }
    }
}
void Set_a(void)
{
    ce_move2_BUFF[0][2] = ce_move1_BUFF[0][2];
    ce_move2_BUFF[1][2] = ce_move1_BUFF[0][2] - 1;
    if (ce_move2_BUFF[1][2] <= 1)
        ce_move2_BUFF[1][2] = 1;
    ce_move2_BUFF[2][2] = ce_move1_BUFF[0][2];
    ce_move2_BUFF[3][2] = ce_move1_BUFF[0][2] - 1;
    if (ce_move2_BUFF[3][2] <= 1)
        ce_move2_BUFF[3][2] = 1;

    OLED_tou();

    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "路线", 1);
    OLED_ShowxcString(32, 16, "5x0", 16, 1);
    OLED_DrawHanzi(0, 32, "路线", 0);
    OLED_ShowxcString(32, 32, "5x2", 16, 0);
    OLED_DrawHanzi(0, 48, "循迹", 1);
    OLED_ShowxcString(32, 48, "ST188", 16, 1);
    OLED_ShowxcNum(96, 16, speed_carrage[ce_move1_BUFF[0][2]], 2, 16, 1);
    OLED_ShowxcNum(96, 32, speed_carrage[ce_move2_BUFF[0][2]], 2, 16, 0);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            if (KEY_TYPE == 'y' || KEY_TYPE == 'o') {
                LCD_16_HanZi_ASCII(10, 6, "go");
                ce_2();
                LCD_16_HanZi_ASCII(10, 6, "  ");
            } else
                break;
            //			MenuOperate();
        }
    }
}
void Set_b(void)
{

    OLED_tou();

    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "速度调节", 0);
    OLED_DrawHanzi(0, 32, "参数调节", 1);
    OLED_ShowxcNum(96, 16, speed_carrage[ce_move1_BUFF[0][2]], 2, 16, 1);
    OLED_ShowxcString(0, 48, "KP:", 16, 1);
    OLED_ShowxcString(56, 48, "KD:", 16, 1);
    OLED_ShowxcNum(24, 48, velocity_PID_KP_qh[ce_move1_BUFF[0][2]], 3, 16, 1);
    OLED_ShowxcNum(80, 48, velocity_PID_KD_qh[ce_move1_BUFF[0][2]], 3, 16, 1);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            if (KEY_TYPE == 'y') {
                LCD_16_HanZi_ASCII(12, 4, "go");
                ce_1();
                LCD_16_HanZi_ASCII(12, 4, "  ");
            } else
                break;
            //			MenuOperate();
        }
    }
}
void Set_c(void)
{
    OLED_tou();

    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "速度调节", 1);
    OLED_DrawHanzi(0, 32, "参数调节", 0);
    OLED_ShowxcNum(96, 16, speed_carrage[ce_move1_BUFF[0][2]], 2, 16, 1);
    OLED_ShowxcString(0, 48, "KP:", 16, 0);
    OLED_ShowxcString(56, 48, "KD:", 16, 1);
    OLED_ShowxcNum(24, 48, velocity_PID_KP_qh[ce_move1_BUFF[0][2]], 3, 16, 1);
    OLED_ShowxcNum(80, 48, velocity_PID_KD_qh[ce_move1_BUFF[0][2]], 3, 16, 1);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            if (KEY_TYPE == 'y') {
                LCD_16_HanZi_ASCII(12, 4, "go");
                ce_1();
                LCD_16_HanZi_ASCII(12, 4, "  ");
            } else
                break;
            //			MenuOperate();
        }
    }
}
void Set_d(void)
{
    OLED_tou();

    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "速度调节", 1);
    OLED_DrawHanzi(0, 32, "参数调节", 0);
    OLED_ShowxcNum(96, 16, speed_carrage[ce_move1_BUFF[0][2]], 2, 16, 1);
    OLED_ShowxcString(0, 48, "KP:", 16, 1);
    OLED_ShowxcString(56, 48, "KD:", 16, 0);
    OLED_ShowxcNum(24, 48, velocity_PID_KP_qh[ce_move1_BUFF[0][2]], 3, 16, 1);
    OLED_ShowxcNum(80, 48, velocity_PID_KD_qh[ce_move1_BUFF[0][2]], 3, 16, 1);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            if (KEY_TYPE == 'y') {
                LCD_16_HanZi_ASCII(12, 4, "go");
                ce_1();
                LCD_16_HanZi_ASCII(12, 4, "  ");
            } else
                break;
            //			MenuOperate();
        }
    }
}
void Set_e(void)
{
    OLED_tou();

    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "速度调节", 0);
    OLED_DrawHanzi(0, 32, "参数调节", 1);
    OLED_ShowxcNum(96, 16, speed_carrage[ce_move1_BUFF[0][2]], 2, 16, 0);
    OLED_ShowxcString(0, 48, "KP:", 16, 1);
    OLED_ShowxcString(56, 48, "KD:", 16, 1);
    OLED_ShowxcNum(24, 48, velocity_PID_KP_qh[ce_move1_BUFF[0][2]], 3, 16, 1);
    OLED_ShowxcNum(80, 48, velocity_PID_KD_qh[ce_move1_BUFF[0][2]], 3, 16, 1);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        OLED_CLS_67(0);
        OLED_ShowxcString(0, 48, "KP:", 16, 1);
        OLED_ShowxcString(56, 48, "KD:", 16, 1);
        OLED_ShowxcNum(96, 16, speed_carrage[ce_move1_BUFF[0][2]], 2, 16, 0);
        OLED_ShowxcNum(24, 48, velocity_PID_KP_qh[ce_move1_BUFF[0][2]], 3, 16, 0);
        OLED_ShowxcNum(80, 48, velocity_PID_KD_qh[ce_move1_BUFF[0][2]], 3, 16, 0);
        OLED_Refresh();

        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;

            switch (KEY_TYPE) {
                case 'y':
                    LCD_16_HanZi_ASCII(12, 4, "go");
                    ce_1();
                    LCD_16_HanZi_ASCII(12, 4, "  ");
                    break;
                case 'z': // 向左按键
                    save_to_flash();

                    break;
                case 's':
                    ce_move1_BUFF[0][2] = ce_move1_BUFF[0][2] + 1; // 向上按键

                    if (ce_move1_BUFF[0][2] >= 4) {
                        ce_move1_BUFF[0][2] = 4;
                    }
                    ce_move1_BUFF[1][2] = ce_move1_BUFF[0][2];

                    break;
                case 'x': // 向下按键
                    ce_move1_BUFF[0][2] = ce_move1_BUFF[0][2] - 1;
                    if (ce_move1_BUFF[0][2] <= 1) {
                        ce_move1_BUFF[0][2] = 1;
                    }
                    ce_move1_BUFF[1][2] = ce_move1_BUFF[0][2];

                    break;
                case 'o': // 中间按键
                    LCD_16_HanZi_ASCII(12, 4, "go");
                    ce_1();
                    LCD_16_HanZi_ASCII(12, 4, "  ");

                    break;
                case '#': // 向左按键
                    save_to_flash();

                    break;
                default:

                    break;
            }
            if (KEY_TYPE == 'z' || KEY_TYPE == '#') {
                break;
            }
        }
    }
}
void Set_f(void)
{
    OLED_tou();

    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "速度调节", 1);
    OLED_DrawHanzi(0, 32, "参数调节", 0);
    OLED_ShowxcNum(96, 16, speed_carrage[ce_move1_BUFF[0][2]], 2, 16, 1);
    OLED_ShowxcString(0, 48, "KP:", 16, 0);
    OLED_ShowxcString(56, 48, "KD:", 16, 1);
    OLED_ShowxcNum(24, 48, velocity_PID_KP_qh[ce_move1_BUFF[0][2]], 3, 16, 0);
    OLED_ShowxcNum(80, 48, velocity_PID_KD_qh[ce_move1_BUFF[0][2]], 3, 16, 1);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        OLED_ShowxcNum(24, 48, velocity_PID_KP_qh[ce_move1_BUFF[0][2]], 3, 16, 0);
        OLED_Refresh();

        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;

            switch (KEY_TYPE) {
                case 'y':
                    LCD_16_HanZi_ASCII(12, 4, "go");
                    ce_1();
                    LCD_16_HanZi_ASCII(12, 4, "  ");
                    break;
                case 'z': // 向左按键
                    save_to_flash();

                    break;
                case 's':
                    velocity_PID_KP_qh[ce_move1_BUFF[0][2]] = velocity_PID_KP_qh[ce_move1_BUFF[0][2]] + 1; // 向上按键

                    break;
                case 'x':                                                                                  // 向下按键
                    velocity_PID_KP_qh[ce_move1_BUFF[0][2]] = velocity_PID_KP_qh[ce_move1_BUFF[0][2]] - 1; // 向上按键

                    break;
                case 'o': // 中间按键
                    LCD_16_HanZi_ASCII(12, 4, "go");
                    ce_1();
                    LCD_16_HanZi_ASCII(12, 4, "  ");
                    break;
                case '#': // 向左按键
                    save_to_flash();

                    break;
                default:

                    break;
            }
            if (KEY_TYPE == 'z' || KEY_TYPE == '#') {
                break;
            }
        }
    }
}

void Set_g(void)
{
    OLED_tou();

    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "速度调节", 1);
    OLED_DrawHanzi(0, 32, "参数调节", 0);
    OLED_ShowxcNum(96, 16, speed_carrage[ce_move1_BUFF[0][2]], 2, 16, 1);
    OLED_ShowxcString(0, 48, "KP:", 16, 1);
    OLED_ShowxcString(56, 48, "KD:", 16, 0);
    OLED_ShowxcNum(24, 48, velocity_PID_KP_qh[ce_move1_BUFF[0][2]], 3, 16, 1);
    OLED_ShowxcNum(80, 48, velocity_PID_KD_qh[ce_move1_BUFF[0][2]], 3, 16, 0);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        OLED_ShowxcNum(80, 48, velocity_PID_KD_qh[ce_move1_BUFF[0][2]], 3, 16, 0);
        OLED_Refresh();

        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;

            switch (KEY_TYPE) {
                case 'y':
                    LCD_16_HanZi_ASCII(12, 4, "go");
                    ce_1();
                    LCD_16_HanZi_ASCII(12, 4, "  ");
                    break;
                case 'z': // 向左按键
                    save_to_flash();

                    break;
                case 's':
                    velocity_PID_KD_qh[ce_move1_BUFF[0][2]] = velocity_PID_KD_qh[ce_move1_BUFF[0][2]] + 1; // 向上按键

                    break;
                case 'x':                                                                                  // 向下按键
                    velocity_PID_KD_qh[ce_move1_BUFF[0][2]] = velocity_PID_KD_qh[ce_move1_BUFF[0][2]] - 1; // 向上按键

                    break;
                case 'o': // 中间按键

                    LCD_16_HanZi_ASCII(12, 4, "go");
                    ce_1();
                    LCD_16_HanZi_ASCII(12, 4, "  ");
                    break;
                case '#': // 向左按键
                    save_to_flash();

                    break;
                default:

                    break;
            }
            if (KEY_TYPE == 'z' || KEY_TYPE == '#') {
                break;
            }
        }
    }
}
void Set_188(void)
{
    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "路线", 1);
    OLED_ShowxcString(32, 16, "5x0", 16, 1);
    OLED_DrawHanzi(0, 32, "路线", 1);
    OLED_ShowxcString(32, 32, "5x2", 16, 1);
    OLED_DrawHanzi(0, 48, "循迹", 0);
    OLED_ShowxcString(32, 48, "ST188", 16, 0);

    OLED_ShowxcNum(96, 16, speed_carrage[ce_move1_BUFF[0][2]], 2, 16, 1);
    OLED_ShowxcNum(96, 32, speed_carrage[ce_move2_BUFF[0][2]], 2, 16, 1);
    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            break;
        }
    }
}
void Set_188_a(void)
{
    u8 k = 0;
    LCD_CLS();
    oled_st188 = 1;
    k          = k;
    while (1) {
        k = St188_Scanf(1);
        k = St178_Scanf(1);

        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            oled_st188  = 0;
            break;
        }
    }
}

void Drive_a(void)
{
    static u8 dj = 0;

    OLED_tou();
    OLED_CLS(0);
    OLED_ShowxcString(0, 16, "1.", 16, 1);
    OLED_DrawHanzi(16, 16, "张开", 1);
    OLED_ShowxcString(64, 16, "2.", 16, 1);
    OLED_DrawHanzi(80, 16, "三角", 1);
    OLED_ShowxcString(0, 32, "3.", 16, 1);
    OLED_DrawHanzi(16, 32, "伸直", 1);
    OLED_ShowxcString(64, 32, "4.", 16, 1);
    OLED_DrawHanzi(80, 32, "收回", 1);
    OLED_ShowxcString(0, 48, "O.", 16, 1);
    OLED_DrawHanzi(16, 48, "设置", 1);
    OLED_Refresh();

    while (1) {
        if (dj == 0) {
            OLED_ShowxcString(64, 48, "z.", 16, 1);
            OLED_DrawHanzi(80, 48, "收回", 1);
            OLED_Refresh();
        } else {
            OLED_ShowxcString(64, 48, "      ", 16, 1);
            OLED_Refresh();
        }
        OLED_tou();
        AD_AnJian();
        //		if(Keykey_Flag==1)
        //		{
        //			Keykey_Flag=0;
        //			switch(KEY_TYPE)
        //			{
        //				case  '1':Hand_BAZI();
        //							break;
        //				case  '2':Hand_SANJIAO();
        //							break;
        //				case  '3':Hand_SHENZHI();
        //							break;
        //				case  '4':Hand_SHOUHUI();
        //							break;
        //				case  'z':if(dj == 0)		Hand_SHOUHUI();
        //							break;
        //				case  'y':dj = !dj;
        //							break;
        //				default:

        //				break;
        //			}
        //			if(KEY_TYPE == 'z'||KEY_TYPE == '0'||KEY_TYPE == '#')
        //			{
        //				break;
        //			}
        //		}
    }
}
void Drive_b(void)
{
}
void Drive_c(void)
{
}
void Drive_d(void)
{
}
void Clock_a(void)
{

    u8 x = 0, y = 16, x1 = 0, y1 = 16;
    u8 sum_flag = 1;
    u8 an_flag = 0, an_flag1 = 0, brck = 0;
    u8 hang = 0;
    u8 i    = 0;

    LCD_CLS();
    OLED_tou();
    OLED_CLS(0);

    if (move_flag == 1)
        for (x = 0; x < 2; x++) {
            for (y = 0; y < 12; y++) {
                move_BUFF_SET[y][x] = 0;
            }
        }
    else if (move_flag == 2) {
        for (i = 0; i < 4; i++) {
            if (move_BUFF_SET2[i][0] == 0 && move_BUFF_SET2[i][1] == 0) {
                OLED_ShowxcString(i * 32, 16, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET2[i][1]) {
                    case 1:
                        OLED_DrawHanzi(i * 32, 16, "前", 0);
                        break;
                    case 0:
                        OLED_DrawHanzi(i * 32, 16, "后", 0);
                        break;
                    case 3:
                        OLED_DrawHanzi(i * 32, 16, "左", 0);
                        break;
                    case 4:
                        OLED_DrawHanzi(i * 32, 16, "右", 0);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum(i * 32 + 16, 16, move_BUFF_SET2[i][0], 1, 16, 1);

                x = i * 32 + 32;
                y = 16;
                hang++;
            }
        }
        for (i = 4; i < 8; i++) {
            if (move_BUFF_SET2[i][0] == 0 && move_BUFF_SET2[i][1] == 0) {
                OLED_ShowxcString((i - 4) * 32, 32, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET2[i][1]) {
                    case 1:
                        OLED_DrawHanzi((i - 4) * 32, 32, "前", 0);
                        break;
                    case 0:
                        OLED_DrawHanzi((i - 4) * 32, 32, "后", 0);
                        break;
                    case 3:
                        OLED_DrawHanzi((i - 4) * 32, 32, "左", 0);
                        break;
                    case 4:
                        OLED_DrawHanzi((i - 4) * 32, 32, "右", 0);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum((i - 4) * 32 + 16, 32, move_BUFF_SET2[i][0], 1, 16, 1);
                x = (i - 4) * 32 + 32;
                y = 32;
                hang++;
            }
        }
        for (i = 8; i < 12; i++) {
            if (move_BUFF_SET2[i][0] == 0 && move_BUFF_SET2[i][1] == 0) {
                OLED_ShowxcString((i - 8) * 32, 48, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET2[i][1]) {
                    case 1:
                        OLED_DrawHanzi((i - 8) * 32, 48, "前", 0);
                        break;
                    case 0:
                        OLED_DrawHanzi((i - 8) * 32, 48, "后", 0);
                        break;
                    case 3:
                        OLED_DrawHanzi((i - 8) * 32, 48, "左", 0);
                        break;
                    case 4:
                        OLED_DrawHanzi((i - 8) * 32, 48, "右", 0);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum((i - 8) * 32 + 16, 48, move_BUFF_SET2[i][0], 1, 16, 1);
                x = (i - 8) * 32 + 32;
                y = 48;
                hang++;
            }
        }
    }

    else if (move_flag == 3) {
        for (i = 0; i < 4; i++) {
            if (move_BUFF_SET3[i][0] == 0 && move_BUFF_SET3[i][1] == 0) {
                OLED_ShowxcString(i * 32, 16, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET3[i][1]) {
                    case 1:
                        OLED_DrawHanzi(i * 32, 16, "前", 0);
                        break;
                    case 0:
                        OLED_DrawHanzi(i * 32, 16, "后", 0);
                        break;
                    case 3:
                        OLED_DrawHanzi(i * 32, 16, "左", 0);
                        break;
                    case 4:
                        OLED_DrawHanzi(i * 32, 16, "右", 0);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum(i * 32 + 16, 16, move_BUFF_SET3[i][0], 1, 16, 1);

                x = i * 32 + 32;
                y = 16;
                hang++;
            }
        }
        for (i = 4; i < 8; i++) {
            if (move_BUFF_SET3[i][0] == 0 && move_BUFF_SET3[i][1] == 0) {
                OLED_ShowxcString((i - 4) * 32, 32, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET3[i][1]) {
                    case 1:
                        OLED_DrawHanzi((i - 4) * 32, 32, "前", 0);
                        break;
                    case 0:
                        OLED_DrawHanzi((i - 4) * 32, 32, "后", 0);
                        break;
                    case 3:
                        OLED_DrawHanzi((i - 4) * 32, 32, "左", 0);
                        break;
                    case 4:
                        OLED_DrawHanzi((i - 4) * 32, 32, "右", 0);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum((i - 4) * 32 + 16, 32, move_BUFF_SET3[i][0], 1, 16, 1);
                x = (i - 4) * 32 + 32;
                y = 32;
                hang++;
            }
        }
        for (i = 8; i < 12; i++) {
            if (move_BUFF_SET3[i][0] == 0 && move_BUFF_SET3[i][1] == 0) {
                OLED_ShowxcString((i - 8) * 32, 48, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET3[i][1]) {
                    case 1:
                        OLED_DrawHanzi((i - 8) * 32, 48, "前", 0);
                        break;
                    case 0:
                        OLED_DrawHanzi((i - 8) * 32, 48, "后", 0);
                        break;
                    case 3:
                        OLED_DrawHanzi((i - 8) * 32, 48, "左", 0);
                        break;
                    case 4:
                        OLED_DrawHanzi((i - 8) * 32, 48, "右", 0);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum((i - 8) * 32 + 16, 48, move_BUFF_SET3[i][0], 1, 16, 1);
                x = (i - 8) * 32 + 32;
                y = 48;
                hang++;
            }
        }
    }

    OLED_Refresh();
    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            if (hang >= 11) hang = 11;

            Keykey_Flag = 0;

            if (KEY_TYPE != '*')
                an_flag = 0;
            if (KEY_TYPE != 'o')
                an_flag1 = 0;
            if (move_flag == 1) {
                if (move_BUFF_SET[0][0] == 0 && move_BUFF_SET[0][1] == 0) {
                    hang = 0;
                }
                switch (KEY_TYPE) {
                    case 'y':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "右", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET[hang][1] = 4;
                        }
                        break;
                    case 'z':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "左", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET[hang][1] = 3;
                        }

                        break;
                    case 's':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "前", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET[hang][1] = 1;
                        }
                        break;
                    case 'x':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "后", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET[hang][1] = 0;
                        }
                        break;
                    case '0':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "O", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET[hang][0] = 0;
                            hang++;
                        }
                        break;
                    case '1':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "1", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET[hang][0] = 1;
                            hang++;
                        }
                        break;
                    case '2':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "2", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET[hang][0] = 2;
                            hang++;
                        }
                        break;
                    case '3':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "3", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET[hang][0] = 3;
                            hang++;
                        }
                        break;
                    case '4':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "4", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET[hang][0] = 4;
                            hang++;
                        }
                        break;
                    case '5':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "5", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET[hang][0] = 5;
                            hang++;
                        }
                        break;
                    case '6':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "6", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET[hang][0] = 6;
                            hang++;
                        }
                        break;
                    case '7':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "7", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET[hang][0] = 7;
                            hang++;
                        }
                        break;
                    case '8':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "8", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET[hang][0] = 8;
                            hang++;
                        }
                        break;
                    case '9':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "9", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET[hang][0] = 9;
                            hang++;
                        }
                        break;
                    case '*':
                        an_flag++;
                        if (an_flag >= 2) {
                            if (move_BUFF_SET[0][0] == 0 && move_BUFF_SET[0][1] == 0) {
                                hang = 0;
                            } else {
                                if (sum_flag == 0) {
                                    move_BUFF_SET[hang - 1][1] = 0; // bu zou
                                    if (hang <= 1)
                                        hang = 1;
                                    else
                                        hang--;
                                } else {
                                    move_BUFF_SET[hang - 1][0] = 0;
                                }
                            }

                            an_flag  = 0;
                            sum_flag = !sum_flag;
                            x        = x1;
                            y        = y1;
                            OLED_ShowxcString(x, y, "  ", 16, 1);
                            OLED_Refresh();

                            if (x1 == 0 && y1 == 16) {
                                sum_flag = 1;
                                break;
                            }
                            if (x >= 16)
                                x1 -= 16;

                            else {
                                x1 = 127;
                                y1 -= 16;
                            }
                        }

                        break;
                    case 'o':
                        an_flag1++;
                        if (an_flag1 >= 2) {
                            an_flag1 = 0;
                            DJ_MOVE_BUFF_shuzu(move_BUFF_SET, hang);
                        }

                        break;
                    case '#':
                        brck               = 1;
                        KEY_TYPE           = 'z';
                        move_BUFF_SET_hang = hang;
                        break;
                    default:

                        break;
                }
                if (brck == 1 && KEY_TYPE == 'z') break;

            } else if (move_flag == 2) {
                if (move_BUFF_SET2[0][0] == 0 && move_BUFF_SET2[0][1] == 0) {
                    hang = 0;
                }
                switch (KEY_TYPE) {
                    case 'y':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "右", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET2[hang][1] = 4;
                        }
                        break;
                    case 'z':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "左", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET2[hang][1] = 3;
                        }

                        break;
                    case 's':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "前", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET2[hang][1] = 1;
                        }
                        break;
                    case 'x':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "后", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET2[hang][1] = 0;
                        }
                        break;
                    case '0':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "O", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET2[hang][0] = 0;
                            hang++;
                        }
                        break;
                    case '1':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "1", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET2[hang][0] = 1;
                            hang++;
                        }
                        break;
                    case '2':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "2", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET2[hang][0] = 2;
                            hang++;
                        }
                        break;
                    case '3':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "3", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET2[hang][0] = 3;
                            hang++;
                        }
                        break;
                    case '4':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "4", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET2[hang][0] = 4;
                            hang++;
                        }
                        break;
                    case '5':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "5", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET2[hang][0] = 5;
                            hang++;
                        }
                        break;
                    case '6':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "6", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET2[hang][0] = 6;
                            hang++;
                        }
                        break;
                    case '7':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "7", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET2[hang][0] = 7;
                            hang++;
                        }
                        break;
                    case '8':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "8", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET2[hang][0] = 8;
                            hang++;
                        }
                        break;
                    case '9':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "9", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET2[hang][0] = 9;
                            hang++;
                        }
                        break;
                    case '*':
                        an_flag++;
                        if (an_flag >= 2) {
                            if (move_BUFF_SET2[0][0] == 0 && move_BUFF_SET2[0][1] == 0) {
                                hang = 0;
                            } else {
                                if (sum_flag == 0) {
                                    move_BUFF_SET2[hang - 1][1] = 0; // bu zou
                                    if (hang <= 1)
                                        hang = 1;
                                    else
                                        hang--;
                                } else {
                                    move_BUFF_SET2[hang - 1][0] = 0;
                                }
                            }

                            an_flag  = 0;
                            sum_flag = !sum_flag;
                            x        = x1;
                            y        = y1;
                            OLED_ShowxcString(x, y, "  ", 16, 1);
                            OLED_Refresh();

                            if (x1 == 0 && y1 == 16) {
                                sum_flag = 1;
                                break;
                            }
                            if (x >= 16)
                                x1 -= 16;

                            else {
                                x1 = 127;
                                y1 -= 16;
                            }
                        }

                        break;
                    case 'o':
                        an_flag1++;
                        if (an_flag1 >= 2) {
                            an_flag1 = 0;
                            DJ_MOVE_BUFF_shuzu(move_BUFF_SET2, hang);
                        }

                        break;
                    case '#':
                        brck                = 1;
                        KEY_TYPE            = 'z';
                        move_BUFF_SET2_hang = hang;
                        break;
                    default:

                        break;
                }
                if (brck == 1 && KEY_TYPE == 'z') break;

            }

            else if (move_flag == 3) {
                if (move_BUFF_SET3[0][0] == 0 && move_BUFF_SET3[0][1] == 0) {
                    hang = 0;
                }
                switch (KEY_TYPE) {
                    case 'y':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "右", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET3[hang][1] = 4;
                        }
                        break;
                    case 'z':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "左", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET3[hang][1] = 3;
                        }

                        break;
                    case 's':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "前", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET3[hang][1] = 1;
                        }
                        break;
                    case 'x':
                        if (sum_flag == 1 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 0;
                            y1       = y;
                            x1       = x;
                            OLED_DrawHanzi(x, y, "后", 0);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET3[hang][1] = 0;
                        }
                        break;
                    case '0':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "O", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET3[hang][0] = 0;
                            hang++;
                        }
                        break;
                    case '1':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "1", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();

                            move_BUFF_SET3[hang][0] = 1;
                            hang++;
                        }
                        break;
                    case '2':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "2", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET3[hang][0] = 2;
                            hang++;
                        }
                        break;
                    case '3':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "3", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET3[hang][0] = 3;
                            hang++;
                        }
                        break;
                    case '4':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "4", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET3[hang][0] = 4;
                            hang++;
                        }
                        break;
                    case '5':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "5", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET3[hang][0] = 5;
                            hang++;
                        }
                        break;
                    case '6':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "6", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET3[hang][0] = 6;
                            hang++;
                        }
                        break;
                    case '7':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "7", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET3[hang][0] = 7;
                            hang++;
                        }
                        break;
                    case '8':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "8", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET3[hang][0] = 8;
                            hang++;
                        }
                        break;
                    case '9':
                        if (sum_flag == 0 && y <= 48) {
                            an_flag  = 0;
                            sum_flag = 1;
                            y1       = y;
                            x1       = x;
                            OLED_ShowxcString(x, y, "9", 16, 1);
                            x += 16;
                            if (x >= 127) {
                                x = 0;
                                y += 16;
                            }
                            OLED_Refresh();
                            move_BUFF_SET3[hang][0] = 9;
                            hang++;
                        }
                        break;
                    case '*':
                        an_flag++;
                        if (an_flag >= 2) {
                            if (move_BUFF_SET3[0][0] == 0 && move_BUFF_SET3[0][1] == 0) {
                                hang = 0;
                            } else {
                                if (sum_flag == 0) {
                                    move_BUFF_SET3[hang - 1][1] = 0; // bu zou
                                    if (hang <= 1)
                                        hang = 1;
                                    else
                                        hang--;
                                } else {
                                    move_BUFF_SET3[hang - 1][0] = 0;
                                }
                            }

                            an_flag  = 0;
                            sum_flag = !sum_flag;
                            x        = x1;
                            y        = y1;
                            OLED_ShowxcString(x, y, "  ", 16, 1);
                            OLED_Refresh();

                            if (x1 == 0 && y1 == 16) {
                                sum_flag = 1;
                                break;
                            }
                            if (x >= 16)
                                x1 -= 16;

                            else {
                                x1 = 127;
                                y1 -= 16;
                            }
                        }

                        break;
                    case 'o':
                        an_flag1++;
                        if (an_flag1 >= 2) {
                            an_flag1 = 0;
                            DJ_MOVE_BUFF_shuzu(move_BUFF_SET3, hang);
                        }

                        break;
                    case '#':
                        brck                = 1;
                        KEY_TYPE            = 'z';
                        move_BUFF_SET3_hang = hang;
                        break;
                    default:

                        break;
                }
                if (brck == 1 && KEY_TYPE == 'z') break;
            }
        }
    }
}
void Clock_b(void)
{
    u8 i, j;
    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "自设", 0);
    OLED_ShowxcString(32, 16, "1", 16, 0);
    OLED_DrawHanzi(0, 32, "自设", 1);
    OLED_ShowxcString(32, 32, "2", 16, 1);
    OLED_DrawHanzi(0, 48, "自设", 1);
    OLED_ShowxcString(32, 48, "3", 16, 1);

    OLED_ShowxcNum(96, 16, move_BUFF_SET_hang, 2, 16, 0);
    OLED_ShowxcNum(96, 32, move_BUFF_SET2_hang, 2, 16, 1);
    OLED_ShowxcNum(96, 48, move_BUFF_SET3_hang, 2, 16, 1);

    if (move_flag1 == 1) {
        OLED_ShowxcString(64, 16, "*", 16, 1);
    } else if (move_flag2 == 1) {
        OLED_ShowxcString(64, 32, "*", 16, 1);
    } else if (move_flag3 == 1) {
        OLED_ShowxcString(64, 48, "*", 16, 1);
    }

    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            if (move_flag1 == 1 || move_flag2 == 1 || move_flag3 == 1) {
                if (KEY_TYPE == '*') {

                    if (move_flag1 == 1) {
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 12; j++) {
                                move_BUFF_SET[j][i] = move_BUFF_SET[j][i];
                            }
                        }
                        move_BUFF_SET_hang = move_BUFF_SET_hang;
                    } else if (move_flag2 == 1) {
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 12; j++) {
                                move_BUFF_SET[j][i] = move_BUFF_SET2[j][i];
                            }
                        }
                        move_BUFF_SET_hang = move_BUFF_SET2_hang;
                    } else if (move_flag3 == 1) {
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 12; j++) {
                                move_BUFF_SET[j][i] = move_BUFF_SET3[j][i];
                            }
                        }
                        move_BUFF_SET_hang = move_BUFF_SET3_hang;
                    }
                    OLED_ShowxcString(64, 16, " ", 16, 1);
                    OLED_ShowxcString(64, 32, " ", 16, 1);
                    OLED_ShowxcString(64, 48, " ", 16, 1);
                    OLED_ShowxcNum(96, 16, move_BUFF_SET_hang, 2, 16, 0);
                    OLED_Refresh();

                    move_flag1 = 0;
                    move_flag2 = 0;
                    move_flag3 = 0;

                } else if (KEY_TYPE == 's' || KEY_TYPE == 'x') {
                    break;
                }

            } else {
                if (KEY_TYPE == 'o') {
                    move_flag = 1;
                } else if (KEY_TYPE == '*') {
                    move_flag1 = 1;
                }
                break;
            }
        }
    }
}
void Clock_c(void)
{
    u8 i, j;
    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "自设", 1);
    OLED_ShowxcString(32, 16, "1", 16, 1);
    OLED_DrawHanzi(0, 32, "自设", 0);
    OLED_ShowxcString(32, 32, "2", 16, 0);
    OLED_DrawHanzi(0, 48, "自设", 1);
    OLED_ShowxcString(32, 48, "3", 16, 1);
    OLED_ShowxcNum(96, 16, move_BUFF_SET_hang, 2, 16, 1);
    OLED_ShowxcNum(96, 32, move_BUFF_SET2_hang, 2, 16, 0);
    OLED_ShowxcNum(96, 48, move_BUFF_SET3_hang, 2, 16, 1);

    if (move_flag1 == 1) {
        OLED_ShowxcString(64, 16, "*", 16, 1);
    } else if (move_flag2 == 1) {
        OLED_ShowxcString(64, 32, "*", 16, 1);
    } else if (move_flag3 == 1) {
        OLED_ShowxcString(64, 48, "*", 16, 1);
    }

    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            if (move_flag1 == 1 || move_flag2 == 1 || move_flag3 == 1) {
                if (KEY_TYPE == '*') {

                    if (move_flag1 == 1) {
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 12; j++) {
                                move_BUFF_SET2[j][i] = move_BUFF_SET[j][i];
                            }
                        }
                        move_BUFF_SET2_hang = move_BUFF_SET_hang;
                    } else if (move_flag2 == 1) {
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 12; j++) {
                                move_BUFF_SET2[j][i] = move_BUFF_SET2[j][i];
                            }
                        }
                        move_BUFF_SET2_hang = move_BUFF_SET2_hang;
                    } else if (move_flag3 == 1) {
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 12; j++) {
                                move_BUFF_SET2[j][i] = move_BUFF_SET3[j][i];
                            }
                        }
                        move_BUFF_SET2_hang = move_BUFF_SET3_hang;
                    }
                    OLED_ShowxcString(64, 16, " ", 16, 1);
                    OLED_ShowxcString(64, 32, " ", 16, 1);
                    OLED_ShowxcString(64, 48, " ", 16, 1);
                    OLED_ShowxcNum(96, 32, move_BUFF_SET2_hang, 2, 16, 0);
                    OLED_Refresh();

                    move_flag1 = 0;
                    move_flag2 = 0;
                    move_flag3 = 0;
                } else if (KEY_TYPE == 's' || KEY_TYPE == 'x') {
                    break;
                }

            } else {
                if (KEY_TYPE == 'o') {
                    move_flag = 2;
                } else if (KEY_TYPE == '*') {
                    move_flag2 = 1;
                }
                break;
            }
        }
    }
}
void Clock_d(void)
{
    u8 i, j;
    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "自设", 1);
    OLED_ShowxcString(32, 16, "1", 16, 1);
    OLED_DrawHanzi(0, 32, "自设", 1);
    OLED_ShowxcString(32, 32, "2", 16, 1);
    OLED_DrawHanzi(0, 48, "自设", 0);
    OLED_ShowxcString(32, 48, "3", 16, 0);

    OLED_ShowxcNum(96, 16, move_BUFF_SET_hang, 2, 16, 1);
    OLED_ShowxcNum(96, 32, move_BUFF_SET2_hang, 2, 16, 1);
    OLED_ShowxcNum(96, 48, move_BUFF_SET3_hang, 2, 16, 0);
    if (move_flag1 == 1) {
        OLED_ShowxcString(64, 16, "*", 16, 1);
    } else if (move_flag2 == 1) {
        OLED_ShowxcString(64, 32, "*", 16, 1);
    } else if (move_flag3 == 1) {
        OLED_ShowxcString(64, 48, "*", 16, 1);
    }

    OLED_Refresh();

    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            if (move_flag1 == 1 || move_flag2 == 1 || move_flag3 == 1) {
                if (KEY_TYPE == '*') {

                    if (move_flag1 == 1) {
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 12; j++) {
                                move_BUFF_SET3[j][i] = move_BUFF_SET[j][i];
                            }
                        }
                        move_BUFF_SET3_hang = move_BUFF_SET_hang;
                    } else if (move_flag2 == 1) {
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 12; j++) {
                                move_BUFF_SET3[j][i] = move_BUFF_SET2[j][i];
                            }
                        }
                        move_BUFF_SET3_hang = move_BUFF_SET2_hang;
                    } else if (move_flag3 == 1) {
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 12; j++) {
                                move_BUFF_SET3[j][i] = move_BUFF_SET3[j][i];
                            }
                        }
                        move_BUFF_SET3_hang = move_BUFF_SET3_hang;
                    }
                    OLED_ShowxcString(64, 16, " ", 16, 1);
                    OLED_ShowxcString(64, 32, " ", 16, 1);
                    OLED_ShowxcString(64, 48, " ", 16, 1);
                    OLED_ShowxcNum(96, 48, move_BUFF_SET3_hang, 2, 16, 0);
                    OLED_Refresh();
                    move_flag1 = 0;
                    move_flag2 = 0;
                    move_flag3 = 0;
                } else if (KEY_TYPE == 's' || KEY_TYPE == 'x') {
                    break;
                }

            } else {
                if (KEY_TYPE == 'o') {
                    move_flag = 3;
                } else if (KEY_TYPE == '*') {
                    move_flag3 = 1;
                }
                break;
            }
        }
    }
}
void Clock_e(void)
{
    u8 i;

    OLED_tou();
    OLED_CLS(0);

    if (move_flag == 1) {
        for (i = 0; i < 4; i++) {
            if (move_BUFF_SET[i][0] == 0 && move_BUFF_SET[i][1] == 0) {
                OLED_ShowxcString(i * 32, 16, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET[i][1]) {
                    case 1:
                        OLED_DrawHanzi(i * 32, 16, "前", 1);
                        // BuJin_Zhuan('S');
                        break;
                    case 0:
                        OLED_DrawHanzi(i * 32, 16, "后", 1);
                        // BuJin_Zhuan('I');
                        break;
                    case 3:
                        OLED_DrawHanzi(i * 32, 16, "左", 1);
                        // BuJin_Zhuan('T');
                        break;
                    case 4:
                        OLED_DrawHanzi(i * 32, 16, "右", 1);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum(i * 32 + 16, 16, move_BUFF_SET[i][0], 1, 16, 1);
            }
        }
        for (i = 4; i < 8; i++) {
            if (move_BUFF_SET[i][0] == 0 && move_BUFF_SET[i][1] == 0) {
                OLED_ShowxcString((i - 4) * 32, 32, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET[i][1]) {
                    case 1:
                        OLED_DrawHanzi((i - 4) * 32, 32, "前", 1);
                        break;
                    case 0:
                        OLED_DrawHanzi((i - 4) * 32, 32, "后", 1);
                        break;
                    case 3:
                        OLED_DrawHanzi((i - 4) * 32, 32, "左", 1);
                        break;
                    case 4:
                        OLED_DrawHanzi((i - 4) * 32, 32, "右", 1);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum((i - 4) * 32 + 16, 32, move_BUFF_SET[i][0], 1, 16, 1);
            }
        }
        for (i = 8; i < 12; i++) {
            if (move_BUFF_SET[i][0] == 0 && move_BUFF_SET[i][1] == 0) {
                OLED_ShowxcString((i - 8) * 32, 48, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET[i][1]) {
                    case 1:
                        OLED_DrawHanzi((i - 8) * 32, 48, "前", 1);
                        break;
                    case 0:
                        OLED_DrawHanzi((i - 8) * 32, 48, "后", 1);
                        break;
                    case 3:
                        OLED_DrawHanzi((i - 8) * 32, 48, "左", 1);
                        break;
                    case 4:
                        OLED_DrawHanzi((i - 8) * 32, 48, "右", 1);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum((i - 8) * 32 + 16, 48, move_BUFF_SET[i][0], 1, 16, 1);
            }
        }
    } else if (move_flag == 2) {
        for (i = 0; i < 4; i++) {
            if (move_BUFF_SET2[i][0] == 0 && move_BUFF_SET2[i][1] == 0) {
                OLED_ShowxcString(i * 32, 16, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET2[i][1]) {
                    case 1:
                        OLED_DrawHanzi(i * 32, 16, "前", 1);
                        break;
                    case 0:
                        OLED_DrawHanzi(i * 32, 16, "后", 1);
                        break;
                    case 3:
                        OLED_DrawHanzi(i * 32, 16, "左", 1);
                        break;
                    case 4:
                        OLED_DrawHanzi(i * 32, 16, "右", 1);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum(i * 32 + 16, 16, move_BUFF_SET2[i][0], 1, 16, 1);
            }
        }
        for (i = 4; i < 8; i++) {
            if (move_BUFF_SET2[i][0] == 0 && move_BUFF_SET2[i][1] == 0) {
                OLED_ShowxcString((i - 4) * 32, 32, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET2[i][1]) {
                    case 1:
                        OLED_DrawHanzi((i - 4) * 32, 32, "前", 1);
                        break;
                    case 0:
                        OLED_DrawHanzi((i - 4) * 32, 32, "后", 1);
                        break;
                    case 3:
                        OLED_DrawHanzi((i - 4) * 32, 32, "左", 1);
                        break;
                    case 4:
                        OLED_DrawHanzi((i - 4) * 32, 32, "右", 1);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum((i - 4) * 32 + 16, 32, move_BUFF_SET2[i][0], 1, 16, 1);
            }
        }
        for (i = 8; i < 12; i++) {
            if (move_BUFF_SET2[i][0] == 0 && move_BUFF_SET2[i][1] == 0) {
                OLED_ShowxcString((i - 8) * 32, 48, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET2[i][1]) {
                    case 1:
                        OLED_DrawHanzi((i - 8) * 32, 48, "前", 1);
                        break;
                    case 0:
                        OLED_DrawHanzi((i - 8) * 32, 48, "后", 1);
                        break;
                    case 3:
                        OLED_DrawHanzi((i - 8) * 32, 48, "左", 1);
                        break;
                    case 4:
                        OLED_DrawHanzi((i - 8) * 32, 48, "右", 1);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum((i - 8) * 32 + 16, 48, move_BUFF_SET2[i][0], 1, 16, 1);
            }
        }
    } else if (move_flag == 3) {
        for (i = 0; i < 4; i++) {
            if (move_BUFF_SET3[i][0] == 0 && move_BUFF_SET3[i][1] == 0) {
                OLED_ShowxcString(i * 32, 16, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET3[i][1]) {
                    case 1:
                        OLED_DrawHanzi(i * 32, 16, "前", 1);
                        break;
                    case 0:
                        OLED_DrawHanzi(i * 32, 16, "后", 1);
                        break;
                    case 3:
                        OLED_DrawHanzi(i * 32, 16, "左", 1);
                        break;
                    case 4:
                        OLED_DrawHanzi(i * 32, 16, "右", 1);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum(i * 32 + 16, 16, move_BUFF_SET3[i][0], 1, 16, 1);
            }
        }
        for (i = 4; i < 8; i++) {
            if (move_BUFF_SET3[i][0] == 0 && move_BUFF_SET3[i][1] == 0) {
                OLED_ShowxcString((i - 4) * 32, 32, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET3[i][1]) {
                    case 1:
                        OLED_DrawHanzi((i - 4) * 32, 32, "前", 1);
                        break;
                    case 0:
                        OLED_DrawHanzi((i - 4) * 32, 32, "后", 1);
                        break;
                    case 3:
                        OLED_DrawHanzi((i - 4) * 32, 32, "左", 1);
                        break;
                    case 4:
                        OLED_DrawHanzi((i - 4) * 32, 32, "右", 1);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum((i - 4) * 32 + 16, 32, move_BUFF_SET3[i][0], 1, 16, 1);
            }
        }
        for (i = 8; i < 12; i++) {
            if (move_BUFF_SET3[i][0] == 0 && move_BUFF_SET3[i][1] == 0) {
                OLED_ShowxcString((i - 8) * 32, 48, "    ", 16, 1);
            } else {
                switch (move_BUFF_SET3[i][1]) {
                    case 1:
                        OLED_DrawHanzi((i - 8) * 32, 48, "前", 1);
                        break;
                    case 0:
                        OLED_DrawHanzi((i - 8) * 32, 48, "后", 1);
                        break;
                    case 3:
                        OLED_DrawHanzi((i - 8) * 32, 48, "左", 1);
                        break;
                    case 4:
                        OLED_DrawHanzi((i - 8) * 32, 48, "右", 1);
                        break;
                    default:
                        break;
                }
                OLED_ShowxcNum((i - 8) * 32 + 16, 48, move_BUFF_SET3[i][0], 1, 16, 1);
            }
        }
    }
    OLED_Refresh();
    i = 0;
    while (1) {
        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            if (KEY_TYPE == 'o') // pao
            {
                i = 0;
                LCD_16_HanZi_ASCII(10, 6, "go");
                if (move_flag == 1) {
                    DJ_MOVE_BUFF_shuzu(move_BUFF_SET, move_BUFF_SET_hang);
                } else if (move_flag == 2) {
                    DJ_MOVE_BUFF_shuzu(move_BUFF_SET2, move_BUFF_SET2_hang);
                } else if (move_flag == 3) {
                    DJ_MOVE_BUFF_shuzu(move_BUFF_SET3, move_BUFF_SET3_hang);
                }
                LCD_16_HanZi_ASCII(10, 6, "  ");
            } else if (KEY_TYPE == 'y') {
                i++;
                if (i >= 2) {
                    i = 0;
                    break;
                }
            } else
                break;
        }
    }
}

void Net_a(void)
{
    u8 luxian;
    u8 a = 0;

    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "初启", 0);
    //	OLED_ShowxcString(32,16,"1",16,0);
    OLED_DrawHanzi(0, 32, "重启", 1);
    //	OLED_ShowxcString(32,32,"2",16,1);
    OLED_DrawHanzi(0, 48, "再启", 1);
    //	OLED_ShowxcString(32,48,"3",16,1);

    OLED_ShowxcString(48, 16, "1.", 16, 1);
    OLED_ShowxcString(88, 16, "2.", 16, 1);
    OLED_ShowxcString(48, 32, "3.", 16, 1);
    OLED_ShowxcString(88, 32, "4.", 16, 1);
    OLED_ShowxcString(48, 48, "5.", 16, 1);
    OLED_ShowxcString(88, 48, "6.", 16, 1);

    OLED_ShowxcString(36, 16, "|", 16, 1);
    OLED_ShowxcString(36, 32, "|", 16, 1);
    OLED_ShowxcString(36, 48, "|", 16, 1);
    OLED_Refresh();

    //	if(SHAUNG_FLAG != 1)
    //	{
    //		printf("SHU\r\n");
    //		delay_ms(100);
    //		printf("SKAS\r\n");		//跳菜单
    //	}

    while (1) {

        OLED_tou();
        AD_AnJian();
        //		if(Keykey_Flag==1 ||(SHAUNG_FLAG == 1 && SHAUNG_LU != 0))
        //		{
        //			Keykey_Flag=0;
        //			if(SHAUNG_FLAG == 1 && SHAUNG_LU != 0)
        //			{
        //				KEY_TYPE = SHAUNG_LU;
        //				SHAUNG_LU = 0;
        //				a=1;
        //			}
        //			switch(KEY_TYPE)
        //			{
        //				case  'y':	switch(luxian)
        //							{
        //								case 1:	LCD_16_HanZi_ASCII(9,2,"go");	//路线1
        //										LCD_16_HanZi_ASCII(9,2,"  ");
        //										break;
        //								case 2:	LCD_16_HanZi_ASCII(14,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,2,"  ");
        //										break;
        //								case 3:	LCD_16_HanZi_ASCII(9,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,4,"  ");
        //										break;
        //								case 4:	LCD_16_HanZi_ASCII(14,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,4,"  ");
        //										break;
        //								case 5:	LCD_16_HanZi_ASCII(9,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,6,"  ");
        //										break;
        //								case 6:	LCD_16_HanZi_ASCII(14,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,6,"  ");
        //										break;
        //
        //								default:break;
        //							}

        //							if(!a)	printf("Sy\r\n");
        //							break;
        //				case  'o':	switch(luxian)
        //							{
        //								case 1:	LCD_16_HanZi_ASCII(9,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,2,"  ");
        //										break;
        //								case 2:	LCD_16_HanZi_ASCII(14,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,2,"  ");
        //										break;
        //								case 3:	LCD_16_HanZi_ASCII(9,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,4,"  ");
        //										break;
        //								case 4:	LCD_16_HanZi_ASCII(14,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,4,"  ");
        //										break;
        //								case 5:	LCD_16_HanZi_ASCII(9,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,6,"  ");
        //										break;
        //								case 6:	LCD_16_HanZi_ASCII(14,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,6,"  ");
        //										break;
        //
        //								default:break;
        //							}
        //
        //							if(!a)	printf("So\r\n");
        //							break;
        //				case  '0':	break;
        //				case  '1':	OLED_ShowxcString(48,16,"1.",16,0);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();

        //							if(!a)	printf("S1\r\n");
        //							break;
        //				case  '2':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,0);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();

        //							if(!a)	printf("S2\r\n");
        //							break;
        //				case  '3':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,0);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();

        //							if(!a)	printf("S3\r\n");
        //							break;
        //				case  '4':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,0);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();
        //
        //							if(!a)	printf("S4\r\n");
        //							break;
        //				case  '5':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,0);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();
        //
        //							if(!a)	printf("S5\r\n");
        //							break;
        //				case  '6':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,0);
        //							OLED_Refresh();

        //							if(!a)	printf("S6\r\n");
        //							break;
        //				case  'z':	if(!a)	printf("Sz\r\n");	break;
        //				case  '#':	if(!a)	printf("Sz\r\n");	break;
        //				case  's':	if(!a)	printf("Ss\r\n");	break;
        //				case  'x':	if(!a)	printf("Sx\r\n");	break;
        //
        //				default:	break;
        //			}
        //			if(KEY_TYPE == 'z'||KEY_TYPE == '#'||KEY_TYPE == 's'||KEY_TYPE == 'x')
        //			{
        //				luxian = 0;
        //				break;
        //			}
        //
        //			a = 0;
        //		}
        //		if(SHAUNG_FLAG == 1&&(SHAUNG_LU_FLAG == 's'||SHAUNG_LU_FLAG == 'x'||SHAUNG_LU_FLAG == 'z'))
        //		{
        //			luxian = 0;
        //			KEY_TYPE = SHAUNG_LU_FLAG;
        //			SHAUNG_LU_FLAG = 0;
        //			break;
        //		}
    }
}
void Net_b(void)
{
    u8 luxian;
    u8 a = 0;
    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "初启", 1);
    //	OLED_ShowxcString(32,16,"1",16,1);
    OLED_DrawHanzi(0, 32, "重启", 0);
    //	OLED_ShowxcString(32,32,"2",16,0);
    OLED_DrawHanzi(0, 48, "再启", 1);
    //	OLED_ShowxcString(32,48,"3",16,1);

    OLED_ShowxcString(48, 16, "1.", 16, 1);
    OLED_ShowxcString(88, 16, "2.", 16, 1);
    OLED_ShowxcString(48, 32, "3.", 16, 1);
    OLED_ShowxcString(88, 32, "4.", 16, 1);
    OLED_ShowxcString(48, 48, "5.", 16, 1);
    OLED_ShowxcString(88, 48, "6.", 16, 1);

    OLED_ShowxcString(36, 16, "|", 16, 1);
    OLED_ShowxcString(36, 32, "|", 16, 1);
    OLED_ShowxcString(36, 48, "|", 16, 1);
    OLED_Refresh();

    while (1) {

        OLED_tou();
        AD_AnJian();
        //		if(Keykey_Flag==1 ||(SHAUNG_FLAG == 1 && SHAUNG_LU != 0))
        //		{
        //			Keykey_Flag=0;
        //			if(SHAUNG_FLAG == 1 && SHAUNG_LU != 0)
        //			{
        //				KEY_TYPE = SHAUNG_LU;
        //				SHAUNG_LU = 0;
        //				a=1;
        //			}
        //			switch(KEY_TYPE)
        //			{
        //				case  'y':	switch(luxian)
        //							{
        //								case 1:	LCD_16_HanZi_ASCII(9,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,2,"  ");
        //										break;
        //								case 2:	LCD_16_HanZi_ASCII(14,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,2,"  ");
        //										break;
        //								case 3:	LCD_16_HanZi_ASCII(9,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,4,"  ");
        //										break;
        //								case 4:	LCD_16_HanZi_ASCII(14,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,4,"  ");
        //										break;
        //								case 5:	LCD_16_HanZi_ASCII(9,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,6,"  ");
        //										break;
        //								case 6:	LCD_16_HanZi_ASCII(14,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,6,"  ");
        //										break;
        //
        //								default:break;
        //							}

        //							if(!a)	printf("Sy\r\n");
        //							break;
        //				case  'o':	switch(luxian)
        //							{
        //								case 1:	LCD_16_HanZi_ASCII(9,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,2,"  ");
        //										break;
        //								case 2:	LCD_16_HanZi_ASCII(14,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,2,"  ");
        //										break;
        //								case 3:	LCD_16_HanZi_ASCII(9,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,4,"  ");
        //										break;
        //								case 4:	LCD_16_HanZi_ASCII(14,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,4,"  ");
        //										break;
        //								case 5:	LCD_16_HanZi_ASCII(9,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,6,"  ");
        //										break;
        //								case 6:	LCD_16_HanZi_ASCII(14,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,6,"  ");
        //										break;
        //
        //								default:break;
        //							}
        //
        //							if(!a)	printf("So\r\n");
        //							break;
        //				case  '0':	break;
        //				case  '1':	OLED_ShowxcString(48,16,"1.",16,0);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();

        //							if(!a)	printf("S1\r\n");
        //							break;
        //				case  '2':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,0);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();

        //							if(!a)	printf("S2\r\n");
        //							break;
        //				case  '3':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,0);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();

        //							if(!a)	printf("S3\r\n");
        //							break;
        //				case  '4':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,0);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();
        //
        //							if(!a)	printf("S4\r\n");
        //							break;
        //				case  '5':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,0);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();
        //
        //							if(!a)	printf("S5\r\n");
        //							break;
        //				case  '6':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,0);
        //							OLED_Refresh();

        //							if(!a)	printf("S6\r\n");
        //							break;
        //				case  'z':	if(!a)	printf("Sz\r\n");	break;
        //				case  '#':	if(!a)	printf("Sz\r\n");	break;
        //				case  's':	if(!a)	printf("Ss\r\n");	break;
        //				case  'x':	if(!a)	printf("Sx\r\n");	break;
        //
        //				default:	break;
        //			}
        //			if(KEY_TYPE == 'z'||KEY_TYPE == '#'||KEY_TYPE == 's'||KEY_TYPE == 'x')
        //			{
        //				luxian = 0;
        //				break;
        //			}
        //
        //			a = 0;
        //		}
        //		if(SHAUNG_FLAG == 1&&(SHAUNG_LU_FLAG == 's'||SHAUNG_LU_FLAG == 'x'||SHAUNG_LU_FLAG == 'z'))
        //		{
        //			luxian = 0;
        //			KEY_TYPE = SHAUNG_LU_FLAG;
        //			SHAUNG_LU_FLAG = 0;
        //			break;
        //		}
    }
}
void Net_c(void)
{
    u8 luxian;
    u8 a = 0;
    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "初启", 1);
    //	OLED_ShowxcString(32,16,"1",16,1);
    OLED_DrawHanzi(0, 32, "重启", 1);
    //	OLED_ShowxcString(32,32,"2",16,1);
    OLED_DrawHanzi(0, 48, "再启", 0);
    //	OLED_ShowxcString(32,48,"3",16,0);
    OLED_ShowxcString(48, 16, "1.", 16, 1);
    OLED_ShowxcString(88, 16, "2.", 16, 1);
    OLED_ShowxcString(48, 32, "3.", 16, 1);
    OLED_ShowxcString(88, 32, "4.", 16, 1);
    OLED_ShowxcString(48, 48, "5.", 16, 1);
    OLED_ShowxcString(88, 48, "6.", 16, 1);

    OLED_ShowxcString(36, 16, "|", 16, 1);
    OLED_ShowxcString(36, 32, "|", 16, 1);
    OLED_ShowxcString(36, 48, "|", 16, 1);
    OLED_Refresh();

    while (1) {

        OLED_tou();
        AD_AnJian();
        //		if(Keykey_Flag==1 ||(SHAUNG_FLAG == 1 && SHAUNG_LU != 0))
        //		{
        //			Keykey_Flag=0;
        //			if(SHAUNG_FLAG == 1 && SHAUNG_LU != 0)
        //			{
        //				KEY_TYPE = SHAUNG_LU;
        //				SHAUNG_LU = 0;
        //				a=1;
        //			}
        //			switch(KEY_TYPE)
        //			{
        //				case  'y':	switch(luxian)
        //							{
        //								case 1:	LCD_16_HanZi_ASCII(9,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,2,"  ");
        //										break;
        //								case 2:	LCD_16_HanZi_ASCII(14,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,2,"  ");
        //										break;
        //								case 3:	LCD_16_HanZi_ASCII(9,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,4,"  ");
        //										break;
        //								case 4:	LCD_16_HanZi_ASCII(14,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,4,"  ");
        //										break;
        //								case 5:	LCD_16_HanZi_ASCII(9,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,6,"  ");
        //										break;
        //								case 6:	LCD_16_HanZi_ASCII(14,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,6,"  ");
        //										break;
        //
        //								default:break;
        //							}

        //							if(!a)	printf("Sy\r\n");
        //							break;
        //				case  'o':	switch(luxian)
        //							{
        //								case 1:	LCD_16_HanZi_ASCII(9,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,2,"  ");
        //										break;
        //								case 2:	LCD_16_HanZi_ASCII(14,2,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,2,"  ");
        //										break;
        //								case 3:	LCD_16_HanZi_ASCII(9,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,4,"  ");
        //										break;
        //								case 4:	LCD_16_HanZi_ASCII(14,4,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,4,"  ");
        //										break;
        //								case 5:	LCD_16_HanZi_ASCII(9,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(9,6,"  ");
        //										break;
        //								case 6:	LCD_16_HanZi_ASCII(14,6,"go");	//路线1
        //
        //										LCD_16_HanZi_ASCII(14,6,"  ");
        //										break;
        //
        //								default:break;
        //							}
        //
        //							if(!a)	printf("So\r\n");
        //							break;
        //				case  '0':	break;
        //				case  '1':	OLED_ShowxcString(48,16,"1.",16,0);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();

        //							if(!a)	printf("S1\r\n");
        //							break;
        //				case  '2':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,0);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();

        //							if(!a)	printf("S2\r\n");
        //							break;
        //				case  '3':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,0);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();

        //							if(!a)	printf("S3\r\n");
        //							break;
        //				case  '4':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,0);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();
        //
        //							if(!a)	printf("S4\r\n");
        //							break;
        //				case  '5':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,0);
        //							OLED_ShowxcString(88,48,"6.",16,1);
        //							OLED_Refresh();
        //
        //							if(!a)	printf("S5\r\n");
        //							break;
        //				case  '6':	OLED_ShowxcString(48,16,"1.",16,1);
        //							OLED_ShowxcString(88,16,"2.",16,1);
        //							OLED_ShowxcString(48,32,"3.",16,1);
        //							OLED_ShowxcString(88,32,"4.",16,1);
        //							OLED_ShowxcString(48,48,"5.",16,1);
        //							OLED_ShowxcString(88,48,"6.",16,0);
        //							OLED_Refresh();

        //							if(!a)	printf("S6\r\n");
        //							break;
        //				case  'z':	if(!a)	printf("Sz\r\n");	break;
        //				case  '#':	if(!a)	printf("Sz\r\n");	break;
        //				case  's':	if(!a)	printf("Ss\r\n");	break;
        //				case  'x':	if(!a)	printf("Sx\r\n");	break;
        //
        //				default:	break;
        //			}
        //			if(KEY_TYPE == 'z'||KEY_TYPE == '#'||KEY_TYPE == 's'||KEY_TYPE == 'x')
        //			{
        //				luxian = 0;
        //				break;
        //			}
        //
        //			a = 0;
        //		}
        //		if(SHAUNG_FLAG == 1&&(SHAUNG_LU_FLAG == 's'||SHAUNG_LU_FLAG == 'x'||SHAUNG_LU_FLAG == 'z'))
        //		{
        //			luxian = 0;
        //			KEY_TYPE = SHAUNG_LU_FLAG;
        //			SHAUNG_LU_FLAG = 0;
        //			break;
        //		}
    }
}

void Net_d(void)
{
    u8 luxian;

    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "初启", 0);
    //	OLED_ShowxcString(32,16,"1",16,0);
    OLED_DrawHanzi(0, 32, "重启", 1);
    //	OLED_ShowxcString(32,32,"2",16,1);
    OLED_DrawHanzi(0, 48, "再启", 1);
    //	OLED_ShowxcString(32,48,"3",16,1);

    OLED_ShowxcString(48, 16, "1.", 16, 1);
    OLED_ShowxcString(88, 16, "2.", 16, 1);
    OLED_ShowxcString(48, 32, "3.", 16, 1);
    OLED_ShowxcString(88, 32, "4.", 16, 1);
    OLED_ShowxcString(48, 48, "5.", 16, 1);
    OLED_ShowxcString(88, 48, "6.", 16, 1);

    OLED_ShowxcString(36, 16, "|", 16, 1);
    OLED_ShowxcString(36, 32, "|", 16, 1);
    OLED_ShowxcString(36, 48, "|", 16, 1);
    OLED_Refresh();

    printf("DAN\r\n");
    printf("DAN\r\n");
    printf("DAN\r\n");

    while (1) {

        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            switch (KEY_TYPE) {
                case 'y':
                    switch (luxian) {
                        case 1:
                            LCD_16_HanZi_ASCII(9, 2, "go"); // 路线1
                            //										DJ_MOVE_BUFF_SET(3,1);
                            //										DJ_MOVE_BUFF_SET(0,4);
                            //										DJ_MOVE_YS(3,1,1,150);
                            change(xiacsd, 1);

                            LCD_16_HanZi_ASCII(9, 2, "  ");
                            break;
                        case 2:
                            LCD_16_HanZi_ASCII(14, 2, "go"); // 路线2
                            //										BMQ_MOVE(1,100,0);
                            change(a, 0);
                            LCD_16_HanZi_ASCII(9, 4, "  ");
                            break;
                        case 3:
                            LCD_16_HanZi_ASCII(9, 4, "go");
                            change_uart(b, 0);
                            LCD_16_HanZi_ASCII(9, 4, "  ");
                            break;
                        case 4:
                            LCD_16_HanZi_ASCII(14, 4, "go");
                            change_uart(c, 0);
                            LCD_16_HanZi_ASCII(14, 4, "  ");
                            break;
                        case 5:
                            LCD_16_HanZi_ASCII(9, 6, "go");
                            change_uart(d, 0);
                            LCD_16_HanZi_ASCII(9, 6, "  ");
                            break;
                        case 6:
                            LCD_16_HanZi_ASCII(14, 6, "go");
                            change_uart(e, 0);
                            LCD_16_HanZi_ASCII(14, 6, "  ");
                            break;

                        default:
                            break;
                    }
                    break;
                case 'o':
                    switch (luxian) {
                        case 1:
                            LCD_16_HanZi_ASCII(9, 2, "go"); // 路线1
                            change(paizhao, 1);
                            LCD_16_HanZi_ASCII(9, 2, "  ");
                            break;
                        case 2:
                            LCD_16_HanZi_ASCII(14, 2, "go"); // 路线1
                            change_uart(a1, 0);
                            LCD_16_HanZi_ASCII(14, 2, "  ");
                            break;
                        case 3:
                            LCD_16_HanZi_ASCII(9, 4, "go"); // 路线1
                            change_uart(b1, 0);
                            LCD_16_HanZi_ASCII(9, 4, "  ");
                            break;
                        case 4:
                            LCD_16_HanZi_ASCII(14, 4, "go"); // 路线1
                            change_uart(c1, 0);
                            LCD_16_HanZi_ASCII(14, 4, "  ");
                            break;
                        case 5:
                            LCD_16_HanZi_ASCII(9, 6, "go"); // 路线1
                            change_uart(d1, 0);
                            LCD_16_HanZi_ASCII(9, 6, "  ");
                            break;
                        case 6:
                            LCD_16_HanZi_ASCII(14, 6, "go"); // 路线1
                            change(b, 0);
                            LCD_16_HanZi_ASCII(14, 6, "  ");
                            break;

                        default:
                            break;
                    }
                    break;
                case '0':
                    break;
                case '1':
                    OLED_ShowxcString(48, 16, "1.", 16, 0);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 1;
                    break;
                case '2':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 0);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 2;
                    break;
                case '3':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 0);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 3;
                    break;
                case '4':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 0);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 4;
                    break;
                case '5':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 0);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 5;
                    break;
                case '6':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 0);
                    OLED_Refresh();
                    luxian = 6;
                    break;

                default:
                    break;
            }
            if (KEY_TYPE == 'z' || KEY_TYPE == '#' || KEY_TYPE == 's' || KEY_TYPE == 'x') {
                break;
            }
        }
    }
}
void Net_e(void)
{
    u8 luxian;

    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "初启", 1);
    //	OLED_ShowxcString(32,16,"1",16,1);
    OLED_DrawHanzi(0, 32, "重启", 0);
    //	OLED_ShowxcString(32,32,"2",16,0);
    OLED_DrawHanzi(0, 48, "再启", 1);
    //	OLED_ShowxcString(32,48,"3",16,1);

    OLED_ShowxcString(48, 16, "1.", 16, 1);
    OLED_ShowxcString(88, 16, "2.", 16, 1);
    OLED_ShowxcString(48, 32, "3.", 16, 1);
    OLED_ShowxcString(88, 32, "4.", 16, 1);
    OLED_ShowxcString(48, 48, "5.", 16, 1);
    OLED_ShowxcString(88, 48, "6.", 16, 1);

    OLED_ShowxcString(36, 16, "|", 16, 1);
    OLED_ShowxcString(36, 32, "|", 16, 1);
    OLED_ShowxcString(36, 48, "|", 16, 1);
    OLED_Refresh();

    printf("DAN\r\n");
    printf("DAN\r\n");
    printf("DAN\r\n");
    while (1) {

        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            switch (KEY_TYPE) {
                case 'y':
                    switch (luxian) {
                        case 1:
                            LCD_16_HanZi_ASCII(9, 2, "go"); // 路线1

                            LCD_16_HanZi_ASCII(9, 2, "  ");
                            break;
                        case 2:
                            LCD_16_HanZi_ASCII(14, 2, "go"); // 路线1
                            change_uart(a2, 0);
                            LCD_16_HanZi_ASCII(14, 2, "  ");
                            break;
                        case 3:
                            LCD_16_HanZi_ASCII(9, 4, "go"); // 路线1
                            change_uart(a2, 0);
                            LCD_16_HanZi_ASCII(9, 4, "  ");
                            break;
                        case 4:
                            LCD_16_HanZi_ASCII(14, 4, "go"); // 路线1
                            change_uart(c2, 0);
                            LCD_16_HanZi_ASCII(14, 4, "  ");
                            break;
                        case 5:
                            LCD_16_HanZi_ASCII(9, 6, "go"); // 路线1
                            change_uart(d2, 0);
                            LCD_16_HanZi_ASCII(9, 6, "  ");
                            break;
                        case 6:
                            LCD_16_HanZi_ASCII(14, 6, "go"); // 路线1
                            change_uart(e2, 0);
                            LCD_16_HanZi_ASCII(14, 6, "  ");
                            break;

                        default:
                            break;
                    }
                    break;
                case 'o':
                    switch (luxian) {
                        case 1:
                            LCD_16_HanZi_ASCII(9, 2, "go"); // 路线1
                            sum_value1 = 0;
                            sum_value2 = 0;
                            sum_flag   = 1;
                            DJ_MOVE(5, 1, 1, 0, 0, 0, 0, 0);
                            sprintf(OLED_BUF, "%d %d   ", sum_value1, sum_value2);
                            LCD_16_HanZi_ASCII(0, 6, OLED_BUF);
                            sum_flag = 0;
                            LCD_16_HanZi_ASCII(9, 2, "  ");
                            break;
                        case 2:
                            LCD_16_HanZi_ASCII(14, 2, "go"); // 路线1

                            LCD_16_HanZi_ASCII(14, 2, "  ");
                            break;
                        case 3:
                            LCD_16_HanZi_ASCII(9, 4, "go"); // 路线1

                            LCD_16_HanZi_ASCII(9, 4, "  ");
                            break;
                        case 4:
                            LCD_16_HanZi_ASCII(14, 4, "go"); // 路线1

                            LCD_16_HanZi_ASCII(14, 4, "  ");
                            break;
                        case 5:
                            LCD_16_HanZi_ASCII(9, 6, "go"); // 路线1

                            LCD_16_HanZi_ASCII(9, 6, "  ");
                            break;
                        case 6:
                            LCD_16_HanZi_ASCII(14, 6, "go"); // 路线1

                            LCD_16_HanZi_ASCII(14, 6, "  ");
                            break;

                        default:
                            break;
                    }
                    break;
                case '0':
                    break;
                case '1':
                    OLED_ShowxcString(48, 16, "1.", 16, 0);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 1;
                    break;
                case '2':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 0);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 2;
                    break;
                case '3':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 0);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 3;
                    break;
                case '4':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 0);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 4;
                    break;
                case '5':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 0);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 5;
                    break;
                case '6':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 0);
                    OLED_Refresh();
                    luxian = 6;
                    break;

                default:
                    break;
            }
            if (KEY_TYPE == 'z' || KEY_TYPE == '#' || KEY_TYPE == 's' || KEY_TYPE == 'x') {
                break;
            }
        }
    }
}
void Net_f(void)
{
    u8 luxian;

    OLED_tou();
    OLED_CLS(0);
    OLED_DrawHanzi(0, 16, "初启", 1);
    //	OLED_ShowxcString(32,16,"1",16,1);
    OLED_DrawHanzi(0, 32, "重启", 1);
    //	OLED_ShowxcString(32,32,"2",16,1);
    OLED_DrawHanzi(0, 48, "再启", 0);
    //	OLED_ShowxcString(32,48,"3",16,0);
    OLED_ShowxcString(48, 16, "1.", 16, 1);
    OLED_ShowxcString(88, 16, "2.", 16, 1);
    OLED_ShowxcString(48, 32, "3.", 16, 1);
    OLED_ShowxcString(88, 32, "4.", 16, 1);
    OLED_ShowxcString(48, 48, "5.", 16, 1);
    OLED_ShowxcString(88, 48, "6.", 16, 1);

    OLED_ShowxcString(36, 16, "|", 16, 1);
    OLED_ShowxcString(36, 32, "|", 16, 1);
    OLED_ShowxcString(36, 48, "|", 16, 1);
    OLED_Refresh();

    printf("DAN\r\n");
    printf("DAN\r\n");
    printf("DAN\r\n");
    while (1) {

        OLED_tou();
        AD_AnJian();
        if (Keykey_Flag == 1) {
            Keykey_Flag = 0;
            switch (KEY_TYPE) {
                case 'y':
                    switch (luxian) {
                        case 1:
                            LCD_16_HanZi_ASCII(9, 2, "go"); // 路线1

                            LCD_16_HanZi_ASCII(9, 2, "  ");
                            break;
                        case 2:
                            LCD_16_HanZi_ASCII(14, 2, "go"); // 路线1

                            LCD_16_HanZi_ASCII(14, 2, "  ");
                            break;
                        case 3:
                            LCD_16_HanZi_ASCII(9, 4, "go"); // 路线1

                            LCD_16_HanZi_ASCII(9, 4, "  ");
                            break;
                        case 4:
                            LCD_16_HanZi_ASCII(14, 4, "go"); // 路线1

                            LCD_16_HanZi_ASCII(14, 4, "  ");
                            break;
                        case 5:
                            LCD_16_HanZi_ASCII(9, 6, "go"); // 路线1

                            LCD_16_HanZi_ASCII(9, 6, "  ");
                            break;
                        case 6:
                            LCD_16_HanZi_ASCII(14, 6, "go"); // 路线1

                            LCD_16_HanZi_ASCII(14, 6, "  ");
                            break;

                        default:
                            break;
                    }
                    break;
                case 'o':
                    switch (luxian) {
                        case 1:
                            LCD_16_HanZi_ASCII(9, 2, "go"); // 路线1

                            LCD_16_HanZi_ASCII(9, 2, "  ");
                            break;
                        case 2:
                            LCD_16_HanZi_ASCII(14, 2, "go"); // 路线1

                            LCD_16_HanZi_ASCII(14, 2, "  ");
                            break;
                        case 3:
                            LCD_16_HanZi_ASCII(9, 4, "go"); // 路线1

                            LCD_16_HanZi_ASCII(9, 4, "  ");
                            break;
                        case 4:
                            LCD_16_HanZi_ASCII(14, 4, "go"); // 路线1

                            LCD_16_HanZi_ASCII(14, 4, "  ");
                            break;
                        case 5:
                            LCD_16_HanZi_ASCII(9, 6, "go"); // 路线1

                            LCD_16_HanZi_ASCII(9, 6, "  ");
                            break;
                        case 6:
                            LCD_16_HanZi_ASCII(14, 6, "go"); // 路线1

                            LCD_16_HanZi_ASCII(14, 6, "  ");
                            break;

                        default:
                            break;
                    }
                    break;
                case '0':
                    break;
                case '1':
                    OLED_ShowxcString(48, 16, "1.", 16, 0);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 1;
                    break;
                case '2':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 0);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 2;
                    break;
                case '3':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 0);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 3;
                    break;
                case '4':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 0);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 4;
                    break;
                case '5':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 0);
                    OLED_ShowxcString(88, 48, "6.", 16, 1);
                    OLED_Refresh();
                    luxian = 5;
                    break;
                case '6':
                    OLED_ShowxcString(48, 16, "1.", 16, 1);
                    OLED_ShowxcString(88, 16, "2.", 16, 1);
                    OLED_ShowxcString(48, 32, "3.", 16, 1);
                    OLED_ShowxcString(88, 32, "4.", 16, 1);
                    OLED_ShowxcString(48, 48, "5.", 16, 1);
                    OLED_ShowxcString(88, 48, "6.", 16, 0);
                    OLED_Refresh();
                    luxian = 6;
                    break;

                default:
                    break;
            }
            if (KEY_TYPE == 'z' || KEY_TYPE == '#' || KEY_TYPE == 's' || KEY_TYPE == 'x') {
                break;
            }
        }
    }
}
void Net_g(void)
{
}
void Net_h(void)
{
}

void MenuOperate(void) // 运行菜单
{

    //	AD_AnJian();

    switch (KEY_TYPE) {
        case 'y':
            KeyFuncIndex = KeyTab[KeyFuncIndex].KeyYou; // 向右按键
            break;
        case 'z':
            KeyFuncIndex = KeyTab[KeyFuncIndex].KeyBackStatus; // 向左按键
            break;
        case 's':
            KeyFuncIndex = KeyTab[KeyFuncIndex].KeyUpStatus; // 向上按键
            break;
        case 'x':
            KeyFuncIndex = KeyTab[KeyFuncIndex].KeyDownStatus; // 向下按键
            break;
        case 'o':
            KeyFuncIndex = KeyTab[KeyFuncIndex].KeyOKStatus; // 中间按键
            break;
        case '#':
            KeyFuncIndex = KeyTab[KeyFuncIndex].KeyBackStatus; // 向左按键
            break;
        default:
            break;
    }
    //	if(SHAUNG_UI == 1)                //双车时使用
    //	{
    //		KeyFuncIndex=KeyTab[1].KeyOKStatus;
    //		SHAUNG_UI = 0;
    //	}

    KeyFuncPtr = KeyTab[KeyFuncIndex].CurrentOperate; // 下面是执行按键的操作
    (*KeyFuncPtr)();                                  // 执行当前的按键操作
}

u16 Speed_buffer[17];
void save_to_flash(void)
{

    Speed_buffer[0] = 78;

    Speed_buffer[1] = ce_move1_BUFF[0][2];
    Speed_buffer[2] = ce_move1_BUFF[1][2];
    Speed_buffer[3] = ce_move2_BUFF[0][2];
    Speed_buffer[4] = ce_move2_BUFF[1][2];
    Speed_buffer[5] = ce_move2_BUFF[2][2];
    Speed_buffer[6] = ce_move2_BUFF[3][2];

    if (ce_move1_BUFF[0][2] == 1) {
        Speed_buffer[7] = velocity_PID_KP_qh[ce_move1_BUFF[0][2]];
        Speed_buffer[8] = velocity_PID_KD_qh[ce_move1_BUFF[0][2]];
    } else if (ce_move1_BUFF[0][2] == 2) {
        Speed_buffer[9]  = velocity_PID_KP_qh[ce_move1_BUFF[0][2]];
        Speed_buffer[10] = velocity_PID_KD_qh[ce_move1_BUFF[0][2]];
    } else if (ce_move1_BUFF[0][2] == 3) {
        Speed_buffer[11] = velocity_PID_KP_qh[ce_move1_BUFF[0][2]];
        Speed_buffer[12] = velocity_PID_KD_qh[ce_move1_BUFF[0][2]];
    } else if (ce_move1_BUFF[0][2] == 4) {
        Speed_buffer[13] = velocity_PID_KP_qh[ce_move1_BUFF[0][2]];
        Speed_buffer[14] = velocity_PID_KD_qh[ce_move1_BUFF[0][2]];
    }

    //	Speed_buffer[7]=D_mt_bl;
    //	Speed_buffer[8]=D_mt_br;
    //
    //	Speed_buffer[9]=L_mt_ll;
    //	Speed_buffer[10]=L_mt_lr;
    //	Speed_buffer[11]=L_mt_bl;
    //	Speed_buffer[12]=L_mt_br;
    //
    //	Speed_buffer[13]=R_mt_ll;
    //	Speed_buffer[14]=R_mt_lr;
    //	Speed_buffer[15]=R_mt_bl;
    //	Speed_buffer[16]=R_mt_br;

    STMFLASH_Write(0X08070000, (u16 *)Speed_buffer, 34);
}
void read_from_flash(void)
{
    STMFLASH_Read(0X08070000, (u16 *)Speed_buffer, 34);
    if (Speed_buffer[0] == 78) {
        ce_move1_BUFF[0][2] = Speed_buffer[1];
        ce_move1_BUFF[1][2] = Speed_buffer[2];
        ce_move2_BUFF[0][2] = Speed_buffer[3];
        ce_move2_BUFF[1][2] = Speed_buffer[4];
        ce_move2_BUFF[2][2] = Speed_buffer[5];
        ce_move2_BUFF[3][2] = Speed_buffer[6];

        velocity_PID_KP_qh[1] = Speed_buffer[7];
        velocity_PID_KD_qh[1] = Speed_buffer[8];
        velocity_PID_KP_qh[2] = Speed_buffer[9];
        velocity_PID_KD_qh[2] = Speed_buffer[10];
        velocity_PID_KP_qh[3] = Speed_buffer[11];
        velocity_PID_KD_qh[3] = Speed_buffer[12];
        velocity_PID_KP_qh[4] = Speed_buffer[13];
        velocity_PID_KD_qh[4] = Speed_buffer[14];

        //		D_mt_bl=	Speed_buffer[7] ;
        //		D_mt_br=	Speed_buffer[8] ;
        //
        //		L_mt_ll=	Speed_buffer[9] ;
        //		L_mt_lr=	Speed_buffer[10];
        //		L_mt_bl=	Speed_buffer[11];
        //		L_mt_br=	Speed_buffer[12];
        //
        //		R_mt_ll=	Speed_buffer[13];
        //		R_mt_lr=	Speed_buffer[14];
        //		R_mt_bl=	Speed_buffer[15];
        //		R_mt_br=	Speed_buffer[16];
    }
}
