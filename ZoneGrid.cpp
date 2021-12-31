#include	"ZoneGrid.h"
#include	"Defines.h"
#include	"Zone.h"
#include	<wx/log.h>

BEGIN_EVENT_TABLE(ZoneGrid, wxGrid)
    EVT_GRID_CELL_CHANGED(ZoneGrid::OnGridCellChanging)
END_EVENT_TABLE()

ZoneGrid::ZoneGrid(wxWindow *pParent) :
    wxGrid(pParent, wxID_ANY)
{
    SetName("ZoneGrid");
    CreateGrid(6,5);
    SetColLabelValue(0,_("Description"));
    SetColLabelValue(1,_("Min pulse"));
    SetColLabelValue(2,_("Max pulse"));
    SetColLabelValue(3,_("Min pace"));
    SetColLabelValue(4,_("Max pace"));
    EnableCellEditControl(false);

    boost::shared_array<Zone> vZoneMap = Zone::GetZoneMap();
    for (int i=0; i<6; i++) {
        SetRowLabelValue(i,vZoneMap[i].shortName);
        SetCellValue(i,0,vZoneMap[i].description);

        if (i==0) {
            SetCellValue(i,3,"0:00 min/km");
            SetCellBackgroundColour(i,3,gIntensityColor[gZoneIntensity[i]]);
            SetCellValue(i,4,"0:00 min/km");
            SetCellBackgroundColour(i,4,gIntensityColor[gZoneIntensity[i]]);
        } else {
            SetCellValue(i,3,"m:ss min/km");
            SetCellBackgroundColour(i,3,wxColour(200,200,200));
            SetCellValue(i,4,"m:ss min/km");
            SetCellBackgroundColour(i,4,wxColour(200,200,200));
        }

        for (int j=0; j<3; j++) {
            SetCellBackgroundColour(i,j,gIntensityColor[gZoneIntensity[i]]);
        }
    }
}


void ZoneGrid::OnGridCellChanging( wxGridEvent &e )
{
    int col = e.GetCol();
    int row = e.GetRow();
    wxString oldString = e.GetString();
    wxString newString = GetCellValue(row,col);
    boost::shared_array<Zone> vZoneMap = Zone::GetZoneMap();
    wxTimeSpan ts = vZoneMap[row].GetTimeSpan( newString );
    if (ts.IsNull()) {
        wxLogWarning(_("Could not parse time %s.\nEnter M:SS where M=minutes, SS=0..59 seconds."), newString);
        SetCellValue(row, col, oldString);
    } else {
        if (col == 3) {
            vZoneMap[row].minPace = ts;
            SetCellBackgroundColour(row,col,gIntensityColor[gZoneIntensity[row]]);
        } else if (col == 4) {
            vZoneMap[row].maxPace = ts;
            SetCellBackgroundColour(row,col,gIntensityColor[gZoneIntensity[row]]);
        }
    }
}

bool ZoneGrid::UpdatePulse( int const &pulse )
{
    for (int i=0; i<6; i++) {
        int minPulse = (int)((pulse*gZoneMap[i].minPercent)/100.0+0.5);
        int maxPulse = (int)((pulse*gZoneMap[i].maxPercent)/100.0+0.5);
        SetCellValue(i,1,wxString::Format("%d (%.0lf%%)",minPulse, gZoneMap[i].minPercent));
        SetCellValue(i,2,wxString::Format("%d (%.0lf%%)",maxPulse, gZoneMap[i].maxPercent));
    }
    return true;
}

bool ZoneGrid::UpdatePace( wxTimeSpan const &pace, bool isMin, int zoneLevel, PTUnit const &unit )
{
    int col = isMin ? 3 : 4;
    int row = zoneLevel;
    wxString s;
    if (pace.IsNull()) {
        s = wxString::Format("m:ss min/%s", gUnit[unit]);
        SetCellBackgroundColour(row,col,wxColour(200,200,200));
    } else {
        s = Zone::GetTimeString( pace, unit );
        SetCellBackgroundColour(row,col,gIntensityColor[gZoneIntensity[row]]);
    }
    SetCellValue(row,col,s);
    boost::shared_array<Zone> vZoneMap = Zone::GetZoneMap();
    if (isMin) {
        vZoneMap[row].minPace = pace;
    } else {
        vZoneMap[row].maxPace = pace;
    }
    return true;
}

bool ZoneGrid::UpdatePace( PTUnit const &unit )
{
    boost::shared_array<Zone> vZoneMap = Zone::GetZoneMap();
    for (int i=0; i<6; i++) {
        wxTimeSpan &time = vZoneMap[i].minPace;
        if (!time.IsNull()) {
            wxString s = Zone::GetTimeString( time, unit );
            SetCellValue(i,3,s);
            SetCellBackgroundColour(i,3,gIntensityColor[gZoneIntensity[i]]);
        } else {
            SetCellValue(i,3,"0:00 min/km");
            SetCellBackgroundColour(i,3,wxColour(200,200,200));
        }
        wxTimeSpan &time2 = vZoneMap[i].maxPace;
        if (!time2.IsNull()) {
            int minutes, seconds;
            Zone::GetMinSec( time, minutes, seconds );
            wxString s = wxString::Format("%d:%d min/%s", minutes, seconds, gUnit[unit]);
            SetCellValue(i,4,s);
            SetCellBackgroundColour(i,4,gIntensityColor[gZoneIntensity[i]]);
        } else {
            SetCellValue(i,3,"0:00 min/km");
            SetCellBackgroundColour(i,4,wxColour(200,200,200));
        }
    }
    return true;
}