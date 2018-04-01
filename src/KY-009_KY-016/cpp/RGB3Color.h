#ifndef __RGB3COLOR_H__
#define __RGB3COLOR_H__
/**
 * @file RGB3Color.h
 * @brief RGB 3 Color
 */

/** 
 *  @class RGB3Color
 *  @brief RGB3Colorクラス
 *
 * @par
 * RGB 3 Color モジュールを点灯したりフラッシュて点灯する。
 *
 */
class RGB3Color {
  public:
    explicit RGB3Color(const int redPin, const int greenPin, const int bluePin);
    virtual ~RGB3Color(void);

    void lighting(const int pin, const int delay_millisecond);
    void flashing(const int times, const int delay_millisecond);

  private:
    /** RED GPIO PIN */
    int redPin;
    /** GREEN GPIO PIN */
    int greenPin;
    /** BLUE GPIO PIN */
    int bluePin;

    void lighting_on(const int pin);
    void lighting_off(const int pin);
};

#endif
