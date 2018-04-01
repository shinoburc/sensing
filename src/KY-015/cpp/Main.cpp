/**
 * @file Main.cpp
 * @brief main関数を定義している
 *
 * @par KY-015: DHT11 Temprature and Humidity Sensor
 *        
 */

#include<iostream>
#include<signal.h>
#include<atomic>
#include<cstring>
#include"KY_015.h"

/* 
 * KY-015: DHT11 Temprature and Humidity Sensor
 * PIN: GND DATA VCC
 */
#define DATA_PIN 29

#define MAXTIMINGS 85

std::atomic<bool> quit(false);    // signal flag
void got_signal(int){ quit.store(true); }
void signalHandling(){
    struct sigaction sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = got_signal;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT,&sa,NULL);
}

/**
 * @brief KY-015: DHT11 Temprature and Humidity Sensor
 *
 * @par
 * - KY-015: DHT11 Temprature and Humidity Sensor
 * 
 * @param argc : 引数の数
 * @param argv : 引数の値の配列
 * @return 実行ステータス
 */
int main(int argc, char** argv) {
    signalHandling();
    try {
        KY_015 module(DATA_PIN);
        while(1){
            if(module.sensing(MAXTIMINGS)){
                std::cout << "Humidity: " << module.getHumidity() << " %";
                std::cout << ", ";
                std::cout << "Temperature: " << module.getTemperature() << " C";
                std::cout << std::endl;
            }
            /* Ctrl-C Handling */
            if( quit.load() ) break;
        }
    }  catch (char *str) {
        std::cerr << str << std::endl;
        return 0;
    }

    return 1;
}
