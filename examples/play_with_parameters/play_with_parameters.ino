/**
 * @example play_with_parameters.ino
 */

#include <Arduino.h>

#include "tts.h"

// 创建tts实例
emakefun::Tts g_tts(emakefun::Tts::kDefaultI2cAddress);

void setup() {
  Serial.begin(115200);
  g_tts.Initialize();
  Serial.println("setup done");
}

void loop() {
  // 定义文本，utf-8编码格式，文本前面增加[v1]来标注音量，以音量为10进行合成播放
  // 文本标注：设置音量格式：[v*]，其中*的范围是0 ~ 10，音量值默认音量为5，10 对应到最高音量
  // 更多文本标注参数见文档
  g_tts.Play(F("[v1]一二三四五"));  // 文本前面增加[v1]来标注音量，以音量为1进行合成播放

  delay(2000);

  // 定义文本，utf-8编码格式，文本前面增加[v10]来标注音量，以音量为10进行合成播放
  // 文本标注：设置音量格式：[v*]，其中*的范围是0 ~ 10，音量值默认音量为5，10 对应到最高音量
  // 更多文本标注参数见文档
  g_tts.Play(F("[v10]一二三四五"));  // 文本前面增加[v10]来标注音量，以音量为10进行合成播放

  delay(2000);
}