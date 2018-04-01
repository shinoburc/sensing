/**
 * @file Main.cpp
 * @brief main関数を定義している
 *
 * @par KY-040: Rotary Encoder Module
 *        
 */

#include<iostream>
#include<signal.h>
#include<atomic>
#include<cstring>
#include<time.h>
#include"KY_040.h"

/* 
 * KY-040: Rotary Encoder Module
 * PIN: GND VCC SW DT CLK
 */
#define CLK_PIN 0
#define DT_PIN  2
#define SW_PIN  3

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
 * @brief KY-040: Rotary Encoder Module
 *
 * @par
 * - KY-040: Rotary Encoder Module
 * 
 * @param argc : 引数の数
 * @param argv : 引数の値の配列
 * @return 実行ステータス
 */
int main(int argc, char** argv) {
    signalHandling();
    
    try {
        KY_040 module(CLK_PIN, DT_PIN, SW_PIN);

        /* 0.1 second */
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 100000000;

        while(1){
            std::cout << "Rotation Value: " << module.getRotationValue() << std::endl;
            nanosleep(&ts, NULL);

            /* Ctrl-C Handling */
            if( quit.load() ) break;
        }
    } catch (char *str) {
        std::cerr << str << std::endl;
        return 0;
    }

    return 1;
}
