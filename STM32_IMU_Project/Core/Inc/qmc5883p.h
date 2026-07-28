#ifndef QMC5883P_H
#define QMC5883P_H

#include "main.h"


uint8_t QMC5883P_Init(I2C_HandleTypeDef *hi2c);


void QMC5883P_Read(
I2C_HandleTypeDef *hi2c,
int16_t *x,
int16_t *y,
int16_t *z
);


#endif
