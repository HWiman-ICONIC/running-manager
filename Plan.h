#pragma once

#include	<vector>
#include	<map>
#include	<Week.h>
#include	<wx/textfile.h>

/**
 * @brief A training plan.
*/
struct Plan {
    /**
     * @brief Default constructor.
    */
    Plan();

    /**
     * @brief Constructor
     * @param distance Competition distance
     * @param level Traing plan level
     * @param date Competition date
     * @param weekDayOrder Which weekdays to have long runs, rest, intervals etc.
    */
    Plan(PTDistance distance, PTLevel level, wxDateTime date, wxArrayInt weekDayOrder);

    /**
     * @brief Create training/activity from string
     * @param sTraining Input string
     * @param sIntensity Output intensity
     * @param day Day
     * @param training Training/activity
    */
    void CreateTraining( wxString const &sTraining, wxString const &sIntensity, wxDateTime const &day, Training &training );

    /**
     * @brief Get training for this day.
     *
     * Possibly two trainings so a list is returned
     * @param day Input day
     * @return Training(s) for this day
    */
    std::list<Training*> GetTraining( wxDateTime const &day );

    /**
     * @brief Convert this plan to a string
     * @return plan as a string
    */
    wxString ToString();

    /**
     * @brief Create training program from given settings.
     *
     * Internally calls CreatePlan, which calls SetPlan.
     * @param unit Unit of distance (km|miles)
    */
    void CreateProgram(PTUnit const &unit);

    /**
     * @brief Helper printing the training program to current log output.
    */
    void Print();

    /**
     * @brief Save training program in Comma Separated Value file.
     *
     * This file can be imported in e.g. Google Calendar.
     * @param filename Output file name
     * @return True on success
    */
    bool SaveCsv( wxString const &filename );

    /**
     * @brief Get number of instances for each training type for each weekday
     * @return Vector with seven entries, one per weekday starting with Monday. The entries are vectors with number of instances for each of the training types
    */
    std::vector<std::vector<int>> GetTrainingTypePerWeekDay();

    std::vector<Week> weeks;
    PTDistance distance;
    PTLevel level;
    PTUnit outUnit;
    wxDateTime date;
    wxDateSpan programLength;
    wxDateTime startTime;
    std::map<int, wxString> distanceString;
    wxTextFile textFile;
    wxArrayInt weekDayOrder;

private:
    /**
    * @brief Use current settings to create training plan.
    * @sa CreateProgram SetPlan
    *
    * The plan is internally stored in a text file, ready to be exported.
    */
    void CreatePlan();

    /**
     * @brief Set plan from this comma separated configuration string
     * @param s Plan in comma separated string, created from a certain level and competition distance.
     * @sa CreateProgram CreatePlan
    */
    void SetPlan(wxString const& s);


};