#pragma once

#include	<wx/grid.h>
#include	<Plan.h>

/**
 * @brief GUI grid for the entire training program
*/
class TrainingProgramGrid : public wxGrid {
public:
    /**
     * @brief Constructor
     * @param pParent Parent
     * @param pt Plan to populate from
     * @param outUnit km|miles
    */
    TrainingProgramGrid( wxWindow *pParent, Plan *pt, PTUnit const &outUnit );

    /**
     * @brief Recreate grid from new plan
     * @param pt Plan
     * @param outUnit km|miles
    */
    void Update(Plan *pt, PTUnit const &outUnit);

    /**
     * @brief Get row number for this date
     * @param date Date
     * @return Row number
    */
    int GetRow( wxDateTime const & date );

    /**
     * @brief Highlight selected line and update todays training with selected activity
     * @param e event
    */
    void OnLabelLeftClick(wxGridEvent &e);

    /**
     * @brief *Unused*
     * @param e
    */
    void OnDateSelected( wxCommandEvent &e );

    int todayLine;
private:
    bool bIsCreated;

    wxDECLARE_EVENT_TABLE();
};