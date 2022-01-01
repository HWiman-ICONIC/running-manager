#pragma once

#include	<wx/string.h>
#include	<wx/intl.h>
#include	<wx/colour.h>
#include	<wx/clntdata.h>
#include	<wx/datetime.h>

#define RM_DATE_SELECTED 1

/**
 * @brief Race distance
*/
enum class PTDistance {
    PTD_5KM = 0,        //!< 5 km
    PTD_10KM,           //!< 10 km
    PTD_HALF_MARATHON,  //!< Half marathon
    PTD_MARATHON        //!< Marathon
};

/**
 * @brief Training program level
*/
enum PTLevel {
    PTL_LOW = 0,        //!< Low level
    PTL_MEDIUM,         //!< Medium level
    PTL_HIGH            //!< High level
};

/**
 * @brief Training type
*/
enum PTTrainingType {
    NONE = 0,   //!< Rst
    RR,         //!< Recovery Run
    FR,         //!< Foundation run
    LR,         //!< Long run
    FFR,        //!< Fast finish run
    TR,         //!< Tempo run
    CIR,        //!< Cruise interval
    LRSP,       //!< Long run speed play
    LRFF,       //!< Long run fast finish
    SPR,        //!< Speed play
    HRR,        //!< Hill repetition
    SIR,        //!< Short interval
    LIR,        //!< Long interval
    MIR,        //!< MIxed interval
    HM,         //!< Half marathon
    M,          //!< Marathon
    KM10,       //!< 10 km
    KM5         //!< 5 km
};

/**
 * @brief Intensity zones
*/
enum PTZone {
    ZONE0 = 0,  //!< No zone
    ZONE1,      //!< Zone 1
    ZONE2,      //!< Zone 2
    ZONE3,      //!< Zone 3
    ZONE4,      //!< Zone 4
    ZONE5       //!< Zone 5
};

/**
 * @brief Unit
*/
enum PTUnit {
    KM =  0,    //!< Kilometers
    MILES,      //!< Miles
    TIME        //!< Time
};

/**
 * @brief Inensity of each zone
 * @sa PTZone
*/
static PTLevel gZoneIntensity[] = {
    PTL_LOW,        //!< No zone
    PTL_LOW,        //!< Zone 1
    PTL_LOW,        //!< Zone 2
    PTL_MEDIUM,     //!< Zone 3
    PTL_HIGH,       //!< Zone 4
    PTL_HIGH        //!< Zone 5
};

/**
 * @brief Intensity of each training type
 * @sa PTTrainingType
*/
static PTLevel gTrainingIntensity[] = {
    PTL_LOW,
    PTL_LOW,
    PTL_LOW,
    PTL_LOW,
    PTL_MEDIUM,
    PTL_MEDIUM,
    PTL_MEDIUM,
    PTL_MEDIUM,
    PTL_MEDIUM,
    PTL_HIGH,
    PTL_HIGH,
    PTL_HIGH,
    PTL_HIGH,
    PTL_HIGH,
    PTL_HIGH,
    PTL_HIGH,
    PTL_HIGH,
    PTL_HIGH
};

/**
 * @brief Training program phase
*/
enum PTPhase {
    PTP_BASE,   //!< Initial base phase
    PTP_PEAK,   //!< Middle peak phase
    PTP_TAPER   //!< Final taper phase
};

static wxString gPhase[] = {
    _("Base"),
    _("Peak"),
    _("Taper")
};

static wxString gUnit[] = {
    _("km"),
    _("miles"),
    _("minutes")
};

static wxString gLevel[] = {
    _("Low"),
    _("Medium"),
    _("High")
};

static wxString gDistance[] = {
    _("5 km"),
    _("10 km"),
    _("Half Marathon (21 097 m)"),
    _("Marathon (42 195m)")
};

static wxColour gIntensityColor[] = {
    wxColour(220,255,220),
    wxColour(255,255,220),
    wxColour(255,220,220),
    wxColour(220,220,255)
};

// GUI item constants
enum {
    // menu items
    Minimal_Quit = wxID_EXIT,
    Minimal_About = wxID_ABOUT,
    Minimal_Create_TrainingProgram = 0,
    Minimal_Save_Calendar,
    Minimal_Save_Perspective,
    Minimal_Load_Perspective,
    Minimal_Unit_Km,
    Minimal_Unit_Miles,
    Minimal_Zone,
    Minimal_Help,
    Minimal_Delete_Perspective,
    Minimal_Fullscreen,
    Minimal_Set_Pace,
    Minimal_Change_Weekday,
    Minimal_Create_User,
    Minimal_Select_User,
    Minimal_Delete_User
};

/**
 * @brief Speed unit
*/
enum ESpeedType {
    MIN_PER_KM, //!< min/km
    MIN_PER_MILE, //!< min/mile
    KM_PER_HOUR //!< km/h
};

/**
 * @brief Data to submit with date events
*/
struct EventData : public wxClientData {
    wxDateTime dt;
};
