#ifndef BMP388_H
#define BMP388_H

#include "main.h"


uint8_t BMP388_Init(I2C_HandleTypeDef *hi2c);


void BMP388_Read(
I2C_HandleTypeDef *hi2c,
uint32_t *pressure,
uint32_t *temperature
);


#endif
