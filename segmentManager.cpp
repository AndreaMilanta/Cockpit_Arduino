#include "segmentManager.h"

byte digitToByte(int value, COMMON common, boolean comma)
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

void intToByteArray(byte data[], int value, int num_digit, COMMON common, boolean fill)
{
    boolean neg = (value < 0);
    int minus = 0;
    value = neg ? value * -1 : value;
    if (neg && fill) {
        data[0] = digitToByte(-1, common, false);
        minus++;
        neg = false;
    }
    for (int i = 1; i <= num_digit - minus; i++) 
    {
        int v = value % 10;
        if (value == 0) {
            if (neg) {
                v = -1;
                neg = false;
            }
            else {
                if (fill || i == 1)
                    v = 0;
                else
                    v = 100;                // Invalid value -> empty digit
            }
        }
        data[num_digit - i] = digitToByte(v, common, false);
        value /= 10;
    }
}
