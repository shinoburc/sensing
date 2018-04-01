/*
 * RGB 3 Color
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

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

void setup();
void release();
void lighting_on(int pin);
void lighting_off(int pin);
void lighting(int pin, int delay_millisecond);
void flashing(int times, int delay_millisecond);

void setup(){
    if(wiringPiSetup() == -1){
        exit (1);
    }
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}

void release(){
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
}

void lighting_on(int pin){
    digitalWrite(pin, HIGH);
    digitalWrite(pin, 1);
}

void lighting_off(int pin){
    digitalWrite(pin, LOW);
}

void lighting(int pin, int delay_millisecond){
    lighting_on(pin);
    delay(delay_millisecond);
    lighting_off(pin);
}

void flashing(int times, int delay_millisecond){
    for(int i = 0; i < times; i++) {
        lighting(RED_PIN, delay_millisecond);
        lighting(GREEN_PIN, delay_millisecond);
        lighting(BLUE_PIN, delay_millisecond);
    }
}

int main(){
    setup();

    flashing(10, 100);

    lighting(RED_PIN, 2000);
    lighting(GREEN_PIN, 2000);
    lighting(BLUE_PIN, 2000);

    release();

    return 0 ;
}
