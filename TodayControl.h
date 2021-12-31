#pragma once

#include	<Plan.h>
#include	<wx/html/htmlwin.h>
#include	<wx/datetime.h>
#include	<wx/grid.h>

class TodayControl : public wxGrid {
public:
    TodayControl(wxWindow *pParent, Plan &plan, wxDateTime &day, PTUnit const &unit);

    void Update(Plan &plan, wxDateTime const &day, PTUnit const &unit, int const &index);
private:
    Plan *cpLastPlan;
    wxDateTime cLastDate;
    PTUnit cLastUnit;
    int cLastIndex;
//	wxGrid *table;
};