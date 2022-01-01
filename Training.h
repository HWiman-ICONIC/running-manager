#pragma once

#include	<Defines.h>
#include	<wx/datetime.h>

/**
 * @brief A training/activity
*/
struct Training {
    /**
     * @brief Return human readable string
     * @param includeDate Include date in returned string
     * @param unit Unit (km|miles)
     * @return human readable string
    */
    wxString ToString(bool includeDate, PTUnit const &unit);

    /**
     * @brief Get min, max and average time for this activity
     * @param minTime Min
     * @param maxTime Max
     * @param avgSpan Average
    */
    void GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgSpan );

    /**
     * @brief Get min, max and average distance for this activity
     * @param minDist Min
     * @param maxDist Max
     * @param avgDist Average
     * @param unit km|miles
    */
    void GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit );

    /**
     * @brief Helper for sorting activities by date
     * @param a First
     * @param b Second
     * @return First is before second
    */
    static bool compareDate(const Training& a, const Training& b);

    PTTrainingType type;
    int intensity;
    wxDateTime date;
};