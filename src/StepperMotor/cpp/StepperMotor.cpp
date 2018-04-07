/**
 * @file StepperMotor.cpp
 * @brief StepperMotor
 */

#include "StepperMotor.h"
#include <wiringPi.h>

/**
 * @brief StepperMotorのコンストラクタ
 * 
 * @param int : IN1 GPIO PIN
 * @param int : IN2 GPIO PIN
 * @param int : IN3 GPIO PIN
 * @param int : IN4 GPIO PIN
 */
StepperMotor::StepperMotor(const int in1Pin, const int in2Pin, const int in3Pin, const int in4Pin){
    if(wiringPiSetup() == -1){
        throw "wiringPiSetup failed. Must root?";
    }
    this->in1Pin = in1Pin;
    this->in2Pin = in2Pin;
    this->in3Pin = in3Pin;
    this->in4Pin = in4Pin;
    pinMode(this->in1Pin, OUTPUT);
    pinMode(this->in2Pin, OUTPUT);
    pinMode(this->in3Pin, OUTPUT);
    pinMode(this->in4Pin, OUTPUT);
    this->outputGpioLow();
}

/**
 * @brief StepperMotorのデストラクタ
 *
 * @param void
 */
StepperMotor::~StepperMotor(void){
    this->outputGpioLow();
}

// public method

/**
 * @brief lighting
 *
 * @param const int : GPIO PIN
 * @param const int : Delay millisecond
 * @return void
 */
void StepperMotor::rotate(const double angle, enum StepperMotorDirection direction, const int delay){
    int gpioSequenceLength = sizeof(this->gpioSequence) / sizeof(int);
    // 512 steps loop = 1 rotation
    int outputSteps = (angle / 360) * 512;
    for(int i = 0; i < outputSteps; i++){
        if(direction == StepperMotorDirection::Clockwise){
            for(int i = gpioSequenceLength - 1; i >= 0; i--) {
                this->outputGpio(i);
            }
        } else {
            for(int i = 0; i < gpioSequenceLength; i++) {
                this->outputGpio(i);
            }
        }
        delayMicroseconds(delay);
    }
}

// private method

void StepperMotor::outputGpio(int step){
    int delay = 200 + (100 * (8 - (sizeof(this->gpioSequence) / sizeof(int))));
    digitalWrite(this->in1Pin, ((this->gpioSequence[step] & 0b1000) == 0b1000) ? HIGH : LOW); delayMicroseconds(delay);
    digitalWrite(this->in2Pin, ((this->gpioSequence[step] & 0b0100) == 0b0100) ? HIGH : LOW); delayMicroseconds(delay);
    digitalWrite(this->in3Pin, ((this->gpioSequence[step] & 0b0010) == 0b0010) ? HIGH : LOW); delayMicroseconds(delay);
    digitalWrite(this->in4Pin, ((this->gpioSequence[step] & 0b0001) == 0b0001) ? HIGH : LOW); delayMicroseconds(delay);
}

void StepperMotor::outputGpioLow(void){
    digitalWrite(this->in1Pin, LOW);
    digitalWrite(this->in2Pin, LOW);
    digitalWrite(this->in3Pin, LOW);
    digitalWrite(this->in4Pin, LOW);
}
