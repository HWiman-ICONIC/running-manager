#include	"Week.h"
#include	<wx/log.h>

wxString Week::ToString()
{
    return wxString::Format(_("Week %d"), number);
}

wxString Week::GetPhaseString() const
{
    return wxString::Format(_("%s phase"), gPhase[cPhase]);
}

bool Week::SetPhase( wxString const &sPhase )
{
    if (sPhase.at(0) == 'B') {
        cPhase = PTP_BASE;
    } else if (sPhase.at(0) == 'P') {
        cPhase = PTP_PEAK;
    } else if (sPhase.at(0) == 'T') {
        cPhase = PTP_TAPER;
    } else {
        wxLogError(_("Could not parse week phase: %s"), sPhase);
        return false;
    }
    return true;
}

void Week::GetTime( wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgTime )
{
    minTime = maxTime = avgTime = wxTimeSpan();
    wxTimeSpan min1, max1, avg1;
    std::list<Training>::iterator it, e;
    for (it=training.begin(); it!=training.end(); it++) {
        Training &t = *it;
        t.GetTime( min1, max1, avg1 );
        minTime += min1;
        maxTime += max1;
        avgTime += avg1;
    }
}

void Week::GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit )
{
    minDist = maxDist = avgDist = 0.0;
    double min1, max1, avg1;
    std::list<Training>::iterator it, e;
    for (it=training.begin(); it!=training.end(); it++) {
        Training &t = *it;
        t.GetDistance( min1, max1, avg1, unit );
        minDist += min1;
        maxDist += max1;
        avgDist += avg1;
    }
}
