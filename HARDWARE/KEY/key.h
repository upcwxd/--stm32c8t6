#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

// 
//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define KEY3 PAin(0)	//PA0  WK_UP
 
#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//��ȡ����2 

#define LCD0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//��ȡѭ������
#define LCD1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//��ȡ����1
#define LCD2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//��ȡ����2 
#define LCD3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//��ȡѭ������

void KEY_Init(void);//IO��ʼ��		
void LCD_Init(void);//IO��ʼ��
#endif
