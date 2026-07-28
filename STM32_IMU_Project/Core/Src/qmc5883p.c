#include "qmc5883p.h"


#define QMC5883P_ADDR (0x2C<<1)



uint8_t QMC5883P_Init(I2C_HandleTypeDef *hi2c)
{

uint8_t data;


if(HAL_I2C_IsDeviceReady(
hi2c,
QMC5883P_ADDR,
3,
100)==HAL_OK)
{

data=0xCF;

HAL_I2C_Mem_Write(
hi2c,
QMC5883P_ADDR,
0x0A,
I2C_MEMADD_SIZE_8BIT,
&data,
1,
1000);


data=0x08;


HAL_I2C_Mem_Write(
hi2c,
QMC5883P_ADDR,
0x0B,
I2C_MEMADD_SIZE_8BIT,
&data,
1,
1000);


return 1;

}

return 0;

}




void QMC5883P_Read(
I2C_HandleTypeDef *hi2c,
int16_t *x,
int16_t *y,
int16_t *z
)
{

uint8_t data[6];


HAL_I2C_Mem_Read(
hi2c,
QMC5883P_ADDR,
0x01,
I2C_MEMADD_SIZE_8BIT,
data,
6,
1000);



*x=(int16_t)(data[0]|data[1]<<8);

*y=(int16_t)(data[2]|data[3]<<8);

*z=(int16_t)(data[4]|data[5]<<8);


}
