#pragma once

#include	"Plan.h"
#include	"Zone.h"
#include	"Mainframe.h"
#include	"SettingsPanel.h"
#include	"TrainingProgramGrid.h"
#include	"TodayControl.h"
#include	"ZoneGrid.h"
#include	"User.h"
#include	<wx/app.h>
#include	<wx/config.h>
#include	<wx/wxhtml.h>
#include	<wx/html/helpwnd.h>
#include	<map>
#include	<vector>

class MyApp : public wxApp {
public:
    MyApp();
    virtual ~MyApp();
    virtual bool OnInit();
    virtual int OnExit();

    TodayControl* GetTodayControl() {
        return today;
    }
    void UpdateCurrentDate(wxDateTime const& date, wxWindow* sender, int index);
    void UpdatePulse();

    std::map<wxString, wxString>& GetPerspectives();
private:
    boost::shared_ptr<wxAuiManager> GetAuiManager() {
        if (!frame) {
            return boost::shared_ptr<wxAuiManager>();
        }
        return frame->GetAuiManager();
    }
    bool ReadPerspective(int const& n);
    void SavePerspectives();
    void ReadPaces(wxString const& user);
    void SavePaces(wxString const& user);

    std::map<wxString, wxString>::iterator FindPerspective(wxString const& s);

    void OnCreateTrainingProgram(wxCommandEvent& event);
    void OnSaveCalendar(wxCommandEvent& event);
    void OnUpdateSaveCalendar(wxUpdateUIEvent& e);
    void OnUnitKm(wxCommandEvent& event);
    void OnZone(wxCommandEvent& event);
    void OnUnitMiles(wxCommandEvent& event);
    void OnUpdateUnit(wxUpdateUIEvent& e);
    void OnLoadPerspective(wxCommandEvent& e);
    void OnDeletePerspective(wxCommandEvent& WXUNUSED(ev));
    void OnUpdateLoadPerspective(wxUpdateUIEvent& e);
    void OnSavePerspective(wxCommandEvent& e);
    void OnSetPace(wxCommandEvent& WXUNUSED(e));

    void OnDateSelected(wxCommandEvent& e);

    Plan* plan;
    wxString lastDir;
    MyFrame* frame;
    //	wxConfig *configuration;

    ZoneGrid* zoneGrid;
    wxGrid* trainingTypeGrid;
    CreateTrainingProgramDialog* trainingDialog;
//    boost::shared_ptr<wxAuiManager> auiManager;
    TrainingProgramGrid* trainingProgram;
    TodayControl* today;
    wxHtmlHelpWindow* cpHelpWindow;
    wxHtmlHelpController* cpHelpController;
    std::map<wxString, wxString> vPerspectives;
    wxString lastPerspective;
    //	std::vector<Zone> vZoneMap;

    wxDECLARE_EVENT_TABLE();
};