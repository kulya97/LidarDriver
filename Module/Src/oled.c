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

#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
#include "spi.h"
//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   

/*
 * 硬件spi发送8位数据
 */
void OLED_send_true(uint8_t data) {
	HAL_SPI_Transmit(&OLED_SPI, &data, 1, 100);
}

/*
 * 发送8位数据
 */
void OLED_WriteData(uint8_t data) {
	HAL_GPIO_WritePin(LED_CTRL, LED_DC, GPIO_PIN_SET);
	OLED_send_true(data);
}

/*
 *发送8位命令
 */
void OLED_WriteIndex(uint8_t data) {
	HAL_GPIO_WritePin(LED_CTRL, LED_DC, GPIO_PIN_RESET);
	OLED_send_true(data);
}

void OLED_Set_Pos(unsigned char x, unsigned char y) {
	OLED_WriteIndex(0xb0 + y);
	OLED_WriteIndex(((x & 0xf0) >> 4) | 0x10);
	OLED_WriteIndex((x & 0x0f) );

}

/*
 * 开启OLED显示
 */
void OLED_Display_On(void) {
	OLED_WriteIndex(0X8D); //SET DCDC命令
	OLED_WriteIndex(0X14); //DCDC ON
	OLED_WriteIndex(0XAF); //DISPLAY ON
}

/*
 * 关闭OLED显示
 */
void OLED_Display_Off(void) {
	OLED_WriteIndex(0X8D); //SET DCDC命令
	OLED_WriteIndex(0X10); //DCDC OFF
	OLED_WriteIndex(0XAE); //DISPLAY OFF
}

/*
 * 清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
 */
void OLED_Clear(void) {
	uint8_t i, n;
	for (i = 0; i < 8; i++) {
		OLED_WriteIndex(0xb0 + i);    //设置页地址（0~7）
		OLED_WriteIndex(0x00);    //设置显示位置—列低地址
		OLED_WriteIndex(0x10);    //设置显示位置—列高地址

		for (n = 0; n < 128; n++)
			OLED_WriteData(0);
	} //更新显示
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr) {
	unsigned char c = 0, i = 0;
	c = chr - ' '; //得到偏移后的值
	if (x > Max_Column - 1) {
		x = 0;
		y = y + 2;
	}

	OLED_Set_Pos(x, y);
	for (i = 0; i < 6; i++)
		OLED_WriteData(F6x8[c][i]);

}

//m^n函数
uint32_t oled_pow(uint8_t m, uint8_t n) {
	uint32_t result = 1;
	while (n--)
		result *= m;
	return result;
}

OLED_DrawPoint() {

}

//x,y :起点坐标
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num) {
	uint32_t res = num, x2;
	uint8_t t = 0;
	if (num == 0) {
		OLED_ShowChar(x, y, '0');
		return;
	}
	while (res) /*得到数字长度t*/
	{
		res /= 10;
		t++;
	}

	while (t-- != 0) {
		x2 = x + ((8)) * t;
		OLED_ShowChar(x2, y, num % 10 + '0');
		num /= 10;
	}

}

//显示一个字符号串
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr) {
	unsigned char j = 0;
	while (chr[j] != '\0') {
		OLED_ShowChar(x, y, chr[j]);
		x += 8;
		if (x > 120) {
			x = 0;
			y += 2;
		}
		j++;
	}
}

//显示汉字
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no) {
	uint8_t t, adder = 0;
	OLED_Set_Pos(x, y);
	for (t = 0; t < 16; t++) {
		OLED_WriteData(Hzk[2 * no][t]);
		adder += 1;
	}
	OLED_Set_Pos(x, y + 1);
	for (t = 0; t < 16; t++) {
		OLED_WriteData(Hzk[2 * no + 1][t]);
		adder += 1;
	}
}

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1,
		unsigned char y1, unsigned char BMP[]) {
	unsigned int j = 0;
	unsigned char x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y < y1; y++) {
		OLED_Set_Pos(x0, y);
		for (x = x0; x < x1; x++) {
			OLED_WriteData(BMP[j++]);
		}
	}
}

//初始化SSD1306
void OLED_Init(void) {

	HAL_GPIO_WritePin(LED_CTRL, LED_RES, GPIO_PIN_SET);
	delay_ms(100);
	HAL_GPIO_WritePin(LED_CTRL, LED_RES, GPIO_PIN_RESET);
	delay_ms(200);
	HAL_GPIO_WritePin(LED_CTRL, LED_RES, GPIO_PIN_SET);

	OLED_WriteIndex(0X8D);
	OLED_WriteIndex(0xAE);
	OLED_WriteIndex(0x00);
	OLED_WriteIndex(0x10);
	OLED_WriteIndex(0x40);
	OLED_WriteIndex(0x81);
	OLED_WriteIndex(0xCF);
	OLED_WriteIndex(0xA1);
	OLED_WriteIndex(0xC8);
	OLED_WriteIndex(0xA6);
	OLED_WriteIndex(0xA8);
	OLED_WriteIndex(0x3f);
	OLED_WriteIndex(0xD3);
	OLED_WriteIndex(0x00);
	OLED_WriteIndex(0xd5);
	OLED_WriteIndex(0x80);
	OLED_WriteIndex(0xD9);
	OLED_WriteIndex(0xF1);
	OLED_WriteIndex(0xDA);
	OLED_WriteIndex(0x12);
	OLED_WriteIndex(0xDB);
	OLED_WriteIndex(0x40);
	OLED_WriteIndex(0x20);
	OLED_WriteIndex(0x02);
	OLED_WriteIndex(0x8D);
	OLED_WriteIndex(0x14);
	OLED_WriteIndex(0xA4);
	OLED_WriteIndex(0xA6);
	OLED_WriteIndex(0xAF);
	OLED_WriteIndex(0xAF);
	OLED_Clear();
	OLED_Set_Pos(0, 0);
}

