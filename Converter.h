#pragma once
#include	"Defines.h"

class Converter {
public:
    static double Convert( double const &distance, PTUnit const &from, PTUnit const &to );
    static double GetKmPerMile();
};