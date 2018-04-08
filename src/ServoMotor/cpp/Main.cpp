/**
 * @file Main.cpp
 * @brief main関数を定義している
 *
 * @par ServoMotor
 *        
 */

#include<iostream>
#include"ServoMotor.h"

/* 
 * ServoMotor
 * PIN: IN1 IN2 IN3 IN4
 */
#define IN1_PIN 25
#define IN2_PIN 24
#define IN3_PIN 23
#define IN4_PIN  0

/**
 * @brief ServoMotor
 *
 * @par
 * - ServoMotor
 * 
 * @param argc : 引数の数
 * @param argv : 引数の値の配列
 * @return 実行ステータス
 */
int main(int argc, char** argv) {

    try {
        ServoMotor module(IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);
        module.rotate(90, ServoMotorDirection::Clockwise, 10);
        module.rotate(90, ServoMotorDirection::AntiClockwise, 10);
    }  catch (char *str) {
        std::cerr << str << std::endl;
        return 0;
    }

    return 1;
}
