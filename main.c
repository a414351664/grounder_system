#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "key.h"

unsigned char item=1;
unsigned char key;           //存储键值
unsigned char Qstart=0x00;
unsigned char t=0;
unsigned char i=0;
void mode_1(void);
void mode_2(void);
void mode_3(void);
void mode_4(void);
void mode_5(void);
void mode_6(void);
void mode_7(void);
void mode_8(void);

int main(void)
{ 
	//float pwmset = 500;
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	KEY_Init();
	PWM_Init();
	//delay_init(168);  //???????
	LED_Init();				//???LED?? 
	//BEEP_Init();      //????????
	//KEY_Init();       //?????????????
	//LED0=0;				  	//?????
	while(1)
	{
		key=KEY_Scan(0);		//????
	   	if(key)
		{						   
			switch(key)
			{				 
				case KEY1_PRES:
					//item=1;
					//Qstart=0x00;
				   mode_1();
					break;
				 case KEY2_PRES:	
					
					mode_2();
					/*switch(Qstart)
					{
						case 0x01:mode_1();break;
						case 0x02:mode_2();break;
						case 0x04:mode_3();break;
						case 0x08:mode_4();break;
						case 0x10:mode_5();break;
						case 0x20:mode_6();break;
						case 0x40:mode_7();break;
						case 0x80:mode_8();break;
						default:break;
					}*/
					break;
				/*case KEY3_PRES:		
					switch(item)
					{
						case 1:Qstart=0x01;break;//0000 0001
						case 2:Qstart=0x02;break;//0000 0010
						case 3:Qstart=0x04;break;//0000 0100
						case 4:Qstart=0x08;break;//0000 1000
						case 5:Qstart=0x10;break;//0001 0000
						case 6:Qstart=0x20;break;//0010 0000
						case 7:Qstart=0x40;break;//0100 0000
						case 8:Qstart=0x80;break;//1000 0000
						default:break;
					}					
					break;
				case KEY4_PRES:
							item++;
							if(item==9)//item=1~8,choose 8 mode
								item=1;
					break;*/
			}
		}else delay_ms(10); 
	}
}


void mode_1(void)
{
	while(1){
		t = 50;
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		Updata_PWM_(t,75,500,20000);	
		delay_ms(5);
		t=t+1;
		if(t==100)t=50;
		
		key=KEY_Scan(0);
		if(key == 2) break;
	}
}
void mode_2(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	while(1)
	{	
		Updata_PWM_(t,i,500,20000);	
		delay_ms(5);
		t=t+1;
		i=i+1;
		if(t==100)t=50;
		//if(t==100)t=20;
		key=KEY_Scan(0);
		if(key == 1) break;
	}
	
	
}
/*void mode_3(void)
{}
void mode_4(void)
{}
void mode_5(void)
{}
void mode_6(void)
{}
void mode_7(void)
{}
void mode_8(void)
{}*/

