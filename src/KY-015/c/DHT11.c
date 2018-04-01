/*
 * DHT11
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

#define MAXTIMINGS 85
#define DHTPIN 29

void read_dht11_dat(){
    // pull pin down for 18 milliseconds
    pinMode(DHTPIN, OUTPUT);
    digitalWrite(DHTPIN, LOW);
    delay(18);

    // then pull it up for 40 microseconds
    digitalWrite(DHTPIN, HIGH);
    delayMicroseconds(40); 

    // prepare to read the pin
    pinMode(DHTPIN, INPUT);

    // detect change and read data
    uint8_t laststate = HIGH;
    int dht11_dat[5] = {0,0,0,0,0};
    uint8_t bit_count = 0;
    uint8_t counter = 0;
    for(int i = 0; i< MAXTIMINGS; i++){
        counter = 0;
        while(digitalRead(DHTPIN) == laststate){
            counter++;
            delayMicroseconds(1);
            if(counter == 255) break;
        }
        laststate = digitalRead(DHTPIN);
        if(counter == 255) break;

        // ignore first 3 transitions
        if((i >= 4) && (i % 2 == 0)){
            // shove each bit into the storage bytes
            dht11_dat[bit_count/8] <<= 1;
            if(counter > 50){
                dht11_dat[bit_count/8] |= 1;
            }
            bit_count++;
        }
    }

    // check we read 40 bits (8bit x 5 ) && verify checksum in the last byte
    // print it out if data is good
    if((bit_count >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF))) {
        printf("Humidity = %d.%d %%, Temperature = %d.%d C\n", 
                dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3]);
    } else {
        //printf("Data not good, skip. bit_count = %d\n",bit_count);
    }
}

int main(){
    if(wiringPiSetup() == -1){
        exit (1);
    }

    while(1){
        read_dht11_dat();
        delay(500);
    }

    return 0 ;
}
