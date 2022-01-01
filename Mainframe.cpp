#include	<Mainframe.h>
#include	<wx/textdlg.h>
#include <wx/aboutdlg.h>
//#include    <sample_128.xpm>
//#include    <sample_32.xpm>

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
    EVT_MENU(Minimal_Help, MyFrame::OnHelp)
    EVT_BUTTON(Minimal_Help, MyFrame::OnHelp)
    EVT_MENU(Minimal_Fullscreen, MyFrame::OnFullscreen)
    EVT_UPDATE_UI(Minimal_Fullscreen, MyFrame::OnUpdateFullscreen)
    EVT_CLOSE(MyFrame::OnClose)
wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title, wxString const &installationDirectory)
    : wxFrame(NULL, wxID_ANY, title)
{
    this->installationDirectory = installationDirectory;
    cpHelp = NULL;
    auiManager = NULL;
    SetIcon(wxICON(sample));
    /*    // set the frame icon
        wxIcon sampleIcon;
    //    #if __WXWINDOWS__
    //    sampleIcon = wxICON(sample);
    //    #else
        sampleIcon = wxIcon(wxICON(sample_32));
        //  #endif
        SetIcon(sampleIcon);

    #ifdef __WXGTK__
        SetFont(GetFont().MakeSmaller());
    #endif*/

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_Help, "&Contents\tF1", "Show help");
    helpMenu->Append(Minimal_About, "&About\tF8", "Show about dialog");


    //fileMenu->Append(Minimal_Create_TrainingProgram, _("Create training program\tCtrl+T"), _("Create a training program"));
    fileMenu->Append(Minimal_Save_Calendar, _("Save training calendar...\tCtrl+S"),_("Save training plan to calendar file (*.csv)"));

    //fileMenu->Append(Minimal_Zone, _("Set pulse...\tCtrl+Z"), _("Set new lactate threshold pulse"));
    fileMenu->AppendSeparator();
    fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");
    /*wxMenu *unitMenu = new wxMenu();
    fileMenu->AppendSubMenu(unitMenu, _("Distance unit"), _("Choose km or miles for distances"));
    unitMenu->AppendCheckItem(Minimal_Unit_Km, _("Kilometer\tCtrl+K"), _("Set distances in km"));
    unitMenu->AppendCheckItem(Minimal_Unit_Miles, _("Miles\tCtrl+M"), _("Set distances in miles"));


    */
    //wxMenu *userMenu = new wxMenu;
    //userMenu->Append(Minimal_Create_User, _("Create user...\tCtrl+N"), _("Create a new user"));
    //userMenu->Append(Minimal_Select_User, _("Select user...\tCtrl+U"), _("Select a user"));
    //userMenu->Append(Minimal_Delete_User, _("Delete user...\tCtrl+X"), _("Delete a user"));

    wxMenu *perspectiveMenu = new wxMenu;
    perspectiveMenu->Append(Minimal_Load_Perspective, _("Load...\tCtrl+L"), _("Apply a saved window layout"));
    perspectiveMenu->Append(Minimal_Save_Perspective, _("Save...\tCtrl+P"), _("Saved current window layout"));
    perspectiveMenu->Append(Minimal_Delete_Perspective, _("Delete...\tCtrl+D"), _("Delete one or more window layouts"));
    perspectiveMenu->Append(Minimal_Fullscreen, _("Show fullscreen\tCtrl+F"), _("Show fullscreen layout"), wxITEM_CHECK);

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
//    menuBar->Append(userMenu, "&User");
    menuBar->Append(perspectiveMenu, "&Perspective");
    menuBar->Append(helpMenu, "&Help");

    //wxAuiNotebook* ctrl = new wxAuiNotebook(this, wxID_ANY);
    //ctrl->AddPage(new wxWindow(ctrl, wxID_ANY), _("

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Welcome to RunningManager!");
#endif // wxUSE_STATUSBAR
}

MyFrame::~MyFrame()
{
    if (auiManager) {
        wxEvtHandler *eh = this->GetEventHandler();
        if ( eh->GetNextHandler() == dynamic_cast<wxEvtHandler*>(auiManager.get()) ) {
            PopEventHandler();
        }
        auiManager = boost::shared_ptr<wxAuiManager>();
    }
    /*	if (this->GetEventHandler() != NULL)
    	{
    		delete GetEventHandler();
    		SetEventHandler(NULL);
    	}*/
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
    //Close(false);
}

void MyFrame::OnClose( wxCloseEvent &WXUNUSED(e) )
{
    if (auiManager) {
        wxConfig::Get()->Write("LastPerspective", GetAuiManager()->SavePerspective());
//        PopEventHandler();
//        auiManager = NULL;
    }
    Destroy();
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo info;
    info.SetName(GetTitle());
    info.SetWebSite(wxT("http://www.mattfitzgerald.org/"));
    info.SetCopyright(wxT("(C) Håkan Wiman (Software)\n(C) Matt Fitzgerald (Training plans, used with permission)"));
    info.AddDeveloper(wxT("Håkan Wiman"));
    wxString description = wxString::Format(_("The training plans and concepts are based on the book \"80/20 Running\" by Matt Fitzgerald (2014).\nTo get the most out of %s you are strongly recommended to buy a copy of this book!\n\n%s"), GetTitle(),wxGetOsDescription());
    info.SetDescription(description);
#ifdef wxHAS_IMAGES_IN_RESOURCES
    info.SetIcon(wxIcon(wxString("aaaaaaaa"),wxBITMAP_TYPE_ICO_RESOURCE,128,128));
#else
    info.SetIcon(wxIcon(wxICON(sample_128)));
#endif
    wxAboutBox(info);
}

void MyFrame::OnHelp(wxCommandEvent& WXUNUSED(event))
{
    wxAuiPaneInfo &helpPane = auiManager->GetPane("Help");
    helpPane.Float();
    helpPane.Show();
    auiManager->Update();
    /*
    	if ( cpHelp == NULL )
    	{
    		cpHelp = new wxHtmlHelpController( wxHF_EMBEDDED , this );
    		cpHelp->UseConfig(wxConfig::Get());
    		//cpHelp->SetTempDir(path);

    		wxFileName fn;
    		fn.SetPath(installationDirectory);
    		fn.SetFullName("RunningManager.zip");
    		cpHelp->AddBook( fn.GetFullPath() );
    		auiManager->AddPane( cpHelp->GetHelpWindow(), wxAuiPaneInfo().Right().Layer(2).Caption(_("Help")).MaximizeButton());
    		auiManager->GetPane("Help").MinSize(wxSize(128,128));
    		cpHelp->Display("80/20 Running Manager Layout");
    		auiManager->Update();
    	}
    	else
    	{
    		auiManager->GetPane("Help").Show();
    	}*/
}

void MyFrame::OnFullscreen( wxCommandEvent &WXUNUSED(e) )
{
    ShowFullScreen(!IsFullScreen(),wxFULLSCREEN_NOTOOLBAR | wxFULLSCREEN_NOSTATUSBAR | wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION);
    wxConfigBase *configuration = wxConfig::Get();
    if (this->IsFullScreen()) {
        configuration->Write("Fullscreen", "1");
    } else {
        configuration->Write("Fullscreen", "0");
    }
}

void MyFrame::OnUpdateFullscreen( wxUpdateUIEvent &e )
{
    e.Check(IsFullScreen());
}

void MyFrame::SetAuiManager(boost::shared_ptr<wxAuiManager> otherAuiManager)
{
    auiManager = otherAuiManager;
    if (auiManager) {
        auiManager->SetManagedWindow(this);
    }
}

boost::shared_ptr<wxAuiManager> MyFrame::GetAuiManager() const
{
    return auiManager;
}
