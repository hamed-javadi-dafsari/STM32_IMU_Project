#include "icm42688.h"


#define ICM42688_ADDR (0x69<<1)


uint8_t ICM42688_Init(I2C_HandleTypeDef *hi2c)
{

uint8_t data[2];

data[0]=0x4E;
data[1]=0x0F;


if(HAL_I2C_Master_Transmit(
hi2c,
ICM42688_ADDR,
data,
2,
1000)==HAL_OK)
{
return 1;
}

return 0;

}



void ICM42688_Read(
I2C_HandleTypeDef *hi2c,
int16_t *ax,
int16_t *ay,
int16_t *az,
int16_t *gx,
int16_t *gy,
int16_t *gz
)
{

uint8_t reg=0x1F;

uint8_t data[12];


HAL_I2C_Master_Transmit(
hi2c,
ICM42688_ADDR,
&reg,
1,
1000);


HAL_I2C_Master_Receive(
hi2c,
ICM42688_ADDR,
data,
12,
1000);



*ax=(data[0]<<8)|data[1];
*ay=(data[2]<<8)|data[3];
*az=(data[4]<<8)|data[5];

*gx=(data[6]<<8)|data[7];
*gy=(data[8]<<8)|data[9];
*gz=(data[10]<<8)|data[11];


}
