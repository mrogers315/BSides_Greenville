
#include "debug.h"
#include "ws2812b.h"


/* Global define */

/* Global Variable */
uint8_t offset = 1;
uint32_t led[16] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};

void WS2812B_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}



int main(void)
{
    RCC_AdjustHSICalibrationValue(0x10);
    WS2812B_Init();
	Delay_Init();
    int i=0;


    while (1)
    {
        //WS2812B_FadeColors(16, 6);
        //WS2812B_ChaseColor(16, 1, 6);
        for(int j=0; j<255; j++){
            WS2812B_Hue_Table(16,(i%256), 6);
            i = i + 16;
        }   

    }
}