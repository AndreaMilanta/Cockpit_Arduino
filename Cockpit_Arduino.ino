/*
 Name:		Cockpit_Arduino.ino
 Created:	2/10/2018 9:47:45 PM
 Author:	Andrea
*/

#include "HardwareSerial.h"
#include "TimerOne.h"
#include "SevenSegDisplay.h"
#include "Encoder.h"

#define REFRESH_RATE 10
#define COUNTDOWN_RATE 10

#define COUNTDOWN 999.99L

#define LATCH_PIN 8
#define CLOCK_PIN 12
#define DATA_PIN 11
#define ENCODER_A 2
#define ENCODER_B 4
#define ENCODER_SW 6

//Counters
volatile int16_t sevSegCounter = 1;
volatile int16_t encCounter = 1;
volatile int16_t countdownCounter = 1;

volatile double value = COUNTDOWN;

SevenSegDisplay disp(DATA_PIN, CLOCK_PIN, LATCH_PIN, 5, CATHODE);
//SevenSegDisplay disp(DATA_PIN, CLOCK_PIN, LATCH_PIN, 3, ANODE);

Encoder enc(ENCODER_A, ENCODER_B, ENCODER_SW, 132.00, 118.00, 1.00, 0.25, 10);

// the setup function runs once when you press reset or power the board
void setup() 
{
    Serial.begin(115200);
    Timer1.initialize(1000);        // 1ms timer interrupt
    Timer1.attachInterrupt(onTimer1Interrupt);
    disp.writeDouble(enc.getValue(), 2, false);
//    attachInterrupt(digitalPinToInterrupt(ENCODER_A), onInterrupt0, CHANGE);
}

// the loop function runs over and over again until power down or reset
void loop() 
{
}

void onTimer1Interrupt()
{
    sevSegCounter--;
    countdownCounter--;
    encCounter--;

    //seven segment code
    if (sevSegCounter <= 0){
        disp.update();
        sevSegCounter = disp.getDt();
    }

    //encoder code
    if (encCounter <= 0) {
        if(enc.update())
            disp.writeDouble(enc.getValue(), 2, false);
        encCounter = ENCODER_DT;
    }

    //countdown code
    if (countdownCounter <= 0) {
        //disp.writeDouble(value, 2, false);
        //disp.writeInt(uint16_t(value), false);
        value -= 0.01L;
        if (value < 0)
            value = COUNTDOWN;
        countdownCounter = COUNTDOWN_RATE;
    }
}

/*
void onInterrupt0() {
    cli();
    enc.update();
    value = enc.getValue();
    sei();
}
//*/
