#pragma once

#include	"Defines.h"
#include	<wx/datetime.h>

struct Training {
    PTTrainingType type;
    int intensity;
    wxDateTime date;
    wxString ToString(bool includeDate, PTUnit const &unit);
    void GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgSpan );
    void GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit );
};