#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>

class MPU6050
{
public:
    MPU6050();
    void begin();
    void update();

    int16_t getAccX();
    int16_t getAccY();
    int16_t getAccZ();
    int16_t getGyroX();
    int16_t getGyroY();
    int16_t getGyroZ();
    int16_t getTemp();

    void setAccOffset(int16_t x, int16_t y, int16_t z);
    void setGyroOffset(int16_t x, int16_t y, int16_t z);

    void getAngleStart();                        // 初期角度を記録
    void getAngle(float &x, float &y, float &z); // 初期角度からの回転角度を取得

private:
    // 加速度とジャイロデータ
    int16_t accX, accY, accZ;
    int16_t gyroX, gyroY, gyroZ;
    int16_t temp;

    // オフセット値
    int16_t accOffsetX, accOffsetY, accOffsetZ;
    int16_t gyroOffsetX, gyroOffsetY, gyroOffsetZ;

    // 角度の積分値
    float gyroAngleX, gyroAngleY, gyroAngleZ;

    // 初期角度
    float angleStartX, angleStartY, angleStartZ;
};

#endif
