#include	"Intensity.h"

Intensity::Intensity( int intensity ) :
    intensity(intensity)
{
}

Intensity::~Intensity()
{
    section.clear();
}

wxString Intensity::ToString(PTUnit const &outUnit)
{
    wxString s;
    s = wxString::Format("%d", intensity);
    std::list<SectionPtr>::iterator it = section.begin();
    while (it!=section.end()) {
        if (it==section.begin()) {
            s += wxString(": ");
        }
        s += (*it)->ToString(outUnit);
        it++;
        if (it!=section.end()) {
            s += wxString(", ");
        }
    }
    return s;
}

void Intensity::GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgTime )
{
    wxTimeSpan minTime1, maxTime1, avgTime1;
    minTime = maxTime = avgTime = wxTimeSpan();
    std::list<SectionPtr>::iterator it = section.begin();
    while (it != section.end()) {
        minTime1 = maxTime1 = avgTime1 = wxTimeSpan();
        (*it)->GetTime( minTime1, maxTime1, avgTime1 );
        minTime += minTime1;
        maxTime += maxTime1;
        avgTime += avgTime1;
        it++;
    }
}

void Intensity::GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit )
{
    double minDist1, maxDist1, avgDist1;
    minDist = maxDist = avgDist = 0.0;
    std::list<SectionPtr>::iterator it = section.begin();
    while (it != section.end()) {
        (*it)->GetDistance( minDist1, maxDist1, avgDist1, unit );
        minDist += minDist1;
        maxDist += maxDist1;
        avgDist += avgDist1;
        it++;
    }
}