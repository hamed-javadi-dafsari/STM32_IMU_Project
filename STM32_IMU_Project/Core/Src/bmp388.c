#include "bmp388.h"


#define BMP388_ADDR (0x77<<1)



uint8_t BMP388_Init(I2C_HandleTypeDef *hi2c)
{

uint8_t id;


HAL_I2C_Mem_Read(
hi2c,
BMP388_ADDR,
0x00,
I2C_MEMADD_SIZE_8BIT,
&id,
1,
1000);


if(id==0x50)
{

uint8_t cfg[2];

cfg[0]=0x1B;
cfg[1]=0x33;


HAL_I2C_Master_Transmit(
hi2c,
BMP388_ADDR,
cfg,
2,
1000);


return 1;

}


return 0;

}




void BMP388_Read(
I2C_HandleTypeDef *hi2c,
uint32_t *pressure,
uint32_t *temperature
)
{


uint8_t data[6];


HAL_I2C_Mem_Read(
hi2c,
BMP388_ADDR,
0x04,
I2C_MEMADD_SIZE_8BIT,
data,
6,
1000);



*pressure=
(data[2]<<16)|
(data[1]<<8)|
data[0];


*temperature=
(data[5]<<16)|
(data[4]<<8)|
data[3];


}
