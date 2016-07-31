#include "mpu6050.h"

msg_t mpu6050_Read(uint8_t addr, uint8_t* out_data)
{
  int ret = 0;
  const i2caddr_t dev_addr = MPU6050_ADDRESS_AD0_LOW;
//  HAL_I2C_Mem_Read(&hi2c1, dev_addr, addr, 1, &data, 1, 0x1000);
  ret = i2cMasterTransmitTimeout(&I2CD1, dev_addr, &addr, sizeof(addr), out_data, 1, TIME_INFINITE);
  if(ret != MSG_OK)
    return ret;

  return 0;
}

msg_t mpu6050_Write(uint8_t addr, uint8_t data)
{
  int ret = 0;
  const i2caddr_t dev_addr = MPU6050_ADDRESS_AD0_LOW;
//  HAL_I2C_Mem_Write(&hi2c1, dev_addr, addr, 1, &data, 1, 0x1000);
  ret = i2cMasterTransmitTimeout(&I2CD1, dev_addr, &addr, 1, NULL, 0, TIME_INFINITE);
  if(ret != MSG_OK) return ret;

  ret = i2cMasterTransmitTimeout(&I2CD1, dev_addr, &data, 1, NULL, 0, TIME_INFINITE);
  if(ret != MSG_OK) return ret;

  return 0;
}

int mpu6050_init(void)
{
  int ret = 0;

  //Sets sample rate to 8000/1+7 = 1000Hz
  ret = mpu6050_Write(MPU6050_RA_SMPLRT_DIV, 0x07);
  if(ret != 0) return ret;

  //Disable FSync, 256Hz DLPF
  ret = mpu6050_Write(MPU6050_RA_CONFIG, 0x00);
  if(ret != 0) return ret;

  //Disable gyro self tests, scale of 500 degrees/s
  ret = mpu6050_Write(MPU6050_RA_GYRO_CONFIG, 0b00001000);
  if(ret != 0) return ret;

  //Disable accel self tests, scale of +-2g, no DHPF
  ret = mpu6050_Write(MPU6050_RA_ACCEL_CONFIG, 0x00);
  if(ret != 0) return ret;

  //Freefall threshold of |0mg|
  ret = mpu6050_Write(MPU6050_RA_FF_THR, 0x00);
  if(ret != 0) return ret;

  //Freefall duration limit of 0
  ret = mpu6050_Write(MPU6050_RA_FF_DUR, 0x00);
  if(ret != 0) return ret;

  //Motion threshold of 0mg
  ret = mpu6050_Write(MPU6050_RA_MOT_THR, 0x00);
  if(ret != 0) return ret;

  //Motion duration of 0s
  ret = mpu6050_Write(MPU6050_RA_MOT_DUR, 0x00);
  if(ret != 0) return ret;

  //Zero motion threshold
  ret = mpu6050_Write(MPU6050_RA_ZRMOT_THR, 0x00);
  if(ret != 0) return ret;

  //Zero motion duration threshold
  ret = mpu6050_Write(MPU6050_RA_ZRMOT_DUR, 0x00);
  if(ret != 0) return ret;

  //Disable sensor output to FIFO buffer
  ret = mpu6050_Write(MPU6050_RA_FIFO_EN, 0x00);
  if(ret != 0) return ret;

  return 0;
}