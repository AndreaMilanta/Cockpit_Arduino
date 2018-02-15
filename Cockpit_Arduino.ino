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

volatile int16_t sevSegCounter = 0;
volatile int16_t countdownCounter = COUNTDOWN_RATE;
volatile double value = COUNTDOWN;

SevenSegDisplay disp(DATA_PIN, CLOCK_PIN, LATCH_PIN, 5, CATHODE);
//SevenSegDisplay disp(DATA_PIN, CLOCK_PIN, LATCH_PIN, 3, ANODE);

//Encoder enc(ENCODER_A, ENCODER_B, 200, -200, -1);

// the setup function runs once when you press reset or power the board
void setup() 
{
    Serial.begin(115200);
    Timer1.initialize(1000);        // 1ms timer interrupt
    Timer1.attachInterrupt(onTimer1Interrupt);
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

    //seven segment code
    if (sevSegCounter <= 0){
        disp.update();
        sevSegCounter = disp.getDt();
    }

    //countdown code
    if (countdownCounter <= 0) {
        disp.writeDouble(value, 2, false);
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
