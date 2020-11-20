#include "USART_Config.h"
void USART_Config(void)
{
  USART_InitTypeDef  USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate=9600;  //9600波特率
  USART_InitStructure.USART_WordLength=USART_WordLength_8b;//8为数据位	
  USART_InitStructure.USART_StopBits=USART_StopBits_1; //1位停止位		
  USART_InitStructure.USART_Parity=USART_Parity_No;		//无校验位
  USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;     //不采用硬件流
  USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	 //全双工
	USART_Init(USART1,&USART_InitStructure);   
	
	USART_Cmd(USART1, ENABLE);    //使能或者失能 USART 外设
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能或者失能指定的 USART 中断
	USART_ClearFlag(USART1,USART_FLAG_TC);//清除 USARTx 的待处理标志位
	
	
}
void USART_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;   //定义	
  SystemInit();  //系统设置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//功能复用 IO 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //USART1时钟
	
	/************串口输出口设置********************/
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;          //复用推挽输出  串口
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;              //GPIO PA0 口  
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/************串口输出口设置********************/
	
	/************串口输入***********************/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10; //输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOA,&GPIO_InitStructure);   
	/************串口输入***********************/
	
}	
void USART_NVIC_Config(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure;
	  
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	  //先占优先级 1 位,从优先级 3 位
	  NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;;   //使能或者失能指定的 IRQ 通道与库标记不一样  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //响应优先级为0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //使能
		NVIC_Init(&NVIC_InitStructure); 
	
}	

void USART_INIT(void)
{
		USART_GPIO_Config();
		USART_NVIC_Config();
		USART_Config();
}

int fputc(int ch, FILE *f)
{
		USART_SendData(USART1, (unsigned char) ch);
		while (!(USART1->SR & USART_FLAG_TXE));
		return (ch);
}
int GetKey (void) 
{
		while (!(USART1->SR & USART_FLAG_RXNE));
		return ((int)(USART1->DR & 0x1FF));
}
	
void USART1_IRQHandler()
{
	extern u8 eu8_Flag;
	extern u8 eu8_what;
  USART_ClearFlag(USART1,USART_FLAG_TC);
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=Bit_RESET)//检查指定的USART中断发生与否
	{
		eu8_Flag=1;
		eu8_what = USART_ReceiveData(USART1);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
	}
}  

		
