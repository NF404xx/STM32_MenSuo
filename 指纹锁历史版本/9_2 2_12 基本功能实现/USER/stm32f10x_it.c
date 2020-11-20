#include "stm32f10x_it.h"
#include"public.h"

/****************串口中断*******************************/
//void USART1_IRQHandler()
//{
//	static u8 k;
//  USART_ClearFlag(USART1,USART_FLAG_TC);
//	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=Bit_RESET)//检查指定的USART中断发生与否
//	{
//		k=USART_ReceiveData(USART1);
//		k++;	
//		USART_SendData(USART1,k);//通过外设USARTx发送单个数据
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
//	}
//}  
/****************串口中断*******************************/

/****************按键中断*******************************/
/*void EXTI0_IRQHandler()  //中断线路0
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET) //如果检测到中断
	{
  EXTI_ClearITPendingBit(EXTI_Line0);   //清除中断
	delay_ms(10);   //超级重要
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1) //读取A0口如果为1，按键按下就执行下面的
	{
    delay_ms(10);     
			if(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_1)==0)   //灯的转换
			{
			   GPIO_SetBits(GPIOC,GPIO_Pin_1);	
			}
			else
			{
				GPIO_ResetBits(GPIOC,GPIO_Pin_1);
			}		 
	}
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1);   //等待按键离开
 }
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
}*/
/****************按键中断*******************************/



