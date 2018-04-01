/**
 * @file HC_SR04.cpp
 * @brief HC_SR04 Ultrasonic Ranging Sensor
 */

#include "HC_SR04.h"
#include <wiringPi.h>

/**
 * @brief HC_SR04のコンストラクタ
 * 
 * @param int : TRIG GPIO PIN
 * @param int : ECHO GPIO PIN
 */
HC_SR04::HC_SR04(const int trigPin, const int echoPin){
    if(wiringPiSetup() == -1){
        throw "wiringPiSetup failed. Must root?";
    }
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
    digitalWrite(this->trigPin, LOW);
    delay(500);
}

/**
 * @brief HC_SR04のデストラクタ
 *
 * @param void
 */
HC_SR04::~HC_SR04(void){
    digitalWrite(this->trigPin, LOW);
    digitalWrite(this->echoPin, LOW);
    delay(10);
}

// public method

/**
 * @brief distance
 *
 * @param const int : timeout
 * @return double distance
 */
double HC_SR04::distance(const unsigned int timeout) {
    long startTime;

    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigPin, LOW);

    startTime = micros();

    while (digitalRead(this->echoPin) == LOW && (micros() - startTime < timeout));

    return 100*((this->detectPulseLength()/1000000.0)*340.29)/2;
}

// private method

/**
 * @brief detectPulseLength
 *
 * @param void
 * @return long
 */
long HC_SR04::detectPulseLength()
{
    long startTimeUsec, endTimeUsec;

    startTimeUsec = micros();
    while(digitalRead(this->echoPin) == HIGH);
    endTimeUsec = micros();

    return endTimeUsec - startTimeUsec;;
}
