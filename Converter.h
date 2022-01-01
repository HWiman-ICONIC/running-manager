#pragma once
#include	<Defines.h>

/**
 * @brief Unit converter
*/
class Converter {
public:
    /**
     * @brief Convert from one distance to another
     * @param distance Distance in \c from unit
     * @param from From unit
     * @param to To unit
     * @return distance in \c to unit
    */
    static double Convert( double const &distance, PTUnit const &from, PTUnit const &to );

    /**
     * @brief Constant for converting km <-> miles
     * @return Constant for converting km <-> miles
    */
    static double GetKmPerMile();

    /**
     * @brief Convert from ne speed to another
     * @param from From this speed unit
     * @param to To this speed unit
     * @param val1 Input 1
     * @param val2 Input 2
     * @param outVal1 Output 1
     * @param outVal2 Output 2
    */
    static void Convert( ESpeedType const &from, ESpeedType const &to, int const &val1, int const &val2, int &outVal1, int &outVal2 );

    /**
     * @brief Get time duration of a specified distance, pace and speed type
     * @param distance Distance
     * @param pace Pace
     * @param type Speec unit
     * @return Time duration
    */
    static wxTimeSpan GetTime(double const &distance, wxTimeSpan const &pace, ESpeedType type);
};