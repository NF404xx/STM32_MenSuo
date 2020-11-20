#include"EXTI_Config.h"
void EXTI_Config(void)
{
  	EXTI_InitTypeDef EXTI_InitStructure; 
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); //中断输入线0
	
	 /**************EXTI设置*********************/ 
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;    //PA0，，，，PE0  
	  EXTI_InitStructure.EXTI_LineCmd=ENABLE;      //设置使能
	
	 /**************中断模式*********************/ 
	  EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;  //设置 EXTI 线路为中断请求
//	  EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Event;  //  设置 EXTI 线路为事件请求
	/**************中断模式*********************/ 
	
		/**************触发模式*********************/ 
	  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;//设置输入线路上升沿为中断请求
//	  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling ;//设置输入线路下降沿为中断请求
//	  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling ;//设置输入线路上升沿和下降沿为中断请求
	  /**************触发模式*********************/ 
	
	
	  EXTI_Init(&EXTI_InitStructure);
	/**************EXTI设置*********************/
}
void EXTI_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;   //定义	
  SystemInit();  //系统设置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//功能复用 IO 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //GPIOC 时钟
	
	/************中断输入口设置********************/
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;          //上拉输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;              //GPIO PA0 口    
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/************中断输入口设置********************/
	
		/************灯********************/
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All; //定义所有端口的引脚  
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//输出最高速度50MHZ	
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //推挽输出模式
   GPIO_Init(GPIOC,&GPIO_InitStructure);     //初始化定义的端口
   GPIO_SetBits(GPIOC,GPIO_Pin_All);
}
void EXTI_NVIC_Config(void)
{
  	NVIC_InitTypeDef NVIC_InitStructure;
	  
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	  //先占优先级 1 位,从优先级 3 位
	  NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;   //使能或者失能指定的 IRQ 通道与库标记不一样  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //响应优先级为0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //使能
		NVIC_Init(&NVIC_InitStructure); 
	
}
void EXTI_INIT(void)
{
   EXTI_GPIO_Config();	
   EXTI_Config();
   EXTI_NVIC_Config();
}

