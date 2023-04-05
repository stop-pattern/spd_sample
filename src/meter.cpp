/**
 * @file meter.cpp
 * @author stop_pattern
 * @brief 速度計の針を制御する
 */

#include <Arduino.h>
#include "define.h"
#include "meter.h"

meter::meter() {}

meter::~meter() {}

void meter::setup() {
    // 黒針
    pinMode(needleB_pin, OUTPUT);
    ledcSetup(needleB_ch, configs::pwm_f, configs::pwm_bits);
    ledcAttachPin(needleB_pin, needleB_ch);

    // 赤針
    pinMode(needleR_pin, OUTPUT);
    ledcSetup(needleR_ch, configs::pwm_f, configs::pwm_bits);
    ledcAttachPin(needleR_pin, needleR_ch);
}

int meter::writeB(double speed) {
    if (abs(speed) > configs::meter_max)
        return false;

    int ret = pow(2, static_cast<int>(configs::pwm_bits)) / configs::meter_max * abs(speed);
    ledcWrite(needleB_ch, ret);
    return ret;
}

int meter::writeR(double speed) {
    if (abs(speed) > configs::meter_max)
        return false;

    int ret = pow(2, static_cast<int>(configs::pwm_bits)) / configs::meter_max * abs(speed);
    ledcWrite(needleR_ch, ret);
    return ret;
}

meter meters;
