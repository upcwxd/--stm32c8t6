#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
//定义各个控制函数
void go();
void ret();//后退
void stop();
void right();
void left();
void xunji();

void left_min();//控制左右电机转速快慢
void left_max();
void right_min();
void right_max();

//串口实验  

 int main(void)
 {		             //以下多个进制定义变量主要为取消多单片机系统兼容性的问题
 	u8 t;//八进制定义变量
	u8 len;	
	u16 times=0;//十六进制定义变量
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
	LCD_Init();        //LCD初始化
 	while(1)
	{

		if(USART_RX_STA&0x8000)//无线通讯
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			switch(USART_RX_BUF[0])//进行数据选择
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
			//printf("\r\n\r\n");//插入换行
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
void xunji()//定义寻迹函数
{
	while((USART_RX_STA&0x8000))//在数据接收未完成时进入循环
	//	while(1)
	{
		if(LCD0|LCD1|LCD2|LCD3)//1，2，3，4各位置光敏元件检测信号
		{
		if(!LCD0) {left_max();}//0未检测到信号，高速左转
		if((!LCD1)&(LCD2)) {left_min();}
		if((!LCD1)&(!LCD2)){go();delay_ms(50);}
		if((LCD1)&(!LCD2)) {right_min();}
		if(!LCD3) {right_max();}//0未检测到信号，高速右转
		}
		go();//直走
	}
}