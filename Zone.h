#pragma once

#include	"Defines.h"
#include	<boost/shared_array.hpp>

struct Zone {
    Zone() {}
    Zone(PTZone zone, wxString shortName, wxString description, double minPercent, double maxPercent);

    PTZone zone;
    wxString shortName;
    wxString description;
    double minPercent;
    double maxPercent;
    wxTimeSpan minPace;
    wxTimeSpan maxPace;

    wxTimeSpan GetAveragePace() const;
    wxTimeSpan GetTimeSpan( wxString const & s );
    static void GetMinSec( wxTimeSpan const &dt, int &minutes, int &seconds );
    static wxString GetTimeString( wxTimeSpan const &dt, PTUnit const &unit );
    static boost::shared_array<Zone> GetZoneMap();
    static boost::shared_array<Zone> cpZones;

};

static Zone gZoneMap[] = {
    Zone(ZONE0, _("Zone 0"), _("Rest"), 0, 75),
    Zone(ZONE1, _("Zone 1"), _("Really slow. You  really hold yourself back."), 75, 80),
    Zone(ZONE2, _("Zone 2"), _("Slow. You hold back a little and do not push yourself."), 81, 89),
    Zone(ZONE3, _("Zone 3"), _("Medium Hard. You could hold this pace in 20-30 min (less trained) or 50-60 min (well trained)."), 96, 100),
    Zone(ZONE4, _("Zone 4"), _("Hard. You could hold this pace for 10 min (less trained) or 15 min (well trained)."), 102, 105),
    Zone(ZONE5, _("Zone 5"), _("Very hard. You can only hold this pace for one or two minutes, maybe less."), 106, 130)
};