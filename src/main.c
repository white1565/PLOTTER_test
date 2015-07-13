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




int main(void) {
	//Initialize system
	SystemInit();

	i=0;
	num=0;
	counter=0;

	int ekr;
	ekr=1;
	ch1_s=0;
	ch2_s=0;
	ch3_s=0;
	ch1_k=0;
	ch2_k=0;
	ch3_k=0;
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
	ekran(1);

	//Create TouchData struct
	TM_STMPE811_TouchData touchData;
	TOUCH_init();
	//Select touch screen orientation
	touchData.orientation = TM_STMPE811_Orientation_Portrait_2;



	while (1) {
		if(i>4){
			tostring(str, num++);
			//TM_ILI9341_Puts(60, 200, str , &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
			i=0;
		}
		if (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) {
            //Touch valid
			if((touchData.x>80 && touchData.x<160)&&(touchData.y>200 && touchData.y<240)&&(ekr==1)){
				ekran(2);
				ekr=2;
			}
//********** EKRAN 2 **************
			if(ekr==2){
//----------------- SUWAKI ------------------
				if((touchData.x>10 && touchData.x<50)&&(touchData.y>10 && touchData.y<210)){
					ch1_v=touchData.y;
					TM_ILI9341_DrawFilledRectangle(10, 10, 50, touchData.y, ILI9341_COLOR_WHITE);
					TM_ILI9341_DrawFilledRectangle(10, touchData.y, 50, 210, ILI9341_COLOR_GREEN2);
					tostring(str, ch1_v);
					TM_ILI9341_Puts(180, 10, "CH1: ", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
					TM_ILI9341_Puts(210, 10, "   ", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
					TM_ILI9341_Puts(210, 10, str, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
				}
				else if((touchData.x>70 && touchData.x<110)&&(touchData.y>10 && touchData.y<210)){
					ch2_v=touchData.y;
					TM_ILI9341_DrawFilledRectangle(70, 10, 110, touchData.y, ILI9341_COLOR_WHITE);
					TM_ILI9341_DrawFilledRectangle(70, touchData.y, 110, 210, ILI9341_COLOR_GREEN2);
					tostring(str, ch2_v);
					TM_ILI9341_Puts(180, 25, "CH2: ", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
					TM_ILI9341_Puts(210, 25, "   ", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
					TM_ILI9341_Puts(210, 25, str, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
					//70, 10, 110, 200,
				}
				else if((touchData.x>130 && touchData.x<170)&&(touchData.y>10 && touchData.y<210)){
					ch3_v=touchData.y;
					TM_ILI9341_DrawFilledRectangle(130, 10, 170, touchData.y, ILI9341_COLOR_WHITE);
					TM_ILI9341_DrawFilledRectangle(130, touchData.y, 170, 210, ILI9341_COLOR_GREEN2);
					tostring(str, ch3_v);
					TM_ILI9341_Puts(180, 40, "CH3: ", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
					TM_ILI9341_Puts(210, 40, "   ", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
					TM_ILI9341_Puts(210, 40, str, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
					//130, 10, 170, 200
				}
//----------------------- BUTTON GO --------------------------
				if((touchData.x>10 && touchData.x<50)&&(touchData.y>220 && touchData.y<260)){
					if(ch1_s==0){
						TM_ILI9341_DrawFilledRectangle(10, 220, 50, 260, ILI9341_COLOR_GREEN);
						TM_ILI9341_Puts(15, 230, "GO", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN);
						ch1_s=1;
					}
					else{
						TM_ILI9341_DrawFilledRectangle(10, 220, 50, 260, ILI9341_COLOR_RED);
						TM_ILI9341_Puts(15, 230, "STOP", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
						ch1_s=0;
					}
					Delayms(100);
					//10, 220, 50, 260
				}
				else if((touchData.x>70 && touchData.x<110)&&(touchData.y>220 && touchData.y<260)){
					if(ch2_s==0){
						TM_ILI9341_DrawFilledRectangle(70, 220, 110, 260, ILI9341_COLOR_GREEN);
						TM_ILI9341_Puts(75, 230, "GO", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN);
						ch2_s=1;
					}
					else{
						TM_ILI9341_DrawFilledRectangle(70, 220, 110, 260, ILI9341_COLOR_RED);
						TM_ILI9341_Puts(75, 230, "STOP", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
						ch2_s=0;
					}
					Delayms(100);
					//70, 220, 110, 260,
				}
				else if((touchData.x>130 && touchData.x<170)&&(touchData.y>220 && touchData.y<260)){
					if(ch3_s==0){
						TM_ILI9341_DrawFilledRectangle(130, 220, 170, 260, ILI9341_COLOR_GREEN);
						TM_ILI9341_Puts(135, 230, "GO", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN);
						ch3_s=1;
					}
					else{
						TM_ILI9341_DrawFilledRectangle(130, 220, 170, 260, ILI9341_COLOR_RED);
						TM_ILI9341_Puts(135, 230, "STOP", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
						ch3_s=0;
					}
					Delayms(100);
					//130, 220, 170, 260,
				}
//---------------- BUTTON KIERUNKU -------------------------------------
				if((touchData.x>10 && touchData.x<50)&&(touchData.y>270 && touchData.y<310)){
					if(ch1_k==0){
						TM_ILI9341_Puts(15, 280, "CCW", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
						ch1_k=1;
					}
					else{
						TM_ILI9341_Puts(15, 280, "CW ", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
						ch1_k=0;
					}
					Delayms(100);
					//10, 270, 50, 310,
				}
				else if((touchData.x>70 && touchData.x<110)&&(touchData.y>270 && touchData.y<310)){
					if(ch2_k==0){
						TM_ILI9341_Puts(75, 280, "CCW", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
						ch2_k=1;
					}
					else{
						TM_ILI9341_Puts(75, 280, "CW ", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
						ch2_k=0;
					}
					Delayms(100);
					//70, 270, 110, 310,
				}
				else if((touchData.x>130 && touchData.x<170)&&(touchData.y>270 && touchData.y<310)){
					if(ch3_k==0){
						TM_ILI9341_Puts(135, 280, "CCW", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
						ch3_k=1;
					}
					else{
						TM_ILI9341_Puts(135, 280, "CW ", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
						ch3_k=0;
					}
					Delayms(100);
					//130, 270, 170, 310,
				}
			}

		}

	}
}



