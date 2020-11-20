#include "AS608_use.h"

#include "oled.h"
#include "bmp.h"
#include "delay.h"
#include "led.h"

extern SysPara AS608Para;							/*指纹模块AS608参数*/
extern u16 ValidN;	/*模块内有效指纹个数*/
int Shua_ZW_OK;
extern int a;

//显示确认码错误信息
void ShowErrMessage(u8 ensure)
{
	printf("\r\n错误信息：%s \r\n",(u8*)EnsureMessage(ensure));
	switch (a)
	{
		case 1:
			BEEP=0;
			OLED_ShowChinese(32,32,8,16);//无
			OLED_ShowChinese(48,32,9,16);//此
			OLED_ShowChinese(64,32,10,16);//指
			OLED_ShowChinese(80,32,11,16);//纹
			OLED_Refresh();
			delay_ms(250);
			BEEP=1;
			delay_ms(250);
			BEEP=0;
			delay_ms(250);
			BEEP=1;
			delay_ms(250);
			AS608_SW=0;
//			OLED_ShowChinese(32,32,0,16);//请
//			OLED_ShowChinese(48,32,1,16);//按
//			OLED_ShowChinese(64,32,2,16);//手
//			OLED_ShowChinese(80,32,3,16);//指
//			OLED_Refresh();
			
			break;
		case 2:
			//OLED_ShowChinese(24,32,0,16);//请
			OLED_ShowChinese(32,32,12,16);//拿
			OLED_ShowChinese(48,32,13,16);//起
			OLED_ShowChinese(64,32,2,16);//手
			OLED_ShowChinese(80,32,3,16);//指
			OLED_Refresh();
			delay_ms(500);
//			OLED_ShowChinese(32,32,0,16);//请
//			OLED_ShowChinese(48,32,1,16);//按
//			OLED_ShowChinese(64,32,2,16);//手
//			OLED_ShowChinese(80,32,3,16);//指
			OLED_Refresh();
		
			break;
	}
}

//刷指纹
void press_FR(void)
{
	SearchResult seach;
	u8 ensure;
	ensure=PS_GetImage();
	if(ensure==0x00)//获取图像成功 
	{	

		ensure=PS_GenChar(CharBuffer1);
		if(ensure==0x00) //生成特征成功
		{		
			ensure=PS_HighSpeedSearch(CharBuffer1,0,AS608Para.PS_max,&seach);
			if(ensure==0x00)//搜索成功
			{				
				printf("刷指纹成功\r\n");
				Shua_ZW_OK = 1;
				printf("确有此人,ID:%d  匹配得分:%d",seach.pageID,seach.mathscore);
				//OLED_ShowString(32,32,"OK",12);
				//OLED_Refresh();
			}
			else 
				ShowErrMessage(ensure);	//显示错误信息				
	  }
		else
			ShowErrMessage(ensure);

	}
		
}

//录指纹
void Add_FR(u16 FR_ID)
{
	u8 i,ensure ,processnum=0;
	u16 ID;
	while(1)
	{
		switch (processnum)
		{
			case 0:
				i++;
				printf("请按指纹\r\n");
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					ensure=PS_GenChar(CharBuffer1);//生成特征
					if(ensure==0x00)
					{
						printf("指纹正常\r\n");
						i=0;
						processnum=1;//跳到第二步						
					}else ShowErrMessage(ensure);				
				}else ShowErrMessage(ensure);						
				break;
			
			case 1:
				i++;
				printf("请按再按一次指纹\r\n");
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					ensure=PS_GenChar(CharBuffer2);//生成特征
					if(ensure==0x00)
					{
						printf("指纹正常\r\n");
						i=0;
						processnum=2;//跳到第三步
					}else ShowErrMessage(ensure);	
				}else ShowErrMessage(ensure);		
				break;

			case 2:
				printf("对比两次指纹\r\n");
				ensure=PS_Match();
				if(ensure==0x00) 
				{
					printf("对比成功,两次指纹一样\r\n");
					processnum=3;//跳到第四步
				}
				else 
				{
					printf("对比失败，请重新录入指纹\r\n");
					ShowErrMessage(ensure);
					i=0;
					processnum=0;//跳回第一步		
				}
				delay_ms(1200);
				break;

			case 3:
				printf("生成指纹模板\r\n");
				ensure=PS_RegModel();
				if(ensure==0x00) 
				{
					printf("生成指纹模板成功\r\n");
					processnum=4;//跳到第五步
				}else {processnum=0;ShowErrMessage(ensure);}
				delay_ms(1200);
				break;
				
			case 4:	
				printf("储存指纹ID\r\n");
				printf("0=< ID <=299\r\n");
				do
					ID=FR_ID;
				while(!(ID<AS608Para.PS_max));//输入ID必须小于指纹容量的最大值
				ensure=PS_StoreChar(CharBuffer2,ID);//储存模板
				if(ensure==0x00) 
				{					
					printf("录入指纹成功\r\n");
					PS_ValidTempleteNum(&ValidN);//读库指纹个数
					return ;
				}else {processnum=0;ShowErrMessage(ensure);}					
				break;				
		}
		delay_ms(1000);
		if(i==5)//超过5次没有按手指则退出
		{
			printf("超过5次没有按手指则退出\r\n");
			break;	
		}				
	}
}

//删除指纹
void Del_FR(u16 FR_ID)	/*输入删除指纹ID*/
{
	u8  ensure;
	printf("删除指纹\r\n");
	ensure=PS_DeletChar(FR_ID,1);//删除单个指纹
	if(ensure==0)
	{
		printf("删除指纹成功\r\n");		
	}
  else
		ShowErrMessage(ensure);	
	delay_ms(1200);
	PS_ValidTempleteNum(&ValidN);//读库指纹个数

}

