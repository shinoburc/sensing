#ifndef __HCSR04_H__
#define __HCSR04_H__
/**
 * @file HC_SR04.h
 * @brief HC_SR04 Ultrasonic Ranging Sensor
 */

/** 
 *  @class HC_SR04
 *  @brief HC_SR04クラス
 *
 * @par
 * HC_SR04 超音波距離センサーからの距離データを取得する
 *
 */
class HC_SR04 {
  public:
    explicit HC_SR04(const int trigPin, const int echoPin);
    virtual ~HC_SR04(void);

    double distance(const unsigned int timeout);

  private:
    int trigPin;
    int echoPin;

    long detectPulseLength(void);
};

#endif
