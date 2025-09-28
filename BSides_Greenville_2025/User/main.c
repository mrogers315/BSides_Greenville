/*
    A basic project to shown the WS2812B capablilties of the CH32V003 MCU
    LEDs are coonected to PC6. 

*/
#include "debug.h"

/* Global define */
#define LED_NUM 16

#include "ws2812b.h"

/* Global Variable */
uint8_t offset = 1;

//GPIO Setup
void WS2812B_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}


//Main Function
int main(void)
{
    RCC_AdjustHSICalibrationValue(0x10);
    WS2812B_Init();
	Delay_Init();

    while (1) //Infinite loop
    {
       for(int i=0; i<4; i++){
            WS2812B_FadeColors(100, 6);
        }
        for(int i=0; i<1; i++){
            WS2812B_ChaseColor(100, 6);
        }
        for(int i=0; i<8; i++){
            WS2812B_Rainbow_Chase(20, 6);
        }

    }
}