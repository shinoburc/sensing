/**
 * @file Main.cpp
 * @brief main関数を定義している
 *
 * @par KY-018:  Photosensitive Resistance Sensor Module
 *        
 */

#include<iostream>
#include<signal.h>
#include<atomic>
#include<cstring>
#include"KY_018.h"

/* 
 * KY-018:  Photosensitive Resistance Sensor Module
 * ADC:
 * PIN:
 */
#define ADC_CS_PIN  23
#define ADC_CLK_PIN 22
#define ADC_DIO_PIN 21

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
 * @brief KY-018:  Photosensitive Resistance Sensor Module
 *
 * @par
 * - KY-018:  Photosensitive Resistance Sensor Module
 * 
 * @param argc : 引数の数
 * @param argv : 引数の値の配列
 * @return 実行ステータス
 */
int main(int argc, char** argv) {
    signalHandling();
    try {
        KY_018 module(ADC_CS_PIN, ADC_CLK_PIN, ADC_DIO_PIN);
        while(1){
            std::cout << "Current illumination : " << module.detectIllumination() << std::endl;

            /* Ctrl-C Handling */
            if( quit.load() ) break;
        }
    } catch (char *str) {
        std::cerr << str << std::endl;
        return 0;
    }

    return 1;
}
