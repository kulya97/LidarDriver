#include "readFlash.h"
#include "spi.h"
#include "gpio.h"

uint8_t sendByte(uint8_t data) {
	while (HAL_SPI_GetState(&SPI_FLASH) == HAL_SPI_STATE_BUSY_TX_RX)
		;
	HAL_SPI_Transmit(&SPI_FLASH, &data, 1, 100);
	while (HAL_SPI_GetState(&SPI_FLASH) == HAL_SPI_STATE_BUSY_TX_RX)
		;
	HAL_SPI_Receive(&SPI_FLASH, &data, 1, 100);
	return data;
}
uint8_t readID() {
	uint8_t TxData[4] = { GET_ID, USELESS, USELESS, USELESS };
	uint8_t RxData[4];
	SPI_CS_CRL();
	HAL_SPI_TransmitReceive(&SPI_FLASH, TxData, RxData, 4, 500);
	SPI_CS_SET();
	return RxData[1];
}
void eraseData(uint32_t addr) {
	uint8_t TxData[4] = { ERASE_DATA, USELESS, USELESS, USELESS };
	uint8_t RxData[4];
	writeEnabled();
	SPI_CS_CRL();
	HAL_SPI_TransmitReceive(&SPI_FLASH, TxData, RxData, 4, 500);
	SPI_CS_SET();
	waitWrite();
}
void readData(uint32_t addr, uint8_t *RxData, uint32_t size) {
	uint8_t TxData[4] = { READ_DATA, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr
			& 0xff };
	SPI_CS_CRL();
	HAL_SPI_TransmitReceive(&SPI_FLASH, TxData, RxData, 4, 500);
	HAL_SPI_TransmitReceive(&SPI_FLASH, TxData, RxData, size, 500);
	SPI_CS_SET();
}
void writeEnabled() {
	uint8_t TxData = WRITE_ENABLED;
	SPI_CS_CRL();
	HAL_SPI_TransmitReceive(&SPI_FLASH, &TxData,0,1, 100);
	SPI_CS_SET();
}
void waitWrite() {
	uint8_t TxData = WAIT_WRITE;
	uint8_t TxData2 = USELESS;
	uint8_t RxData[1];
	SPI_CS_CRL();
	HAL_SPI_TransmitReceive(&SPI_FLASH, &TxData, 0, 2, 500);
	do {
		HAL_SPI_TransmitReceive(&SPI_FLASH, &TxData2, RxData, 1, 500);
	} while ((RxData[1] & 0x01) == 1);
	SPI_CS_SET();
}
void writeData(uint32_t addr, uint8_t *TxData, uint32_t size) {
	uint8_t Txindex[4] = { WRITE_DATA, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr
			& 0xff };
	writeEnabled();
	SPI_CS_CRL();
	HAL_SPI_TransmitReceive(&SPI_FLASH, Txindex, 0, 4, 100);
	HAL_SPI_TransmitReceive(&SPI_FLASH, TxData, 0, size, 100);
	SPI_CS_SET();
	waitWrite();
}
