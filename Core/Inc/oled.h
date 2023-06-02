/*
 * oled.h
 *
 *  Created on: May 29, 2023
 *      Author: tzh15
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_
#include "stm32f1xx_hal.h"

void OLED_WriteCmd(uint8_t cmd);
void OLED_WriteData(uint8_t dat);
void OLED_DisON(void);
void OLED_DisOFF(void);
void OLED_Clear(void);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_Init(void);

#endif /* INC_OLED_H_ */
