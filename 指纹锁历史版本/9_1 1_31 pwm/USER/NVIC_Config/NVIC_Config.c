#include"NVIC_Config.h"
void NVIC_Config(void)
{
	
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	  //先占优先级 1 位,从优先级 3 位
	  NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;;   //使能或者失能指定的 IRQ 通道与库标记不一样  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //响应优先级为0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //使能
		NVIC_Init(&NVIC_InitStructure); 
	
}		






