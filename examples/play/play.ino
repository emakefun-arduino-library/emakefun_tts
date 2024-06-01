/**
 * @example play.ino
 */

#include "tts.h"

#define INFINITE_LOOP_ON_FAILURE InfiniteLoopOnFailure(__FUNCTION__, __LINE__)

namespace {
emakefun::Tts g_tts;  // 创建tts实例

void InfiniteLoopOnFailure(const char* function, const uint32_t line_number) {
  Serial.println(String(F("entering an infinite loop due to failure in ")) + function + F(", at line number: ") + line_number);
  while (true) {
    yield();
  }
}
}  // namespace

void setup() {
  Serial.begin(115200);
  Serial.println(F("setup"));
  Wire.begin();
  const auto ret = g_tts.Initialize();
  if (emakefun::Tts::kOK == ret) {
    Serial.println(F("tts module initialization successful"));
  } else {
    Serial.println(String(F("tts module initialization failed: ")) + ret);
    INFINITE_LOOP_ON_FAILURE;
  }
  Serial.println(F("setup successful"));
}

void loop() {
  // 默认以utf-8编码格式合成播放文本
  g_tts.Play(F("一二三四五"));
  delay(2000);
}