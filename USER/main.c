#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
//����������ƺ���
void go();
void ret();//����
void stop();
void right();
void left();
void xunji();

void left_min();//�������ҵ��ת�ٿ���
void left_max();
void right_min();
void right_max();

//����ʵ��  

 int main(void)
 {		             //���¶�����ƶ��������ҪΪȡ���൥Ƭ��ϵͳ�����Ե�����
 	u8 t;//�˽��ƶ������
	u8 len;	
	u16 times=0;//ʮ�����ƶ������
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	LCD_Init();        //LCD��ʼ��
 	while(1)
	{

		if(USART_RX_STA&0x8000)//����ͨѶ
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			switch(USART_RX_BUF[0])//��������ѡ��
				{
					case 0x00:stop();break;
					case 0x01:go();break;
					case 0x02:ret();break;
					case 0x03:right();break;
					case 0x04:left();break;
					case 0x05:xunji();break;
					case 0x06:{
											if(!KEY0)
											{
												left();
												delay_ms(400);
												go();
											}
					}break;
				}
			//printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}else
		{
//			times++;
//		if(times%200==0)printf("123");  
//			delay_ms(10);   
		}		
	}	 
 }
 void stop()
 {
	 IN1=0;
	 IN2=0;
	 IN3=0;
	 IN4=0;
 }
  void go()
 {
	 IN1=1;
	 IN2=0;
	 IN3=0;
	 IN4=1;
 }
  void ret()
 {
	 IN1=0;
	 IN2=1;
	 IN3=1;
	 IN4=0;
 }
  void right()
 {
	 IN1=1;
	 IN2=0;
	 IN3=1;
	 IN4=0;
 }
 void left()
 {
	 IN1=0;
	 IN2=1;
	 IN3=0;
	 IN4=1;
 }
 
 void left_min()
 {
	 left();
	 delay_ms(2);
 }
 void left_max()
 {
	 left();
	 delay_ms(5);
 }
 void right_min()
 {
	 right();
	 delay_ms(2);
 }
 void right_max()
 {
	 right();
	 delay_ms(5);
 }
void xunji()//����Ѱ������
{
	while((USART_RX_STA&0x8000))//�����ݽ���δ���ʱ����ѭ��
	//	while(1)
	{
		if(LCD0|LCD1|LCD2|LCD3)//1��2��3��4��λ�ù���Ԫ������ź�
		{
		if(!LCD0) {left_max();}//0δ��⵽�źţ�������ת
		if((!LCD1)&(LCD2)) {left_min();}
		if((!LCD1)&(!LCD2)){go();delay_ms(50);}
		if((LCD1)&(!LCD2)) {right_min();}
		if(!LCD3) {right_max();}//0δ��⵽�źţ�������ת
		}
		go();//ֱ��
	}
}