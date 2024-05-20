/**
 * @example play.ino
 */

#include <Arduino.h>

#include "tts.h"

// 创建tts实例
namespace {
emakefun::Tts g_tts(emakefun::Tts::kDefaultI2cAddress);
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("setup"));
  Wire.begin();
  const auto ret = g_tts.Initialize(&Wire);
  if (0 == ret) {
    Serial.println(F("tts module initialization was successful"));
  } else {
    Serial.println(String(F("tts module initialization failed: ")) + ret);
    while (true)
      ;
  }
  Serial.println(F("setup was successful"));
}

void loop() {
  // 默认以utf-8编码格式合成播放文本
  g_tts.Play(F("一二三四五"));
  delay(2000);
}