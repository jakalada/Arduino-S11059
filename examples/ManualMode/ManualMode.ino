/**********************************************************************
  Sensor Datasheet:
    - EN: http://www.hamamatsu.com/resources/pdf/ssd/s11059-02dt_etc_kpic1082e.pdf
          (Cat. No. KPIC1082E05 Nov. 2015 DN)
    - JP: http://www.hamamatsu.com/resources/pdf/ssd/s11059-02dt_etc_kpic1082j.pdf
          (Cat. No. KPIC1082J05 Nov. 2015 DN)
**********************************************************************/

#include <Wire.h>
#include <S11059.h>

S11059 colorSensor;

void setup() {
  Serial.begin(9600);
  colorSensor.begin();

  // 積分モードをマニュアル設定モードに設定
  colorSensor.setMode(S11059_MODE_MANUAL);

  // ゲイン選択
  // * S11059_GAIN_HIGH: Highゲイン
  // * S11059_GAIN_LOW: Lowゲイン
  colorSensor.setGain(S11059_GAIN_LOW);

  // 1色あたりの積分時間設定(下記は指定する定数とマニュアル設定モードの場合の積分時間)
  // * S11059_TINT0: 175 us
  // * S11059_TINT1: 2.8 ms
  // * S11059_TINT2: 44.8 ms
  // * S11059_TINT3: 358.4 ms
  colorSensor.setTint(S11059_TINT0);

  // マニュアルタイミング(0~65535)
  // setTint()で指定した積分時間を何倍まで長くするかを設定
  colorSensor.setManualTiming(3120);
}

void loop() {
  // ADCリセット、スリープ解除
  if (!colorSensor.reset()) {
    Serial.println("reset failed");
  }

  // ADCリセット解除、バスリリース
  if (!colorSensor.start()) {
    Serial.println("start failed");
  }

  // 積分時間よりも長く待機
  //
  // マニュアル設定モード時のS11059.delay()で実行される待機処理の時間は
  // S11059.setTint(tint)、S11059.setManualTiming(manualTiming)で
  // 設定した値に応じて異なります
  colorSensor.delay();

  // 赤、緑、青、赤外データをリード
  if (colorSensor.update()) {
    Serial.print(colorSensor.getRed());
    Serial.print(",");
    Serial.print(colorSensor.getGreen());
    Serial.print(",");
    Serial.print(colorSensor.getBlue());
    Serial.print(",");
    Serial.print(colorSensor.getIR());
    Serial.println("");
  } else {
    Serial.println("update failed");
  }

  delay(1000);
}

