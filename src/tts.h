#ifndef EMAKEFUN_TTS_H_
#define EMAKEFUN_TTS_H_

#include <WString.h>
#include <Wire.h>
#include <stdint.h>

namespace emakefun {

/**
 * @class Tts
 * @brief 语音合成模块
 */
class Tts {
 public:
  /**
   * @brief 语音合成模块默认I2C地址
   */
  static constexpr uint8_t kDefaultI2cAddress = 0x40;

  /**
   * @brief 文本数据最大字节数
   */
  static constexpr uint8_t kMaxTextBytesSize = 250;

  /**
   * @brief  缓存块索引最大值
   */
  static constexpr uint8_t kMaxCacheIndex = 15;

  /**
   * @brief 从缓存合成播放次数的最小值
   */
  static constexpr uint8_t kMinSpeechCount = 1;

  /**
   * @brief 从缓存合成播放次数的最大值
   */
  static constexpr uint8_t kMaxSpeechCount = 15;

  /**
   * @enum ErrorCode
   * @brief 错误码
   */
  enum ErrorCode : uint32_t {
    kOK = 0,                                  /**< 0：成功 */
    kI2cDataTooLongToFitInTransmitBuffer = 1, /**< 1：I2C数据太长，无法装入传输缓冲区 */
    kI2cReceivedNackOnTransmitOfAddress = 2,  /**< 2：在I2C发送地址时收到NACK */
    kI2cReceivedNackOnTransmitOfData = 3,     /**< 3：在I2C发送数据时收到NACK */
    kI2cOtherError = 4,                       /**< 4：其他I2C错误 */
    kI2cTimeout = 5,                          /**< 5：I2C通讯超时 */
    kInvalidParameter = 6,                    /**< 6：参数错误 */
    kUnknownError = 7,                        /**< 7: 未知错误*/
  };

  /**
   * @enum TextEncodingType
   * @brief 文本编码类型
   */
  enum TextEncodingType : uint8_t {
    kGb23212 = 0x00, /**< GB2312 */
    kGbk = 0x01,     /**< GBK */
    kBig5 = 0x02,    /**< BIG5 */
    kUtf16le = 0x03, /**< UTF16LE */
    kUtf8 = 0x04,    /**< UTF8 */
  };

  /**
   * @brief 构造函数
   * @param di2c_address 语音合成模块I2C地址，默认为0x40
   */
  explicit Tts(TwoWire& wire = Wire, const uint8_t i2c_address = kDefaultI2cAddress);

  /**
   * @brief 初始化函数
   * @return 返回值请参考 @ref ErrorCode
   */
  ErrorCode Initialize();

  /**
   * @brief 文本转语音并播放
   * @param[in] text 文本数据，数据长度不大于250个字节
   * @param[in] text_encoding_type 文本编码类型，参考 @ref TextEncodingType, 默认为 @ref kUtf8
   * @return 返回值请参考 @ref ErrorCode
   */
  ErrorCode Play(const String& text, const TextEncodingType text_encoding_type = kUtf8);

  /**
   * @brief 从缓存块0的文本开始转语音并播放
   * @param[in] text_encoding_type 文本编码类型，参考 @ref TextEncodingType，默认为 @ref kUtf8
   * @param[in] synthesizing_count 合成播放次数，范围 1 ~ 15
   * @return 返回值请参考 @ref ErrorCode
   */
  ErrorCode PlayFromCache(const TextEncodingType text_encoding_type = kUtf8, uint8_t count = kMinSpeechCount);

  /**
   * @brief 将文本内容上传到指定缓存块
   * @param[in] text 文本数据，数据长度不大于250个字节
   * @param[in] cache_index 缓存块索引，范围 0 ~ 15
   * @return 返回值请参考 @ref ErrorCode
   */
  ErrorCode PushTextToCache(const String& text, const uint8_t cache_index);

  /**
   * @brief 停止播放
   * @return 返回值请参考 @ref ErrorCode
   */
  ErrorCode Stop();

  /**
   * @brief 暂停播放
   * @return 返回值请参考 @ref ErrorCode
   */
  ErrorCode Pause();

  /**
   * @brief 恢复播放
   * @return 返回值请参考 @ref ErrorCode
   */
  ErrorCode Resume();

 private:
  Tts(const Tts&) = delete;
  Tts& operator=(const Tts&) = delete;
  ErrorCode I2cWrite(const uint8_t* data, const uint8_t length);

  TwoWire& wire_ = Wire;
  const uint8_t i2c_address_ = kDefaultI2cAddress;
};
}  // namespace emakefun

#endif