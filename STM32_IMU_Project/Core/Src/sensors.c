#include "sensors.h"

#include "icm42688.h"
#include "qmc5883p.h"
#include "bmp388.h"

#include <stdio.h>
#include <string.h>


extern UART_HandleTypeDef huart2;


void Sensors_Init(I2C_HandleTypeDef *hi2c)
{

ICM42688_Init(hi2c);

QMC5883P_Init(hi2c);

BMP388_Init(hi2c);

}



void Sensors_Read(
I2C_HandleTypeDef *hi2c
)
{

int16_t ax,ay,az,gx,gy,gz;

int16_t mx,my,mz;

uint32_t p,t;


ICM42688_Read(
hi2c,
&ax,&ay,&az,
&gx,&gy,&gz);



QMC5883P_Read(
hi2c,
&mx,&my,&mz);



BMP388_Read(
hi2c,
&p,&t);



char msg[200];


sprintf(msg,
"ACC %d %d %d | GYRO %d %d %d | MAG %d %d %d | BMP %lu %lu\r\n",
ax,ay,az,
gx,gy,gz,
mx,my,mz,
p,t);



HAL_UART_Transmit(
&huart2,
(uint8_t*)msg,
strlen(msg),
1000);


}
