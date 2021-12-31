#pragma once

#include	<vector>
#include	<map>
#include	<Week.h>
#include	<wx/textfile.h>

struct Plan {
    std::vector<Week> weeks;
    PTDistance distance;
    PTLevel level;
    PTUnit outUnit;
    wxDateTime date;
    wxDateSpan programLength;
    wxDateTime startTime;
    std::map<int,wxString> distanceString;
    wxTextFile textFile;
    wxArrayInt weekDayOrder;

    Plan();
    Plan(PTDistance distance, PTLevel level, wxDateTime date, wxArrayInt weekDayOrder);

    void CreatePlan();
    void SetPlan( wxString const &s );
    void CreateTraining( wxString const &sTraining, wxString const &sIntensity, wxDateTime const &day, Training &training );
    std::list<Training*> GetTraining( wxDateTime const &day );
    wxString ToString();
    void CreateProgram(PTUnit const &unit);
    void Print();
    bool SaveCsv( wxString const &filename );
    std::vector<std::vector<int>> GetTrainingTypePerWeekDay();
};