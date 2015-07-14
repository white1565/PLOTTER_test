/*
 * fun.c
 *
 *  Created on: Jul 13, 2015
 *      Author: £ukasz
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

void ekran(int nr){
	switch(nr){
	case 1:
		//Rotate LCD for 90 degrees
		TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);
		//FIll lcd with color
		TM_ILI9341_Fill(ILI9341_COLOR_ORANGE);
		//Draw white circle
		//TM_ILI9341_DrawCircle(0, 0, 10, ILI9341_COLOR_GREEN);
		//Draw red filled circle
		TM_ILI9341_DrawFilledCircle(60, 40, 35, ILI9341_COLOR_RED);
		//Draw blue rectangle
		//TM_ILI9341_DrawRectangle(120, 20, 220, 100, ILI9341_COLOR_BLUE);
		//Draw black filled rectangle
		TM_ILI9341_DrawFilledRectangle(70, 200, 160, 240, ILI9341_COLOR_RED);
		TM_ILI9341_Puts(85, 215, "START", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
		//Draw line with custom color 0x0005
		TM_ILI9341_DrawLine(20, 120, 220, 120, 0x0005);
		//Put string with black foreground color and blue background with 11x18px font
		TM_ILI9341_Puts(40, 110, " STEP DRIVER ", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		//Put string with black foreground color and blue background with 11x18px font
		TM_ILI9341_Puts(10, 140, "Press START to begin", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		//Put string with black foreground color and red background with 11x18px font
		TM_ILI9341_Puts(1, 310, "LB", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		return;
	case 2:
		//Rotate LCD for 90 degrees
		TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);
		//FIll lcd with color
		TM_ILI9341_Fill(ILI9341_COLOR_BLUE2);
		//Draw blue rectangle
		//TM_ILI9341_DrawRectangle(120, 20, 220, 100, ILI9341_COLOR_BLUE);
		//Draw black filled rectangle
		TM_ILI9341_DrawFilledRectangle(10, 10, 50, 210, ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(70, 10, 110, 210, ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(130, 10, 170, 210, ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(10, 220, 50, 260, ILI9341_COLOR_RED);
		TM_ILI9341_Puts(15, 230, "STOP", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
		TM_ILI9341_DrawFilledRectangle(70, 220, 110, 260, ILI9341_COLOR_RED);
		TM_ILI9341_Puts(75, 230, "STOP", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
		TM_ILI9341_DrawFilledRectangle(130, 220, 170, 260, ILI9341_COLOR_RED);
		TM_ILI9341_Puts(135, 230, "STOP", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
		TM_ILI9341_DrawFilledRectangle(10, 270, 50, 310, ILI9341_COLOR_YELLOW);
		TM_ILI9341_Puts(15, 280, "CW", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
		TM_ILI9341_DrawFilledRectangle(70, 270, 110, 310, ILI9341_COLOR_YELLOW);
		TM_ILI9341_Puts(75, 280, "CW", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
		TM_ILI9341_DrawFilledRectangle(130, 270, 170, 310, ILI9341_COLOR_YELLOW);
		TM_ILI9341_Puts(135, 280, "CW", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
		TM_ILI9341_DrawFilledRectangle(180, 100, 235, 125, ILI9341_COLOR_BLUE);
		TM_ILI9341_Puts(185, 105, "FULL", &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLUE);
		TM_ILI9341_DrawFilledRectangle(180, 130, 235, 155, ILI9341_COLOR_WHITE);
		TM_ILI9341_Puts(185, 135, "1/2", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(180, 160, 235, 185, ILI9341_COLOR_WHITE);
		TM_ILI9341_Puts(185, 165, "1/4", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(180, 190, 235, 215, ILI9341_COLOR_WHITE);
		TM_ILI9341_Puts(185, 195, "1/8", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(180, 220, 235, 245, ILI9341_COLOR_WHITE);
		TM_ILI9341_Puts(185, 225, "1/16", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		return;
	default:
		//Rotate LCD for 90 degrees
		TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);
		//FIll lcd with color
		TM_ILI9341_Fill(ILI9341_COLOR_GREEN);
		//Draw white circle
		//TM_ILI9341_DrawCircle(0, 0, 10, ILI9341_COLOR_GREEN);
		//Draw red filled circle
		TM_ILI9341_DrawFilledCircle(60, 60, 35, ILI9341_COLOR_RED);
		//Draw blue rectangle
		//TM_ILI9341_DrawRectangle(120, 20, 220, 100, ILI9341_COLOR_BLUE);
		//Draw black filled rectangle
		TM_ILI9341_DrawFilledRectangle(120, 200, 220, 230, ILI9341_COLOR_RED);
		return;
	}
}

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        i++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

void TIM3_IRQHandler()
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        counter1++;
        counter2++;
        counter3++;
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

void set_krok(int kr,int ch){
	if(ch==1){
		GPIO_SetBits(EN_CH1);
		Delayms(100);
		if(kr){
			GPIO_ResetBits(KROK1_CH1);
			GPIO_ResetBits(KROK2_CH1);
			GPIO_ResetBits(KROK3_CH1);
		}
		else if(kr==2){
			GPIO_SetBits(KROK1_CH1);
			GPIO_ResetBits(KROK2_CH1);
			GPIO_ResetBits(KROK3_CH1);
		}
		else if(kr==4){
			GPIO_ResetBits(KROK1_CH1);
			GPIO_SetBits(KROK2_CH1);
			GPIO_ResetBits(KROK3_CH1);
		}
		else if(kr==8){
			GPIO_SetBits(KROK1_CH1);
			GPIO_SetBits(KROK2_CH1);
			GPIO_ResetBits(KROK3_CH1);
		}
		else if(kr==16){
			GPIO_SetBits(KROK1_CH1);
			GPIO_SetBits(KROK2_CH1);
			GPIO_SetBits(KROK3_CH1);
		}
		Delayms(100);
		GPIO_ResetBits(EN_CH1);
		Delayms(100);
	}
	else if (ch==2){
		GPIO_SetBits(EN_CH2);
		Delayms(100);
		if(kr){
			GPIO_ResetBits(KROK1_CH2);
			GPIO_ResetBits(KROK2_CH2);
			GPIO_ResetBits(KROK3_CH2);
		}
		else if(kr==2){
			GPIO_SetBits(KROK1_CH2);
			GPIO_ResetBits(KROK2_CH2);
			GPIO_ResetBits(KROK3_CH2);
		}
		else if(kr==4){
			GPIO_ResetBits(KROK1_CH2);
			GPIO_SetBits(KROK2_CH2);
			GPIO_ResetBits(KROK3_CH2);
		}
		else if(kr==8){
			GPIO_SetBits(KROK1_CH2);
			GPIO_SetBits(KROK2_CH2);
			GPIO_ResetBits(KROK3_CH2);
		}
		else if(kr==16){
			GPIO_SetBits(KROK1_CH2);
			GPIO_SetBits(KROK2_CH2);
			GPIO_SetBits(KROK3_CH2);
		}
		Delayms(100);
		GPIO_ResetBits(EN_CH2);
		Delayms(100);
	}
}

void LED_init(){
	//Enable clock for GPOIG
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	//Initialize struct
	GPIO_InitTypeDef GPIO_InitDef;

	//Pins 13 and 14
	GPIO_InitDef.GPIO_Pin = LED_RED | LED_GREEN;
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

void TOUCH_init(){
	//Initialize Touch
	    if (TM_STMPE811_Init() != TM_STMPE811_State_Ok) {
	        TM_ILI9341_Puts(20, 20, "STMPE811 Error", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);

	        while (1);
	    }
}

void WY_init(){
		//Enable clock for GPOIG
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
		//Initialize struct
		GPIO_InitTypeDef GPIO_InitDef;

		//Pins 2,5,7
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_7;
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

		//Enable clock for GPOIA
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		//Pins 8,10
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10;
		//Initialize pins
		GPIO_Init(GPIOA, &GPIO_InitDef);

		//Enable clock for GPOIB
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		//Pins 14
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_14;
		//Initialize pins
		GPIO_Init(GPIOB, &GPIO_InitDef);

		//Enable clock for GPOIC
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		//Pins 6,8
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8;
		//Initialize pins
		GPIO_Init(GPIOC, &GPIO_InitDef);

		//Enable clock for GPOID
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		//Pins 8,10,12,14
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_14;
		//Initialize pins
		GPIO_Init(GPIOD, &GPIO_InitDef);
}

void sEE_TIMEOUT_UserCallback(){
	while(1){

	}
}
