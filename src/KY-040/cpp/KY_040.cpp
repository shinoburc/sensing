/**
 * @file KY_040.cpp
 * @brief KY-040:  Photosensitive Resistance Sensor
 */

#include <wiringPi.h>
#include "KY_040.h"

/* KY_040 instances vector. */
std::vector<KY_040*> KY_040::modules = {};

/**
 * @brief KY_040のコンストラクタ
 * 
 * @param int : CLK  GPIO PIN
 * @param int : DT GPIO PIN
 * @param int : SW GPIO PIN
 */
KY_040::KY_040(const int clkPin, const int dtPin, const int swPin){
    if(wiringPiSetup() == -1){
        throw "wiringPiSetup failed. Must root?";
    }
    this->clkPin = clkPin;
    this->dtPin = dtPin;
    this->swPin = swPin;

    pinMode(this->clkPin, INPUT);
    pinMode(this->dtPin, INPUT);
    pullUpDnControl(this->clkPin, PUD_UP);
    pullUpDnControl(this->dtPin, PUD_UP);
    KY_040::modules.push_back(this);
    wiringPiISR(this->clkPin,INT_EDGE_BOTH, KY_040::wiringPiISRCallback);
    wiringPiISR(this->dtPin,INT_EDGE_BOTH, KY_040::wiringPiISRCallback);
}

/**
 * @brief KY_040のデストラクタ
 *
 * @param void
 */
KY_040::~KY_040(void){
}

// static method

/**
 * @brief rotation callback function using wiringPiISR
 *
 * @param void
 */
void KY_040::wiringPiISRCallback(){
  for (KY_040* module : KY_040::modules) {
      module->updateEncoder();
  }
}

// public method

/**
 * @brief rotationValue getter
 *
 * @param void
 * @return int
 */
int KY_040::getRotationValue(){
    return this->rotationValue;
}

// private method

/**
 * @brief update rotationValue
 *
 * @param void
 * @return void
 */
void KY_040::updateEncoder(){
    int MSB = digitalRead(KY_040::clkPin);
    int LSB = digitalRead(KY_040::dtPin);

    int encoded = (MSB << 1) | LSB;
    int sum = (KY_040::lastEncoded << 2) | encoded;

    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) KY_040::rotationValue++;
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) KY_040::rotationValue--;

    KY_040::lastEncoded = encoded;
}
