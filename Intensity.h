#pragma once

#include	<Defines.h>
#include	<Section.h>
#include	<boost/shared_ptr.hpp>
#include	<wx/string.h>
#include	<list>

/**
 * @brief An Intensity is a specific intensity of a TrainingType.
 *
 * Each TrainingType contains a number of different intensities.
 * Each intensity contains a number of sections, e.g. warm up, foundation and cool down.
 * @sa Section TrainingType
*/
struct Intensity {
    /**
     * @brief Constructor
     * @param intensity Intensity number. Higher numbers are more intensive.
    */
    Intensity( int intensity );

    /**
     * @brief Destructor
    */
    virtual ~Intensity();

    /**
     * @brief Returns string with human readable intenisty information
     * @param outUnit Unit of output string
     * @return string with human readable intenisty information
    */
    virtual wxString ToString(PTUnit const &outUnit);

    /**
     * @brief Get min, max and average total times for this intensity.
     *
     * For long runs, this requires that pace is registered.
     * @param minTime Min time
     * @param maxTime Max time
     * @param avgSpan Average time
    */
    void GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgSpan );

    /**
     * @brief Get min, max and average distances for this intensity.
     *
     * For all training types except long runs, this requires that pace is registered.
     * @param minDist Min distance
     * @param maxDist Max distance
     * @param avgDist Average distance
     * @param unit Unit of output distance
    */
    void GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit );

    int intensity;
    std::list<SectionPtr> section;

};

typedef boost::shared_ptr<Intensity> IntensityPtr;