/**
 * @example play_flow_control.ino
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