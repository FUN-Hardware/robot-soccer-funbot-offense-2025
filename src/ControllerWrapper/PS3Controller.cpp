#include "PS3Controller.h"

// static メンバー変数の定義
bool PS3Controller::up = false;
bool PS3Controller::down = false;
bool PS3Controller::left = false;
bool PS3Controller::right = false;
bool PS3Controller::triangle = false;
bool PS3Controller::circle = false;
bool PS3Controller::cross = false;
bool PS3Controller::square = false;
bool PS3Controller::L1 = false;
bool PS3Controller::L2 = false;
bool PS3Controller::R1 = false;
bool PS3Controller::R2 = false;
bool PS3Controller::select = false;
bool PS3Controller::start = false;

PS3Controller::PS3Controller() {}

void PS3Controller::begin()
{
    Ps3.begin();

    // 接続待機
    while (!Ps3.isConnected())
    {
        delay(100);
    }

    // コールバック関数の登録
    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.attachOnDisconnect(onDisconnect);
}

void PS3Controller::notify()
{
    // Serial.println("PS3 Controller Event Received!");
    if (Ps3.data.button.up)
    {
        up = true;
    }
    else
    {
        up = false;
    }
    if (Ps3.data.button.down)
    {
        down = true;
    }
    else
    {
        down = false;
    }
    if (Ps3.data.button.left)
    {
        left = true;
    }
    else
    {
        left = false;
    }
    if (Ps3.data.button.right)
    {
        right = true;
    }
    else
    {
        right = false;
    }
    if (Ps3.data.button.cross)
    {
        cross = true;
    }
    else
    {
        cross = false;
    }
    if (Ps3.data.button.square)
    {
        square = true;
    }
    else
    {
        square = false;
    }
    if (Ps3.data.button.triangle)
    {
        triangle = true;
    }
    else
    {
        triangle = false;
    }
    if (Ps3.data.button.circle)
    {
        circle = true;
    }
    else
    {
        circle = false;
    }
    if (Ps3.data.button.l1)
    {
        L1 = true;
    }
    else
    {
        L1 = false;
    }
    if (Ps3.data.button.l2)
    {
        L2 = true;
    }
    else
    {
        L2 = false;
    }
    if (Ps3.data.button.r1)
    {
        R1 = true;
    }
    else
    {
        R1 = false;
    }
    if (Ps3.data.button.r2)
    {
        R2 = true;
    }
    else
    {
        R2 = false;
    }
    if (Ps3.data.button.select)
    {
        select = true;
    }
    else
    {
        select = false;
    }
    if (Ps3.data.button.start)
    {
        start = true;
    }
    else
    {
        start = false;
    }
}

void PS3Controller::onConnect()
{
    Serial.println("PS3 Controller Connected!");
}

void PS3Controller::onDisconnect()
{
    Serial.println("PS3 Controller Disconnected!");
}

bool PS3Controller::isConnected()
{
    return Ps3.isConnected(); // PS3コントローラーが接続されているかどうか
}

int16_t PS3Controller::getLeftStickX()
{
    return Ps3.data.analog.stick.lx;
}

int16_t PS3Controller::getLeftStickY()
{
    return Ps3.data.analog.stick.ly;
}

int16_t PS3Controller::getRightStickX()
{
    return Ps3.data.analog.stick.rx; // -128 ~ 127 に正規化
}
