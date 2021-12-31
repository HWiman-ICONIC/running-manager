#pragma once
#include	<Defines.h>

class Converter {
public:
    static double Convert( double const &distance, PTUnit const &from, PTUnit const &to );
    static double GetKmPerMile();
    static void Convert( ESpeedType const &from, ESpeedType const &to, int const &val1, int const &val2, int &outVal1, int &outVal2 );
    static wxTimeSpan GetTime(double const &distance, wxTimeSpan const &pace, ESpeedType type);
};