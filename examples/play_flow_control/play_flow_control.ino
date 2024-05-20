/**
 * @example play_flow_control.ino
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
  g_tts.Play(F("一二三四五六七八九十"));
  delay(1000);

  // 暂停合成播放
  g_tts.Pause();

  // 延时1s
  delay(1000);

  // 恢复合成播放
  g_tts.Resume();

  // 延时1s
  delay(1000);

  // 停止合成播放
  g_tts.Stop();
}