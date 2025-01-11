#include "MPU6050.h"
#include <Wire.h>

MPU6050::MPU6050() : gyroAngleX(0), gyroAngleY(0), gyroAngleZ(0), angleStartX(0), angleStartY(0), angleStartZ(0)
{
    // Constructor
}

void MPU6050::begin()
{
    Wire.begin();
    Wire.beginTransmission(0x68); // MPU6050 I2C address
    Wire.write(0x6B);             // PWR_MGMT_1 register
    Wire.write(0);                // Set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);

    // Initialize offsets (optional, can be tuned)
    accOffsetX = accOffsetY = accOffsetZ = 0;
    gyroOffsetX = gyroOffsetY = gyroOffsetZ = 0;
}

void MPU6050::update()
{
    Wire.beginTransmission(0x68);
    Wire.write(0x3B); // Starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 14, true); // Request a total of 14 registers

    accX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    accY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    accZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    temp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    gyroX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    gyroY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    gyroZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    // Apply offsets
    gyroX -= gyroOffsetX;
    gyroY -= gyroOffsetY;
    gyroZ -= gyroOffsetZ;

    // Calculate angles
    const float dt = 0.01;           // Assuming update() is called every 10ms
    const float sensitivity = 131.0; // MPU6050 gyro sensitivity for full scale ±250 degrees/s

    gyroAngleX += (gyroX / sensitivity) * dt + 0.05;
    gyroAngleY += (gyroY / sensitivity) * dt + 0.05;
    if (abs((gyroZ / sensitivity) * dt + 0.05) >= 0.25)
        gyroAngleZ += (gyroZ / sensitivity) * dt + 0.05;
}

int16_t MPU6050::getAccX()
{
    return accX;
}

int16_t MPU6050::getAccY()
{
    return accY;
}

int16_t MPU6050::getAccZ()
{
    return accZ;
}

int16_t MPU6050::getGyroX()
{
    return gyroX;
}

int16_t MPU6050::getGyroY()
{
    return gyroY;
}

int16_t MPU6050::getGyroZ()
{
    return gyroZ;
}

int16_t MPU6050::getTemp()
{
    return temp;
}

void MPU6050::setAccOffset(int16_t x, int16_t y, int16_t z)
{
    accOffsetX = x;
    accOffsetY = y;
    accOffsetZ = z;
}

void MPU6050::setGyroOffset(int16_t x, int16_t y, int16_t z)
{
    gyroOffsetX = x;
    gyroOffsetY = y;
    gyroOffsetZ = z;
}

void MPU6050::getAngleStart()
{
    angleStartX = gyroAngleX;
    angleStartY = gyroAngleY;
    angleStartZ = gyroAngleZ;
}

void MPU6050::getAngle(float &x, float &y, float &z)
{
    x = gyroAngleX - angleStartX;
    y = gyroAngleY - angleStartY;
    z = gyroAngleZ - angleStartZ;
}
