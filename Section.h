#pragma once

#include	<Defines.h>
#include	<boost/shared_ptr.hpp>
#include	<wx/datetime.h>
#include	<list>

struct SectionBase;
typedef boost::shared_ptr<SectionBase> SectionPtr; //!< Smart pointer to a section

/**
 * @brief Base class for a section.
 *
 * A section is a part of a Training or activity.
*/
struct SectionBase {
    SectionBase( PTZone azone ) : zone(azone) {}
    PTZone zone;
    wxString shortName;
    wxString description;
    std::list<SectionPtr> subSections;
    virtual wxString ToString(PTUnit const &outUnit, bool bZone=true, bool bTime = true) = 0;
    static SectionPtr Create( PTZone zone, wxTimeSpan time );
    static SectionPtr Create( PTZone zone, double distance, PTUnit unit );
    static SectionPtr Create( PTZone, int nRepetitions );
    void Add( SectionPtr pSubSection );
    virtual void GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgSpan ) = 0;
    virtual void GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit ) = 0;
};

/**
 * @brief A collection of sections, e.g. multiple repetitions of interval/pause
*/
struct SectionGroup : public SectionBase {
    SectionGroup( PTZone zone, int nRepetitions );
    virtual wxString ToString(PTUnit const &outUnit, bool bZone=true, bool bTime = true);
    int nRepetitions;
    void GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgSpan );
    void GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit );
};

/**
 * @brief A section defined by a distance
*/
struct SectionDistance : public SectionBase {
    SectionDistance(PTZone zone, double distance, PTUnit unit);

    double distance;
    PTUnit unit;
    virtual wxString ToString(PTUnit const &outUnit, bool bZone=true, bool bTime = true);

    void GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgSpan );
    void GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit );
};

/**
 * @brief A section defined by a time/duration
*/
struct SectionTime : public SectionBase {
    SectionTime(PTZone zone, wxTimeSpan time) :
        SectionBase(zone) {
        this->time = time;
    }
    wxTimeSpan time;
    virtual wxString ToString(PTUnit const &outUnit, bool bZone=true, bool bTime = true);
    void GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgSpan );
    void GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit );
};