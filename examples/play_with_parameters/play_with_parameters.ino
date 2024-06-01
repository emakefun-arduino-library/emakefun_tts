/**
 * @example play_with_parameters.ino
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
  // 定义文本，utf-8编码格式，文本前面增加[v1]来标注音量，以音量为10进行合成播放
  // 文本标注：设置音量格式：[v*]，其中*的范围是0 ~ 10，音量值默认音量为5，10 对应到最高音量
  // 更多文本标注参数见文档
  g_tts.Play(F("[v1]音量一"));  // 文本前面增加[v1]来标注音量，以音量为1进行合成播放

  delay(2000);

  // 定义文本，utf-8编码格式，文本前面增加[v10]来标注音量，以音量为10进行合成播放
  // 文本标注：设置音量格式：[v*]，其中*的范围是0 ~ 10，音量值默认音量为5，10 对应到最高音量
  // 更多文本标注参数见文档
  g_tts.Play(F("[v10]音量十"));  // 文本前面增加[v10]来标注音量，以音量为10进行合成播放

  delay(2000);
}