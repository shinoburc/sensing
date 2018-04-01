#ifndef __KY015_H__
#define __KY015_H__
/**
 * @file KY_015.h
 * @brief KY-015: DHT11 Temprature and Humidity Sensor
 */

/** 
 *  @class KY_015
 *  @brief KY_015クラス
 *
 * @par KY-015: DHT11 Temprature and Humidity Sensor モジュールを利用して湿度と温度を取得する
 *
 */
class KY_015{
  public:
    explicit KY_015(const int dataPin);
    virtual ~KY_015(void);


    bool sensing(const int maxTimings);
    double getHumidity(void);
    double getTemperature(void);

  private:
    /** DATA GPIO PIN */
    int dataPin;

    /** Sensing Data */
    double humidity;
    double temperature;
};

#endif
