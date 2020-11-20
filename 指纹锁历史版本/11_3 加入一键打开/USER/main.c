#include "delay.h"
#include "led.h"

#include "oled.h"
#include "bmp.h"

#include "pwm.h"

#include "public.h"
u8  eu8_Flag = 0;								/*全局变量串口一发生中断标志位*/
u8  eu8_what = 0;        			  /*全局变量串口一接收到的一位数据*/
int DJ1=0;//舵机调速用
int FenMin=1; //蜂鸣器是否开启
extern int Shua_ZW_OK;//全局变量 指纹验证通过为1
#define usart2_baund  57600			/*串口2波特率，根据指纹模块波特率更改*/
SysPara AS608Para;							/*指纹模块AS608参数*/
u16 ValidN;											/*模块内有效指纹个数*/

int main()
{
	u8 ensure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init();								/*延时初始化*/
	USART_INIT();								/*串口一初始化*/
	
	
	
	LED_Init();//LED及蜂鸣器初始化

	//AS608_SW=1;
	BEEP=0;
	AS608_SW=1;	
	LED1=1;	

	
//	AS608_SW=0;	
//	delay_ms(1000);
//	LED1=0;
//	
//	AS608_SW=1;	
//	delay_ms(1000);
//	AS608_SW=0;	
	
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	OLED_Refresh();
		
	OLED_ShowString(72,52,"by NF404",12);
	OLED_Refresh();
	
	TIM3_PWM_Init(199,7199);//初始化    4为0度 23为180
  TIM_SetCompare2(TIM3, 4);//TIM3_CH2 舵机180度 

	
	printf("初始化中\r\n");
	usart2_init(usart2_baund);	/*初始化串口2,用于与指纹模块通讯*/
	PS_StaGPIO_Init();					/*初始化FR读状态引脚*/
	printf("与指纹模块握手\r\n");
	while(PS_HandShake(&AS608Addr))			/*与AS608模块握手*/
	{
		delay_ms(400);
		printf("未检测到模块\r\n");
		OLED_ShowString(48,20,"NO AS608",12);
		OLED_Refresh();
		
		delay_ms(800);
		printf("尝试重新连接模块\r\n"); 
	}
	printf("通讯成功\r\n");
	printf("波特率:%d   地址:%x\r\n",usart2_baund,AS608Addr);		/*打印信息*/
	ensure=PS_ValidTempleteNum(&ValidN);										/*读库指纹个数*/
	if(ensure!=0x00)
		ShowErrMessage(ensure);								/*显示确认码错误信息*/
	ensure=PS_ReadSysPara(&AS608Para);  		/*读参数 */
	if(ensure==0x00)
	{
		printf("库容量:%d     对比等级: %d",AS608Para.PS_max-ValidN,AS608Para.PS_level);
	}
	else
		ShowErrMessage(ensure);	
	
	OLED_Clear();
	OLED_ShowChinese(32,32,0,16);//请
	OLED_ShowChinese(48,32,1,16);//按
	OLED_ShowChinese(64,32,2,16);//手
	OLED_ShowChinese(80,32,3,16);//指
	//OLED_Refresh();
	OLED_ShowChinese(48,0,0,32);//锁
	OLED_ShowString(0,52,"(-_-)  V1.1-by NF404",12);
	//OLED_ShowString(72,52,"V1.1by NF404",12);
	OLED_Refresh();

	
  while(1)
	{
			
			//AS608_SW=0;	
			//usart1_execute();			 /*串口一接收到串口屏数据后执行子函数*/
			//OLED_ShowString(32,32,"NI DE YAN JIN",12);
			//OLED_Refresh();
//			OLED_ShowChinese(32,32,0,16);//请
//			OLED_ShowChinese(48,32,1,16);//按
//			OLED_ShowChinese(64,32,2,16);//手
//			OLED_ShowChinese(80,32,3,16);//指
//			OLED_Refresh();
			AS608_SW=0;	
			
		if(KEY==1)//检测按键
			{
				delay_ms(10);
				if(KEY==1)
				{
					Shua_ZW_OK=1;
					FenMin=0;
				}
							
			}
			
			if(PS_Sta && Shua_ZW_OK==0)	 //检测PS_Sta状态，如果有手指按下
			{
			LED1=0;
			AS608_SW=1;
			
			OLED_ShowChinese(32,32,14,16);//搜索指纹
			OLED_ShowChinese(48,32,15,16);//
			OLED_ShowChinese(64,32,10,16);//
			OLED_ShowChinese(80,32,11,16);//
			OLED_Refresh();
			
			delay_ms(100);
				
			press_FR();//刷指纹	
			LED1=1;
			delay_ms(50);
			//AS608_SW=0;
			}
			
			if(Shua_ZW_OK)
			{
				//TIM_SetCompare2(TIM3, 23);
				Shua_ZW_OK=0;//指纹验证通过标志清除
				//OLED_Clear();
				OLED_ShowChinese(48,0,1,32);//解1
				OLED_ShowChinese(80,0,2,32);//解2
				OLED_ShowChinese(32,32,4,16);//验
				OLED_ShowChinese(48,32,5,16);//证
				OLED_ShowChinese(64,32,6,16);//通
				OLED_ShowChinese(80,32,7,16);//过
				OLED_ShowString(0,52,"(>_<)  V1.1-by NF404",12);
				OLED_Refresh();
								
				//TIM_SetCompare2(TIM3, 23);
			
				for(DJ1=4;DJ1<10;DJ1++)
				{
					TIM_SetCompare2(TIM3, DJ1);
					delay_ms(50);
				}
				delay_ms(300);
				if(FenMin)
					{						
						BEEP=0;
						OLED_ShowString(0,0,"Bee~ ~",12);
						OLED_Refresh();
						delay_ms(250);
						BEEP=1;
					}else
						{
							
							FenMin=1;
						}
			
				delay_ms(250);		
				delay_ms(1000);
				delay_ms(1000);
								
				TIM_SetCompare2(TIM3, 4);
				delay_ms(500);
				
				OLED_Clear();
				OLED_ShowString(0,52,"(-_-)  V1.1-by NF404",12);
				OLED_ShowChinese(48,0,0,32);//锁
				OLED_ShowChinese(32,32,0,16);//请
				OLED_ShowChinese(48,32,1,16);//按
				OLED_ShowChinese(64,32,2,16);//手
				OLED_ShowChinese(80,32,3,16);//指
				OLED_Refresh();			
				AS608_SW=0;
				
				//TIM_SetCompare2(TIM3, 4);
				//OLED_ShowString(32,0,"tongguo",12);
				//OLED_Refresh();
			}else
				{
					OLED_ShowChinese(32,32,0,16);//请
					OLED_ShowChinese(48,32,1,16);//按
					OLED_ShowChinese(64,32,2,16);//手
					OLED_ShowChinese(80,32,3,16);//指
					OLED_Refresh();
				}
				
			//a=KEY_Scan();
		//	OLED_ShowNum(0,32,a,3,16);
		//	printf("%d\r\n",a);
	
			
	}
}

