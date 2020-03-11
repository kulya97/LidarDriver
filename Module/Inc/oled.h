//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   :
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明:
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PA5（SCL）
//              D1   接PA7（SDA）
//              RES  接PB0
//              DC   接PB1
//              CS   接PA4
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   :
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 

#include "main.h"
#define OLED_SPI hspi2
//OLED模式设置
////0:4线串行模式
////1:并行8080模式
//#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

#define LED_CTRL   	  	GPIOB		//定义TFT数据端口
#define LED_D0        	GPIO_PIN_10  //MCU_PB9--->>TFT --BL
#define LED_D1         	GPIO_PIN_15	//PB11--->>TFT --RS/DC
#define LED_RES        	GPIO_PIN_13  //MCU_PB11--->>TFT --CS/CE
#define LED_DC      	GPIO_PIN_14	//PB10--->>TFT --RST
#define LED_CS        	GPIO_PIN_12	//PB13--->>TFT --SCL/SCK

//OLED控制用函数
void OLED_send_true(uint8_t data);
void OLED_WriteData(uint8_t data);
void OLED_WriteIndex(uint8_t data);
void OLED_WR_Byte(uint8_t dat, uint8_t cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void OLED_Fill(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t dot);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1,
		unsigned char y1, unsigned char BMP[]);
#endif  

