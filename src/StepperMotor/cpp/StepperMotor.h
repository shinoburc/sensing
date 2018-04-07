#ifndef __STEPPERMOTOR_H__
#define __STEPPERMOTOR_H__
/**
 * @file StepperMotor.h
 * @brief StepperMotor
 */

enum struct StepperMotorDirection {
    Clockwise,
    AntiClockwise
};

/** 
 *  @class StepperMotor
 *  @brief StepperMotorクラス
 *
 * @par
 * StepperMotor を回転する。
 *
 */
class StepperMotor {
  public:
    explicit StepperMotor(const int in1Pin, const int in2Pin, const int in3Pin, const int in4Pin);
    virtual ~StepperMotor(void);

    void rotate(const double angle, enum StepperMotorDirection direction, const int delay);

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
