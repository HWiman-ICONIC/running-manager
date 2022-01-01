#pragma once

#include	<Defines.h>
#include	<wx/button.h>
#include	<wx/panel.h>
#include	<wx/calctrl.h>
#include	<wx/log.h>
#include    <wx/radiobox.h>
#include    <wx/spinctrl.h>

/**
 * @brief GUI for creating a training program
*/
class CreateTrainingProgramDialog : public wxPanel {
public:
    /**
     * @brief Constructor
     * @param pParent Parent
     * @param unit Unit for training program (km or miles)
     * @param level Level of training program
     * @param distance Competition distance
     * @param raceDate Date of competition
     * @param pulse Lactate threshold heart rate
    */
    CreateTrainingProgramDialog(wxWindow *pParent, PTUnit const &unit, PTLevel const &level, PTDistance const &distance, wxDateTime const &raceDate, int const &pulse);

    /**
     * @brief Get competition distance
     * @return competition distance
    */
    PTDistance GetDistance() const {
        return ptDistance;
    }

    /**
     * @brief Get level
     * @return level
    */
    PTLevel GetLevel() const {
        return ptLevel;
    }

    /**
     * @brief Get unit
     * @return unit
    */
    PTUnit GetUnit() const {
        return ptUnit;
    }

    /**
     * @brief Get competition date
     * @return date
    */
    wxDateTime GetDate() const {
        return date;
    }

    /**
     * @brief Set competition date
     * @param date Date
    */
    void SetDate( wxDateTime const &date );

    /**
     * @brief Get lactate threshold heart rate
     * @return lactate threshold heart rate
    */
    int GetPulse() const {
        return pulse;
    }

    /**
     * @brief Copy entered values to training program
     * @return True on success
    */
    virtual bool TransferDataFromWindow();

    /**
     * @brief Set log level, i.e. how much log info to display
     * @param level Log Level
    */
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
