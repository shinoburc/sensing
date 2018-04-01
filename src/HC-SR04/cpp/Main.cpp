/**
 * @file Main.cpp
 * @brief main関数を定義している
 *
 * @par HC_SR04 Ultrasonic Ranging Sensor Program
 *        
 */

#include<iostream>
#include<signal.h>
#include<atomic>
#include<cstring>
#include<unistd.h>
#include"HC_SR04.h"

#define TRIG_PIN 22
#define ECHO_PIN 21

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
 * @brief HC_SR04 Ultrasonic Ranging Sensor Program
 *
 * @par
 * - HC_SR04 Ultrasonic Ranging Sensor Program
 * 
 * @param argc : 引数の数
 * @param argv : 引数の値の配列
 * @return 実行ステータス
 */
int main(int argc, char** argv) {
    signalHandling();

    const unsigned int timeout = 30000;
    try {
        HC_SR04 module(TRIG_PIN, ECHO_PIN);
        while(1){
            std::cout << "Distance: " << module.distance(timeout) << " cm." << std::endl;
            sleep(1);
            /* Ctrl-C Handling */
            if( quit.load() ) break;
        }
    }  catch (char *str) {
        std::cerr << str << std::endl;
        return 0;
    }

    return 1;
}
