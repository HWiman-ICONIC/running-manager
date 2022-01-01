#pragma once

#include	<Defines.h>
#include	<Intensity.h>
#include	<wx/string.h>
#include	<vector>

/**
 * @brief Type of training
*/
struct TrainingType {
    /**
     * @brief Default constructor
    */
    TrainingType() {}

    /**
     * @brief Create a training type with all intensisties
     * @param type Type of training, e.g. Recovery
     * @param shortName Human readable short name
     * @param description Human readable description
     * @param format Format string
     * @todo Use boost::property_tree and xml for formatting instead
    */
    TrainingType( PTTrainingType type, wxString const &shortName, wxString const &description, wxString const &format );

    /**
     * @brief Destructor
    */
    virtual ~TrainingType();

    /**
     * @brief Create from format string
     * @param format format string
     * @return
    */
    bool Create( wxString const &format );

    wxString shortName;
    wxString description;
    PTTrainingType type;
    std::vector<IntensityPtr> intensity;
};

static TrainingType gTrainingType[] = {
    TrainingType(NONE, _("Rest"), _("No activity"), wxString("-1")),

    TrainingType(RR,_("Recovery Run"), _("Zone 1 only. The day after challenging workout.\nAn alternative to a day off. Increases running volume."),
                 wxString("2,\
		    1,1,20.0,-1,\
			2,1,25.0,-1,\
			3,1,30.0,-1,\
			4,1,35.0,-1,\
			5,1,40.0,-1,\
			6,1,45.0,-1,\
			7,1,50.0,-1,\
			8,1,55.0,-1,\
			9,1,60.0,-1")),

    TrainingType(FR,_("Foundation Run"), _("The bread and butter of 80/20 training.\nEnsures that you do enough low intensity running."),
                 wxString("2,\
			1,1,5,2,10,1,5,-1,\
			2,1,5,2,15,1,5,-1,\
			3,1,5,2,20,1,5,-1,\
			4,1,5,2,25,1,5,-1,\
			5,1,5,2,30,1,5,-1,\
			6,1,5,2,35,1,5,-1,\
			7,1,5,2,40,1,5,-1,\
			8,1,5,2,45,1,5,-1,\
			9,1,5,2,50,1,5,-1")),

    TrainingType(LR,_("Long Run"), _("Extended foundation run. Measured in distance to enforce\nendurance for the entire race distance regardless of training level."),
                 wxString("1,\
			1,1,1.0,2,4.5,1,0.5,-1,\
			2,1,1.0,2,5.5,1,0.5,-1,\
			3,1,1.0,2,6.5,1,0.5,-1,\
			4,1,1.0,2,7.5,1,0.5,-1,\
			5,1,1.0,2,8.5,1,0.5,-1,\
			6,1,1.0,2,9.5,1,0.5,-1,\
			7,1,1.0,2,10.5,1,0.5,-1,\
			8,1,1.0,2,11.5,1,0.5,-1,\
			9,1,1.0,2,12.5,1,0.5,-1,\
			10,1,1.0,2,13.5,1,0.5,-1,\
			11,1,1.0,2,14.5,1,0.5,-1,\
			12,1,1.0,2,15.5,1,0.5,-1,\
			13,1,1.0,2,16.5,1,0.5,-1,\
			14,1,1.0,2,17.5,1,0.5,-1,\
			15,1,1.0,2,18.5,1,0.5,-1")),

    TrainingType(FFR,_("Fast Finish Run"), _("A relatively short Zone 3 at the end of a foundation\nrun. Provides some quality during base and recovery training."),
                 wxString("2,\
			1,1,5,2,15,3,5,-1,\
			2,1,5,2,20,3,5,-1,\
			3,1,5,2,20,3,10,-1,\
			4,1,5,2,25,3,10,-1,\
			5,1,5,2,25,3,12,-1,\
			6,1,5,2,30,3,12,-1,\
			7,1,5,2,35,3,12,-1,\
			8,1,5,2,35,3,15,-1,\
			9,1,5,2,40,3,15,-1,\
			10,1,5,2,45,3,15,-1")),

    TrainingType(TR, _("Tempo Run"), _("Zone 3 with warm up and cool down.\nImproves sustained aggressive speed."),
                 wxString("2,\
			1,1,5,2,5,3,15,2,5,1,5,-1,\
			2,1,5,2,5,3,18,2,5,1,5,-1,\
			3,1,5,2,5,3,20,2,5,1,5,-1,\
			4,1,5,2,5,3,24,2,5,1,5,-1,\
			5,1,5,2,5,3,28,2,5,1,5,-1,\
			6,1,5,2,5,3,30,2,5,1,5,-1,\
			7,1,5,2,5,3,32,2,5,1,5,-1,\
			8,1,5,2,5,3,36,2,5,1,5,-1,\
			9,1,5,2,5,3,40,2,5,1,5,-1,\
			10,1,5,2,5,3,45,2,5,1,5,-1")),

    TrainingType(CIR, _("Cruise Interval Run"), _("Multiple long intervals with Zone 1 recoveries.\nAllows more total work than tempo runs."),
                 wxString("2,\
			1,1,5,2,5,4X,3,5,1,3,1X,2,5,1,5,-1,\
			2,1,5,2,5,4X,3,8,1,3,1X,2,5,1,5,-1,\
			3,1,5,2,5,4X,3,10,1,3,1X,2,5,1,5,-1,\
			4,1,5,2,5,4X,3,12,1,3,1X,2,5,1,5,-1,\
			5,1,5,2,5,4X,3,15,1,3,1X,2,5,1,5,-1")),

    TrainingType(LRSP, _("Long Run Speed Play"), _("Short bursts in Zone 3 sprinkled in long run.\nDone late in training cycle to increase fatigue resistance."),
                 wxString("1,\
			1,1,0.5,2,1,8X,3,0.25,1,0.75,1X,1,0.5,-1,\
			2,1,0.5,2,1,10X,3,0.25,1,0.75,1X,1,0.5,-1,\
			3,1,0.5,2,1,12X,3,0.25,1,0.75,1X,1,0.5,-1,\
			4,1,0.5,2,1,14X,3,0.25,1,0.75,1X,1,0.5,-1,\
			5,1,0.5,2,1,16X,3,0.25,1,0.75,1X,1,0.5,-1,\
			6,1,0.5,2,1,18X,3,0.25,1,0.75,1X,1,0.5,-1")),

    TrainingType(LRFF, _("Long Run Fast Finish"), _("Fast finish at end of long run.\nDone late in training cycle to increase fatigue resistance."),
                 wxString("1,\
			1,1,0.5,2,8.5,3,1,-1,\
			2,1,0.5,2,10.5,3,1,-1,\
			3,1,0.5,2,12,3,1.5,-1,\
			4,1,0.5,2,14,3,1.5,-1,\
			5,1,0.5,2,15.5,3,2,-1,\
			6,1,0.5,2,17.5,3,2,-1")),

    TrainingType(SPR, _("Speed Play Run"), _("Cross between foundation run and interval run.\nEasier than interval runs."),
                 wxString("2,\
			1,1,5,2,5,3X,4,2,1,2,1X,1,5,-1,\
			2,1,5,2,5,5X,5,1,1,2,1X,1,5,-1,\
			3,1,5,2,5,4X,4,2,1,2,1X,1,5,-1,\
			4,1,5,2,5,6X,5,1,1,2,1X,1,5,-1,\
			5,1,5,2,5,5X,4,2,1,2,1X,1,5,-1,\
			6,1,5,2,5,7X,5,1,1,2,1X,1,5,-1,\
			7,1,5,2,5,6X,4,2,1,2,1X,1,5,-1,\
			8,1,5,2,5,8X,5,1,1,2,1X,1,5,-1,\
			9,1,5,2,5,9X,5,1,1,2,1X,1,5,-1,\
			10,1,5,2,5,7X,4,2,1,2,1X,1,5,-1,\
			11,1,5,2,5,10X,5,1,1,2,1X,1,5,-1,\
			12,1,5,2,5,8X,4,2,1,2,1X,1,5,-1,\
			13,1,5,2,5,9X,4,2,1,2,1X,1,5,-1,\
			14,1,5,2,5,12X,5,1,1,2,1X,1,5,-1")),

    TrainingType(HRR, _("Hill Repetition Run"), _("Short uphill interval runs.\nBridge between base and peak training.\nLess stressful on the legs than interval runs."),
                 wxString("2,\
			1,1,5,2,5,6X,5,0.5,1,1.5,1X,1,5,-1,\
			2,1,5,2,5,8X,5,0.5,1,1.5,1X,1,5,-1,\
			3,1,5,2,5,6X,5,1,1,2,1X,1,5,-1,\
			4,1,5,2,5,10X,5,0.5,1,1.5,1X,1,5,-1,\
			5,1,5,2,5,12X,5,0.5,1,1.5,1X,1,5,-1,\
			6,1,5,2,5,8X,5,1,1,2,1X,1,5,-1,\
			7,1,5,2,5,6X,5,1.5,1,2.5,1X,1,5,-1,\
			8,1,5,2,5,10X,5,1,1,2,1X,1,5,-1,\
			9,1,5,2,5,8X,5,1.5,1,2.5,1X,1,5,-1,\
			10,1,5,2,5,12X,5,1,1,2,1X,1,5,-1,\
			11,1,5,2,5,10X,5,1.5,1,2.5,1X,1,5,-1,\
			12,1,5,2,5,12X,5,0.5,1,1.5,1X,1,5,-1")),

    TrainingType(SIR, _("Short Interval Run"), _("Intensive short Zone 5 with Zone 1 recoveries.\nEnhances aerobic capacity, fatigue\nresistance and running economy."),
                 wxString("2,\
			1,1,5,2,5,6X,5,1,1,2,1X,1,5,-1,\
			2,1,5,2,5,8X,5,1,1,2,1X,1,5,-1,\
			3,1,5,2,5,6X,5,1.5,1,2.5,1X,1,5,-1,\
			4,1,5,2,5,10X,5,1,1,2,1X,1,5,-1,\
			5,1,5,2,5,8X,5,1.5,1,2.5,1X,1,5,-1,\
			6,1,5,2,5,12X,5,1,1,2,1X,1,5,-1,\
			7,1,5,2,5,10X,5,1.5,1,2.5,1X,1,5,-1,\
			8,1,5,2,5,12X,5,1.5,1,2.5,1X,1,5,-1")),

    TrainingType(LIR, _("Long Interval Run"), _("Zone 4 intervals with Zone 1 recoveries.\nMaximizes high-intensity fatigue resistance.."),
                 wxString("2,\
			1,1,5,2,5,3X,4,3,1,2,1X,1,5,-1,\
			2,1,5,2,5,4X,4,3,1,2,1X,1,5,-1,\
			3,1,5,2,5,3X,4,5,1,3,1X,1,5,-1,\
			4,1,5,2,5,5X,4,3,1,2,1X,1,5,-1,\
			5,1,5,2,5,6X,4,3,1,2,1X,1,5,-1,\
			6,1,5,2,5,4X,4,5,1,3,1X,1,5,-1,\
			7,1,5,2,5,5X,4,5,1,3,1X,1,5,-1,\
			8,1,5,2,5,6X,4,5,1,3,1X,1,5,-1,\
			9,1,5,2,5,7X,4,5,1,3,1X,1,5,-1,\
			10,1,5,2,5,8X,4,5,1,3,1X,1,5,-1")),

    TrainingType(MIR, _("Mixed Interval Run"), _("Sharpens the runner up for racing after\nobtaining a solid foundation."),
                 wxString("2,\
			1,1,5,2,5,5,1,1,2,4,3,1,2,3,5,1,2,4,3,1,2,5,1,1,5,-1,\
			2,1,5,2,5,5,1.5,1,2,4,5,1,2,3,10,1,2,4,5,1,2,5,1.5,1,5,-1,\
			3,1,5,2,5,2X,5,1,1,2,2X,4,3,1,2,1X,3,10,1,2,2X,4,3,1,2,2X,5,1,1,2,1X,1,5,-1,\
			4,1,5,2,5,2X,5,1.5,1,2.5,2X,4,5,1,2,1X,3,10,1,2,2X,4,5,1,2,2X,5,1.5,1,2,1X,1,5,-1")),

    TrainingType(HM, _("Half Marathon"), _("Competition"),
                 wxString("0,\
			1,3,21.0975,-1")),

    TrainingType(M, _("Marathon"), _("Competition"),
                 wxString("0,\
			1,3,42.195,-1")),

    TrainingType(KM10, _("10 kilometer competition"), _("Competition"),
                 wxString("0,\
			1,3,10,-1")),

    TrainingType(KM5, _("5 kilometer competition"), _("Competition"),
                 wxString("0,\
			1,3,5,-1")),
};