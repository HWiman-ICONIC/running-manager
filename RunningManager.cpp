// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "RunningManager.h"
#include	"Zone.h"
#include	"WebView.h"
#include	"TodayControl.h"
#include	"TrainingType.h"
#include	"Event.h"
#include	<vector>
#include	<list>
#include	<map>
#include    <boost/make_shared.hpp>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include	<wx/calctrl.h>
#include	<wx/tokenzr.h>
#include	<wx/config.h>
#include	<wx/filename.h>
#include	<wx/textfile.h>
#include	<wx/grid.h>
#include	<wx/textdlg.h>
#include    <wx/aui/framemanager.h>
#include	<wx/fs_zip.h>

#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../sample.xpm"
#endif

class MyFrame;
class CreateTrainingProgramDialog;
class TrainingProgramGrid;

IMPLEMENT_APP(MyApp)

wxBEGIN_EVENT_TABLE(MyApp, wxApp)
    EVT_BUTTON(Minimal_Create_TrainingProgram, MyApp::OnCreateTrainingProgram)
    EVT_MENU(Minimal_Save_Calendar, MyApp::OnSaveCalendar)
    EVT_UPDATE_UI(Minimal_Save_Calendar, MyApp::OnUpdateSaveCalendar)
    EVT_MENU(Minimal_Load_Perspective, MyApp::OnLoadPerspective)
    EVT_UPDATE_UI(Minimal_Load_Perspective, MyApp::OnUpdateLoadPerspective)
    EVT_MENU(Minimal_Delete_Perspective, MyApp::OnDeletePerspective)
    EVT_UPDATE_UI(Minimal_Delete_Perspective, MyApp::OnUpdateLoadPerspective)
    EVT_MENU(Minimal_Save_Perspective, MyApp::OnSavePerspective)
//	EVT_MENU(Minimal_Unit_Km, MyApp::OnUnitKm)
//	EVT_MENU(Minimal_Unit_Miles, MyApp::OnUnitMiles)
    EVT_UPDATE_UI_RANGE(Minimal_Unit_Km, Minimal_Unit_Miles, MyApp::OnUpdateUnit)
    EVT_MENU(Minimal_Zone, MyApp::OnZone)
//	EVT_BUTTON(wxID_OK, MyApp::OnCreate)
    EVT_BUTTON(Minimal_Set_Pace, MyApp::OnSetPace)
//	EVT_RM_COMMAND( RM_DATE_SELECTED, MyApp::OnDateSelected)
wxEND_EVENT_TABLE()

MyApp::MyApp() :
    wxApp()
{
    zoneGrid = NULL;
    plan = NULL;


    /*configuration = new wxConfig(wxString("RunningManager"));
    wxString users;
    UserPtr pUser;
    configuration->Read("Users", &users, wxEmptyString);
    wxStringTokenizer tokenizer(users, ";");
    while (tokenizer.HasMoreTokens())
    {
    	wxString user = tokenizer.GetNextToken();
    	pUser = User::AddUser(user);
    	int i;
    	wxString entry;
    	entry = user + wxString("/Unit");
    	configuration->Read(entry, &i, 0);
    	pUser->unit = (PTUnit) i;

    	entry = user + wxString("/Level");
    	configuration->Read(entry, &i, 0);
    	pUser->level = (PTLevel) i;

    	entry = user + wxString("/Distance");
    	configuration->Read(entry, &i, 0);
    	pUser->distance = (PTDistance) i;

    	entry = user + wxString("/Pulse");
    	configuration->Read(entry, &(pUser->pulse), 0);
    	if (pUser->pulse < 0)
    		pUser->pulse = 0;

    	entry = user + wxString("/RaceDate");
    	wxString sRaceDate;
    	configuration->Read(entry, &sRaceDate, wxDateTime::Today().FormatISODate());
    	pUser->raceDate.ParseISODate(sRaceDate);
    }
    configuration->Read("LastDir", &lastDir, wxEmptyString);
    configuration->Read("LastUser", &users, wxEmptyString);
    pUser = User::GetUser( users );
    if (!pUser)
    {
    	pUser = User::GetUser(wxString("Default"));
    	if (!pUser)
    	{
    		pUser = User::AddUser(wxString("Default"));
    	}
    }
    User::SetCurrentUser( pUser );

    for (int i=0; i<5; i++)
    {
    	if (!ReadPerspective(i))
    		break;
    }

    configuration->Read("LastPerspective", &lastPerspective, wxEmptyString);*/

    cpHelpWindow = NULL;
}

MyApp::~MyApp()
{
}

bool MyApp::ReadPerspective(int const& n)
{
    wxString perspectiveEntry;
    wxString perspective;
    wxString code;

    perspectiveEntry = wxString::Format("PerspectiveName%d", n);
    wxConfigBase* configuration = wxConfig::Get();
    configuration->Read(perspectiveEntry, &perspective, wxEmptyString);
    if (perspective.IsEmpty()) {
        return false;
    }
    perspectiveEntry = wxString::Format("PerspectiveCode%d", n);
    configuration->Read(perspectiveEntry, &code, wxEmptyString);
    if (code.IsEmpty()) {
        return false;
    }

    vPerspectives[perspective] = code;
    return true;
}

void MyApp::OnCreateTrainingProgram(wxCommandEvent& WXUNUSED(event))
{
    trainingDialog->SetLogLevel(wxLOG_Info);
    if (!trainingDialog->TransferDataFromWindow()) {
        wxLogError(_("Cold not transfer data from panel"));
        return;
    }

    //	int answer = ::wxMessageBox(_("You have chosen to create a training plan for"));

    if (plan != NULL) {
        delete plan;
    }
    plan = new Plan(trainingDialog->GetDistance(), trainingDialog->GetLevel(), trainingDialog->GetDate());
    plan->CreateProgram(trainingDialog->GetUnit());
    UserPtr pUser = User::GetUser();
    pUser->unit = trainingDialog->GetUnit();
    pUser->level = trainingDialog->GetLevel();
    pUser->distance = trainingDialog->GetDistance();
    pUser->raceDate = trainingDialog->GetDate();
    pUser->pulse = trainingDialog->GetPulse();
    trainingProgram->Update(plan, pUser->unit);

    wxDateTime toDay = wxDateTime::Today();
    UpdateCurrentDate(toDay, trainingDialog, 0);
    //	today->Update(*plan, toDay, unit);
    GetAuiManager()->GetPane(trainingProgram).BestSize(trainingProgram->GetSize()).Caption(plan->ToString());
    //	trainingProgram->MakeCellVisible(trainingProgram->todayLine,0);

    UpdatePulse();

    GetAuiManager()->Update();
}

void MyApp::UpdatePulse()
{
    UserPtr pUser = User::GetUser();
    for (int i = 0; i < 6; i++) {
        int minPulse = (int)((pUser->pulse * gZoneMap[i].minPercent) / 100.0 + 0.5);
        int maxPulse = (int)((pUser->pulse * gZoneMap[i].maxPercent) / 100.0 + 0.5);
        zoneGrid->SetCellValue(i, 1, wxString::Format("%d (%.0lf%%)", minPulse, gZoneMap[i].minPercent));
        zoneGrid->SetCellValue(i, 2, wxString::Format("%d (%.0lf%%)", maxPulse, gZoneMap[i].maxPercent));
    }
    zoneGrid->AutoSize();
    GetAuiManager()->GetPane(zoneGrid).BestSize(zoneGrid->GetSize());
}

bool MyApp::OnInit()
{
    if (!wxApp::OnInit()) {
        return false;
    }

#if wxUSE_STREAMS && wxUSE_ZIPSTREAM && wxUSE_ZLIB
    wxFileSystem::AddHandler(new wxZipFSHandler);
#endif

    this->SetAppName("RunningManager");
    this->SetVendorName("ReVisitor");

    wxConfigBase* configuration = wxConfig::Get();
    //configuration = new wxConfig(wxString("RunningManager"));
    wxString users;
    UserPtr pUser;
    configuration->Read("Users", &users, wxEmptyString);
    wxStringTokenizer tokenizer(users, ";");
    while (tokenizer.HasMoreTokens()) {
        wxString user = tokenizer.GetNextToken();
        pUser = User::AddUser(user);
        int i;
        wxString entry;
        entry = user + wxString("/Unit");
        configuration->Read(entry, &i, 0);
        pUser->unit = (PTUnit)i;

        entry = user + wxString("/Level");
        configuration->Read(entry, &i, 0);
        pUser->level = (PTLevel)i;

        entry = user + wxString("/Distance");
        configuration->Read(entry, &i, 0);
        pUser->distance = (PTDistance)i;

        entry = user + wxString("/Pulse");
        configuration->Read(entry, &(pUser->pulse), 0);
        if (pUser->pulse < 0) {
            pUser->pulse = 0;
        }

        entry = user + wxString("/RaceDate");
        wxString sRaceDate;
        configuration->Read(entry, &sRaceDate, wxDateTime::Today().FormatISODate());
        pUser->raceDate.ParseISODate(sRaceDate);
    }
    wxString fullscreen;
    configuration->Read("Fullscreen", &fullscreen, wxEmptyString);
    configuration->Read("LastDir", &lastDir, wxEmptyString);
    configuration->Read("LastUser", &users, wxEmptyString);
    pUser = User::GetUser(users);
    if (!pUser) {
        pUser = User::GetUser(wxString("Default"));
        if (!pUser) {
            pUser = User::AddUser(wxString("Default"));
        }
    }
    User::SetCurrentUser(pUser);

    for (int i = 0; i < 5; i++) {
        if (!ReadPerspective(i)) {
            break;
        }
    }

    configuration->Read("LastPerspective", &lastPerspective, wxEmptyString);

    boost::shared_array<Zone> vZoneMap = Zone::GetZoneMap();
    for (int i = 0; i < 6; i++) {
        vZoneMap[i] = gZoneMap[i];
    }

    frame = new MyFrame("RunningManager v1.5", wxFileName::GetCwd());
    frame->SetAuiManager(boost::make_shared<wxAuiManager>());
    frame->SetBackgroundColour(wxColour(255, 255, 255));
    frame->Maximize();
    if (fullscreen.IsSameAs("1")) {
        frame->ShowFullScreen(true, wxFULLSCREEN_NOTOOLBAR | wxFULLSCREEN_NOSTATUSBAR | wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION);
    }

    wxSize screenSize = ::wxGetDisplaySize();

    wxBitmap icon(wxIcon(wxString("aaaaaaaa")));
    wxAuiPaneInfo commonInfo;
    commonInfo.MaximizeButton(true).Icon(icon).MinimizeButton(true).CloseButton(true);

    wxString userName = User::GetName(pUser);
    if (zoneGrid == NULL) {
        std::vector<wxTimeSpan> minPace(6), maxPace(6);
        zoneGrid = new ZoneGrid(frame);
        zoneGrid->UpdatePulse(pUser->pulse);
        ReadPaces(userName);

        GetAuiManager()->AddPane(zoneGrid, wxAuiPaneInfo(commonInfo).Name("Zones").Top().Layer(1).Caption(_("Zones")));

        zoneGrid->AutoSize();
        GetAuiManager()->GetPane(zoneGrid).BestSize(zoneGrid->GetSize());
    }

    trainingTypeGrid = new wxGrid(frame, wxID_ANY);
    GetAuiManager()->AddPane(trainingTypeGrid, wxAuiPaneInfo(commonInfo).Name("TrainingType").Right().Layer(2).Caption(_("Training types")));
    trainingTypeGrid->CreateGrid(MIR + 1, 1);
    trainingTypeGrid->SetColLabelValue(0, _("Description"));
    trainingTypeGrid->SetRowLabelSize(192);
    for (int i = 0; i <= MIR; i++) {
        trainingTypeGrid->SetRowLabelValue(i, gTrainingType[i].shortName);
        trainingTypeGrid->SetCellValue(i, 0, gTrainingType[i].description);
        trainingTypeGrid->SetCellBackgroundColour(i, 0, gIntensityColor[gTrainingIntensity[i]]);
    }
    trainingTypeGrid->AutoSize();
    GetAuiManager()->GetPane(trainingTypeGrid).BestSize(trainingTypeGrid->GetSize());

    trainingDialog = new CreateTrainingProgramDialog(this->frame, pUser->unit, pUser->level, pUser->distance, pUser->raceDate, pUser->pulse);
    trainingDialog->SetLogLevel(wxLOG_Error);
    trainingDialog->TransferDataFromWindow();
    {
        if (plan != NULL) {
            delete plan;
        }
        plan = new Plan(trainingDialog->GetDistance(), trainingDialog->GetLevel(), trainingDialog->GetDate());
        plan->CreateProgram(trainingDialog->GetUnit());
        pUser->unit = trainingDialog->GetUnit();
        pUser->level = trainingDialog->GetLevel();
        pUser->distance = trainingDialog->GetDistance();
        pUser->raceDate = trainingDialog->GetDate();
        pUser->pulse = trainingDialog->GetPulse();
        UpdatePulse();
    }
    GetAuiManager()->AddPane(trainingDialog, wxAuiPaneInfo(commonInfo).Name("Settings").Layer(2).Left().Caption(_("Settings for training program")).BestSize(trainingDialog->GetSize()));

    // Create the webview
    wxString url("https://www.amazon.com/80-20-Running-Stronger-Training-ebook/dp/B00IIVFAEY");
    //	wxString url("http://www.jogg.se");
    //	wxString url("http://www.mattfitzgerald.org/books");
    wxWebView* webView = wxWebView::New(frame, wxID_ANY, url);

    //	WebView *webView = new WebView( frame,  );
    GetAuiManager()->AddPane(webView, wxAuiPaneInfo(commonInfo).Name("Book").Layer(2).Left().Caption(_("Buy the \"80/20 Running\" book by Matt Fitzgerald")).MinSize(wxSize(512, 512)));

    wxDateTime date = wxDateTime::Today();
    //date -= wxTimeSpan(12*24);
    today = new TodayControl(frame, *plan, date, pUser->unit);
    GetAuiManager()->AddPane(today, wxAuiPaneInfo(commonInfo).Name("Today").Right().Layer(2).Caption(_("Training " + date.GetWeekDayName(date.GetWeekDay()) + " " + date.FormatISODate())).CloseButton(true).MaxSize(wxSize(100, 0)));
    //auiManager->GetPane(today).BestSize(today->GetSize()).MaxSize(wxSize(100,-1));

    trainingProgram = new TrainingProgramGrid(frame, plan, pUser->unit);
    GetAuiManager()->AddPane(trainingProgram, wxAuiPaneInfo(commonInfo).Name("TrainingTable").Layer(1).DefaultPane().Center().Caption(plan->ToString()).BestSize(trainingProgram->GetSize()));

    if (cpHelpWindow == NULL) {
        // Create embedded HTML Help window
        cpHelpController = new wxHtmlHelpController(wxHF_DEFAULTSTYLE | wxHF_FLAT_TOOLBAR, frame);
        cpHelpWindow = new wxHtmlHelpWindow;
        cpHelpWindow->UseConfig(configuration, wxString("Help")); // Set your own config object here
//		cpHelpController->UseConfig(configuration);
        cpHelpController->SetHelpWindow(cpHelpWindow);
        cpHelpWindow->Create(frame, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                             wxTAB_TRAVERSAL | wxBORDER_NONE, wxHF_DEFAULT_STYLE);
        cpHelpController->AddBook(::wxGetCwd() + wxFileName::GetPathSeparator() + "rmhelp.zip");
        cpHelpController->DisplayContents();
        GetAuiManager()->AddPane(cpHelpWindow, wxAuiPaneInfo(commonInfo).Name("Help").BestSize(screenSize.x / 2, screenSize.y - 20).Float().Caption("Help").DestroyOnClose(false));
        GetAuiManager()->GetPane("Help").Hide();
    }

    if (vPerspectives.size() == 0) {
        vPerspectives["Default"] = GetAuiManager()->SavePerspective();
    }

    if (!lastPerspective.IsEmpty()) {
        GetAuiManager()->LoadPerspective(lastPerspective);
    }

    GetAuiManager()->Update();


    frame->Show(true);

    trainingProgram->GoToCell(trainingProgram->todayLine, 0);
    trainingProgram->SetGridCursor(trainingProgram->todayLine, 0);

    return true;
}

int MyApp::OnExit()
{
    wxConfigBase* configuration = wxConfig::Get();

    delete plan;
    plan = NULL;

    wxString users, user;
    UserPtr pUser;
    std::map<wxString, UserPtr>& userMap = User::GetUsers();
    std::map<wxString, UserPtr>::iterator it = userMap.begin(), e = userMap.end();
    while (it != e) {
        users += it->first;
        it++;
        if (it != userMap.end()) {
            users += wxString(";");
        }
    }

    configuration->Write("Users", users);

    it = userMap.begin();
    while (it != e) {
        user = it->first;
        UserPtr pUser = it->second;

        wxString entry;
        entry = user + wxString("/Unit");
        configuration->Write(entry, (int)pUser->unit);

        entry = user + wxString("/Level");
        configuration->Write(entry, (int)pUser->level);

        entry = user + wxString("/Distance");
        configuration->Write(entry, (int)pUser->distance);

        entry = user + wxString("/Pulse");
        configuration->Write(entry, (int)pUser->pulse);

        entry = user + wxString("/RaceDate");
        wxString sRaceDate;
        configuration->Write(entry, pUser->raceDate.FormatISODate());

        SavePaces(user);

        it++;
    }

    configuration->Write("LastDir", lastDir);
    pUser = User::GetUser();
    wxString s = User::GetName(pUser);
    configuration->Write("LastUser", s);

    SavePerspectives();

    cpHelpWindow = NULL;

    //	cpHelpWindow->WriteCustomization(configuration, wxString("Help"));
    delete cpHelpController;
    cpHelpController = NULL;
    delete configuration;

    //if (auiManager != NULL) {
    //    delete auiManager;
    //}


    return 0;
}

void MyApp::OnSaveCalendar(wxCommandEvent& WXUNUSED(event))
{
    wxString filename = ::wxFileSelector(_("Save training plan"), lastDir, plan->ToString(), wxString("csv"), wxString("Comma Separated Values (*.csv)|*.csv"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, this->frame);
    if (filename.IsEmpty()) {
        return;
    }
    if (filename.EndsWith("csv")) {
        if (!plan->SaveCsv(filename)) {
            return;
        }
    }
    wxFileName fn(filename);
    lastDir = fn.GetFullPath();
}

void MyApp::OnZone(wxCommandEvent& WXUNUSED(e))
{
    UserPtr pUser = User::GetUser();
    wxString userName = User::GetName(pUser);
    wxString defaultValue = wxString::Format("%d", pUser->pulse);
    wxString caption(_("Enter lactate threshold pulse (not max pulse!)"));
    wxString title(_("Pulse"));
    wxString sPulse = ::wxGetTextFromUser(caption, title, defaultValue);
    wxBitmap icon(wxIcon(wxString("aaaaaaaa")));
    wxAuiPaneInfo commonInfo;
    commonInfo.MaximizeButton(true).Icon(icon).MinimizeButton(true).CloseButton(true);

    if (!sPulse.IsEmpty()) {
        long lpulse;
        sPulse.ToLong(&lpulse);
        pUser->pulse = (int)lpulse;
    }
    if (zoneGrid == NULL) {
        zoneGrid = new ZoneGrid(frame);
        GetAuiManager()->AddPane(zoneGrid, wxAuiPaneInfo(commonInfo).Name("Zones").Top().Caption(_("Zones")).Layer(1));
        zoneGrid->UpdatePulse(pUser->pulse);
        ReadPaces(userName);
    }

    zoneGrid->AutoSize();
    GetAuiManager()->GetPane(zoneGrid).BestSize(zoneGrid->GetSize());
    GetAuiManager()->Update();
}

void MyApp::OnUnitKm(wxCommandEvent& WXUNUSED(event))
{
    User::GetUser()->unit = KM;
}
void MyApp::OnUnitMiles(wxCommandEvent& WXUNUSED(event))
{
    User::GetUser()->unit = MILES;
}

void MyApp::OnUpdateUnit(wxUpdateUIEvent& e)
{
    e.Check(User::GetUser()->unit + Minimal_Unit_Km == e.GetId());
}

void MyApp::OnUpdateSaveCalendar(wxUpdateUIEvent& e)
{
    e.Enable(plan != NULL);
}

void MyApp::UpdateCurrentDate(wxDateTime const& date, wxWindow* sender, int index)
{
    UserPtr pUser = User::GetUser();
    if (sender != today) {
        today->Update(*plan, date, pUser->unit, index);
        GetAuiManager()->GetPane("Today").Caption(_("Training " + date.GetWeekDayName(date.GetWeekDay()) + " " + date.FormatISODate()));
    }
    if (sender != this->trainingProgram) {
        int row = trainingProgram->GetRow(date);
        if (row != -1) {
            trainingProgram->GoToCell(row, 0);
        }
    }
    if (sender != this->trainingDialog) {
        //trainingDialog->SetDate(date);
    }
    GetAuiManager()->Update();
}

void MyApp::SavePerspectives()
{
    wxConfigBase* configuration = wxConfig::Get();
    bool lastPerspectiveFound = false;
    wxString entry;
    int i = 0;
    std::map<wxString, wxString>::iterator it = vPerspectives.begin(), e = vPerspectives.end();
    while (it != e) {
        std::pair<wxString, wxString> aPair = *it;
        entry = wxString::Format("PerspectiveName%d", i);
        configuration->Write(entry, it->first);
        entry = wxString::Format("PerspectiveCode%d", i);
        configuration->Write(entry, it->second);
        if (lastPerspective.Cmp(it->first) == 0) {
            lastPerspectiveFound = true;
        }
        it++;
        i++;
    }
    for (; i < 5; i++) {
        entry = wxString::Format("PerspectiveName%d", i);
        configuration->DeleteEntry(entry);
    }
    if (!lastPerspectiveFound) {
        lastPerspective = wxEmptyString;
    }
}

void MyApp::ReadPaces(wxString const& user)
{
    wxConfigBase* configuration = wxConfig::Get();
    UserPtr pUser = User::GetUser();
    boost::shared_array<Zone> vZoneMap = Zone::GetZoneMap();
    wxString s;
    for (int i = 0; i < 6; i++) {
        configuration->Read(wxString::Format("%s/minPace%d", user, i), &s, wxEmptyString);
        if (s.IsEmpty()) {
            vZoneMap[i].minPace = wxTimeSpan();
        } else {
            vZoneMap[i].minPace = vZoneMap[i].GetTimeSpan(s);
        }
        zoneGrid->UpdatePace(vZoneMap[i].minPace, true, i, pUser->unit);

        configuration->Read(wxString::Format("%s/maxPace%d", user, i), &s, wxEmptyString);
        if (s.IsEmpty()) {
            vZoneMap[i].maxPace = wxTimeSpan();
        } else {
            vZoneMap[i].maxPace = vZoneMap[i].GetTimeSpan(s);
        }
        //gZoneMap[i].minPace = vZoneMap[i].minPace;
        //gZoneMap[i].maxPace = vZoneMap[i].maxPace;
        Zone& aZone = Zone::GetZoneMap()[i];
        aZone.minPace = vZoneMap[i].minPace;
        aZone.maxPace = vZoneMap[i].maxPace;
        zoneGrid->UpdatePace(vZoneMap[i].maxPace, false, i, pUser->unit);
    }
}

void MyApp::SavePaces(wxString const& user)
{
    wxConfigBase* configuration = wxConfig::Get();
    boost::shared_array<Zone> vZoneMap = Zone::GetZoneMap();
    for (int i = 0; i < 6; i++) {
        if (vZoneMap[i].minPace.IsNull()) {
            configuration->Write(wxString::Format("%s/minPace%d", user, i), wxEmptyString);
        } else {
            int minutes, seconds;
            Zone::GetMinSec(vZoneMap[i].minPace, minutes, seconds);
            configuration->Write(wxString::Format("%s/minPace%d", user, i), wxString::Format("%d:%d", minutes, seconds));
        }
        if (vZoneMap[i].maxPace.IsNull()) {
            configuration->Write(wxString::Format("%s/maxPace%d", user, i), wxEmptyString);
        } else {
            int minutes, seconds;
            Zone::GetMinSec(vZoneMap[i].maxPace, minutes, seconds);
            configuration->Write(wxString::Format("%s/maxPace%d", user, i), wxString::Format("%d:%d", minutes, seconds));
        }
    }
}

std::map<wxString, wxString>& MyApp::GetPerspectives()
{
    return vPerspectives;
}

void MyApp::OnDeletePerspective(wxCommandEvent& WXUNUSED(ev))
{
    if (vPerspectives.size() == 0) {
        return;
    }
    wxArrayString selections;
    wxArrayInt deleteSelections;
    std::map<wxString, wxString>::iterator it = vPerspectives.begin(), e = vPerspectives.end();
    while (it != e) {
        selections.Add(it->first);
        it++;
    }
    int n = ::wxGetSelectedChoices(deleteSelections, _("Select perspectives to delete"), _("Perspectives"), selections, frame);
    if (n == 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        int j = deleteSelections[i];
        if (selections[j].Cmp("Default") == 0) {
            wxLogWarning(_("You can not delete the default perspective!"));
            continue;
        }
        std::map<wxString, wxString>::iterator it = FindPerspective(selections[j]);
        if (it != vPerspectives.end()) {
            vPerspectives.erase(it);
        }
    }
}

std::map<wxString, wxString>::iterator MyApp::FindPerspective(wxString const& s)
{
    std::map<wxString, wxString>::iterator it = vPerspectives.begin(), e = vPerspectives.end();
    while (it != e) {
        if (it->first.Cmp(s) == 0) {
            return it;
        }
        it++;
    }
    return it;
}

void MyApp::OnLoadPerspective(wxCommandEvent& WXUNUSED(ev))
{
    if (vPerspectives.size() == 0) {
        return;
    }
    wxArrayString selections;
    std::map<wxString, wxString>::iterator it = vPerspectives.begin(), e = vPerspectives.end();
    int idx = 0;
    int i = 0;
    while (it != e) {
        if (this->lastPerspective.Cmp(it->first) == 0) {
            idx = i;
        }
        selections.Add(it->first);
        it++;
        i++;
    }
    wxString selection = ::wxGetSingleChoice(_("Select a perspective"), _("Perspectives"), selections, idx, frame);
    if (selection.IsEmpty()) {
        return;
    }
    GetAuiManager()->LoadPerspective(vPerspectives[selection], true);
    GetAuiManager()->GetPane(trainingProgram).Caption(plan->ToString());
    wxDateTime date = wxDateTime::Today();
    GetAuiManager()->GetPane(today).Caption(_("Training " + date.GetWeekDayName(date.GetWeekDay()) + " " + date.FormatISODate()));

    GetAuiManager()->Update();
    //	auiManager->Update();
    lastPerspective = selection;
}

void MyApp::OnUpdateLoadPerspective(wxUpdateUIEvent& e)
{
    if (vPerspectives.size() == 0) {
        e.Enable(false);
    } else {
        e.Enable(true);
    }
}

void MyApp::OnSavePerspective(wxCommandEvent& WXUNUSED(e))
{
    wxString s = ::wxGetTextFromUser(_("Enter a name for the perspective"), _("Save perspective"), wxString::Format(_("Perspective %d"), (int)(vPerspectives.size() + 1)), frame);
    if (s.IsEmpty()) {
        return;
    }
    vPerspectives[s] = GetAuiManager()->SavePerspective();
}

void MyApp::OnSetPace(wxCommandEvent& WXUNUSED(e))
{
    UserPtr pUser = User::GetUser();
    pUser->use_pace = !(pUser->use_pace);

}

//void MyApp::OnDateSelected( wxCommandEvent & e)
//{
//	EventData* evtData = (EventData*) e.GetClientData();
//}