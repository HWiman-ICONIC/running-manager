#pragma once

#include	<Plan.h>
#include	<wx/html/htmlwin.h>
#include	<wx/datetime.h>
#include	<wx/grid.h>

/**
 * @brief GUI grid showing training a specific day.
*/
class TodayControl : public wxGrid {
public:
    /**
     * @brief Constructor
     * @param pParent Parent
     * @param plan Plan to extract date from
     * @param day Date to extract
     * @param unit Unit (km|miles)
    */
    TodayControl(wxWindow *pParent, Plan &plan, wxDateTime &day, PTUnit const &unit);

    /**
     * @brief Update the control with new date
     * @param plan Plan to extract date from
     * @param day Date to extract
     * @param unit Unit (km|miles)
     * @param index 0 for first training this date, 1 for second training the same date etc.
    */
    void Update(Plan &plan, wxDateTime const &day, PTUnit const &unit, int const &index);
private:
    Plan *cpLastPlan;
    wxDateTime cLastDate;
    PTUnit cLastUnit;
    int cLastIndex;
//	wxGrid *table;
};