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

void LED_init();
void BUTTON_init();
void TIM_init();
void TIMINT_init();
void TOUCH_init();
void tostring(char [], int);
void ekran(int);

int i,num,counter1,counter2,counter3;
char str[10];
int x_pr,y_pr,x_dir,y_dir;
int ch1_v,ch2_v,ch3_v;
int ch1_s,ch2_s,ch3_s;
int ch1_k,ch2_k,ch3_k;
int krok;


#endif /* DEFINE_H_ */
