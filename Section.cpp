#include	<Section.h>
#include	<Zone.h>
#include	<Converter.h>
#include	<wx/log.h>

wxString SectionTime::ToString(PTUnit const &WXUNUSED(outUnit), bool bZone, bool bTime)
{
    wxString s;
    wxString formatString;
    if (time.GetHours() > 0) {
        formatString = wxString(_("%H hours"));
    }
    int minutes = time.GetMinutes();
    if (minutes > 0) {
        if ( formatString.Length() > 0 ) {
            formatString += wxString(" ");
        }
        formatString += wxString(_("%M minutes"));
    }
    wxLongLong sec = time.GetSeconds();
    if (sec != 60*minutes) {
        if ( formatString.Length() > 0 ) {
            formatString += wxString(" ");
        }
        formatString += wxString(_("%S seconds"));
    }
    if ( bZone ) {
        if ( bTime ) {
            s = wxString::Format(("%s %s"),time.Format(formatString),gZoneMap[zone].shortName);
        } else {
            s = gZoneMap[zone].shortName;
        }
    } else if ( bTime ) {
        s = time.Format(formatString);
    }

    return s;
}

void SectionTime::GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgTime )
{
    minTime = maxTime = avgTime = this->time;
}

void SectionTime::GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &WXUNUSED(unit) )
{
    Zone &theZone = Zone::GetZoneMap()[this->zone];

    wxLongLong paceSeconds, timeSeconds;
    timeSeconds = time.GetSeconds();

    paceSeconds = theZone.minPace.GetSeconds();
    minDist = timeSeconds.ToDouble() / paceSeconds.ToDouble();

    paceSeconds = theZone.maxPace.GetSeconds();
    maxDist = timeSeconds.ToDouble() / paceSeconds.ToDouble();

    paceSeconds = theZone.maxPace.GetSeconds() + theZone.minPace.GetSeconds();
    avgDist = timeSeconds.ToDouble() / paceSeconds.ToDouble() * 2.0;
}

wxString SectionDistance::ToString(PTUnit const &outUnit, bool bZone, bool bTime)
{
    wxString s;
    if ( bTime ) {
        double outDistance = Converter::Convert(this->distance, this->unit, outUnit);
        if (outDistance > 1.5) {
            s = wxString::Format(("%d %s"), (int)(outDistance+0.5), gUnit[outUnit]);
        } else {
            s = wxString::Format(("%.2lf %s"), outDistance, gUnit[outUnit]);
        }
        if ( bZone ) {
            s += wxString(" ") + gZoneMap[zone].shortName;
        }
    } else if ( bZone ) {
        s = gZoneMap[zone].shortName;
    }
    return s;
}

void SectionDistance::GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgTime )
{
    minTime= maxTime = avgTime = wxTimeSpan();

    Zone &theZone = Zone::GetZoneMap()[this->zone];

    double dist = Converter::Convert(this->distance, MILES, KM);

    wxLongLong seconds;
    seconds = theZone.maxPace.GetSeconds();
    seconds = (wxLongLong) (seconds.ToDouble()*dist+0.5);
    minTime = wxTimeSpan(0,0,seconds);

    seconds = theZone.minPace.GetSeconds();
    seconds = (wxLongLong) (seconds.ToDouble()*dist+0.5);
    maxTime = wxTimeSpan(0,0,seconds);

    avgTime = theZone.minPace + theZone.maxPace;
    seconds = avgTime.GetSeconds();
    seconds  = (wxLongLong) (seconds.ToDouble()*dist/2.0+0.5);
    avgTime = wxTimeSpan(0,0,seconds);
}

void SectionDistance::GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit )
{
    minDist = maxDist = avgDist = Converter::Convert(this->distance, this->unit, unit );
}

SectionPtr SectionBase::Create( PTZone zone, wxTimeSpan time )
{
    return SectionPtr( new SectionTime( zone, time ) );
}

SectionPtr SectionBase::Create( PTZone zone, double distance, PTUnit unit )
{
    switch ( unit ) {
    case TIME: {
        int min = (int) distance;
        double dsec = distance - min;
        int sec = (int) (60*dsec+0.5);
        return SectionBase::Create( zone, wxTimeSpan(0,min, sec));
    }
    break;

    default:
        return SectionPtr( new SectionDistance( zone, distance, unit) );
    }
}

SectionPtr SectionBase::Create( PTZone zone, int nRepetitions )
{
    return SectionPtr( new SectionGroup( zone, nRepetitions ) );
}

void SectionBase::Add( SectionPtr pSubSection )
{
    SectionGroup *group = dynamic_cast<SectionGroup*>(this);
    if ( group ) {
        group->subSections.push_back( pSubSection );
    }
}

SectionGroup::SectionGroup( PTZone zone, int nRepetitions ) :
    SectionBase(zone), nRepetitions( nRepetitions )
{

}

wxString SectionGroup::ToString(PTUnit const &outUnit, bool bZone, bool bTime)
{
    wxString s;
    s = wxString::Format(wxString("%d x ("), nRepetitions );
    std::list<SectionPtr>::iterator it = this->subSections.begin();
    while (it != subSections.end()) {
        s += (*it)->ToString(outUnit, bZone, bTime);
        it++;
        if (it!=subSections.end()) {
            if ( bZone && bTime ) {
                s += wxString(", ");
            } else {
                s += wxString("\n");
            }
        }
    }
    s += wxString(wxString(")"));
    return s;
}

void SectionGroup::GetTime(wxTimeSpan &minTime, wxTimeSpan &maxTime, wxTimeSpan &avgTime )
{
    wxTimeSpan minTime1, maxTime1, avgTime1;
    minTime = maxTime = avgTime = wxTimeSpan();
    std::list<SectionPtr>::iterator it = this->subSections.begin();
    while (it != subSections.end()) {
        minTime1 = maxTime1 = avgTime1 = wxTimeSpan();
        (*it)->GetTime( minTime1, maxTime1, avgTime1 );
        minTime += (minTime1*this->nRepetitions);
        maxTime += (maxTime1*this->nRepetitions);
        avgTime += (avgTime1*this->nRepetitions);
        it++;
    }
}

void SectionGroup::GetDistance( double &minDist, double &maxDist, double &avgDist, PTUnit const &unit )
{
    double minDist1, maxDist1, avgDist1;
    minDist = maxDist = avgDist = 0.0;
    std::list<SectionPtr>::iterator it = this->subSections.begin();
    while (it != subSections.end()) {
        (*it)->GetDistance( minDist1, maxDist1, avgDist1, unit );
        minDist += (minDist1*this->nRepetitions);
        maxDist += (maxDist1*this->nRepetitions);
        avgDist += (avgDist1*this->nRepetitions);
        it++;
    }
}

SectionDistance::SectionDistance(PTZone zone, double distance, PTUnit unit) :
    SectionBase(zone)
{
    this->distance = distance;
    this->unit = unit;
}