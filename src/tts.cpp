#include <Arduino.h>
#include <tts.h>

#ifdef AVR
#include "utility/TinyI2CMaster.h"
#endif

namespace emakefun {
namespace {
template <typename T>
inline T Min(const T x, const T y) {
  return x < y ? x : y;
}

}  // namespace

Tts::Tts(const uint8_t i2c_address) : i2c_address_(i2c_address) {
}

int32_t Tts::Initialize(TwoWire* const wire) {
  wire_ = wire;
  if (wire_ == nullptr) {
    return -1;
  }

  wire_->beginTransmission(i2c_address_);
  return wire_->endTransmission();
}

void Tts::Play(const String& text, const TextEncodingType text_encoding_type) {
  const uint8_t text_length = Min<uint8_t>(kMaxTextBytesSize, text.length());
  const uint8_t data_length = text_length + 5;
  uint8_t* data = new uint8_t[data_length];
  uint8_t index = 0;
  data[index++] = 0xFD;
  data[index++] = 0x00;
  data[index++] = text_length + 2;
  data[index++] = 0x01;
  data[index++] = text_encoding_type;
  memcpy(data + index, text.c_str(), text_length);
  I2cWrite(data, data_length);
  delete[] data;
}

void Tts::PlayFromCache(const TextEncodingType text_encoding_type, uint8_t count) {
  count = constrain(count, kMinSpeechCount, kMaxSpeechCount);
  const uint8_t data[] = {0xFD, 0x00, 0x02, 0x32, (count << 4) | text_encoding_type};
  I2cWrite(data, sizeof(data));
}

void Tts::PushTextToCache(const String& text, const uint8_t cache_index) {
  if (cache_index > kMaxCacheIndex) {
    return;
  }

  const uint8_t text_length = Min<uint8_t>(kMaxTextBytesSize, text.length());
  const uint8_t data_length = text_length + 5;
  uint8_t* const data = new uint8_t[data_length];
  uint8_t index = 0;
  data[index++] = 0xFD;
  data[index++] = 0x00;
  data[index++] = text_length + 2;
  data[index++] = 0x31;
  data[index++] = cache_index;
  memcpy(data + index, text.c_str(), text_length);
  I2cWrite(data, data_length);
  delete[] data;
}

void Tts::Stop() {
  const uint8_t data[] = {0x00, 0x01, 0x02};
  I2cWrite(data, sizeof(data));
}

void Tts::Pause() {
  const uint8_t data[] = {0x00, 0x01, 0x03};
  I2cWrite(data, sizeof(data));
}

void Tts::Resume() {
  const uint8_t data[] = {0x00, 0x01, 0x04};
  I2cWrite(data, sizeof(data));
}

void Tts::I2cWrite(const uint8_t* data, const uint8_t length) {
#ifdef AVR
  TinyI2C.start(i2c_address_, 0);
  for (uint8_t i = 0; i < length; i++) {
    TinyI2C.write(data[i]);
  }
  TinyI2C.stop();
#else
  wire_->beginTransmission(i2c_address_);
  wire_->write(data, length);
  wire_->endTransmission();
#endif
}

}  // namespace emakefun