/**
 * @file KY_015.cpp
 * @brief KY015: DHT11 Temprature and Humidity Sensor
 */

#include <stdint.h>
#include <wiringPi.h>
#include "KY_015.h"

/**
 * @brief KY_015のコンストラクタ
 * 
 * @param int : DATA GPIO PIN
 */
KY_015::KY_015(const int dataPin){
    this->dataPin = dataPin;
    if(wiringPiSetup() == -1){
        throw "wiringPiSetup failed. Must root?";
    }
}

/**
 * @brief KY_015のデストラクタ
 *
 * @param void
 */
KY_015::~KY_015(void){
}

// public method

/**
 * @brief sensing
 *
 * @param const int : Max timings
 * @return void
 */
bool KY_015::sensing(const int maxTimings){
    // pull pin down for 18 milliseconds
    pinMode(this->dataPin, OUTPUT);
    digitalWrite(this->dataPin, LOW);
    delay(18);

    // then pull it up for 40 microseconds
    digitalWrite(this->dataPin, HIGH);
    delayMicroseconds(40);

    // prepare to read the pin
    pinMode(this->dataPin, INPUT);

    // detect change and read data
    uint8_t laststate = HIGH;
    int dht11_dat[5] = {0,0,0,0,0};
    uint8_t bit_count = 0;
    uint8_t counter = 0;
    for(int i = 0; i< maxTimings; i++){
        counter = 0;
        while(digitalRead(this->dataPin) == laststate){
            counter++;
            delayMicroseconds(1);
            if(counter == 255) break;
        }
        laststate = digitalRead(this->dataPin);
        if(counter == 255) break;

        // ignore first 3 transitions
        if((i >= 4) && (i % 2 == 0)){
            // shove each bit into the storage bytes

            dht11_dat[bit_count/8] <<= 1;
            if(counter > 50){
                dht11_dat[bit_count/8] |= 1;
            }
            bit_count++;
        }
    }

    // check we read 40 bits (8bit x 5 ) && verify checksum in the last byte
    // print it out if data is good
    if((bit_count >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF))) {
        //printf("Humidity = %d.%d %%, Temperature = %d.%d C\n", dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3]);
        this->humidity    = dht11_dat[0] + ((double)dht11_dat[1]/10);
        this->temperature = dht11_dat[2] + ((double)dht11_dat[3]/10);
        return true;
    } else {
        return false;
    }
}

/**
 * @brief this->humidity getter
 *
 * @param void
 * @return double
 */
double KY_015::getHumidity(){
    return this->humidity;
}

/**
 * @brief this->temperature getter
 *
 * @param void
 * @return double
 */
double KY_015::getTemperature(){
    return this->temperature;
}
