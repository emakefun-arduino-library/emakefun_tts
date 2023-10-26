/**
 * @example play.ino
 */

#include <Arduino.h>

#include "tts.h"

// 创建tts实例
emakefun::Tts g_tts(emakefun::Tts::kDeviceI2cAddress);

void setup() {
  Serial.begin(115200);
  g_tts.Initialize();
  Serial.println("setup");
}

void loop() {
  // 默认以utf-8编码格式合成播放文本
  g_tts.Play(F("一二三四五"));
  delay(2000);
}