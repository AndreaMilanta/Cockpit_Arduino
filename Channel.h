#pragma once
#include <Arduino.h>
#include "ChannelsID.h"

#define BITWISE_ID 'b'
#define INT_ID 'i'
#define FLOAT_ID 'f'
#define SEP_CHAR char(255)//'%'
#define DOT '.'
#define ZERO '0'
#define END_CHAR SEP_CHAR

#define HEADER_LEN 6
#define DEC_LEN 2
#define INT_LEN 3
#define TAIL_LEN 2
#define STR_LEN 5 // HEADER_LEN + DEC_LEN + INT_LEN + TAIL_LEN + 1   // Max length is header + int part + dot + dec part + tail (final char)

class Channel
{
private:
    uint8_t _id;
    uint8_t str[STR_LEN];
public:
    Channel();
    Channel(ChanId id);
    void setId(ChanId id);
    uint8_t * dbl2str(double v);
    uint8_t * int2str(int16_t v);
    uint8_t * bit2str(uint16_t v, uint8_t numSig);
    ~Channel();
};

