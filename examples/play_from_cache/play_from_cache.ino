/**
 * @example play_from_cache.ino
 */

#include <Arduino.h>

#include "tts.h"

// 创建tts实例
emakefun::Tts g_tts(emakefun::Tts::kDeviceI2cAddress);

void setup() {
  Serial.begin(115200);
  g_tts.Initialize();
  Serial.println("setup done");
}

void loop() {
  // 将文本1内容上传到缓存块0
  g_tts.PushTextToCache(F("一二三四五"), 0);

  // 将文本2内容上传到缓存块1
  g_tts.PushTextToCache(F("六七八九十"), 1);

  // 开始从缓存区域合成播放文本，合成播放1次
  g_tts.PlayFromCache();

  delay(3000);
}