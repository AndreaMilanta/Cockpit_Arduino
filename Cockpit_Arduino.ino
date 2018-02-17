/*
 Name:		Cockpit_Arduino.ino
 Created:	2/10/2018 9:47:45 PM
 Author:	Andrea
*/

#include "HardwareSerial.h"
#include "TimerOne.h"
#include "SevenSegDisplay.h"
#include "Encoder.h"
#include "ChannelsID.h"

#define REFRESH_RATE 10
#define COUNTDOWN_RATE 10
#define SERIAL_RATE 100

#define COUNTDOWN 999.99L

#define LATCH_PIN 8
#define CLOCK_PIN 12
#define DATA_PIN 11
#define ENCODER_A 2
#define ENCODER_B 4
#define ENCODER_SW 6

enum serialId {
    CHAN,
    MSB,
    LSB
};

//Counters
volatile int16_t sevSegCounter = 1;
volatile int16_t encCounter = 1;
volatile int16_t countdownCounter = 1;
volatile int16_t serialCounter = 1;

volatile double value = COUNTDOWN;

SevenSegDisplay disp(DATA_PIN, CLOCK_PIN, LATCH_PIN, 5, CATHODE);
//SevenSegDisplay disp(DATA_PIN, CLOCK_PIN, LATCH_PIN, 3, ANODE);

Encoder enc(MAIN_RADIO_ACT, ENCODER_A, ENCODER_B, ENCODER_SW, 132.00, 118.00, 1.00, 0.125, 10, true);

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
    serialCounter--;

    //seven segment code
    if (sevSegCounter <= 0){
        disp.update();
        sevSegCounter = disp.getDt();
    }

    //encoder code
    if (encCounter <= 0) {
        if (enc.update()) {
            disp.writeDouble(enc.getValue(), 2, false);
            Serial.write(enc.toString(), STR_LEN);
            Serial.println();
        }
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

    if (serialCounter <= 0){
        byte vals[3];
        if (Serial.available() >= 3) {
            handleSerialInput();
        }
        serialCounter = SERIAL_RATE;
    }
}

void handleSerialInput() 
{
    uint8_t values[3];
    while(true) 
    {
        do
            values[CHAN] = Serial.read();
        while (values[CHAN] == SEP_CHAR);
        values[MSB] = Serial.read();
        if (values[MSB] == SEP_CHAR)
            continue;
        values[LSB] = Serial.read();
        if (values[LSB] == SEP_CHAR)
            continue;
        break;
    }
    switch (values[CHAN]) {
        case MAIN_RADIO_ACT:
            uint8_t decLen = 1;
            uint8_t t = values[LSB];
            while (t > 0) {
                decLen *= 10;
                t /= 10;
            }
            double v = double(values[MSB]);
            v += double(values[LSB]) / decLen;
            enc.setValue(v);
            disp.writeDouble(v, 2, false);
    }
}
