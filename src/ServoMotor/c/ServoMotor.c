/*
 * ServoMotor
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

/*
 * ServoMotor
 * PIN: IN1
 */
#define GPIO_PIN 1

void setup();
void release();
void rotate(const double angle, const int delay);

void setup(){
    if(wiringPiSetup() == -1){
        exit (1);
    }
    pinMode(GPIO_PIN, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(50);
    //pwmSetRange(1024);
    release();
    delayMicroseconds(10);
}

void release(){
    digitalWrite(GPIO_PIN, LOW);
}

void rotate(const double angle, const int delay){
    pwmWrite(GPIO_PIN, 12);
}

int main(){
    setup();

    rotate(90, 10);

    release();

    return 0 ;
}
