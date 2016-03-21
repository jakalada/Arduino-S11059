#include <Wire.h>
#include <S11059.h>

S11059 colorSensor;

void setup() {
  Serial.begin(9600);
  colorSensor.begin();

  colorSensor.setMode(S11059_MODE_FIXED);
  colorSensor.setGain(S11059_GAIN_HIGH);
  colorSensor.setTint(S11059_TINT3);
  if (!colorSensor.reset()) {
    Serial.println("reset failed");
  }

  delay(500);
}

void printValues() {
  for (int i = 0; i < 10; i++) {
    delay(500);
    if (colorSensor.update()) {
      Serial.print(colorSensor.getRed());
      Serial.print(",");
      Serial.print(colorSensor.getGreen());
      Serial.print(",");
      Serial.print(colorSensor.getRed());
      Serial.print(",");
      Serial.print(colorSensor.getIR());
      Serial.println("");
    } else {
      Serial.println("update(): failed");
    }
  }
}

void loop() {
  // 動作が開始され更新されることを確認する
  Serial.println("----- not standby");
  if (!colorSensor.start()) {
    Serial.println("start(): failed");
  }
  Serial.print("isStandby(): ");
  Serial.println(colorSensor.isStandby());
  printValues();

  // 待機モードに入り値が更新されないことを確認する
  Serial.println("----- standby");
  if (!colorSensor.standby()) {
    Serial.println("standby(): failed");
  }
  Serial.print("isStandby(): ");
  Serial.println(colorSensor.isStandby());
  printValues();
}

