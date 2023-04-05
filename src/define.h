/**
 * @file define.h
 * @author stop_pattern
 * @brief 各種定数などの定義
 */
#pragma once

/**
 * @brief 使用するピン番号
 */
enum pins {
    PWM_A = 19,
    PWM_B = 18,
    REG_SER = 12,
    REG_SCK = 33,
    REG_SCL = 32,
    REG_RCK = 27,
    REG_OE = 14,
};

/**
 * @brief 各種設定
 */
enum configs {
    pwm_f = 1220,
    pwm_bits = 16,
    meter_max = 120,
};