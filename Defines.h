#pragma once

#include	<wx/string.h>
#include	<wx/intl.h>
#include	<wx/colour.h>
#include	<wx/clntdata.h>
#include	<wx/datetime.h>

#define RM_DATE_SELECTED 1

enum PTDistance
{
	PTD_5KM = 0,
	PTD_10KM,
	PTD_HALF_MARATHON,
	PTD_MARATHON
};

enum PTLevel
{
	PTL_LOW = 0,
	PTL_MEDIUM,
	PTL_HIGH
};

enum PTTrainingType
{
	NONE = 0, 
	RR,
	FR,
	LR,
	FFR,
	TR,
	CIR,
	LRSP,
	LRFF,
	SPR,
	HRR,
	SIR,
	LIR,
	MIR,
	HM,
	M,
	KM10,
	KM5
};

enum PTZone
{
	ZONE0 = 0,
	ZONE1,
	ZONE2,
	ZONE3,
	ZONE4,
	ZONE5
};

enum PTUnit
{
	KM =  0,
	MILES,
	TIME
};

static PTLevel gZoneIntensity[] = {
	PTL_LOW,
	PTL_LOW,
	PTL_LOW,
	PTL_MEDIUM,
	PTL_HIGH,
	PTL_HIGH
};

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

enum PTPhase
{
	PTP_BASE,
	PTP_PEAK,
	PTP_TAPER
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

enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,
    Minimal_About = wxID_ABOUT,
	Minimal_Create_TrainingProgram = 5000,
	Minimal_Save_Calendar,
	Minimal_Save_Perspective,
	Minimal_Load_Perspective,
	Minimal_Unit_Km,
	Minimal_Unit_Miles,
	Minimal_Zone,
	Minimal_Help,
	Minimal_Delete_Perspective,
	Minimal_Fullscreen,
	Minimal_Set_Pace 
};

struct EventData : public wxClientData
{
	wxDateTime dt;
};