#ifndef __SERVOMOTOR_H__
#define __SERVOMOTOR_H__
/**
 * @file ServoMotor.h
 * @brief ServoMotor
 */

enum struct ServoMotorDirection {
    Clockwise,
    AntiClockwise
};

/** 
 *  @class ServoMotor
 *  @brief ServoMotorクラス
 *
 * @par
 * ServoMotor を回転する。
 *
 */
class ServoMotor {
  public:
    explicit ServoMotor(const int in1Pin, const int in2Pin, const int in3Pin, const int in4Pin);
    virtual ~ServoMotor(void);

    void rotate(const double angle, enum ServoMotorDirection direction, const int delay);

  private:
    int in1Pin;
    int in2Pin;
    int in3Pin;
    int in4Pin;

    //2-2相励磁
    const int gpioSequence[8] = {0b01000, 0b01100, 0b00100, 0b00110, 0b00010, 0b00011, 0b00001, 0b01001};
    //1-1相励磁
    //int gpioSequence[4] = {0b01000, 0b00100, 0b00010, 0b00001};


    void outputGpio(const int step);
    void outputGpioLow(void);
};

#endif
