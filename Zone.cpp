#include	"Zone.h"

boost::shared_array<Zone> Zone::cpZones = boost::shared_array<Zone>();

Zone::Zone(PTZone zone, wxString shortName, wxString description, double minPercent, double maxPercent)
{
    this->zone = zone;
    this->shortName = shortName;
    this->description = description;
    this->minPercent = minPercent;
    this->maxPercent = maxPercent;
}

boost::shared_array<Zone> Zone::GetZoneMap()
{
    if (!cpZones) {
        Zone *zone1 = new Zone[6];
        cpZones = boost::shared_array<Zone>(zone1);
        for (int i=0; i<6; i++) {
            cpZones[i] = gZoneMap[i];
        }
    }
    return cpZones;
}

wxTimeSpan Zone::GetTimeSpan( wxString const & s )
{
    wxString minutes = s.BeforeFirst(':');
    wxString seconds = s.AfterFirst(':').BeforeFirst(' ');
    long m, sec;
    if (!minutes.ToLong(&m) || !seconds.ToLong(&sec)) {
        return wxTimeSpan();
    } else {
        return wxTimeSpan(0,m,sec);
    }
}

wxTimeSpan Zone::GetAveragePace() const
{
    wxTimeSpan avgTime = minPace + maxPace;
    wxLongLong seconds = avgTime.GetSeconds();
    seconds  = (wxLongLong) (seconds.ToDouble()/2.0+0.5);
    avgTime = wxTimeSpan(0,0,seconds);
    return avgTime;
}

void Zone::GetMinSec( wxTimeSpan const &dt, int &minutes, int &seconds )
{
    if ( dt.IsNull() ) {
        minutes = seconds = 0;
        return;
    }
    wxTimeSpan ts = dt;
    wxLongLong ll = ts.GetMinutes();
    long l = ll.ToLong();
    minutes = (int) l;
    ts -= wxTimeSpan(0,minutes);
    ll = ts.GetSeconds();
    l = ll.ToLong();
    seconds = (int) l;
}

wxString Zone::GetTimeString( wxTimeSpan const &dt, PTUnit const &unit )
{
    wxString s;
    int minutes, seconds;
    Zone::GetMinSec( dt, minutes, seconds );
    if ( seconds < 10 ) {
        s = wxString::Format("%d:0%d min/%s", minutes, seconds, gUnit[unit]);
    } else {
        s  = wxString::Format("%d:%d min/%s", minutes, seconds, gUnit[unit]);
    }
    return s;
}