/**
 * @file meter.h
 * @author stop_pattern
 * @brief 速度計の針を制御する
 */

#pragma once
#include "define.h"

/**
 * @brief 指針の制御をするクラス
 * @note 単一のオブジェクトで使用
 */
class meter {
  private:
    /**
     * @brief 黒針のpwmチャンネル
     */
    const int needleB_ch = 0;
    /**
     * @brief 黒針のpwmピン
     */
    const int needleB_pin = pins::PWM_A;

    /**
     * @brief 赤針のpwmチャンネル
     */
    const int needleR_ch = 1;
    /**
     * @brief 赤針のpwmピン
     */
    const int needleR_pin = pins::PWM_B;

  public:
    /**
     * @brief Construct a new meter object
     *
     */
    meter();

    /**
     * @brief Destroy the meter object
     *
     */
    ~meter();

    /**
     * @brief 入出力設定
     */
    void setup();

    /**
     * @brief 黒針の指示速度を書き込む
     *
     * @param[in] speed 書き込む速度
     * @return int 書き込んだ速度（正常に処理した場合）
     */
    int writeB(double speed);

    /**
     * @brief 赤針の指示速度を書き込む
     *
     * @param[in] speed 書き込む速度
     * @return int 書き込んだ速度（正常に処理した場合）
     */
    int writeR(double speed);
};

/**
 * @brief 指針
 */
extern meter meters;
