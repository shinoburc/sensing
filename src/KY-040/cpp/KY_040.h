#ifndef __KY040_H__
#define __KY040_H__
/**
 * @file KY_040.h
 * @brief KY-040: Rotary Encoder Module
 */

#include<vector>

/** 
 *  @class KY_040
 *  @brief KY_040クラス
 *
 * @par KY-040: Rotary Encoder モジュールを利用して回転つまみの値を取得する
 *
 */
class KY_040{
  public:
    explicit KY_040(const int clkPin, const int dtPin, const int swPin);
    virtual ~KY_040(void);

    void updateEncoder(void);
    int getRotationValue(void);

  private:
    /** ADC PIN */
    int clkPin;
    int dtPin;
    int swPin;

    /** Sensing value */
    int rotationValue;

    volatile int lastEncoded;

    static std::vector<KY_040*> modules;
    static void wiringPiISRCallback(void);
};

#endif
