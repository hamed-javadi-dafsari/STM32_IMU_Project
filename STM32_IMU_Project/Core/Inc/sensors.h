#ifndef SENSORS_H
#define SENSORS_H

#include "main.h"


void Sensors_Init(I2C_HandleTypeDef *hi2c);


void Sensors_Read(
I2C_HandleTypeDef *hi2c
);


#endif
