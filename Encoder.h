#pragma once
#include <Arduino.h>
#include "Channel.h"

#define ENCODER_DT 2  // delta t between consecutive pinvalue checks

class Encoder
{
private:
    Channel _chan;
    boolean _round;
    uint8_t _pinA, _pinB, _pinSW;
    uint16_t _pushedTicks;
    volatile uint16_t _pushedCounter;
    double _maxVal, _minVal;
    volatile double _value;
    double _step, _stepPush;
    volatile boolean _changedA, _changedSW, _pushed;
    volatile boolean _valA;

public:
    Encoder(ChanId chan, uint8_t pinA, uint8_t pinB, uint8_t pinSW, double maxVal, double minVal, double step, double stepPush, uint16_t pushedTime, boolean round);
    void setValue(double value);
    void setDeltaValue(double delta);
    double getValue(void);
    boolean update(void);
    uint8_t* toString();
    ~Encoder();
};

