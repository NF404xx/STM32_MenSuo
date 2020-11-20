#include "pwm.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//PWM  驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM4_PWM_Init(u16 arr,u16 psc)

{ 

      GPIO_InitTypeDef GPIO_InitStructure;
      TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
      TIM_OCInitTypeDef TIM_OCInitStructure;
    
      //使能定时器TIM4
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
      //使能PWM输出GPIO时钟
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); 
                                                                        
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//定时器TIM4的通道1，TIM4_CH1（PB6）
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//定时器TIM4的通道1，TIM4_CH2（PB7）
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//定时器TIM4的通道1，TIM4_CH3（PB8）
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//定时器TIM4的通道1，TIM4_CH4（PB9）
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化

      
      TIM_TimeBaseStructure.TIM_Period = arr;//自动重装载值
      TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟预分频数
      TIM_TimeBaseStructure.TIM_ClockDivision = 0;
      TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
      TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //初始化TIM4

 
      //初始化TIM_CH1的PWM模式

      TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//设置pwm模式1

      TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能

      TIM_OCInitStructure.TIM_Pulse = 0;

      TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性高

      TIM_OC1Init(TIM4, &TIM_OCInitStructure);//初始化TIM4_CH1

      

      //初始化TIM_CH2的PWM模式

      TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
      TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
      TIM_OCInitStructure.TIM_Pulse = 0;
      TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
      
      TIM_OC2Init(TIM4, &TIM_OCInitStructure);

      
     
			//初始化TIM_CH3的PWM模式
      TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
      TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
      TIM_OCInitStructure.TIM_Pulse = 0;
      TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
      
			TIM_OC3Init(TIM4, &TIM_OCInitStructure);

      
      //初始化TIM_CH3的PWM模式
      TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
      TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
      TIM_OCInitStructure.TIM_Pulse = 0;
      TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

      TIM_OC4Init(TIM4, &TIM_OCInitStructure);

 

      //使能4哥通道的预装载寄存器
      TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//OC1
      TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);//OC2
      TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);//OC3
      TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);//OC4
     
      TIM_ARRPreloadConfig(TIM4, ENABLE); //使能重装载值
      

      TIM_Cmd(TIM4, ENABLE);//使能定时器TIM4，准备工作

}

