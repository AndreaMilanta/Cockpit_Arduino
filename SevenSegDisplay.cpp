#include "SevenSegDisplay.h"

byte SevenSegDisplay::digitToByte(int value, COMMON common, boolean comma)
{
    byte digit;
    // int v = value % 16;
    switch (value) {
        case -1:
            digit = byte(MINUS);
            break;
        case 0:
            digit = byte(ZERO);
            break;
        case 1:
            digit = byte(ONE);
            break;
        case 2:
            digit = byte(TWO);
            break;
        case 3:
            digit = byte(THREE);
            break;
        case 4:
            digit = byte(FOUR);
            break;
        case 5:
            digit = byte(FIVE);
            break;
        case 6:
            digit = byte(SIX);
            break;
        case 7:
            digit = byte(SEVEN);
            break;
        case 8:
            digit = byte(EIGHT);
            break;
        case 9:
            digit = byte(NINE);
            break;
        case 0xA:
            digit = byte(A);
            break;
        case 0xB:
            digit = byte(B);
            break;
        case 0xC:
            digit = byte(C);
            break;
        case 0xD:
            digit = byte(D);
            break;
        case 0xE:
            digit = byte(E);
            break;
        case 0xF:
            digit = byte(F);
            break;
        default:
            digit = byte(OFF);
    }
    if (comma)
        digit |= 0x01;      // add comma bit
    if (common == ANODE)
        digit = ~digit;
    return digit;
}

SevenSegDisplay::SevenSegDisplay(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t digitNum, COMMON comm)
{
    _dataPin = dataPin;
    _clockPin = clockPin;
    _latchPin = latchPin;
    _digitNum = digitNum;
    _comm = comm;
    _dt = uint16_t(SEVEN_SEG_UPDATE_RATE / _digitNum);
    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);
    digitalWrite(_latchPin, LOW);
    digitalWrite(_latchPin, HIGH);
}


//To be called on timer1 interrupt
void SevenSegDisplay::update(void)
{
    byte digits = 1 << (7 - _currDigit);
    if (_comm == CATHODE)
        digits = ~digits;
    digitalWrite(_latchPin, LOW);
    shiftOut(_dataPin, _clockPin, LSBFIRST, data[_currDigit]);      // Write segments
    shiftOut(_dataPin, _clockPin, LSBFIRST, digits);       // Open digits
    digitalWrite(_latchPin, HIGH);
    _currDigit++;
    if (_currDigit >= _digitNum)
        _currDigit = 0;
}


void SevenSegDisplay::writeDouble(double value, uint8_t decLen, boolean fill)
{
    boolean neg = (value < 0);      //is negtative
    boolean comma = false;          // write comma?
    int minus = 0;                  //used to balance the '-' as first char 
    value = neg ? value * -1 : value;
    for (int i = 0; i < decLen; i++)
        value *= 10;
    int32_t intValue = int32_t(value);
    // put '-' as first char if is neg and fill is true
    if (neg && fill) {
        data[0] = digitToByte(-1, _comm, false);
        minus++;
        neg = false;
    }
    for (int i = 1; i <= _digitNum - minus; i++) 
    {
        int v = intValue % 10;
        if (intValue == 0 && i > decLen + 1) {   // write '-' as soon as the significamtful digits are done
            if (neg) {
                v = -1;
                neg = false;
            }
            else {
                if (fill) // write '0' if the original value is 0 or to fill
                    v = 0;
                else
                    v = 100;                // Invalid value -> empty digit
            }
        }
        if (i == decLen + 1)
            comma = true;
        data[_digitNum - i] = digitToByte(v, _comm, comma);
        intValue /= 10;
        comma = false;
    }
}

SevenSegDisplay::~SevenSegDisplay()
{
}

void SevenSegDisplay::writeInt(int16_t value, boolean fill)
{
    boolean neg = (value < 0);      //is negtative
    int minus = 0;                  //used to balance the '-' as first char 
    value = neg ? value * -1 : value;
    // put '-' as first char if is neg and fill is true
    if (neg && fill) {
        data[0] = digitToByte(-1, _comm, false);
        minus++;
        neg = false;
    }
    for (int i = 1; i <= _digitNum - minus; i++) 
    {
        int v = value % 10;
        if (value == 0) {   // write '-' as soon as the significamtful digits are done
            if (neg) {
                v = -1;
                neg = false;
            }
            else {
                if (fill || i == 1) // write '0' if the original value is 0 or to fill
                    v = 0;
                else
                    v = 100;                // Invalid value -> empty digit
            }
        }
        data[_digitNum - i] = digitToByte(v, _comm, false);
        value /= 10;
    }
}
