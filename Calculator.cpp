#include	<Calculator.h>
#include	<Converter.h>
#include	<User.h>

#include	<wx/sizer.h>
#include	<wx/statbox.h>
#include	<wx/spinctrl.h>
#include	<wx/stattext.h>
#include	<wx/textctrl.h>
#include	<wx/combobox.h>

using namespace rm;

Calculator::Calculator( wxWindow *pParent ) :
wxAuiNotebook( pParent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_SCROLL_BUTTONS )
{
#ifdef __WXGTK__
    SetSelectedFont(GetFont().MakeSmaller());
#endif
    SetArtProvider(new wxAuiSimpleTabArt());
	
	AddPage( new Predictor(this), wxString("Predict") );
	SetPageToolTip(0,_("Predict time for different distances."));

	AddPage( new Speed(this), wxString("Convert") );
	SetPageToolTip(1,_("Convert between units and \nget times for common distances."));

	
	
	SetMinSize( wxSize(200,200) );

	Fit();
}

Calculator::Speed::Speed(wxWindow *pParent) :
wxPanel( pParent, wxID_ANY, wxDefaultPosition, wxDefaultSize )
{

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

	// Min/km
	wxStaticBoxSizer *minPerKmSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Minutes per km [min/km]")), wxHORIZONTAL);
	sizer->Add(minPerKmSizer, 0, wxEXPAND|wxALL);

	cMinPerKmMinSpin = new wxSpinCtrl(this, wxID_ANY, "5", wxDefaultPosition, wxSize(-1,-1), wxSP_ARROW_KEYS|wxALIGN_CENTRE_HORIZONTAL,
							0, 20, 5);
	Connect(cMinPerKmMinSpin->GetId(),  -1, wxEVT_SPINCTRL,
		 (wxObjectEventFunction)
		 (wxEventFunction)
		 (wxCommandEventFunction)
		 (wxSpinEventFunction)&Calculator::Speed::OnMinPerKm);

	cMinPerKmMinSpin->SetToolTip(_("Enter minutes."));
	minPerKmSizer->Add( cMinPerKmMinSpin, 0, wxEXPAND|wxALL);

	minPerKmSizer->Add( new wxStaticText(this, wxID_ANY,_("min ")));

	cMinPerKmSecSpin = new wxSpinCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxALIGN_CENTRE_HORIZONTAL,
							0, 59, 0);
	cMinPerKmSecSpin->SetToolTip(_("Enter seconds."));
	minPerKmSizer->Add( cMinPerKmSecSpin, 0, wxEXPAND|wxALL);
	minPerKmSizer->Add( new wxStaticText(this, wxID_ANY,_("sec")));

	Connect(cMinPerKmSecSpin->GetId(),  -1, wxEVT_SPINCTRL,
		 (wxObjectEventFunction)
		 (wxEventFunction)
		 (wxCommandEventFunction)
		 (wxSpinEventFunction)&Calculator::Speed::OnMinPerKm);

	// Min/mile
	wxStaticBoxSizer *minPerMileSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Minutes per mile [min/mile]")), wxHORIZONTAL);
	sizer->Add(minPerMileSizer, 0, wxEXPAND|wxALL);

	cMinPerMileMinSpin = new wxSpinCtrl(this, wxID_ANY, "5", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxALIGN_CENTRE_HORIZONTAL,
							0, 20, 5);
	Connect(cMinPerMileMinSpin->GetId(),  -1, wxEVT_SPINCTRL,
		 (wxObjectEventFunction)
		 (wxEventFunction)
		 (wxCommandEventFunction)
		 (wxSpinEventFunction)&Calculator::Speed::OnMinPerMile);
	cMinPerMileMinSpin->SetToolTip(_("Enter minutes."));
	minPerMileSizer->Add( cMinPerMileMinSpin, 0, wxEXPAND|wxALL);

	minPerMileSizer->Add( new wxStaticText(this, wxID_ANY,_("min ")));

	cMinPerMileSecSpin = new wxSpinCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxALIGN_CENTRE_HORIZONTAL,
							0, 59, 0);

	Connect(cMinPerMileMinSpin->GetId(),  -1, wxEVT_SPINCTRL,
		 (wxObjectEventFunction)
		 (wxEventFunction)
		 (wxCommandEventFunction)
		 (wxSpinEventFunction)&Calculator::Speed::OnMinPerMile);
	cMinPerMileSecSpin->SetToolTip(_("Enter seconds."));
	minPerMileSizer->Add( cMinPerMileSecSpin, 0, wxEXPAND|wxALL);
	minPerMileSizer->Add( new wxStaticText(this, wxID_ANY,_("sec")));

	// Km/h
	wxStaticBoxSizer *kmPerHourSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Kilometer per hour [km/h]")), wxHORIZONTAL);
	sizer->Add(kmPerHourSizer, 0, wxEXPAND|wxALL);

	cKmPerHour = new wxTextCtrl(this, wxID_ANY, "12", wxDefaultPosition, wxSize(70,-1));
	cKmPerHour->SetToolTip(_("Enter km/h."));
	kmPerHourSizer->Add( cKmPerHour, 0, wxEXPAND|wxALL);

	cDistanceGrid = new wxGrid( this, wxID_ANY );
//	cDistanceGrid->SetLabelFont(cDistanceGrid->GetLabelFont().MakeSmaller());
	sizer->Add(cDistanceGrid,1, wxEXPAND|wxALL, 5);

	cDistanceGrid->CreateGrid(10, 1);
	cDistanceGrid->SetColLabelValue(0,_("Time"));
	cDistanceGrid->SetRowLabelValue(0,_("100m"));
	cDistanceGrid->SetRowLabelValue(1,_("200m"));
	cDistanceGrid->SetRowLabelValue(2,_("400m"));
	cDistanceGrid->SetRowLabelValue(3,_("800m"));
	cDistanceGrid->SetRowLabelValue(4,_("1500m"));
	cDistanceGrid->SetRowLabelValue(5,_("3000m"));
	cDistanceGrid->SetRowLabelValue(6,_("5000m"));
	cDistanceGrid->SetRowLabelValue(7,_("10000m"));
	cDistanceGrid->SetRowLabelValue(8,_("Half marathon"));
	cDistanceGrid->SetRowLabelValue(9,_("Marathon"));
	cDistanceGrid->AutoSize();

	SetSizerAndFit(sizer);

	UserPtr pUser = User::GetUser();
	cMinPerKmMinSpin->SetValue(pUser->calculatorSpeedMin);
	cMinPerKmSecSpin->SetValue(pUser->calculatorSpeedSec);

	Update(MIN_PER_KM);
}

void Calculator::Speed::OnMinPerKm( wxSpinEvent &WXUNUSED(e) )
{
	Update(MIN_PER_KM);
}

void Calculator::Speed::OnMinPerMile( wxSpinEvent &WXUNUSED(e) )
{
	Update(MIN_PER_MILE);
}

void Calculator::Speed::Update(ESpeedType const &sender )
{
	int inVal1, inVal2;
	int val1=0, val2=0;
	switch (sender)
	{
	case MIN_PER_KM:
		inVal1 = cMinPerKmMinSpin->GetValue();
		inVal2 = cMinPerKmSecSpin->GetValue();
		Converter::Convert(MIN_PER_KM, MIN_PER_MILE, inVal1, inVal2, val1, val2);
		cMinPerMileMinSpin->SetValue(val1);
		cMinPerMileSecSpin->SetValue(val2);

		Converter::Convert(MIN_PER_KM, KM_PER_HOUR, inVal1, inVal2, val1, val2);
		if (val2 >= 10)
			cKmPerHour->ChangeValue( wxString::Format("%d.%d",val1,val2) );
		else
			cKmPerHour->ChangeValue( wxString::Format("%d.0%d",val1,val2) );
		break;

	case MIN_PER_MILE:
		inVal1 = cMinPerMileMinSpin->GetValue();
		inVal2 = cMinPerMileSecSpin->GetValue();
		Converter::Convert(MIN_PER_MILE, MIN_PER_KM, inVal1, inVal2, val1, val2);
		cMinPerKmMinSpin->SetValue(val1);
		cMinPerKmSecSpin->SetValue(val2);

		Converter::Convert(MIN_PER_MILE, KM_PER_HOUR, inVal1, inVal2, val1, val2);
		if (val2 >= 10)
			cKmPerHour->ChangeValue( wxString::Format("%d.%d",val1,val2) );
		else
			cKmPerHour->ChangeValue( wxString::Format("%d.0%d",val1,val2) );
		break;

	}

	wxTimeSpan time, pace(0,cMinPerKmMinSpin->GetValue(), cMinPerKmSecSpin->GetValue());

	cDistanceGrid->Freeze();
	time = Converter::GetTime(0.1,pace,MIN_PER_KM);
	cDistanceGrid->SetCellValue(0,0,time.Format());
	time = Converter::GetTime(0.2,pace,MIN_PER_KM);
	cDistanceGrid->SetCellValue(1,0,time.Format());
	time = Converter::GetTime(0.4,pace,MIN_PER_KM);
	cDistanceGrid->SetCellValue(2,0,time.Format());
	time = Converter::GetTime(0.8,pace,MIN_PER_KM);
	cDistanceGrid->SetCellValue(3,0,time.Format());
	time = Converter::GetTime(1.5,pace,MIN_PER_KM);
	cDistanceGrid->SetCellValue(4,0,time.Format());
	time = Converter::GetTime(3.0,pace,MIN_PER_KM);
	cDistanceGrid->SetCellValue(5,0,time.Format());
	time = Converter::GetTime(5.0,pace,MIN_PER_KM);
	cDistanceGrid->SetCellValue(6,0,time.Format());
	time = Converter::GetTime(10.0,pace,MIN_PER_KM);
	cDistanceGrid->SetCellValue(7,0,time.Format());
	time = Converter::GetTime(21.0975,pace,MIN_PER_KM);
	cDistanceGrid->SetCellValue(8,0,time.Format());
	time = Converter::GetTime(42.195,pace,MIN_PER_KM);
	cDistanceGrid->SetCellValue(9,0,time.Format());
	cDistanceGrid->SetColSize(0, 64);
	//cDistanceGrid->AutoSize();
	//cDistanceGrid->AdjustScrollbars();
	cDistanceGrid->Thaw();

	UserPtr pUser = User::GetUser();
	pUser->calculatorSpeedMin = cMinPerKmMinSpin->GetValue();
	pUser->calculatorSpeedSec = cMinPerKmSecSpin->GetValue();

//    cDistanceGrid->SetSize(cDistanceGrid->GetBestVirtualSize());
//    cDistanceGrid->Fit();
//    cDistanceGrid->Refresh();
}

Calculator::Predictor::Predictor( wxWindow *pParent ) :
wxPanel (pParent, wxID_ANY, wxDefaultPosition, wxDefaultSize )
{

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL); 
	

	
	wxStaticBoxSizer *raceSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Predict times for this race")), wxHORIZONTAL);
	sizer->Add(raceSizer, 0, wxEXPAND|wxALL);

	// Distance
	cDistanceNames.Add(_("3 km         ")); 
	cDistanceNames.Add(_("5 km         ")); 
	cDistanceNames.Add(_("10 km        ")); 
	cDistanceNames.Add(_("Half marathon")); 
	cDistanceNames.Add(_("Marathon     ")); 

	int i=0;
	cDistances = std::vector<double>(5);
	cDistances[i++] = 3.000;
	cDistances[i++] = 5.000;
	cDistances[i++] = 10.000;
	cDistances[i++] = 21.0975;
	cDistances[i++] = 42.195;
	cpSelectedDistance = new wxComboBox(this, wxID_ANY, cDistanceNames[2], wxDefaultPosition, wxDefaultSize, cDistanceNames, wxCB_READONLY | wxCB_DROPDOWN );

	Connect(cpSelectedDistance->GetId(),  -1, wxEVT_COMBOBOX,
		 (wxObjectEventFunction)
		 (wxEventFunction)
		 (wxCommandEventFunction)&Calculator::Predictor::OnDistance);

	raceSizer->Add( cpSelectedDistance, 0, wxRIGHT, 5 );

	// Hour
	cHourSpin = new wxSpinCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize(-1,-1), wxSP_ARROW_KEYS|wxALIGN_CENTRE_HORIZONTAL,
							0, 7, 0);
	Connect(cHourSpin->GetId(),  -1, wxEVT_SPINCTRL,
		 (wxObjectEventFunction)
		 (wxEventFunction)
		 (wxCommandEventFunction)
		 (wxSpinEventFunction)&Calculator::Predictor::OnHour);

	cHourSpin->SetToolTip(_("Enter hours."));
	raceSizer->Add( cHourSpin, 0, wxALL);

	raceSizer->Add( new wxStaticText(this, wxID_ANY,_("hours ")));

	// Minute
	cMinuteSpin = new wxSpinCtrl(this, wxID_ANY, "45", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxALIGN_CENTRE_HORIZONTAL,
							0, 59, 45);
	cMinuteSpin->SetToolTip(_("Enter minutes."));
	raceSizer->Add( cMinuteSpin, 0, wxALL);
	raceSizer->Add( new wxStaticText(this, wxID_ANY,_("min ")));

	Connect(cMinuteSpin->GetId(),  -1, wxEVT_SPINCTRL,
		 (wxObjectEventFunction)
		 (wxEventFunction)
		 (wxCommandEventFunction)
		 (wxSpinEventFunction)&Calculator::Predictor::OnMinute);

	// Second
	cSecondSpin = new wxSpinCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxALIGN_CENTRE_HORIZONTAL,
							0, 59, 0);
	cSecondSpin->SetToolTip(_("Enter minutes."));
	raceSizer->Add( cSecondSpin, 0, wxALL);
	raceSizer->Add( new wxStaticText(this, wxID_ANY,_("sec")));

	Connect(cSecondSpin->GetId(),  -1, wxEVT_SPINCTRL,
		 (wxObjectEventFunction)
		 (wxEventFunction)
		 (wxCommandEventFunction)
		 (wxSpinEventFunction)&Calculator::Predictor::OnSecond);

	// Result
	wxStaticBoxSizer *resultSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Predicted times")), wxHORIZONTAL);
	sizer->Add(resultSizer, 0, wxEXPAND|wxALL);

	cResultText = new wxStaticText(this, wxID_ANY, _(""));
	resultSizer->Add( cResultText );

	SetSizer( sizer );

	Update();
}

void Calculator::Predictor::OnHour( wxSpinEvent &e )
{
	Update();
}

void Calculator::Predictor::OnMinute( wxSpinEvent &e )
{
	Update();
}

void Calculator::Predictor::OnSecond( wxSpinEvent &e )
{
	Update();
}

void Calculator::Predictor::OnDistance( wxCommandEvent &e )
{
	Update();
}

void Calculator::Predictor::Update()
{
	int distIdx = cpSelectedDistance->GetCurrentSelection();
	double d1 = cDistances[distIdx];
	wxTimeSpan raceTime(this->cHourSpin->GetValue(), cMinuteSpin->GetValue(), cSecondSpin->GetValue());
	double t1 = raceTime.GetValue().ToDouble();
	wxString msg;
	for (int i=0; i<cDistances.size(); i++)
	{
		double d2 = cDistances[i];
		double t2 = t1*pow(d2/d1, 1.06);
		wxLongLong l;
		l.Assign(t2);
		wxTimeSpan ts(l);
		msg += wxString::Format("%s %s\n", cDistanceNames[i], ts.Format() );
	}
	wxFontInfo fontInfo(14);
	fontInfo.Bold(true);
	fontInfo.Family(wxFONTFAMILY_TELETYPE);
	wxFont font(fontInfo);
	cResultText->SetFont(font);
	cResultText->SetLabel( msg );
	Fit();
}
