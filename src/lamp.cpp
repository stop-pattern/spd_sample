/**
 * @file lamp.cpp
 * @author stop_pattern
 * @brief 速度計の灯火を制御する
 */

#include <Arduino.h>
#include "define.h"
#include "lamp.h"

lamp::lamp() {}

lamp::~lamp() {}

void lamp::setup() {
    pinMode(ser_pin, OUTPUT);
    pinMode(clk_pin, OUTPUT);
    pinMode(scl_pin, OUTPUT);
    pinMode(rck_pin, OUTPUT);
    pinMode(oen_pin, OUTPUT);

    digitalWrite(ser_pin, LOW);
    digitalWrite(clk_pin, LOW);
    digitalWrite(scl_pin, HIGH);
    digitalWrite(rck_pin, LOW);

    clear();
    setOutputStatus(true);
}

void lamp::clear() {
    digitalWrite(scl_pin, HIGH);
    digitalWrite(scl_pin, LOW);
    digitalWrite(scl_pin, HIGH);
    data = 0;
}

void lamp::setOutputStatus(bool status) {
    // digitalWrite(oen_pin, status ? LOW : HIGH);
    digitalWrite(oen_pin, LOW);
}

void lamp::setLamps(uint64_t index) {
    if (data != index) {
        data = index;
        write(data);
    }
}

void lamp::setLampOn(lampIndex index) {
    if (data | index != data) {
        data |= index;
        write(data);
    }
}

void lamp::setLampOff(lampIndex index) {
    if (!(data & ~index)) {
        data &= ~index;
        write(data);
    }
}

void lamp::setLampStatus(uint64_t index, bool status) {
    auto temp = data;
    if (status)
        temp |= index;
    else
        temp &= ~index;
    if (temp != data){
        data = temp;
        write(data);
    }
}

void lamp::write(uint64_t val) {
    for (size_t i = 0; i < 6; i++) {
        uint8_t out = val >> (i * 8) & 0xFF;
        shiftOut(pins::REG_SER, pins::REG_SCK, MSBFIRST, out);
    }
    digitalWrite(pins::REG_RCK, LOW);
    digitalWrite(pins::REG_RCK, HIGH);
}

lamp lamps;
