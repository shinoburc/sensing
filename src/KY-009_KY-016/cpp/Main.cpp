/**
 * @file Main.cpp
 * @brief main関数を定義している
 *
 * @par RGB 3 Color Program
 *        
 */

#include<iostream>
#include"RGB3Color.h"

/* 
 * KY-009: 3 color LED module(SMD:Surface Mount Device)
 * PIN: B R G GND
 */
#define BLUE_PIN 23
#define RED_PIN 24
#define GREEN_PIN 25

/* 
 * KY-016: 3 color LED module(COB:Chip On Board)
 * PIN: R G B GND
 */
//#define RED_PIN 23
//#define GREEN_PIN 24
//#define BLUE_PIN 25

/**
 * @brief RGB 3 Color Program
 *
 * @par
 * - RGB 3 Color Program
 * 
 * @param argc : 引数の数
 * @param argv : 引数の値の配列
 * @return 実行ステータス
 */
int main(int argc, char** argv) {

    try {
        RGB3Color module(RED_PIN, GREEN_PIN, BLUE_PIN);
        module.flashing(10, 100);
        module.lighting(RED_PIN, 2000);
        module.lighting(GREEN_PIN, 2000);
        module.lighting(BLUE_PIN, 2000);
    }  catch (char *str) {
        std::cerr << str << std::endl;
        return 0;
    }

    return 1;
}
