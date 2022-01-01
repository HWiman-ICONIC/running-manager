#pragma once

#include	<Defines.h>
#include	<vector>

#include	<wx/aui/auibook.h>
#include	<wx/panel.h>
#include	<wx/textctrl.h>
#include	<wx/grid.h>
#include	<wx/stattext.h>

/**
 * @brief RunningManager namespace
*/
namespace rm {
/**
 * @brief GUI for predictor and unit conversion
*/
class Calculator : public wxAuiNotebook {
public:
    /**
     * @brief GUI panel for unit conversion
    */
    class Speed : public wxPanel {
    public:

        /**
         * @brief Constructor
         * @param pParent Parent window
        */
        Speed( wxWindow *pParent );

        /**
         * @brief Convert from min/km
         * @param e Event
        */
        void OnMinPerKm( wxSpinEvent &e );

        /**
         * @brief Convert from min/mile
         * @param e
        */
        void OnMinPerMile( wxSpinEvent &e );

        /**
         * @brief Update after new event
         * @param sender Convert from this
        */
        void Update(ESpeedType const &sender );

        wxSpinCtrl *cMinPerKmMinSpin;
        wxSpinCtrl *cMinPerKmSecSpin;
        wxSpinCtrl *cMinPerMileMinSpin;
        wxSpinCtrl *cMinPerMileSecSpin;
        wxTextCtrl *cKmPerHour;
        wxGrid *cDistanceGrid;
    };

    /**
     * @brief GUI for time predictor for different distances
    */
    class Predictor : public wxPanel {
    public:
        /**
         * @brief Constructor
         * @param pParent Parent
        */
        Predictor( wxWindow *pParent );

        /**
         * @brief Handle changed hour
         * @param e Event
        */
        void OnHour( wxSpinEvent &e );

        /**
         * @brief Handle changed minute
         * @param e Event
        */
        void OnMinute( wxSpinEvent &e );

        /**
         * @brief Handle changed second
         * @param e Event
        */
        void OnSecond( wxSpinEvent &e );

        /**
         * @brief Handle changed distance
         * @param e
        */
        void OnDistance( wxCommandEvent &e );

        /**
         * @brief Update after change
        */
        void Update();

        wxArrayString cDistanceNames;
        std::vector<double> cDistances;

        wxComboBox *cpSelectedDistance;
        wxSpinCtrl *cHourSpin;
        wxSpinCtrl *cMinuteSpin;
        wxSpinCtrl *cSecondSpin;
        wxStaticText *cResultText;
    };

    /**
     * @brief Constructor
     * @param pParent Parent
    */
    Calculator( wxWindow *pParent );
};
}