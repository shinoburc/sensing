/**
 * @file RGB3Color.cpp
 * @brief RGB 3 Color
 */

#include "RGB3Color.h"
#include <wiringPi.h>

/**
 * @brief RGB3Colorのコンストラクタ
 * 
 * @param int : RED GPIO PIN
 * @param int : GREEN GPIO PIN
 * @param int : BLUE GPIO PIN
 */
RGB3Color::RGB3Color(const int redPin, const int greenPin, const int bluePin){
    if(wiringPiSetup() == -1){
        throw "wiringPiSetup failed. Must root?";
    }
    this->redPin = redPin;
    this->greenPin = greenPin;
    this->bluePin = bluePin;
    pinMode(this->redPin, OUTPUT);
    pinMode(this->greenPin, OUTPUT);
    pinMode(this->bluePin, OUTPUT);
}

/**
 * @brief RGB3Colorのデストラクタ
 *
 * @param void
 */
RGB3Color::~RGB3Color(void){
    digitalWrite(this->redPin, LOW);
    digitalWrite(this->redPin, LOW);
    digitalWrite(this->redPin, LOW);
}

// public method

/**
 * @brief lighting
 *
 * @param const int : GPIO PIN
 * @param const int : Delay millisecond
 * @return void
 */
void RGB3Color::lighting(const int pin, const int delay_millisecond){
    this->lighting_on(pin);
    delay(delay_millisecond);
    this->lighting_off(pin);
}

/**
 * @brief flashing
 *
 * @param const times : number of lighting 
 * @param const int : Delay millisecond
 * @return void
 */
void RGB3Color::flashing(const int times, const int delay_millisecond){
    for(int i = 0; i < times; i++) {
        this->lighting(this->redPin, delay_millisecond);
        this->lighting(this->greenPin, delay_millisecond);
        this->lighting(this->bluePin, delay_millisecond);
    }
}

// private method

/**
 * @brief lighting on
 *
 * @param const int : GPIO PIN
 * @return void
 */
void RGB3Color::lighting_on(const int pin){
    digitalWrite(pin, HIGH);
    digitalWrite(pin, 1);
}

/**
 * @brief lighting off
 *
 * @param const int : GPIO PIN
 * @return void
 */
void RGB3Color::lighting_off(const int pin){
      digitalWrite(pin, LOW);
}

