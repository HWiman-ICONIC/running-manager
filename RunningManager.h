#pragma once

#include	"Plan.h"
#include	"Zone.h"
#include	"Mainframe.h"
#include	"SettingsPanel.h"
#include	"TrainingProgramGrid.h"
#include	"TodayControl.h"
#include	"ZoneGrid.h"
#include	"User.h"
#include	<WeekDay.h>
#include	<wx/app.h>
#include	<wx/config.h>
#include	<wx/wxhtml.h>
#include	<wx/html/helpwnd.h>
#include	<map>
#include	<vector>

/**
 * @brief The RunningManager application
*/
class MyApp : public wxApp {
public:
    /**
     * @brief Constructor
    */
    MyApp();

    /**
     * @brief Destructor
    */
    virtual ~MyApp();

    /**
     * @brief Initialize application
     * @return True on success
    */
    virtual bool OnInit();

    /**
     * @brief Close application
     * @return 0 on success
    */
    virtual int OnExit();

    /**
     * @brief Get the panel for todays training
     * @return
    */
    TodayControl* GetTodayControl() const;

    /**
     * @brief Update current date
     * @param date Current date
     * @param sender Sender does not need to be updated
     * @param index 0 if single activity this day, 1 if second activity this day is wanted.
    */
    void UpdateCurrentDate(wxDateTime const& date, wxWindow* sender, int index);

    /**
     * @brief Update lactate threshold heart rate
    */
    void UpdatePulse();

    /**
     * @brief Get a map with all perspectives.
     *
     * First entry is descriptive name of perspective, second entry is initialization string to open and open the panes for the named perspective.
     * @return Map with perspectives.
    */
    std::map<wxString, wxString>& GetPerspectives();
private:
    boost::shared_ptr<wxAuiManager> GetAuiManager() const;
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
    void OnCreateUser( wxCommandEvent &WXUNUSED(e) );
    void OnSelectUser( wxCommandEvent &WXUNUSED(e) );
    void OnDeleteUser( wxCommandEvent &WXUNUSED(e) );

    void OnDateSelected(wxCommandEvent& e);

    Plan* plan;
    wxString lastDir;
    MyFrame* frame;
    int cMajorVersion;
    int cMinorVersion;

    ZoneGrid* zoneGrid;
    wxGrid* trainingTypeGrid;
    CreateTrainingProgramDialog* trainingDialog;
//    boost::shared_ptr<wxAuiManager> auiManager;
    TrainingProgramGrid* trainingProgram;
    TodayControl* today;
    WeekDay *weekDayControl;
    wxHtmlHelpWindow* cpHelpWindow;
    wxHtmlHelpController* cpHelpController;
    std::map<wxString, wxString> vPerspectives;
    wxString lastPerspective;
    //	std::vector<Zone> vZoneMap;

    wxDECLARE_EVENT_TABLE();
};