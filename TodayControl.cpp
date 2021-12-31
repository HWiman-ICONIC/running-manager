#include	"TodayControl.h"
#include	<wx/sizer.h>
#include	"TrainingType.h"
#include	"Zone.h"
#include	"ZoneGrid.h"
//#include	<sgis/xml/HtmlTable.h>

TodayControl::TodayControl(wxWindow *pParent, Plan &plan, wxDateTime &day, PTUnit const &unit) :
    wxGrid( pParent, wxID_ANY )
{
    cpLastPlan = NULL;
    Update(plan, day, unit, 0);
}

void TodayControl::Update(Plan &plan, wxDateTime const &day, PTUnit const &unit, int const &index)
{
    if (&plan == cpLastPlan && cLastDate.IsSameDate(day) && unit == cLastUnit && index == cLastIndex) {
        return;
    }

    std::list<Training*> trainings = plan.GetTraining( day );

    //wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    //table = new wxGrid(this, wxID_ANY);
    wxGrid *table = this;

    if (trainings.size() == 0) {
        int nRows = 2;
        int nCols = 1;
        if ( this->GetNumberCols() && GetNumberRows() ) {
            if (GetNumberCols() > nCols) {
                DeleteCols(0,GetNumberCols() - nCols);
            }
            if (GetNumberRows() > nRows) {
                DeleteRows(0,GetNumberRows() - nRows);
            }
            if (GetNumberCols() < nCols) {
                AppendCols(nCols-GetNumberCols());
            }
            if (GetNumberRows() < nRows) {
                AppendRows(nRows-GetNumberRows());
            }
            ClearGrid();
            SetBackgroundColour( wxColour(255,255,255) );
        } else {
            table->CreateGrid(nRows, nCols);
        }

        //table->CreateGrid(2,1);
        table->SetRowLabelValue(0,_("Date"));
        table->SetCellValue(0,0,day.FormatISODate());
        table->SetRowLabelValue(1,_("Training"));
        table->SetCellValue(1,0,_("No training"));
        SetCellBackgroundColour(1,0,gIntensityColor[NONE]);
    } else {

        int nRows = 5;
        int nCols = 5;
        Training *t;
        if ( index == 0 ) {
            t = trainings.front();
            cLastIndex = 0;
        } else {
            int index2 = 0;
            std::list<Training*>::iterator it = trainings.begin(), e = trainings.end();
            while (it!=e && index2 != index) {
                it++;
                index2++;
            }
            if (it==e) {
                it--;
                cLastIndex = trainings.size()-1;
            } else {
                cLastIndex = index2;
            }
            t = *it;
        }
        TrainingType &tt = gTrainingType[t->type];
        IntensityPtr pIntensity;
        if (tt.intensity.size()) {
            pIntensity = tt.intensity[t->intensity-1];
            if ( pIntensity ) {
//				nRows++;
                std::list<SectionPtr> &sections = pIntensity->section;
                nRows += sections.size();
            }
        }

        if ( GetNumberCols() && GetNumberRows() ) {
            if (GetNumberCols() > nCols) {
                DeleteCols(nCols,GetNumberCols() - nCols);
            }
            if (GetNumberRows() > nRows) {
                DeleteRows(nRows,GetNumberRows() - nRows);
            }
            if (GetNumberCols() < nCols) {
                AppendCols(nCols-GetNumberCols());
            }
            if (GetNumberRows() < nRows) {
                AppendRows(nRows-GetNumberRows());
            }
            ClearGrid();
            /*if ( table->GetCellSize(0,0).y == 1 )
            {
            	table->SetCellSize(0,0,1,5);
            	table->SetCellSize(1,1,1,4);
            	table->SetCellSize(2,0,1,5);
            }*/
            SetBackgroundColour( wxColour(255,255,255) );
        } else {
            table->CreateGrid(nRows,nCols);
            //table->SetCellSize(0,0,1,5);
            //table->SetCellSize(1,1,1,4);
            //table->SetCellSize(2,0,1,5);
        }
        if ( table->GetCellSize(wxGridCellCoords(0,0)).y == 1 ) {
            table->SetCellSize(0,0,1,5);
        }
        if ( table->GetCellSize(wxGridCellCoords(1,1)).y == 1) {
            table->SetCellSize(1,1,1,4);
        }
        if ( table->GetCellSize(wxGridCellCoords(2,0)).y == 1 ) {
            table->SetCellSize(2,0,1,5);
        }
        if ( table->GetCellSize(wxGridCellCoords(3,0)).y == 1 ) {
            table->SetCellSize(3,0,1,5);
        }
        if ( table->GetCellSize(wxGridCellCoords(4,0)).y == 1 ) {
            table->SetCellSize(4,0,1,5);
        }
//		table->CreateGrid(nRows,1);
        table->SetRowLabelValue(0,_("Date"));
        wxString dateString = day.GetWeekDayName(day.GetWeekDay())+wxString(" ")+day.FormatISODate();
        table->SetCellValue(0,0,dateString);


        table->SetRowLabelValue(1,_("Training"));
        table->SetCellValue(1,0,tt.shortName);
        table->SetCellValue(1,1,tt.description);


        //table->SetCellValue(1,1,tt.description);
        //table->SetCellValue(1,1,tt.description);
        table->SetRowLabelValue(2,_("Level"));
        table->SetCellValue(2,0,wxString::Format("%d",t->intensity));


        table->SetRowLabelValue(3,_("Total time"));
        table->SetRowLabelValue(4,_("Total distance"));

        SetCellBackgroundColour(0,0,gIntensityColor[gTrainingIntensity[t->type]]);
        SetCellBackgroundColour(1,0,gIntensityColor[gTrainingIntensity[t->type]]);
        SetCellBackgroundColour(1,1,gIntensityColor[gTrainingIntensity[t->type]]);
        SetCellBackgroundColour(2,0,gIntensityColor[gTrainingIntensity[t->type]]);

        ZoneGrid *pZoneGrid = (ZoneGrid *) wxWindow::FindWindowByName("ZoneGrid");

        if ( pIntensity ) {
            wxTimeSpan min1, max1, avg1;
            pIntensity->GetTime(min1, max1, avg1);
            table->SetCellValue(3,0,avg1.Format());
            SetCellBackgroundColour(3,0,gIntensityColor[gTrainingIntensity[t->type]]);

            double minDist, maxDist, avgDist;
            pIntensity->GetDistance(minDist, maxDist, avgDist, unit);
            table->SetCellValue(4,0,wxString::Format("%.1lf %s", avgDist, gUnit[unit] ) );
            SetCellBackgroundColour(4,0,gIntensityColor[gTrainingIntensity[t->type]]);

            //table->SetRowLabelValue(3,_("Parts"));
            std::list<SectionPtr> &sections = pIntensity->section;
            std::list<SectionPtr>::iterator it = sections.begin();
            int line = 5;
            while (it != sections.end()) {
                SectionPtr section = *it;

                Zone &zone = Zone::GetZoneMap()[section->zone];
//				section->GetTime(min1, max1, avg1);
                table->SetRowLabelValue(line, section->ToString(unit, true, false));
                table->SetCellValue(line, 0,section->ToString(unit, false, true));
                SetCellBackgroundColour(line, 0, gIntensityColor[gZoneIntensity[section->zone]]);

                SetCellValue(line,1,pZoneGrid->GetCellValue(zone.zone,1));
                SetCellBackgroundColour(line, 1, gIntensityColor[gZoneIntensity[section->zone]]);
                SetCellValue(line,2,pZoneGrid->GetCellValue(zone.zone,2));
                SetCellBackgroundColour(line, 2, gIntensityColor[gZoneIntensity[section->zone]]);
                SetCellValue(line,3,pZoneGrid->GetCellValue(zone.zone,3));
                SetCellBackgroundColour(line, 3, gIntensityColor[gZoneIntensity[section->zone]]);
                SetCellValue(line,4,pZoneGrid->GetCellValue(zone.zone,4));
                SetCellBackgroundColour(line, 4, gIntensityColor[gZoneIntensity[section->zone]]);
                it++;
                line++;
            }
//			table->SetCellValue(3,0,pIntensity->ToString( unit ));
        }
    }

    table->HideColLabels();
    table->AutoSize();
    this->SetInitialSize(table->GetSize());
//	sizer->Add( table );//, 1, wxEXPAND|wxALL );
//	sgis::html::html htmlDoc(day.FormatISODate(), _("Todays training"));
//	SetSizerAndFit( sizer );

    Layout();

    cpLastPlan = &plan;
    cLastDate = day;
    cLastUnit = unit;
}