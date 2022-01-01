#pragma once
#include "wx\panel.h"
#include	<wx/grid.h>
#include	<wx/button.h>
#include	<vector>
#include	<Plan.h>

/**
 * @brief Grid which can change order of columns.
 *
 * USe to change which week days long runs, intervals etc are on.
 */
class DragGrid : public wxGrid {
public:
    /**
     * @brief Constructor
     * @param parent Parent
     * @param id Window ID
     * @param createButton Button for updating according to current drag state
    */
    DragGrid(wxWindow *parent, wxWindowID id, wxButton *createButton);

    /**
     * @brief  Handle a column darg event
     * @param e
    */
    void OnColumnMoved(wxGridEvent &e);

    /**
     * @brief Return the current order of the columns
     * @return current order of the columns
    */
    wxArrayInt GetColumnOrder();

    /**
     * @brief Set current order of columns
     * @param order current order of columns
    */
    void SetColumnOrder(wxArrayInt order);

    /**
     * @brief Refresh this panel
     * @param e event
    */
    void OnPaint(wxPaintEvent &e);

protected:
    bool isColumnOrderChanged;
    wxButton *createButton;

    DECLARE_EVENT_TABLE()
};

/**
 * @brief GUI for weekdays.
 *
 * Defines which trainings appear on which week days.
 * Contains a DragGrid to enable change order of weekdays.
*/
class WeekDay: public wxPanel {
public:
    /**
     * @brief Constructor
     * @param parent Parent
     * @param plan training plan
    */
    WeekDay(wxWindow *parent, Plan &plan);

    /**
     * @brief Desctructor
     * @param
    */
    virtual ~WeekDay(void);

    /**
     * @brief Return current weekday order
     * @return
    */
    wxArrayInt GetWeekdayOrder();

    /**
     * @brief Update the plan according to current weekday order
     * @param plan
     * @return
    */
    bool Update(Plan &plan);

    /**
     * @brief Set week day order
     * @param order week day order
    */
    void SetWeekdayOrder(wxArrayInt order);

    DragGrid *table;
    wxButton *createButton;
    std::vector<std::vector<int>> cTrainingPerDay;

protected:
    void _Init();
};
