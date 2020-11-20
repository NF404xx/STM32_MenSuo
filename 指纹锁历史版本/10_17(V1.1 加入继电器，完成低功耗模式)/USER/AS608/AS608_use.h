#ifndef _AS608_use_h_
#define _AS608_use_h_
#include "stm32f10x.h"   //stm32头文件
#include "as608.h"						/*指纹模块初始化*/
#include "DELAY.h"						/*延时函数*/

void Add_FR(u16 FR_ID);						/*录哪个ID的指纹*/
void Del_FR(u16 FR_ID);						/*删除哪个ID的指纹*/
void press_FR(void);							/*刷指纹*/
void ShowErrMessage(u8 ensure);		/*显示确认码错误信息*/

#endif
