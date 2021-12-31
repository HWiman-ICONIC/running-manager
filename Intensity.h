#pragma once

#include	<Defines.h>
#include	<Section.h>
#include	<boost/shared_ptr.hpp>
#include	<wx/string.h>
#include	<list>

struct Intensity {
    Intensity( int intensity );

    virtual ~Intensity();
    virtual wxString ToString(PTUnit const &outUnit);

    int intensity;
    std::list<SectionPtr> section;

    void GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgSpan );
    void GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit );
};

typedef boost::shared_ptr<Intensity> IntensityPtr;