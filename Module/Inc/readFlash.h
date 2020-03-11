/*
 * readFlash.h
 *
 *  Created on: Jan 8, 2020
 *      Author: hhh
 */

#ifndef INC_READFLASH_H_
#define INC_READFLASH_H_

#include "main.h"

#define SPI_FLASH       hspi1

#define FLASH_CTRL   	  	GPIOA
#define SPI_CS         	GPIO_PIN_4  //片选信号
#define SPI_SCK        	GPIO_PIN_5  //时钟信号
#define SPI_MISO        GPIO_PIN_6	//输出信号
#define SPI_MOSI        GPIO_PIN_7  //输入信号

#define SPI_CS_CRL()        	FLASH_CTRL->BSRR=(uint32_t)SPI_CS << 16U
#define SPI_CS_SET()        	FLASH_CTRL->BSRR=SPI_CS

#define GET_ID                   0x9f
#define USELESS                  0X00
#define ERASE_DATA               0X20
#define READ_DATA                0X03
#define WRITE_ENABLED            0x06
#define WAIT_WRITE               0x05
#define WRITE_DATA               0x02
//PB15连接至TFT - SDI
uint8_t sendByte(uint8_t data);
uint8_t readID();
void eraseData(uint32_t addr);
void readData(uint32_t addr, uint8_t *RxData, uint32_t size);
void writeEnabled();
void writeData(uint32_t addr, uint8_t *TxData, uint32_t size);
void waitWrite();

#endif /* INC_READFLASH_H_ */
