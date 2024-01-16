#pragma once
#include "Utility.h"

class Interval
{
public:
    double min, max;
    Interval() : min(+infinity), max(-infinity) {} //Default interval is empty
    Interval(double pMin, double pMax) : min(pMin), max(pMax) {}

    bool Contains(double x) const
    {
        return min <= x && x <= max;
    }

    bool Surrounds(double x) const
    {
        return min < x && x < max;
    }

    double Clamp(double x) const
    {
        return x < min ? min : x > max ? max : x;
    }


    static const Interval Empty, Universe;
};

const static Interval Empty(+infinity, -infinity);
const static Interval Universe(-infinity, +infinity);
