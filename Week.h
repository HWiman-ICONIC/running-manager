#pragma once

#include	<list>
#include	<wx/string.h>
#include	"Training.h"

struct Week {
    Week() {
    }
    wxString ToString();

    wxString GetPhaseString() const;

    bool SetPhase( wxString const &sPhase );

    void GetTime( wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgSpan );

    void GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit );

    int number;
    PTPhase cPhase;
    std::list<Training> training;
};