#include "Style.h"

Style::Style() {
    this->start = 0;
    this->end = 0;
}

int Style::getStart()
{
    return this->start;
}

int Style::getEnd()
{
    return this->end;
}

char Style::getType()
{
    return this->type;
}

void Style::setStart(int start)
{
    this->start = start;
}

void Style::setEnd(int end)
{
    this->end = end;
}

void Style::setType(int type)
{
    this->type = type;
}
