#pragma once

#include	<wx/grid.h>
#include	<Plan.h>

class TrainingProgramGrid : public wxGrid {
public:
    TrainingProgramGrid( wxWindow *pParent, Plan *pt, PTUnit const &outUnit );
    void Update(Plan *pt, PTUnit const &outUnit);
    int todayLine;

    int GetRow( wxDateTime const & date );

    void OnLabelLeftClick(wxGridEvent &e);

    void OnDateSelected( wxCommandEvent &e );

    bool bIsCreated;

    wxDECLARE_EVENT_TABLE();
};