#include "MPU6050.h"

//#include "i2c.h"
//void MPU6050_Init(void) {
//	HAL_I2C_MspInit(&hi2c1);
//	HAL_I2C_Mem_Write(&hi2c1, SlaveAddress, PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT,
//			0x00, 1, 1000);
//	HAL_I2C_Mem_Write(&hi2c1, SlaveAddress, SMPLRT_DIV, I2C_MEMADD_SIZE_8BIT,
//			0x07, 1, 1000);
//	HAL_I2C_Mem_Write(&hi2c1, SlaveAddress, CONFIG, I2C_MEMADD_SIZE_8BIT,
//			0x06,1, 1000);
//	HAL_I2C_Mem_Write(&hi2c1, SlaveAddress, GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT,
//			0x18, 1, 1000);
//	HAL_I2C_Mem_Write(&hi2c1, SlaveAddress, ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT,
//			0x01, 1, 1000);
//
//}
//short getAcc_X(void) {
//	uint8_t buf[6]={0};
//	HAL_I2C_Mem_Read(&hi2c1, SlaveAddress, ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT,
//			buf, 6, 1000);
//	return (buf[0] << 8) | buf[1];
//}
