/*
 * StepperMotor
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

/*
 * StepperMotor
 * PIN: IN1 IN2 IN3 IN4
 */
#define IN1_PIN 25
#define IN2_PIN 24
#define IN3_PIN 23
#define IN4_PIN  0

//2-2相励磁
int gpioSequence[8] = {0b01000, 0b01100, 0b00100, 0b00110, 0b00010, 0b00011, 0b00001, 0b01001};
//1-1相励磁
//int gpioSequence[4] = {0b01000, 0b00100, 0b00010, 0b00001};

enum Direction {
  Clockwise,
  AntiClockwise
};

void setup();
void release();
void rotate(const double angle, enum Direction direction, const int delay);
void outputGpio(int step);

void setup(){
    if(wiringPiSetup() == -1){
        exit (1);
    }
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);
    pinMode(IN3_PIN, OUTPUT);
    pinMode(IN4_PIN, OUTPUT);
    release();
    delayMicroseconds(10);
}

void release(){
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);
}

void rotate(const double angle, enum Direction direction, const int delay){
    int gpioSequenceLength = sizeof(gpioSequence) / sizeof(int);
    // 512 steps loop = 1 rotation
    int outputSteps = (angle / 360) * 512;
    for(int i = 0; i < outputSteps; i++){
        if(direction == Clockwise){
            for(int i = gpioSequenceLength - 1; i >= 0; i--) {
                outputGpio(i);
            }
        } else {
            for(int i = 0; i < gpioSequenceLength; i++) {
                outputGpio(i);
            }
        }
        delayMicroseconds(delay);
    }
}

void outputGpio(int step){
    int delay = 200 + (100 * (8 - (sizeof(gpioSequence) / sizeof(int))));
    digitalWrite(IN1_PIN, ((gpioSequence[step] & 0b1000) == 0b1000) ? HIGH : LOW); delayMicroseconds(delay);
    digitalWrite(IN2_PIN, ((gpioSequence[step] & 0b0100) == 0b0100) ? HIGH : LOW); delayMicroseconds(delay);
    digitalWrite(IN3_PIN, ((gpioSequence[step] & 0b0010) == 0b0010) ? HIGH : LOW); delayMicroseconds(delay);
    digitalWrite(IN4_PIN, ((gpioSequence[step] & 0b0001) == 0b0001) ? HIGH : LOW); delayMicroseconds(delay);
}

int main(){
    setup();

    rotate(90, Clockwise, 10);
    rotate(90, AntiClockwise, 10);

    release();

    return 0 ;
}
