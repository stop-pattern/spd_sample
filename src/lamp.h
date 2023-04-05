/**
 * @file lamp.h
 * @author stop_pattern
 * @brief 速度計の灯火を制御する
 */

#pragma once
#include "define.h"

enum lampIndex : uint64_t {
    NOT = 0x000000000000,   // 全消灯
    S00 = 0x010000000000,
    S05 = 0x020000000000,   // cannot show
    S10 = 0x040000000000,
    S15 = 0x080000000000,
    S20 = 0x100000000000,
    S25 = 0x200000000000,
    S30 = 0x400000000000,
    S35 = 0x800000000000,
    S40 = 0x000100000000,
    S45 = 0x000200000000,
    S50 = 0x000400000000,
    S55 = 0x000800000000,
    S60 = 0x001000000000,
    S65 = 0x002000000000,
    S70 = 0x004000000000,
    S75 = 0x008000000000,
    S80 = 0x000001000000,
    S85 = 0x000002000000,
    S90 = 0x000004000000,
    S95 = 0x000008000000,
    S100= 0x000010000000,
    S105= 0x000020000000,   // cannot show
    S110= 0x000040000000,
    R   = 0x000000020000,   // ATC信号現示 停止
    G   = 0x000000040000,   // ATC信号現示 進行
    SFN = 0x000000080000,   // 前方予告
    P   = 0x000000100000,   // ORP表示灯
    X   = 0x000000200000,   // ATC信号現示 02
    L15 = 0x000000000001,   // 東武ATS パターン15
    L60 = 0x000000000002,   // 東武ATS パターン60
    ATS = 0x000000000004,   // 東武ATS ATS動作
    BL  = 0x000000000080,   // バックライト
    ALL = 0xffffffffffff,   // 全点灯
};

/**
 * @brief 灯火の制御をするクラス
 * @note 単一のオブジェクトで使用
 */
class lamp {
  private:
    /**
     * @brief データピン
     */
    const int ser_pin = pins::REG_SER;
    /**
     * @brief クロックピン
     */
    const int clk_pin = pins::REG_SCK;
    /**
     * @brief クリアピン
     */
    const int scl_pin = pins::REG_SCL;
    /**
     * @brief ラッチクロックピン
     */
    const int rck_pin = pins::REG_RCK;
    /**
     * @brief イネーブルピン
     */
    const int oen_pin = pins::REG_OE;

    /**
     * @brief 書き込み値
     */
    uint64_t data = 0;

  public:
    /**
     * @brief Construct a new lamp object
     */
    lamp();

    /**
     * @brief Destroy the lamp object
     */
    ~lamp();

    /**
     * @brief 入出力設定
     */
    void setup();

    /**
     * @brief 出力の0初期化
     */
    void clear();

    /**
     * @brief 出力の設定
     * 
     * @param[in] status 出力状態
     */
    void setOutputStatus(bool status);

    /**
     * @brief Set the Lamps
     * 
     * @param[in] index lamps index
     */
    void setLamps(uint64_t index);

    /**
     * @brief Set the Lamp On
     * 
     * @param[in] index On index
     */
    void setLampOn(lampIndex index);

    /**
     * @brief Set the Lamp Off
     * 
     * @param[in] index Off index
     */
    void setLampOff(lampIndex index);

    /**
     * @brief Set the Lamp Output Status
     * 
     * @param index lamps index
     * @param status output status
     */
    void setLampStatus(uint64_t index, bool status);

    /**
     * @brief シフトレジスタに値を書き込む
     * 
     * @param[in] val 
     */
    void write(uint64_t val);
};

/**
 * @brief 灯火
 */
extern lamp lamps;
