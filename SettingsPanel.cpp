#include	<SettingsPanel.h>
#include	<wx/sizer.h>
#include	<wx/radiobox.h>
#include	<wx/spinctrl.h>
#include    <wx/statbox.h>

wxBEGIN_EVENT_TABLE(CreateTrainingProgramDialog, wxPanel)
//	EVT_BUTTON(wxID_OK, CreateTrainingProgramDialog::OnCreate)
wxEND_EVENT_TABLE()

CreateTrainingProgramDialog::CreateTrainingProgramDialog(wxWindow *pParent, PTUnit const &outUnit, PTLevel const &alevel,
        PTDistance const &adistance, wxDateTime const &raceDate, int const &pulse):
    wxPanel(pParent, wxID_ANY),cLogLevel(wxLOG_Info)
{
    wxBoxSizer *pParentSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *pRadioSizer = new wxBoxSizer(wxHORIZONTAL);
    pParentSizer->Add( pRadioSizer );

    distances.Add(wxString("&")+gDistance[(int)PTDistance::PTD_5KM]);
    distances.Add(wxString("&")+gDistance[(int)PTDistance::PTD_10KM]);
    distances.Add(gDistance[(int)PTDistance::PTD_HALF_MARATHON]);
    distances.Add(gDistance[(int)PTDistance::PTD_MARATHON]);
    distance = new wxRadioBox(this, wxID_ANY, _("Distance"), wxDefaultPosition, wxDefaultSize, distances, 0, wxVERTICAL);
    //distance->SetBackgroundColour(wxColour(255,255,255));
    distance->SetSelection((int)adistance);
    distance->SetToolTip(_("Select your race distance"));

    Connect(distance->GetId(), -1, wxEVT_COMMAND_RADIOBUTTON_SELECTED,
            (wxObjectEventFunction)
            (wxEventFunction)
            (wxCommandEventFunction)&CreateTrainingProgramDialog::OnDistanceSelected);

    pRadioSizer->Add(distance, 1, wxALL|wxEXPAND, 2);

    levels.Add(gLevel[PTL_LOW]);
    levels.Add(gLevel[PTL_MEDIUM]);
    levels.Add(gLevel[PTL_HIGH]);
    level = new wxRadioBox(this, wxID_ANY, _("Training level"), wxDefaultPosition, wxDefaultSize, levels, 0, wxVERTICAL);
    level->SetSelection((int)alevel);
    level->SetToolTip(_("Select your training intensity.\nYou should have a good running foundation\neven for low intensity."));
    pRadioSizer->Add(level, 1, wxEXPAND|wxALL, 2);

    wxBoxSizer *verticalSizer = new wxBoxSizer( wxVERTICAL );
    pRadioSizer->Add(verticalSizer, 0, wxALL, 2);

    units.Add(gUnit[KM]);
    units.Add(gUnit[MILES]);
    unit = new wxRadioBox(this, wxID_ANY, _("Distance unit"), wxDefaultPosition, wxDefaultSize, units, 0, wxVERTICAL);
    unit->SetSelection((int) outUnit);
    unit->SetToolTip(_("Most training is defined in minutes.\nSelect unit for the few trainings defined by distance."));
    verticalSizer->Add(unit, 1, wxEXPAND|wxDOWN,2);


    wxStaticBoxSizer *pulseSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Lactate pulse")), wxVERTICAL);
    verticalSizer->Add(pulseSizer, 0, wxALL|wxUP, 2);

    wxString s = wxString::Format("%d", pulse);
    pulseCtrl = new wxSpinCtrl(this, wxID_ANY, s, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxALIGN_CENTRE_HORIZONTAL,
                               0, 220, pulse);
    pulseCtrl->SetToolTip(_("Set your lactate threshold pulse.\nOptional, but helps defining your zones."));
    pulseSizer->Add(pulseCtrl);

    wxStaticBoxSizer *textSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Race date")), wxVERTICAL);
    pParentSizer->Add(textSizer, 1, wxEXPAND|wxALL);
    calendar = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime,wxDefaultPosition, wxDefaultSize, wxCAL_MONDAY_FIRST);
    calendar->SetDate(raceDate);
    calendar->SetToolTip(_("Select the date of your competition."));
    date = calendar->GetDate();
    //calendar->SetMinSize(wxSize(-1,300));
    textSizer->Add(calendar, 1, wxEXPAND);

    wxBoxSizer *btnSizer = new wxBoxSizer(wxVERTICAL);
    pRadioSizer->Add(btnSizer, 0, wxALL, 2);

    createButton = new wxButton(this, Minimal_Create_TrainingProgram, _("&Update"), wxDefaultPosition, wxDefaultSize, 0);
    //createButton->SetBackgroundColour(wxColour(255,255,255));
    createButton->SetToolTip(_("Click to generate training program"));
    btnSizer->Add(createButton, 1, wxCENTER|wxEXPAND);

    /*wxButton *paceButton = new wxButton(this, Minimal_Set_Pace, _("&Pace..."), wxDefaultPosition, wxDefaultSize, 0);
    paceButton->SetBackgroundColour(wxColour(255,255,255));
    paceButton->SetToolTip(_("Optionally set pace per zone"));
    btnSizer->Add(paceButton, 1, wxCENTER|wxEXPAND);*/

    wxButton *exportButton = new wxButton(this, Minimal_Save_Calendar, _("&Export..."), wxDefaultPosition, wxDefaultSize, 0);
    //createButton->SetBackgroundColour(wxColour(255,255,255));
    exportButton->SetToolTip(_("Click to export the program to calendar"));
    btnSizer->Add(exportButton, 1, wxCENTER|wxEXPAND);


    wxButton *helpButton = new wxButton(this, Minimal_Help, _("&Help..."), wxDefaultPosition, wxDefaultSize, 0);
    //helpButton->SetBackgroundColour(wxColour(255,255,255));
    helpButton->SetToolTip(_("Show help"));
    btnSizer->Add(helpButton, 0, wxCENTER|wxEXPAND);

//	wxSizer *btnSizer = new wxBoxSizer(wxHORIZONTAL);//CreateButtonSizer(wxOK|wxCANCEL);//|wxHELP);
//	pParentSizer->Add(btnSizer);
    SetSizerAndFit( pParentSizer );
//	this->SetBackgroundColour(wxColour(255.0, 128.0, 128.0));
}

void CreateTrainingProgramDialog::OnDistanceSelected( wxCommandEvent &e )
{
    wxLogMessage(_("You selected %d"), e.GetSelection());
}

bool CreateTrainingProgramDialog::TransferDataFromWindow()
{
    // wxMessageBox("You selected distance "+distances[distance->GetSelection()]+" at level "+levels[level->GetSelection()]+" on a race that will take place on "+calendar->GetDate().FormatISODate(), _("Training selections"));
    ptDistance = (PTDistance) distance->GetSelection();
    ptLevel = (PTLevel) level->GetSelection();
    ptUnit = (PTUnit) unit->GetSelection();
    date = calendar->GetDate();
    pulse = pulseCtrl->GetValue();
    if (cLogLevel >= wxLOG_Warning) {
        if (date.GetWeekDay() != 0) {
            wxString msg = wxString::Format(_("Race date is currently always set to a Sunday.\nYou have chosen a %s."), date.GetWeekDayName(date.GetWeekDay()));
            wxLogWarning(msg);
        }
    }
    return true;
}

void CreateTrainingProgramDialog::SetDate( wxDateTime const &date )
{
    if (calendar->GetDate() != date) {
        calendar->SetDate(date);
    }
}
