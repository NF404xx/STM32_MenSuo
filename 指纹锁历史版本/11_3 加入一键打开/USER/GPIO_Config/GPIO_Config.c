#include"GPIO_Config.h"
void GPIO_Config(void)
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
	
	//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;  //选择你要设置的IO口
		/*****************APB1时钟设置************************/	
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);	//TIM2 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM3 ,ENABLE); //TIM3 时钟
//  RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM4 ,ENABLE); //TIM4 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_WWDG ,ENABLE);  //WWDG 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_SPI2 ,ENABLE);  //SPI2 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2 ,ENABLE);   //USART2 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3  ,ENABLE);  //USART3 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_I2C1  ,ENABLE);   //I2C1 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_I2C2  ,ENABLE);   //I2C2 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USB ,ENABLE);   //USB 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_CAN  ,ENABLE);  //CAN 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_BKP  ,ENABLE);  //BKP 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_PWR   ,ENABLE);  //PWR 时钟
	/*****************APB1时钟设置************************/
	
	/*****************APB2时钟设置************************/	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//功能复用 IO 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA 时钟
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //GPIOB 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //GPIOC 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);  //GPIOD 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);   //GPIOE 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 ,ENABLE);  //ADC1 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 ,ENABLE);   //ADC2 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 ,ENABLE);   //TIM1 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 ,ENABLE);   //SPI1 时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 ,ENABLE);  //USART1 时钟
	/*****************APB2时钟设置*************************/
	
	
	/*****************GPIO设置*************************/
	
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;  //选择你要设置的IO口

		/*****************输入模式*************************/
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;	           //模拟输入   I2c,USART接收端
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING ;	 //浮空输入  ADC模块采集
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	           //下拉输入  无输入时默认低电平
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU ;	         //上拉输入 无输入时默认高电平
	 /*****************输入模式*************************/
	 
	 /*****************输出模式*************************/
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;	 //开漏输出    0控制低电平，输出1既不高也不低，高阻太，需上啦电阻
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //推挽输出    高电平3.3  低电平0
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_OD ;	 //复用开漏输出 IC，SMBUS
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;	 //复用推挽输出  串口
//	  /*****************输出模式*************************/
	
		  /*****************输出速度*************************/
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;	  //最高输出速率 2MHz
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	  //最高输出速率 10MHz
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //最高输出速率 50MHz
		  /*****************输出速度*************************/
	
//	GPIO_Init(GPIOC,&GPIO_InitStructure); 

  /*****************GPIO设置*************************/
}
	

