#include	"TrainingProgramGrid.h"
#include	"TrainingType.h"
#include	"RunningManager.h"
#include	"Event.h"

wxBEGIN_EVENT_TABLE(TrainingProgramGrid, wxGrid)
    EVT_GRID_SELECT_CELL(TrainingProgramGrid::OnLabelLeftClick)
//EVT_RM_COMMAND( RM_DATE_SELECTED, TrainingProgramGrid::OnDateSelected)
//CELL_LEFT_CLICK
wxEND_EVENT_TABLE()

void TrainingProgramGrid::OnDateSelected( wxCommandEvent &e )
{

    EventData *evtData = (EventData*) e.GetClientData();
    wxLogMessage(_("Date selected: %s"), evtData->dt.FormatISODate());
}

TrainingProgramGrid::TrainingProgramGrid( wxWindow *pParent, Plan *pt, PTUnit const &outUnit ) :
    wxGrid(pParent, wxID_ANY)
{
    bIsCreated = false;
    todayLine = -1;
    CreateGrid(1,3);
    HideRowLabels();

    SetColLabelValue(0,_("Date"));
    SetColLabelValue(1,_("Training"));
    SetColLabelValue(2,_("Level"));

    Update(pt, outUnit);
}

void TrainingProgramGrid::OnLabelLeftClick(wxGridEvent &e)
{
    if (!bIsCreated) {
        return;
    }
    int row = e.GetRow();
    if (this->GetGridCursorRow() != row ) {
        SelectRow(row);
    }
    wxString dateString = this->GetCellValue(row,0);
    if (dateString.StartsWith(_("Week")) || dateString.IsEmpty()) {
        return;
    }
    wxDateTime dt;
    dt.ParseDate(dateString);

    //wxCommandEvent *e2 = new wxCommandEvent(wxEVT_RM_COMMAND, RM_DATE_SELECTED);
    //EventData *evtData = new EventData();
    //evtData->dt = dt;
    //e2->SetClientData( evtData );

    //wxQueueEvent(this, e2);

    int index = 0;
    if (row>0) {
        // Check if there is a previous training on the same day
        dateString = this->GetCellValue(row-1,0);
        if (!dateString.StartsWith(_("Week"))) {
            wxDateTime dt2;
            dt2.ParseDate(dateString);
            if ( dt2 == dt ) {
                index = 1;
            }
        }
    }

    MyApp *app = (MyApp*) wxTheApp;
    app->UpdateCurrentDate(dt, this, index);
}

int TrainingProgramGrid::GetRow( wxDateTime const & date )
{
    wxString sdate = date.FormatISODate();
    for (int i=0; i< this->GetNumberRows(); i++) {
        if (sdate.CompareTo(this->GetCellValue(i,0))==0) {
            return i;
        }
    }
    return -1;
}

void TrainingProgramGrid::Update(Plan *pt, PTUnit const &outUnit)
{
    Freeze();
    std::vector<Week> &weeks = pt->weeks;
    int nLines = 0;
    for (size_t i=0; i<weeks.size(); i++) {
        std::list<Training>::iterator it = weeks[i].training.begin();
        nLines++;
        while (it != weeks[i].training.end()) {
            Training &t = *it;
            if (t.type != NONE) {
                nLines++;
            }
            it++;
        }
    }

    ClearGrid();
    int deleteRows = this->GetNumberRows() - nLines;
    if ( deleteRows > 0 ) {
        DeleteRows(0, deleteRows);
    }
    int addRows = nLines - GetNumberRows();
    if ( addRows > 0 ) {
        AppendRows(addRows);
    }
    for (int i=0; i<GetNumberCols(); i++) {
        for (int j=0; j<GetNumberRows(); j++) {
            SetCellBackgroundColour(i,j,wxColour(255,255,255));
        }
    }
    //SetBackgroundColour(wxColour(255,255,255));

    todayLine = 0;
    nLines = 0;
    wxTimeSpan minTime, maxTime, avgTime;
    double minDist, maxDist, avgDist;
    for (size_t i=0; i<weeks.size(); i++) {
        weeks[i].GetTime(minTime, maxTime, avgTime);
        weeks[i].GetDistance(minDist, maxDist, avgDist, outUnit);
        SetCellValue(nLines,0,weeks[i].ToString());
        SetCellBackgroundColour(nLines, 0, gIntensityColor[3]);
        SetCellValue(nLines,1,weeks[i].GetPhaseString());
        SetCellBackgroundColour(nLines, 1, gIntensityColor[3]);
        SetCellValue(nLines,2,wxString::Format(_("%.1lf %s, %s"),avgDist,gUnit[outUnit],avgTime.Format()));
        SetCellBackgroundColour(nLines, 2, gIntensityColor[3]);
        nLines++;
        std::list<Training>::iterator it = weeks[i].training.begin();
        while (it != weeks[i].training.end()) {
            Training &t = *it;
            if (t.type != NONE) {
                TrainingType &tt = gTrainingType[t.type];
                wxString shortName = tt.shortName;
                wxString dateString = t.date.FormatISODate();
                if ( t.date == wxDateTime::Today() && !todayLine ) {
                    todayLine = nLines;
                }
                //wxString trainingString = t.ToString(false,outUnit);

//                SetCellRenderer(nLines,0,new wxGridCellDateTimeRenderer(wxString("MM/DD/YYYY"), wxString("YYYY-MM-DD")));
                SetCellValue(nLines,0,dateString);
                SetCellValue(nLines,1,shortName);
                SetCellValue(nLines,2,wxString::Format("%d",t.intensity));

                for (int j=0; j<3; j++) {
                    SetCellBackgroundColour(nLines, j, gIntensityColor[gTrainingIntensity[t.type]]);
                }
                for (int j=3; j<GetNumberCols(); j++) {
                    SetCellBackgroundColour(nLines, j, wxColour(255,255,255));
                }

                int nIntensities = tt.intensity.size();
                if ( nIntensities >= t.intensity) {
                    IntensityPtr pIntensity = tt.intensity[t.intensity-1];
                    if (pIntensity->section.size() ) {
                        /*int c = GetNumberCols();
                        while ( (2*i->section.size() + 3) > this->GetNumberCols() )
                        {
                        	this->AppendCols(2);
                        	SetColLabelValue(c, wxString::Format(_("Part number %d"), c-2));
                        	SetColLabelValue(c+1, wxString::Format(_("Time/distance")));
                        	c = GetNumberCols();
                        }*/
                        int s=1;
                        std::list<SectionPtr>::iterator it2 = pIntensity->section.begin();
                        while ( it2 != pIntensity->section.end() ) {
                            if (2*s + 3 > GetNumberCols()) {
                                AppendCols(2);
                                SetColLabelValue(2*s + 1, wxString::Format(_("Part %d"), s));
                                SetColLabelValue(2*s + 2, wxString::Format(_("Time/distance")));
                                for (int r=0; r<GetNumberRows(); r++) {
                                    SetCellBackgroundColour(r, 2*s + 1, wxColour(255,255,255));
                                    SetCellBackgroundColour(r, 2*s + 2, wxColour(255,255,255));
                                }
                            }
                            wxString zoneString = (*it2)->ToString(outUnit, true, false);
                            SetCellValue(nLines, 2*s+1, zoneString );
                            wxString timeString = (*it2)->ToString(outUnit, false, true);
                            SetCellValue(nLines, 2*s+2, timeString );
                            PTZone zone = (*it2)->zone;
                            wxColour colour(gIntensityColor[gZoneIntensity[zone]]);
                            SetCellBackgroundColour(nLines,  2*s+1, colour);
                            SetCellBackgroundColour(nLines,  2*s+2, colour);
                            it2++;
                            s++;
                        }

                    }
                }
                //SetCellValue(nLines,2,trainingString);
                nLines++;
            }
            it++;
        }
    }

    AutoSize();

    bIsCreated = true;
    Thaw();
//	MakeCellVisible(todayLine, 0);
}