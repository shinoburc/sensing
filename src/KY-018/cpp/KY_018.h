#ifndef __KY018_H__
#define __KY018_H__
/**
 * @file KY_018.h
 * @brief KY-018:  Photosensitive Resistance Sensor
 */

/** 
 *  @class KY_018
 *  @brief KY_018クラス
 *
 * @par KY-018:  Photosensitive Resistance Sensor モジュールを利用して光量を取得する
 *
 */
class KY_018{
  public:
    explicit KY_018(const int adcCsPin, const int adcClkPin, const int adcDioPin);
    virtual ~KY_018(void);

    unsigned int detectIllumination(void);

  private:
    /** ADC PIN */
    int adcCsPin;
    int adcClkPin;
    int adcDioPin;
};

#endif
