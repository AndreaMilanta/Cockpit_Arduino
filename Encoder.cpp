#include "Encoder.h"

// pushedTime is time in second for which pushed lasts, round iff when overflows goes back to min and viceversa
Encoder::Encoder(ChanId chan, uint8_t pinA, uint8_t pinB, uint8_t pinSW, double maxVal, double minVal, double step, double stepPush, uint16_t pushedTime, boolean round)
{
    _round = round;
    _chan.setId(chan);
    _pinA = pinA;
    _pinB = pinB;
    _pinSW = pinSW;
    _maxVal = maxVal > minVal ? maxVal : minVal;
    _minVal = maxVal > minVal ? minVal : maxVal;
    _step = step;
    _stepPush = stepPush;
    _value = (_maxVal + _minVal) / 2;
    _pushedTicks = pushedTime * 1000 / ENCODER_DT;
    //set as input and turn on internal pull-up
    pinMode(_pinA, INPUT_PULLUP);
    pinMode(_pinB, INPUT_PULLUP);
    pinMode(_pinSW, INPUT_PULLUP);
    _valA = digitalRead(_pinA);
    _pushed = false;
}

void Encoder::setValue(double value)
{
    _value = value;
    if (_value < _minVal)
        _value = round ? _maxVal : _minVal;
    if (_value > _maxVal)
        _value = round ? _minVal : _maxVal;
}

void Encoder::setDeltaValue(double delta)
{
    this->setValue(_value + delta);
}

double Encoder::getValue(void)
{
    return _value;
}

// Check if the encoder has moved. If so return true
boolean Encoder::update(void)
{
    boolean hasChanged = false;
    double currStep;
    boolean b = digitalRead(_pinB);
    boolean a = digitalRead(_pinA);
    boolean sw = digitalRead(_pinSW);

    // Handle Switch
    if (!sw) {
        _pushedCounter = _pushedTicks;
        _pushed = true;
    }
    else {
        if (_pushedCounter > 0 && _pushed)
            _pushedCounter--;
        else
            _pushed = false;
    }

    //Handle Encoder
    currStep = _pushed ? _stepPush : _step;
    if (_changedA)
    {
        if (a == _valA && a)
        {
            b ? setDeltaValue(currStep) : setDeltaValue(-currStep);
            hasChanged = true;
        }
        _changedA = false;
    }
    else
    {
        if (a != _valA)
            _changedA = true;
    }
    _valA = a;
    return hasChanged;
}

uint8_t * Encoder::toString()
{
    return _chan.dbl2str(_value);
}

Encoder::~Encoder()
{}
