#pragma once

#include	<list>
#include	<wx/string.h>
#include	<Training.h>

/**
 * @brief  A training week
 *
 * Contains a number of Traning instances or activities
*/
struct Week {
    /**
     * @brief Constructor
    */
    Week();

    /**
     * @brief Return human readable string
     * @return human readable string
    */
    wxString ToString();

    /**
     * @brief Get which phase this week is in
     * @return
    */
    wxString GetPhaseString() const;

    /**
     * @brief Set phase for this week
     * @param sPhase
     * @return
    */
    bool SetPhase( wxString const &sPhase );

    /**
     * @brief  Get total min, max and average time fro this week
     * @param minTime Min
     * @param maxTime Max
     * @param avgSpan Average
    */
    void GetTime( wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgSpan );

    /**
     * @brief Get total min, max and average distance for this week
     * @param minDist Min
     * @param maxDist Max
     * @param avgDist Average
     * @param unit km|miles
    */
    void GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit );

    /**
     * @brief Sort week based on training dates
    */
    void Sort();

    int number;
    PTPhase cPhase;
    std::list<Training> training;
};