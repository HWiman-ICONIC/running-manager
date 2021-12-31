#include	<WeekDay.h>
#include	<TrainingType.h>
#include	<wx/sizer.h>
#include	<wx/stattext.h>
#include	<wx/grid.h>

wxBEGIN_EVENT_TABLE(DragGrid, wxGrid)
    EVT_GRID_COL_MOVE(DragGrid::OnColumnMoved)
    EVT_PAINT(DragGrid::OnPaint)
wxEND_EVENT_TABLE()

DragGrid::DragGrid(wxWindow *parent, wxWindowID id, wxButton *createButton) :
    wxGrid(parent,id), isColumnOrderChanged(false)
{
    this->createButton = createButton;
}

wxArrayInt DragGrid::GetColumnOrder()
{

    return wxGrid::m_colAt;
}

void DragGrid::SetColumnOrder(wxArrayInt order)
{
    for (int i=0; i<7; i++) {
        wxMessageOutputDebug().Printf("ctrl %d: -> %d", i, order[i]);
    }
    wxGrid::SetColumnsOrder(order);
    isColumnOrderChanged = true;
    Refresh();
}

void DragGrid::OnPaint(wxPaintEvent &e)
{
    if (isColumnOrderChanged) {
        isColumnOrderChanged = false;
        wxString weekDay[] = {_("Monday"), _("Tuesday"), _("Wednesday"), _("Thursday"), _("Friday"), _("Saturday"), _("Sunday") };
        for (int i=0; i<7; i++) {
            int idx = GetColAt(i);
            SetColLabelValue(idx,weekDay[i]);
        }
        createButton->Enable(true);
    }
    e.Skip();
}

void DragGrid::OnColumnMoved(wxGridEvent &WXUNUSED(e))
{
    isColumnOrderChanged = true;
    Refresh();
}

WeekDay::WeekDay(wxWindow *parent, Plan &plan) :
    wxPanel(parent)
{
    _Init();
    Update(plan);
}

bool WeekDay::Update(Plan &plan)
{
    cTrainingPerDay = plan.GetTrainingTypePerWeekDay();
    wxString weekDay[] = {_("Monday"), _("Tuesday"), _("Wednesday"), _("Thursday"), _("Friday"), _("Saturday"), _("Sunday") };
    int colorVote[3];
    std::list<wxString> details[7];
    int intensity[7];
    int maxNumDetails = 0;
    for (int i=0; i<7; i++) {
        wxString types;
        colorVote[0] = colorVote[1] = colorVote[2] = 0;
        for (int j=0; j<cTrainingPerDay[i].size(); j++) {
            if ( cTrainingPerDay[i][j] ) {
                TrainingType &t = gTrainingType[j];
                wxString str = wxString::Format("%s : %d ",t.shortName,cTrainingPerDay[i][j]);
                details[i].push_back(str);
                if (details[i].size() > maxNumDetails) {
                    maxNumDetails = details[i].size();
                }
                colorVote[gTrainingIntensity[j]]+=cTrainingPerDay[i][j];
                types += str;
            }
        }
        if (colorVote[0] > colorVote[1])
            if (colorVote[0] > colorVote[2]) {
                intensity[i] = 0;
            } else {
                intensity[i] = 2;
            } else if (colorVote[1] > colorVote[2]) {
            intensity[i] = 1;
        } else {
            intensity[i] = 2;
        }
    }

    table->ClearGrid();
    if (table->GetNumberRows() > maxNumDetails+1) {
        table->DeleteRows(maxNumDetails, table->GetNumberRows()-(maxNumDetails+1),false);
    } else if (table->GetNumberRows() < maxNumDetails+1) {
        table->AppendRows(maxNumDetails+1-table->GetNumberRows(),false);
    }
    for (int i=0; i<7; i++) {
        table->SetColLabelValue(i,weekDay[i]);
        table->SetCellValue(0,i,gLevel[intensity[i]]);
        table->SetCellBackgroundColour(0, i,gIntensityColor[intensity[i]]);
        int j=1;
        for (std::list<wxString>::iterator it=details[i].begin(); it != details[i].end(); it++, j++) {
            table->SetCellValue(j,i,*it);
            table->SetCellBackgroundColour(j,i,gIntensityColor[intensity[i]]);
        }
    }
    table->EnableDragColMove();
    table->SetColumnOrder(plan.weekDayOrder);
    table->AutoSizeRow(1,true);
    table->HideRowLabels();
    table->SetUseNativeColLabels();
    table->Fit();
    Fit();
    return true;
}

void WeekDay::_Init()
{
    wxBoxSizer *pParentSizer = new wxBoxSizer(wxVERTICAL);

    createButton = new wxButton(this, Minimal_Create_TrainingProgram, _("&Update"), wxDefaultPosition, wxDefaultSize, 0);
    table = new DragGrid( this, Minimal_Change_Weekday, createButton );
    pParentSizer->Add(table);
    table->CreateGrid(2,7);

    //table->CreateGrid(maxNumDetails+1,7);

    createButton->Enable(false);
    createButton->SetToolTip(_("Create/update training plan\nbased on changed weekday order."));
    pParentSizer->Add(createButton, 0, wxALL, 5);

    pParentSizer->Add( new wxStaticText(this, wxID_ANY,_("Select a weekday (e.g. Monday) and drag it to the weekday where you want the training.\nRelease the mouse button when the marker between desired weekdays is highlighted.")));

    SetSizerAndFit( pParentSizer );
}

WeekDay::~WeekDay(void)
{
}

wxArrayInt WeekDay::GetWeekdayOrder()
{
    wxArrayInt columnOrder = table->GetColumnOrder();
    if (columnOrder.size() != 7) {
        for (int i=0; i<7; i++) {
            columnOrder.Add(i);
        }
    }
    return columnOrder;
}

