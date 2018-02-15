#pragma once
#include <Arduino.h>

#define SEVEN_SEG_UPDATE_RATE 15
#define MAX_DIGIT 5

enum COMMON {
    CATHODE,
    ANODE
};

enum DIGIT {
    ZERO = 0xFC,
    ONE = 0x60,
    TWO = 0xDA,
    THREE = 0xF2,
    FOUR = 0x66,
    FIVE = 0xB6,
    SIX = 0xBE,
    SEVEN = 0xE0,
    EIGHT = 0xFE,
    NINE = 0xF6,
    A = 0xEE,
    B = 0x3E,
    C = 0x9C,
    D = 0x7A,
    E = 0x9E,
    F = 0x8E,
    MINUS = 0x02,       // '-' char 
    OFF = 0x00
};

class SevenSegDisplay
{
private:
    uint8_t _dataPin, _clockPin, _latchPin, _digitNum;
    volatile uint8_t _currDigit = 0;
    uint16_t _dt;
    volatile byte digits;
    volatile byte data[MAX_DIGIT];
    COMMON _comm;
    static byte digitToByte(int value, COMMON common, boolean comma);

public:
    SevenSegDisplay(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t digitNum, COMMON comm);
    void update(void);
    void writeInt(int16_t value, boolean fill);
    void writeDouble(double value, uint8_t decLen, boolean fill);
    ~SevenSegDisplay();

    // used for comparison in timer1 interrupt
    inline uint16_t SevenSegDisplay::getDt()
    {
        return _dt;
    }
};

