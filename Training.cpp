#include	<Training.h>
#include	<TrainingType.h>

wxString Training::ToString(bool includeDate, PTUnit const &unit)
{
    wxString s;
    if (type >= 0 && type <= KM10 ) {
        TrainingType &t = gTrainingType[type];

        if (includeDate) {
            s = wxString::Format(_("%s: "), date.FormatISODate());
        }
        if (t.intensity.size()) {
            IntensityPtr i = t.intensity[intensity-1];
            s += wxString::Format(_("%s %s"), t.shortName, i->ToString(unit));
        } else {
            s += wxString::Format(_("%s"), t.shortName);
        }
    }
    return s;
}

void Training::GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgTime )
{
    minTime = wxTimeSpan();
    maxTime = wxTimeSpan();
    avgTime = wxTimeSpan();
    if (type >= 0 && type <= KM10 ) {
        TrainingType &t = gTrainingType[type];
        if (t.intensity.size()) {
            IntensityPtr i = t.intensity[intensity-1];
            i->GetTime( minTime, maxTime, avgTime );
        }
    }
}

void Training::GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit )
{
    minDist = maxDist = avgDist = 0.0;
    if (type >= 0 && type <= KM10 ) {
        TrainingType &t = gTrainingType[type];
        if (t.intensity.size()) {
            IntensityPtr i = t.intensity[intensity-1];
            i->GetDistance( minDist, maxDist, avgDist, unit );
        }
    }
}