/*
 * define.h
 *
 *  Created on: Jul 12, 2015
 *      Author: £ukasz
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#define LED_GREEN GPIO_Pin_13
#define LED_RED GPIO_Pin_14
#define LED1 GPIO_Pin_11
#define LED2 GPIO_Pin_15

//--------- Wyjscia sterowników ----------------
#define KROK1_CH1 GPIOG,GPIO_Pin_5
#define KROK2_CH1 GPIOG,GPIO_Pin_7
#define KROK3_CH1 GPIOC,GPIO_Pin_6

#define DIR_CH1 GPIOC,GPIO_Pin_8
#define STEP_CH1 GPIOA,GPIO_Pin_8
#define EN_CH1 GPIOA,GPIO_Pin_10

#define KROK1_CH2 GPIOG,GPIO_Pin_2
#define KROK2_CH2 GPIOD,GPIO_Pin_14
#define KROK3_CH2 GPIOD,GPIO_Pin_12

#define DIR_CH2 GPIOD,GPIO_Pin_10
#define STEP_CH2 GPIOD,GPIO_Pin_8
#define EN_CH2 GPIOB,GPIO_Pin_14


void LED_init();
void WY_init();
void BUTTON_init();
void TIM_init();
void TIMINT_init();
void TOUCH_init();
void tostring(char [], int);
void ekran(int);
void set_krok(int,int);

int i,num,counter1,counter2,counter3;
char str[10];
int x_pr,y_pr,x_dir,y_dir;
int ch1_v,ch2_v,ch3_v;
int ch1_s,ch2_s,ch3_s;
int ch1_k,ch2_k,ch3_k;
int krok;


#endif /* DEFINE_H_ */
