/**
 * @example play_flow_control.ino
 */

#include <Arduino.h>

#include "tts.h"

emakefun::Tts g_tts(emakefun::Tts::kDefaultI2cAddress);

void setup() {
  Serial.begin(115200);
  g_tts.Initialize();
  Serial.println("setup done");
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