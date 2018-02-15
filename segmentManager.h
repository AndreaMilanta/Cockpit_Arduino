/*
Created:	2/11/2018 3:00:450 PM
Author:	    Andrea
Description: Manages segment syntax
*/
#pragma once

#include <Arduino.h>

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

// get byte from one digit -- value needs to be between 0 and 15(F)
byte digitToByte(int value, COMMON common, boolean comma);

// get byteArray value from int -- data size is not checked
void intToByteArray(byte data[], int value, int num_digit, COMMON common, boolean fill);
