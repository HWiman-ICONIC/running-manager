#pragma once

#include	<Defines.h>
#include	<wx/button.h>
#include	<wx/panel.h>
#include	<wx/calctrl.h>
#include	<wx/log.h>
#include    <wx/radiobox.h>
#include    <wx/spinctrl.h>

class CreateTrainingProgramDialog : public wxPanel {
public:
    CreateTrainingProgramDialog(wxWindow *pParent, PTUnit const &unit, PTLevel const &level, PTDistance const &distance, wxDateTime const &raceDate, int const &pulse);

    PTDistance GetDistance() const {
        return ptDistance;
    }
    PTLevel GetLevel() const {
        return ptLevel;
    }
    PTUnit GetUnit() const {
        return ptUnit;
    }
    wxDateTime GetDate() const {
        return date;
    }
    void SetDate( wxDateTime const &date );
    int GetPulse() const {
        return pulse;
    }

    virtual bool TransferDataFromWindow();

    void SetLogLevel(wxLogLevel level) {
        cLogLevel=level;
    }

private:
    void OnDistanceSelected( wxCommandEvent &e );
    wxLogLevel cLogLevel;
    wxRadioBox *level;
    wxRadioBox *distance;
    wxRadioBox *unit;
    wxCalendarCtrl *calendar;
    wxButton *createButton;
    wxSpinCtrl *pulseCtrl;

    wxArrayString levels;
    wxArrayString distances;
    wxArrayString units;

    PTDistance ptDistance;
    PTLevel ptLevel;
    PTUnit ptUnit;
    wxDateTime date;
    int pulse;

    wxDECLARE_EVENT_TABLE();
};
