#pragma once

#include	<wx/grid.h>
#include	<wx/datetime.h>
#include	<vector>
#include	<Defines.h>
#include	<Zone.h>

/**
 * @brief GUI for zones.
 * @sa Zone
*/
class ZoneGrid : public wxGrid {
public:

    ZoneGrid(wxWindow *pParent);
    void OnGridCellChanging( wxGridEvent &e );

    bool UpdatePulse( int const &pulse );

    bool UpdatePace(PTUnit const &unit);

    bool UpdatePace( wxTimeSpan const &pace, bool isMin, int zoneLevel, PTUnit const &unit );

    //std::vector<Zone> *pZoneMap;

    //std::vector<wxTimeSpan> minPace;
    //std::vector<wxTimeSpan> maxPace;

    DECLARE_EVENT_TABLE()
};