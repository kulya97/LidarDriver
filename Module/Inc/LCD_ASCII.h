#ifndef __LCD_ASCII_H
#define __LCD_ASCII_H

#ifdef __cplusplus
extern "C" {
#endif
#include "stdint.h"

#define LCD_EN_W 8
#define LCD_EN_H 16
#define LED_EN_SIZE  ((LCD_EN_W + 7)/8) * LCD_EN_H

extern uint8_t const CHARASII[1536];
#ifdef __cplusplus
}

#endif
#endif
