/**
 * @file main.cpp
 * @author stop_pattern
 * @brief メインの処理
 */
#include <Arduino.h>
#include "meter.h"
#include "lamp.h"
#include "TR.BIDS.libs.h"

BIDS bids = BIDS(&Serial);
bool isNonAS = false;

/**
 * @brief BIDS受信文字列をintに変換
 *
 * @param str BIDS受信文字列
 * @return int BIDS受信値
 */
int str2i(String str) {
    auto index = str.indexOf('X') + 1;
    return str.substring(index).toInt();
}

/**
 * @brief BIDS受信文字列をfloatに変換
 *
 * @param str BIDS受信文字列
 * @return float BIDS受信値
 */
float str2f(String str) {
    auto index = str.indexOf('X') + 1;
    return str.substring(index).toFloat();
}

/**
 * @brief デモンストレーション
 */
void demo() {
    int change = 500;
    int wait = 10;

    // 全点灯
    lamps.setLamps(lampIndex::ALL);

    delay(change);

    // 針0->120
    for (size_t i = 0; i < configs::meter_max; i++) {
        meters.writeB(i);
        meters.writeR(i * 4 / 10);
        delay(wait);
    }

    delay(change);

    // 針120->0
    for (int i = configs::meter_max - 1; i >= 0; i--) {
        meters.writeB(i);
        meters.writeR(i * 4 / 10);
        delay(wait);
    }

    delay(change);

    // 消灯
    lamps.setLamps(lampIndex::NOT);

    delay(change);
}

/**
 * @brief loop ポーリングでの実装
 */
void loop_polling() {
    meters.writeB(bids.CmdSenderF("TRIE1"));
    lamps.setLampStatus(lampIndex::L15, bids.CmdSenderI("TRIP42"));
    lamps.setLampStatus(lampIndex::L60, bids.CmdSenderI("TRIP43"));
    lamps.setLampStatus(lampIndex::ATS, bids.CmdSenderI("TRIP44"));
    lamps.setLampStatus(lampIndex::X, bids.CmdSenderI("TRIP101"));
    lamps.setLampStatus(lampIndex::S00, bids.CmdSenderI("TRIP102"));
    lamps.setLampStatus(lampIndex::S10, bids.CmdSenderI("TRIP104"));
    lamps.setLampStatus(lampIndex::S15, bids.CmdSenderI("TRIP105"));
    lamps.setLampStatus(lampIndex::S20, bids.CmdSenderI("TRIP106"));
    lamps.setLampStatus(lampIndex::S25, bids.CmdSenderI("TRIP107"));
    lamps.setLampStatus(lampIndex::S30, bids.CmdSenderI("TRIP108"));
    lamps.setLampStatus(lampIndex::S35, bids.CmdSenderI("TRIP109"));
    lamps.setLampStatus(lampIndex::S40, bids.CmdSenderI("TRIP110"));
    lamps.setLampStatus(lampIndex::S45, bids.CmdSenderI("TRIP111"));
    lamps.setLampStatus(lampIndex::S50, bids.CmdSenderI("TRIP112"));
    lamps.setLampStatus(lampIndex::S55, bids.CmdSenderI("TRIP113"));
    lamps.setLampStatus(lampIndex::S60, bids.CmdSenderI("TRIP114"));
    lamps.setLampStatus(lampIndex::S65, bids.CmdSenderI("TRIP115"));
    lamps.setLampStatus(lampIndex::S70, bids.CmdSenderI("TRIP116"));
    lamps.setLampStatus(lampIndex::S75, bids.CmdSenderI("TRIP117"));
    lamps.setLampStatus(lampIndex::S80, bids.CmdSenderI("TRIP118"));
    lamps.setLampStatus(lampIndex::S85, bids.CmdSenderI("TRIP119"));
    lamps.setLampStatus(lampIndex::S90, bids.CmdSenderI("TRIP120"));
    lamps.setLampStatus(lampIndex::S95, bids.CmdSenderI("TRIP121"));
    lamps.setLampStatus(lampIndex::S100, bids.CmdSenderI("TRIP122"));
    lamps.setLampStatus(lampIndex::S105, bids.CmdSenderI("TRIP123"));
    lamps.setLampStatus(lampIndex::S110, bids.CmdSenderI("TRIP124"));
    lamps.setLampStatus(lampIndex::R, bids.CmdSenderI("TRIP131"));
    lamps.setLampStatus(lampIndex::G, bids.CmdSenderI("TRIP132"));
    lamps.setLampStatus(lampIndex::SFN, bids.CmdSenderI("TRIP133"));
    lamps.setLampStatus(lampIndex::P, bids.CmdSenderI("TRIP134"));
    meters.writeR(bids.CmdSenderI("TRIP135") / 10);
    lamps.setLampStatus(lampIndex::BL, bids.CmdSenderI("TRIP161"));
}

/**
 * @brief loop AS使用可能時の実装
 */
void loop_AutoSend() {
    if (Serial.available()) {
        auto str = Serial.readStringUntil('\n');
        if (!str.startsWith("TR"))
            return;
        else if (str.startsWith("TRIE1X")) {
            meters.writeB(str2f(str));
        } else if (str.startsWith("TRIP42X")) {
            lamps.setLampStatus(lampIndex::L15, str2i(str));
        } else if (str.startsWith("TRIP43X")) {
            lamps.setLampStatus(lampIndex::L60, str2i(str));
        } else if (str.startsWith("TRIP44X")) {
            lamps.setLampStatus(lampIndex::ATS, str2i(str));
        } else if (str.startsWith("TRIP101X")) {
            lamps.setLampStatus(lampIndex::X, str2i(str));
        } else if (str.startsWith("TRIP102X")) {
            lamps.setLampStatus(lampIndex::S00, str2i(str));
        } else if (str.startsWith("TRIP104X")) {
            lamps.setLampStatus(lampIndex::S10, str2i(str));
        } else if (str.startsWith("TRIP105X")) {
            lamps.setLampStatus(lampIndex::S15, str2i(str));
        } else if (str.startsWith("TRIP106X")) {
            lamps.setLampStatus(lampIndex::S20, str2i(str));
        } else if (str.startsWith("TRIP107X")) {
            lamps.setLampStatus(lampIndex::S25, str2i(str));
        } else if (str.startsWith("TRIP108X")) {
            lamps.setLampStatus(lampIndex::S30, str2i(str));
        } else if (str.startsWith("TRIP109X")) {
            lamps.setLampStatus(lampIndex::S35, str2i(str));
        } else if (str.startsWith("TRIP110X")) {
            lamps.setLampStatus(lampIndex::S40, str2i(str));
        } else if (str.startsWith("TRIP111X")) {
            lamps.setLampStatus(lampIndex::S45, str2i(str));
        } else if (str.startsWith("TRIP112X")) {
            lamps.setLampStatus(lampIndex::S50, str2i(str));
        } else if (str.startsWith("TRIP113X")) {
            lamps.setLampStatus(lampIndex::S55, str2i(str));
        } else if (str.startsWith("TRIP114X")) {
            lamps.setLampStatus(lampIndex::S60, str2i(str));
        } else if (str.startsWith("TRIP115X")) {
            lamps.setLampStatus(lampIndex::S65, str2i(str));
        } else if (str.startsWith("TRIP116X")) {
            lamps.setLampStatus(lampIndex::S70, str2i(str));
        } else if (str.startsWith("TRIP117X")) {
            lamps.setLampStatus(lampIndex::S75, str2i(str));
        } else if (str.startsWith("TRIP118X")) {
            lamps.setLampStatus(lampIndex::S80, str2i(str));
        } else if (str.startsWith("TRIP119X")) {
            lamps.setLampStatus(lampIndex::S85, str2i(str));
        } else if (str.startsWith("TRIP120X")) {
            lamps.setLampStatus(lampIndex::S90, str2i(str));
        } else if (str.startsWith("TRIP121X")) {
            lamps.setLampStatus(lampIndex::S95, str2i(str));
        } else if (str.startsWith("TRIP122X")) {
            lamps.setLampStatus(lampIndex::S100, str2i(str));
        } else if (str.startsWith("TRIP123X")) {
            lamps.setLampStatus(lampIndex::S105, str2i(str));
        } else if (str.startsWith("TRIP124X")) {
            lamps.setLampStatus(lampIndex::S110, str2i(str));
        } else if (str.startsWith("TRIP131X")) {
            lamps.setLampStatus(lampIndex::R, str2i(str));
        } else if (str.startsWith("TRIP132X")) {
            lamps.setLampStatus(lampIndex::G, str2i(str));
        } else if (str.startsWith("TRIP133X")) {
            lamps.setLampStatus(lampIndex::SFN, str2i(str));
        } else if (str.startsWith("TRIP134X")) {
            lamps.setLampStatus(lampIndex::P, str2i(str));
        } else if (str.startsWith("TRIP135X")) {
            meters.writeB(str2f(str) / 10);
        } else if (str.startsWith("TRIP161X")) {
            lamps.setLampStatus(lampIndex::BL, str2i(str));
        }
        // delay(1);
    }
}

/**
 * @brief 初めに一度だけ実行される関数
 */
void setup() {
    Serial.begin(1500000);
    meters.setup();
    lamps.setup();

    delay(250);

    demo();
    
    delay(250);

    // AutoSendでの実装（設定）
    bids.CmdSenderI("TRAE1");
    bids.CmdSenderI("TRAP42");
    bids.CmdSenderI("TRAP43");
    bids.CmdSenderI("TRAP44");
    bids.CmdSenderI("TRAP101");
    bids.CmdSenderI("TRAP102");
    bids.CmdSenderI("TRAP104");
    bids.CmdSenderI("TRAP105");
    bids.CmdSenderI("TRAP106");
    bids.CmdSenderI("TRAP107");
    bids.CmdSenderI("TRAP108");
    bids.CmdSenderI("TRAP109");
    bids.CmdSenderI("TRAP110");
    bids.CmdSenderI("TRAP111");
    bids.CmdSenderI("TRAP112");
    bids.CmdSenderI("TRAP113");
    bids.CmdSenderI("TRAP114");
    bids.CmdSenderI("TRAP115");
    bids.CmdSenderI("TRAP116");
    bids.CmdSenderI("TRAP117");
    bids.CmdSenderI("TRAP118");
    bids.CmdSenderI("TRAP119");
    bids.CmdSenderI("TRAP120");
    bids.CmdSenderI("TRAP121");
    bids.CmdSenderI("TRAP122");
    bids.CmdSenderI("TRAP123");
    bids.CmdSenderI("TRAP124");
    bids.CmdSenderI("TRAP131");
    bids.CmdSenderI("TRAP132");
    bids.CmdSenderI("TRAP133");
    bids.CmdSenderI("TRAP134");
    bids.CmdSenderI("TRAP135");
    bids.CmdSenderI("TRAP161");
    
    delay(250);
}

/**
 * @brief 繰り返し実行される関数
 */
void loop() {
    // ポーリング
    loop_polling();

    // BIDS AS
    // loop_AutoSend();
}
