#include "usart1_view.h"
#include "USART_Config.h"
extern void Add_FR(u16 FR_ID);						/*录哪个ID的指纹*/
extern void Del_FR(u16 FR_ID);						/*删除哪个ID的指纹*/
void usart1_execute(void)  /*串口一接收到数据后执行子函数*/
{
		extern u8 eu8_Flag;
	  extern u8 eu8_what;
		if(eu8_Flag)
		{
			printf("\r\n接收失败\r\n");
			eu8_Flag=0;
			switch(eu8_what)
			{
				case '1': Add_FR(1);			/*录哪个ID的指纹*/
					break;
				case '2': Del_FR(1);			/*删除哪个ID的指纹*/
					break;			
				default: printf("\r\n接收失败\r\n");
				break;
			}		
		}
}

