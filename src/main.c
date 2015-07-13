/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO(R)
**                STMicroelectronics STM32F4xx Standard Peripherals Library
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. This file may only be built (assembled or compiled and linked)
**  using the Atollic TrueSTUDIO(R) product. The use of this file together
**  with other tools than Atollic TrueSTUDIO(R) is not permitted.
**
*****************************************************************************
*/

/* Includes */
/**
 *	Keil project for ILI9341 LCD example
 *
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision 5
 */
#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "TM_lib/tm_stm32f4_ili9341.h"
#include "TM_lib/tm_stm32f4_fonts.h"
#include "defines.h"
#include <stdio.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TM_lib/tm_stm32f4_stmpe811.h"

#define LED_GREEN GPIO_Pin_13
#define LED_RED GPIO_Pin_14
#define LED1 GPIO_Pin_11
#define LED2 GPIO_Pin_15

void LED_init();
void BUTTON_init();
void TIM_init();
void TIMINT_init();

int i,num,counter;
char str[10];
int x_pr,y_pr,x_dir,y_dir;

void tostring(char [], int);

int main(void) {
	//Initialize system
	SystemInit();

	i=0;
	num=0;
	counter=0;

	//Enable HSE clock
	RCC_HSEConfig(RCC_HSE_ON);
	//Wait for clock to stabilize
	while (!RCC_WaitForHSEStartUp());

	LED_init();
	BUTTON_init();
	TIM_init();
	TIMINT_init();

	GPIO_SetBits(GPIOG,LED_GREEN);

	//Initialize ILI9341
	TM_ILI9341_Init();
	//Rotate LCD for 90 degrees
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);
	//FIll lcd with color
	TM_ILI9341_Fill(ILI9341_COLOR_ORANGE);
	//Draw white circle
	//TM_ILI9341_DrawCircle(0, 0, 10, ILI9341_COLOR_GREEN);
	//Draw red filled circle
	TM_ILI9341_DrawFilledCircle(60, 60, 35, ILI9341_COLOR_RED);
	//Draw blue rectangle
	//TM_ILI9341_DrawRectangle(120, 20, 220, 100, ILI9341_COLOR_BLUE);
	//Draw black filled rectangle
	TM_ILI9341_DrawFilledRectangle(120, 200, 220, 230, ILI9341_COLOR_RED);

	//Create TouchData struct
	TM_STMPE811_TouchData touchData;

	//Initialize Touch
	    if (TM_STMPE811_Init() != TM_STMPE811_State_Ok) {
	        TM_ILI9341_Puts(20, 20, "STMPE811 Error", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);

	        while (1);
	    }

	 //Select touch screen orientation
	    touchData.orientation = TM_STMPE811_Orientation_Portrait_2;

	//Draw line with custom color 0x0005
	TM_ILI9341_DrawLine(20, 120, 220, 120, 0x0005);

	//Put string with black foreground color and blue background with 11x18px font
	TM_ILI9341_Puts(65, 130, "Hello World!", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	//Put string with black foreground color and blue background with 11x18px font
	TM_ILI9341_Puts(60, 150, "Test LCD", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	//Put string with black foreground color and red background with 11x18px font
	TM_ILI9341_Puts(1, 310, "LB", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);


	while (1) {
		if(i>4){
			tostring(str, num++);
			TM_ILI9341_Puts(60, 200, str , &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
			i=0;
		}
		if (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) {
            //Touch valid
			if((touchData.x>120 && touchData.x<220)&&(touchData.y>200 && touchData.y<230)){
				num=0;
				//TM_ILI9341_Puts(60, 200, "    ", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
			}

		}

	}
}



void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        GPIO_ToggleBits(GPIOG,LED_GREEN | LED_RED);
        i++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

void TIM3_IRQHandler()
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        GPIO_ToggleBits(GPIOG,LED_GREEN | LED_RED);
        counter++;
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

void tostring(char str[], int num)
{
    int i,j, rem, len = 0, n;
    if (num==0) {
    	str[0]='0';
    	for(j=1;j<4;j++){
    		str[j]=' ';
    	}
    	return;
    }
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

void LED_init(){
	//Enable clock for GPOIG
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	//Initialize struct
	GPIO_InitTypeDef GPIO_InitDef;

	//Pins 13 and 14
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_11 | GPIO_Pin_15;
	//Mode output
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	//Output type push-pull
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	//Without pull resistors
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//50MHz pin speed
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

	//Initialize pins
	GPIO_Init(GPIOG, &GPIO_InitDef);
}
void BUTTON_init(){

	//Enable clock for GPOIA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//Initialize struct
	GPIO_InitTypeDef GPIO_InitDef;

	//Pin 0
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_0;
	//Mode output
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
	//Output type push-pull
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	//With pull down resistor
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
	//50MHz pin speed
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

	//Initialize pin on GPIOA port
	GPIO_Init(GPIOA, &GPIO_InitDef);
}

void TIM_init(){
	//TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 18000;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 1000;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	//TIM3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 18000;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 10;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerInitStructure);
	TIM_Cmd(TIM3, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void TIMINT_init()
{
	//TIM2
    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);

    //TIM3
    //NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
}

void sEE_TIMEOUT_UserCallback(){
	while(1){

	}
}
