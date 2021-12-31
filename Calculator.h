#pragma once

#include	<Defines.h>
#include	<vector>

#include	<wx/aui/auibook.h>
#include	<wx/panel.h>
#include	<wx/textctrl.h>
#include	<wx/grid.h>
#include	<wx/stattext.h>

namespace rm
{
	class Calculator : public wxAuiNotebook
	{
	public:
		class Speed : public wxPanel
		{
		public:
			

			Speed( wxWindow *pParent );

			void OnMinPerKm( wxSpinEvent &e );
			void OnMinPerMile( wxSpinEvent &e );

			void Update(ESpeedType const &sender );

			wxSpinCtrl *cMinPerKmMinSpin;
			wxSpinCtrl *cMinPerKmSecSpin;
			wxSpinCtrl *cMinPerMileMinSpin;
			wxSpinCtrl *cMinPerMileSecSpin;
			wxTextCtrl *cKmPerHour;
			wxGrid *cDistanceGrid;
		};

		class Predictor : public wxPanel {
		public:
			Predictor( wxWindow *pParent );
			wxArrayString cDistanceNames;
			std::vector<double> cDistances;
			void OnHour( wxSpinEvent &e );

			void OnMinute( wxSpinEvent &e );

			void OnSecond( wxSpinEvent &e );

			void OnDistance( wxCommandEvent &e );

			void Update();

			wxComboBox *cpSelectedDistance;
			wxSpinCtrl *cHourSpin;
			wxSpinCtrl *cMinuteSpin;
			wxSpinCtrl *cSecondSpin;
			wxStaticText *cResultText;
		};

		Calculator( wxWindow *pParent );
	};
}