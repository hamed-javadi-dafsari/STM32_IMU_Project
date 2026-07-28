#ifndef ICM42688_H
#define ICM42688_H

#include "main.h"

uint8_t ICM42688_Init(I2C_HandleTypeDef *hi2c);

void ICM42688_Read(
I2C_HandleTypeDef *hi2c,
int16_t *ax,
int16_t *ay,
int16_t *az,
int16_t *gx,
int16_t *gy,
int16_t *gz
);

#endif
