#include "Channel.h"



Channel::Channel()
{
}

Channel::Channel(ChanId id)
{
    this->setId(id);
}

void Channel::setId(ChanId id)
{
    _id = id;
}

uint8_t * Channel::dbl2str(double v)
{
    str[0] = SEP_CHAR;
    str[1] = uint8_t(_id);
    str[2] = uint8_t(v);
    str[3] = uint8_t((v - int16_t(v)) * 100);
    str[4] = END_CHAR;
    return str;
}

uint8_t* Channel::int2str(int16_t v)
{
    str[0] = SEP_CHAR;
    str[1] = uint8_t(_id);
    str[2] = uint8_t(v >> 8);
    str[3] = uint8_t(v);
    str[4] = END_CHAR;
    return str;
}

uint8_t * Channel::bit2str(uint16_t v, uint8_t numSig)
{
    str[0] = SEP_CHAR;
    str[1] = uint8_t(_id);
    str[2] = uint8_t(v >> 8);
    str[3] = uint8_t(v);
    str[4] = END_CHAR;
    return str;
}

Channel::~Channel()
{
}
