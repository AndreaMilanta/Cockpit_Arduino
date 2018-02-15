#pragma once
#include <Arduino.h>

#define MINIMUM_DELTA_TIME 100  // minimu duration between two consecutive interrupts

class Encoder
{
private:
    uint8_t _pinA, _pinB;
    int16_t _maxVal, _minVal;
    volatile int16_t _value;
    uint16_t _step;
    volatile uint32_t _time;

public:
    Encoder(uint8_t pinA, uint8_t pinB, int16_t maxVal, int16_t minVal, uint16_t step);
    void setValue(int16_t value);
    void setDeltaValue(int16_t delta);
    int16_t getValue(void);
    void update(void);
    ~Encoder();
};

