/**
 * @file KY_018.cpp
 * @brief KY-018:  Photosensitive Resistance Sensor
 */

#include <wiringPi.h>
#include "KY_018.h"

/**
 * @brief KY_018のコンストラクタ
 * 
 * @param int : ADC CS  GPIO PIN
 * @param int : ADC CLK GPIO PIN
 * @param int : ADC DIO GPIO PIN
 */
KY_018::KY_018(const int adcCsPin, const int adcClkPin, const int adcDioPin){
    if(wiringPiSetup() == -1){
        throw "wiringPiSetup failed. Must root?";
    }
    this->adcCsPin = adcCsPin;
    this->adcClkPin = adcClkPin;
    this->adcDioPin = adcDioPin;
    pinMode(this->adcCsPin,  OUTPUT);
    pinMode(this->adcClkPin, OUTPUT);
}

/**
 * @brief KY_018のデストラクタ
 *
 * @param void
 */
KY_018::~KY_018(void){
    digitalWrite(this->adcCsPin, LOW);
    digitalWrite(this->adcClkPin, LOW);
    digitalWrite(this->adcDioPin, LOW);
}

// public method

/**
 * @brief detect illumination
 *
 * @param void
 * @return unsigned int 
 */
unsigned int KY_018::detectIllumination(){
	unsigned char i;
	unsigned int  dat1=0, dat2=0;

  pinMode(this->adcDioPin, OUTPUT);
  delay(1000);

	digitalWrite(this->adcCsPin, LOW);
	digitalWrite(this->adcClkPin,LOW);
	digitalWrite(this->adcDioPin,HIGH);	delayMicroseconds(2);
	digitalWrite(this->adcClkPin,HIGH);	delayMicroseconds(2);

	digitalWrite(this->adcClkPin,LOW);	
	digitalWrite(this->adcDioPin,HIGH); delayMicroseconds(2);
	digitalWrite(this->adcClkPin,HIGH);	delayMicroseconds(2);

	digitalWrite(this->adcClkPin,LOW);	
	digitalWrite(this->adcDioPin,LOW);	delayMicroseconds(2);
	digitalWrite(this->adcClkPin,HIGH);	
	digitalWrite(this->adcDioPin,HIGH); delayMicroseconds(2);
	digitalWrite(this->adcClkPin,LOW);	
	digitalWrite(this->adcDioPin,HIGH); delayMicroseconds(2);
	
	for(i=0;i<8;i++)
	{
		digitalWrite(this->adcClkPin,HIGH);	delayMicroseconds(2);
		digitalWrite(this->adcClkPin,LOW);  delayMicroseconds(2);

		pinMode(this->adcDioPin, INPUT);
		dat1=dat1<<1 | digitalRead(this->adcDioPin);
	}
	
	for(i=0;i<8;i++)
	{
		dat2 = dat2 | ((unsigned int)(digitalRead(this->adcDioPin))<<i);
		digitalWrite(this->adcClkPin,HIGH); delayMicroseconds(2);
		digitalWrite(this->adcClkPin,LOW);  delayMicroseconds(2);
	}

	digitalWrite(this->adcCsPin,HIGH);
	
	return 210 - ((dat1==dat2) ? dat1 : 0);
}
