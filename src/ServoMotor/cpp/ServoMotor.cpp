/**
 * @file ServoMotor.cpp
 * @brief ServoMotor
 */

#include "ServoMotor.h"
#include <wiringPi.h>

/**
 * @brief ServoMotorのコンストラクタ
 * 
 * @param int : IN1 GPIO PIN
 * @param int : IN2 GPIO PIN
 * @param int : IN3 GPIO PIN
 * @param int : IN4 GPIO PIN
 */
ServoMotor::ServoMotor(const int in1Pin, const int in2Pin, const int in3Pin, const int in4Pin){
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
 * @brief ServoMotorのデストラクタ
 *
 * @param void
 */
ServoMotor::~ServoMotor(void){
    this->outputGpioLow();
}

// public method

/**
 * @brief lighting
 *
 * @param const int : rotate angle
 * @param enum ServoMotorDirection : rotate direction
 * @param const int : rotate delay (speed)
 * @return void
 */
void ServoMotor::rotate(const double angle, enum ServoMotorDirection direction, const int delay){
    int gpioSequenceLength = sizeof(this->gpioSequence) / sizeof(int);
    // 512 steps loop = 1 rotation
    int outputSteps = (angle / 360) * 512;
    for(int i = 0; i < outputSteps; i++){
        if(direction == ServoMotorDirection::Clockwise){
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

void ServoMotor::outputGpio(int step){
    int delay = 200 + (100 * (8 - (sizeof(this->gpioSequence) / sizeof(int))));
    digitalWrite(this->in1Pin, ((this->gpioSequence[step] & 0b1000) == 0b1000) ? HIGH : LOW); delayMicroseconds(delay);
    digitalWrite(this->in2Pin, ((this->gpioSequence[step] & 0b0100) == 0b0100) ? HIGH : LOW); delayMicroseconds(delay);
    digitalWrite(this->in3Pin, ((this->gpioSequence[step] & 0b0010) == 0b0010) ? HIGH : LOW); delayMicroseconds(delay);
    digitalWrite(this->in4Pin, ((this->gpioSequence[step] & 0b0001) == 0b0001) ? HIGH : LOW); delayMicroseconds(delay);
}

void ServoMotor::outputGpioLow(void){
    digitalWrite(this->in1Pin, LOW);
    digitalWrite(this->in2Pin, LOW);
    digitalWrite(this->in3Pin, LOW);
    digitalWrite(this->in4Pin, LOW);
}
