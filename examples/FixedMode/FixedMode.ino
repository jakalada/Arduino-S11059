#include <Wire.h>
#include <S11059.h>

S11059 colorSensor;

void setup() {
  Serial.begin(9600);
  colorSensor.begin();

  // 積分モードを固定時間モードに設定
  colorSensor.setMode(S11059_MODE_FIXED);

  // ゲイン選択
  // * S11059_GAIN_HIGH: Highゲイン
  // * S11059_GAIN_LOW: Lowゲイン
  colorSensor.setGain(S11059_GAIN_HIGH);

  // 1色あたりの積分時間設定(下記は指定可能な定数ごとの固定時間モードの場合の積分時間)
  // * S11059_TINT0: 87.5 us
  // * S11059_TINT1: 1.4 ms
  // * S11059_TINT2: 22.4 ms
  // * S11059_TINT3: 179.2 ms
  colorSensor.setTint(S11059_TINT1);

  // ADCリセット、スリープ解除
  if (!colorSensor.reset()) {
    Serial.println("reset failed");
  }

  // ADCリセット解除、バスリリース
  if (!colorSensor.start()) {
    Serial.println("start failed");
  }
}

void loop() {
  // 積分時間よりも長く待機
  //
  // 固定時間モード時のS11059.delay()で実行される待機処理の時間は
  // S11059.setTint(tint)で設定した値に応じて異なります
  colorSensor.delay();

  // センサのデータ用レジスタ(赤、緑、青、赤外)をまとめてリード
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

  delay(500);
}

