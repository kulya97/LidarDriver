#include "delay.h"
#include "tim.h"
void delay_us(uint32_t us) {
	uint16_t counter = us & 0xffff;

	HAL_TIM_Base_Start(&htim3);
	__HAL_TIM_SetCounter(&htim3,counter);

	while (counter > 1) {
		counter = __HAL_TIM_GetCounter(&htim3);
	}

	HAL_TIM_Base_Stop(&htim3);
}
void delay_ms(uint32_t us) {
	for (int i = 0; i < 1000; i++) {
		delay_us(us);
	}
}
