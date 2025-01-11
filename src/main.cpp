#include <Arduino.h>

#include "./DeviceWrapper/AllDeviceWrapper.h"
#include "./ControllerWrapper/AllControllerWrapper.h"

// #define BUZZER_PIN 8

// MotorDriver pointers
Motor *motor1;
Motor *motor2;
Motor *motor3;
Motor *motor4;

Kicker *kicker;

// MPU6050 sensor
MPU6050 mpu;

// PS3 Controller wrapper
PS3Controller ps3Controller;

bool isSetup = false;

// Dead zone threshold
const int DEADZONE = 20;

void setup()
{
  Serial.begin(115200);

  // Initialize buzzer
  // pinMode(BUZZER_PIN, OUTPUT);

  // Initialize motors
  motor1 = new Motor(12, 14, 0, 1);
  motor2 = new Motor(26, 27, 2, 3);
  motor3 = new Motor(33, 25, 4, 5);
  motor4 = new Motor(32, 23, 6, 7);

  kicker = new Kicker();

  mpu.begin();
  delay(1000);         // センサーの安定化待ち
  mpu.getAngleStart(); // 初期角度を設定

  // Initialize PS3 controller
  ps3Controller.begin();
  Serial.println("PS3 Controller Connected");
}

void loop()
{
  if (!ps3Controller.isConnected())
  {
    // Skip the loop if PS3 controller is not connected
    return;
  }
  else if (!isSetup)
  {
    isSetup = true;
    // tone(BUZZER_PIN, 880, 300);
  }

  mpu.update();

  float x, y, z;
  mpu.getAngle(x, y, z);

  if (ps3Controller.L1)
  {
    float angle = z;
    while (true)
    {
      mpu.update();
      mpu.getAngle(x, y, z);
      if (abs(z - angle) >= 140)
      {
        break;
      }

      if(ps3Controller.down) {
        return;
      }

      int forward = 110;
      int rotation = -255;

      int motor1Speed = forward  + rotation;
      int motor2Speed = forward  + rotation;
      int motor3Speed = forward  - rotation;
      int motor4Speed = forward  - rotation;

      // Limit speed to valid range (-255 to 255)
      motor1->setSpeed(constrain(motor1Speed, -255, 255));
      motor2->setSpeed(constrain(motor2Speed, -255, 255));
      motor3->setSpeed(constrain(motor3Speed, -255, 255));
      motor4->setSpeed(constrain(motor4Speed, -255, 255));
      delay(10);
    }
    motor1->setSpeed(0);
    motor2->setSpeed(0);
    motor3->setSpeed(0);
    motor4->setSpeed(0);

    delay(500);

    kicker->kick();
    delay(1000);
    kicker->stop();
  }

  if (ps3Controller.R1)
  {
    float angle = z;
    while (true)
    {
      mpu.update();
      mpu.getAngle(x, y, z);
      if (abs(z - angle) >= 140)
      {
        break;
      }

      if(ps3Controller.down) {
        return;
      }
      
      int forward = 110;
      int rotation = 255;

      int motor1Speed = forward  + rotation;
      int motor2Speed = forward  + rotation;
      int motor3Speed = forward  - rotation;
      int motor4Speed = forward  - rotation;

      // Limit speed to valid range (-255 to 255)
      motor1->setSpeed(constrain(motor1Speed, -255, 255));
      motor2->setSpeed(constrain(motor2Speed, -255, 255));
      motor3->setSpeed(constrain(motor3Speed, -255, 255));
      motor4->setSpeed(constrain(motor4Speed, -255, 255));
      delay(10);
    }
    motor1->setSpeed(0);
    motor2->setSpeed(0);
    motor3->setSpeed(0);
    motor4->setSpeed(0);

    delay(500);

    kicker->kick();
    delay(1000);
    kicker->stop();
  }

  if (ps3Controller.circle)
  {
    kicker->kick();
  }
  else if (ps3Controller.square)
  {
    kicker->hold();
  }
  else if (ps3Controller.triangle)
  {
    kicker->stop();
  }

  if (ps3Controller.cross)
  {
    motor1->brake();
    motor2->brake();
    motor3->brake();
    motor4->brake();
    delay(300);
    motor1->setSpeed(0);
    motor2->setSpeed(0);
    motor3->setSpeed(0);
    motor4->setSpeed(0);
  }
  else
  {
    int16_t leftX = ps3Controller.getLeftStickX();   // -128 ~ 127
    int16_t leftY = ps3Controller.getLeftStickY();   // -128 ~ 127
    int16_t rightX = ps3Controller.getRightStickX(); // -128 ~ 127

    // Normalize values to -255 ~ 255
    int forward = map(leftY, -128, 127, 255, -255); // 前後の制御を反転
    int strafe = map(leftX, -128, 127, -255, 255);
    int rotation = map(rightX, -128, 127, -255, 255);

    // Apply dead zone
    if (abs(forward) < DEADZONE)
      forward = 0;
    if (abs(strafe) < DEADZONE)
      strafe = 0;
    if (abs(rotation) < DEADZONE)
      rotation = 0;

    // Debug output
    Serial.print("Angle: ");
    Serial.print(z);
    Serial.print(" Forward: ");
    Serial.print(forward);
    Serial.print(" Strafe: ");
    Serial.print(strafe);
    Serial.print(" Rotation: ");
    Serial.println(rotation);

    // Omni wheel control logic
    int motor1Speed = forward + strafe + rotation;
    int motor2Speed = forward - strafe + rotation;
    int motor3Speed = forward - strafe - rotation;
    int motor4Speed = forward + strafe - rotation;

    // Limit speed to valid range (-255 to 255)
    motor1->setSpeed(constrain(motor1Speed, -255, 255));
    motor2->setSpeed(constrain(motor2Speed, -255, 255));
    motor3->setSpeed(constrain(motor3Speed, -255, 255));
    motor4->setSpeed(constrain(motor4Speed, -255, 255));
  }

  delay(10); // Small delay for smooth control
}
