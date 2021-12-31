#pragma once
#include "wx\panel.h"
#include	<wx/grid.h>
#include	<wx/button.h>
#include	<vector>
#include	<Plan.h>

class DragGrid : public wxGrid {
public:
    DragGrid(wxWindow *parent, wxWindowID id, wxButton *createButton);
    void OnColumnMoved(wxGridEvent &e);
    wxArrayInt GetColumnOrder();
    void SetColumnOrder(wxArrayInt order);
    void OnPaint(wxPaintEvent &e);

protected:
    bool isColumnOrderChanged;
    wxButton *createButton;

    DECLARE_EVENT_TABLE()
};



class WeekDay :
    public wxPanel {
public:
    WeekDay(wxWindow *parent, Plan &plan);
    virtual ~WeekDay(void);

    wxArrayInt GetWeekdayOrder();

    bool Update(Plan &plan);

    void SetWeekdayOrder(wxArrayInt order);

    DragGrid *table;
    wxButton *createButton;
    std::vector<std::vector<int>> cTrainingPerDay;

protected:
    void _Init();
};
