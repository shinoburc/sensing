#include <stdio.h>
#include <time.h>
#include <wiringPi.h>
#include "rotaryencoder.h"

#define GPIO_PIN_CLK 0
#define GPIO_PIN_DT  2
#define GPIO_PIN_SW  3

int main(int argc, char *argv[]){

  long lastValue = -1;

  /* 0.1 second */
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 100000000;

  wiringPiSetup();

  struct encoder *encoder = setupencoder(GPIO_PIN_CLK, GPIO_PIN_DT);
  while(1){
    long value = encoder->value;
    if(lastValue !=  value){
      lastValue = value;
      printf("Encoder value is: %ld\n", value);
    }
    nanosleep(&ts, NULL);
  }
}
