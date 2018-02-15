#include "Encoder.h"

Encoder::Encoder(uint8_t pinA, uint8_t pinB, int16_t maxVal, int16_t minVal, uint16_t step)
{
    _pinA = pinA;
    _pinB = pinB;
    _maxVal = maxVal > minVal ? maxVal : minVal;
    _minVal = maxVal > minVal ? minVal : maxVal;
    _step = step;
    _value = (_maxVal + _minVal) / 2;
    pinMode(_pinA, INPUT);
    pinMode(_pinB, INPUT);
    // turn on internal pull-up
    digitalWrite(_pinA, HIGH);
    digitalWrite(_pinB, HIGH);
    _time = millis();
}

void Encoder::setValue(int16_t value)
{
    _value = value < _minVal ? _minVal : value;
    _value = value > _maxVal ? _maxVal : _value;
}

void Encoder::setDeltaValue(int16_t delta)
{
    this->setValue(_value + delta);
}

int16_t Encoder::getValue(void)
{
    return _value;
}

void Encoder::update(void)
{
    boolean b = digitalRead(_pinB);
    boolean a = digitalRead(_pinA);
    uint32_t t_time = millis();
    if (t_time - _time < MINIMUM_DELTA_TIME)
        return;
    _time = t_time;
    if (a) 
        b ? setDeltaValue(_step) : setDeltaValue(-_step);
    else
        b ? setDeltaValue(-_step) : setDeltaValue(_step);
}

Encoder::~Encoder()
{}
