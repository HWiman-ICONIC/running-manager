#pragma once

#include	"Defines.h"
#include	<wx/frame.h>
#include    <wx/aui/framemanager.h>
#include	<wx/menu.h>
#include	<wx/html/helpctrl.h>
#include    <boost/make_shared.hpp>


// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame {
public:
    // ctor(s)
    MyFrame(const wxString& title, wxString const &installationDirectory);
    virtual ~MyFrame();

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose( wxCloseEvent &e );
    void OnFullscreen( wxCommandEvent &e );
    void OnUpdateFullscreen( wxUpdateUIEvent &e );
    void SetAuiManager( boost::shared_ptr<wxAuiManager> otherAuiManager ) {
        auiManager = otherAuiManager;
        if (auiManager) {
            auiManager->SetManagedWindow(this);
        }
    }
    boost::shared_ptr<wxAuiManager> GetAuiManager() {
        return auiManager;
    }

    void OnHelp(wxCommandEvent& event);
private:
    boost::shared_ptr<wxAuiManager> auiManager;
    wxHtmlHelpController *cpHelp;
    wxString installationDirectory;
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};