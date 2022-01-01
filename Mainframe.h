#pragma once

#include	<Defines.h>
#include	<wx/frame.h>
#include    <wx/aui/framemanager.h>
#include	<wx/menu.h>
#include	<wx/html/helpctrl.h>
#include    <boost/make_shared.hpp>


// Define a new frame type: this is going to be our main frame

/**
 * @brief The main frame for the application.
 *
 * Contains multiple panes, which are configurable into perspectives.
*/
class MyFrame : public wxFrame {
public:
    /**
     * @brief Constructor
     * @param title Title
     * @param installationDirectory Installation directory
    */
    MyFrame(const wxString& title, wxString const &installationDirectory);

    /**
     * @brief Destructor
    */
    virtual ~MyFrame();

    /**
     * @brief Handle quit
     * @param event event
    */
    void OnQuit(wxCommandEvent& event);

    /**
     * @brief Show about dialog
     * @param event event
    */
    void OnAbout(wxCommandEvent& event);

    /**
     * @brief Handle close
     * @param e event
    */
    void OnClose( wxCloseEvent &e );

    /**
     * @brief Toggle fullscreen mode on/off
     * @param e
    */
    void OnFullscreen( wxCommandEvent &e );

    /**
     * @brief Toggle check/uncheck fullscreen depending on mode
     * @param e
    */
    void OnUpdateFullscreen( wxUpdateUIEvent &e );

    /**
     * @brief Set Advanced User Interface (AUI) manager.
     * @param otherAuiManager AUI manager
    */
    void SetAuiManager(boost::shared_ptr<wxAuiManager> otherAuiManager);

    /**
     * @brief Get Advanced User Interface (AUI) manager.
     * @return AUI manager
    */
    boost::shared_ptr<wxAuiManager> GetAuiManager() const;

    /**
     * @brief Show help window
     * @param event event
    */
    void OnHelp(wxCommandEvent& event);

private:
    boost::shared_ptr<wxAuiManager> auiManager;
    wxHtmlHelpController *cpHelp;
    wxString installationDirectory;
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};