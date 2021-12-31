#include	"Plan.h"
#include	"TrainingType.h"
#include	<wx/tokenzr.h>
#include	<wx/log.h>

Plan::Plan(PTDistance distance, PTLevel level, wxDateTime date)
{
    this->distance = distance;
    this->level = level;
    this->date = date;

    switch (distance) {
    case PTD_5KM:
        programLength = wxTimeSpan(24*7*9);
        break;

    case PTD_10KM:
        programLength = wxTimeSpan(24*7*12);
        break;

    case PTD_HALF_MARATHON:
        programLength = wxTimeSpan(24*7*15);
        break;

    case PTD_MARATHON:
        programLength = wxTimeSpan(24*7*18);
        break;
    }
}

void Plan::CreateProgram(PTUnit const &unit)
{
    this->outUnit = unit;
    startTime = date-programLength;
    int i = 0;
    while (startTime.GetWeekDay() != wxDateTime::Sun) {
        startTime += wxTimeSpan(24);
        programLength -= wxTimeSpan(24);
        i++;
    }

    if (i > 3) {
        // Race is on Mon, Tue or Wed
        // Extend program a few days
        startTime = wxDateTime(date);
        startTime -= programLength;
        while (startTime.GetWeekDay() != wxDateTime::Sun) {
            startTime -= wxTimeSpan(24);
            programLength += wxTimeSpan(24);
        }
    }
    startTime += wxTimeSpan(24); // Always a Monday!
//	wxLogMessage(_("Your program will start on ")+startTime.GetWeekDayName(startTime.GetWeekDay())+" "+startTime.FormatISODate());

    CreatePlan();
    wxString s = ToString();
}

void Plan::CreatePlan()
{
    switch (distance) {
    case PTD_5KM: {
        switch (level) {
        case PTL_LOW: {
            SetPlan(wxString("\
1,B,,,FR,1,FR,1,SPR,1,FR,1,FR,2,FR,1,\
2,B,,,FFR,1,FR,2,FR,2,SPR,2,FR,2,FR,3,\
3,B,,,FFR,1,FR,2,FR,2,SPR,1,FR,2,FR,3,\
4,P,,,SPR,2,FR,3,FR,3,HRR,1,RR,3,FFR,2,\
5,P,,,SPR,3,FR,4,FR,4,HRR,2,RR,4,FFR,3,\
6,P,,,SPR,2,FR,3,FR,3,HRR,1,RR,3,FFR,2,\
7,P,,,SPR,4,RR,4,FR,4,LIR,1,RR,4,FFR,4,\
8,P,,,SPR,5,RR,5,FR,5,LIR,2,RR,5,FFR,5,\
9,T,,,LIR,1,RR,3,FR,3,SPR,1,RR,1,KM5,1"));
        }
        break;

        case PTL_MEDIUM: {
            SetPlan(wxString("\
1,B,FR,5,SPR,3,FR,5,FR,5,HRR,2,RR,5,LR,1,\
2,B,FR,5,SPR,5,FR,6,FR,5,HRR,4,RR,5,LR,2,\
3,B,,,SPR,3,FR,6,FR,5,HRR,4,RR,6,LR,1,\
4,P,FR,6,LIR,1,RR,6,FR,6,SIR,4,RR,6,FFR,7,\
5,P,RR,6,LIR,2,RR,6,FR,7,SIR,5,RR,6,FFR,8,\
6,P,,,LIR,1,RR,5,FR,6,SIR,2,RR,5,FFR,6,\
7,P,RR,6,SIR,3,RR,6,FR,8,LIR,6,RR,6,FFR,9,\
8,P,RR,6,SIR,2,RR,6,FR,9,LIR,7,RR,6,FFR,10,\
9,T,,,LIR,2,RR,4,FR,3,SPR,2,RR,2,KM5,1"));
        }
        break;

        case PTL_HIGH: {
            SetPlan(wxString("\
1,B,FR,6,2X,SPR,5,FR,4,FR,6,FR,6,HRR,4,RR,6,LR,2,\
2,B,FR,6,2X,SPR,10,FR,4,FR,6,2X,FR,6,FR,4,HRR,5,RR,6,LR,3,\
3,B,,,2X,SPR,7,FR,6,FR,6,FR,6,HRR,3,RR,6,LR,2,\
4,P,FR,6,2X,LIR,2,RR,5,FR,6,2X,FR,6,FR,5,SIR,7,2X,RR,6,FR,5,TR,6,\
5,P,RR,6,2X,LIR,4,RR,6,FR,6,2X,FR,6,FR,6,SIR,8,2X,RR,6,FR,6,TR,7,\
6,P,,,2X,LIR,2,RR,5,FR,6,2X,FR,6,FR,5,SIR,5,2X,RR,6,FR,5,TR,4,\
7,P,RR,6,2X,SIR,4,RR,6,FR,6,2X,FR,6,FR,6,LIR,9,2X,RR,6,FR,6,FFR,10,\
8,P,RR,6,2X,SIR,3,RR,5,FR,6,2X,FR,6,FR,5,LIR,8,2X,RR,6,FR,5,FFR,8,\
9,T,,,LIR,4,RR,5,FR,4,SPR,2,RR,3,KM5,1"));
        }
        break;
        }
    }
    break;

    case PTD_10KM: {
        switch (level) {
        case PTL_LOW: {
            SetPlan(wxString("\
1,B,,,FFR,1,FR,2,FR,2,SPR,1,FR,2,FR,3,\
2,B,,,FFR,2,FR,3,FR,2,SPR,2,FR,2,FR,4,\
3,B,,,FFR,1,FR,2,FR,2,SPR,1,FR,2,FR,3,\
4,B,,,FFR,3,FR,3,FR,2,HRR,1,RR,3,FR,5,\
5,B,,,FFR,3,FR,3,FR,3,HRR,2,RR,3,FR,6,\
6,B,,,FFR,2,FR,2,FR,2,HRR,1,RR,3,FR,5,\
7,P,,,SPR,3,FR,3,FR,4,SIR,1,RR,3,FR,5,\
8,P,,,SPR,5,FR,3,FR,4,SIR,2,RR,4,FR,6,\
9,P,,,LIR,3,FR,3,FR,4,SPR,2,RR,3,FFR,2,\
10,P,,,LIR,2,FR,4,FR,4,MIR,2,RR,4,FR,7,\
11,T,,,LIR,4,FR,4,FR,3,MIR,1,FR,3,FR,6,\
12,T,,,SPR,2,FR,3,FR,2,FFR,1,RR,1,KM10,1"));
        }
        break;

        case PTL_MEDIUM: {
            SetPlan(wxString("\
1,B,FR,5,FFR,4,FR,5,FR,5,SPR,4,FR,5,LR,1,\
2,B,FR,5,FFR,5,FR,6,FR,5,SPR,5,FR,5,LR,2,\
3,B,,,FFR,4,FR,5,FR,6,SPR,4,FR,5,LR,1,\
4,B,FR,5,FFR,7,FR,6,FR,5,HRR,5,RR,6,LR,3,\
5,B,RR,5,FFR,8,FR,6,FR,6,HRR,6,RR,6,LR,4,\
6,B,,,FFR,5,FR,6,FR,6,HRR,3,RR,6,LR,2,\
7,P,FR,6,SPR,7,FR,6,FR,6,SIR,4,RR,6,FFR,9,\
8,P,RR,6,SPR,10,FR,7,FR,6,SIR,5,RR,7,FFR,10,\
9,P,,,LIR,2,FR,6,FR,5,SPR,6,RR,6,FFR,7,\
10,P,FR,6,LIR,4,FR,7,FR,6,MIR,3,RR,7,LRSP,1,\
11,T,RR,5,LIR,3,FR,5,FR,5,MIR,1,FR,4,FFR,7,\
12,T,,,SPR,5,FR,4,FR,3,FFR,3,RR,2,KM10,1"));
        }
        break;
        case PTL_HIGH: {
            SetPlan(wxString("\
1,B,FR,6,2X,FFR,4,FR,3,FR,6,FR,6,SPR,6,FR,6,LR,2,\
2,B,FR,6,2X,FFR,5,FR,3,FR,6,2X,FR,6,FR,3,SPR,7,FR,6,LR,3,\
3,B,,,2X,FFR,4,FR,5,FR,6,FR,6,SPR,6,FR,5,LR,4,\
4,B,FR,6,2X,TR,2,FR,3,FR,6,2X,FR,6,FR,3,HRR,4,2X,RR,6,FR,3,LRFF,1,\
5,B,RR,6,2X,TR,3,RR,4,FR,6,2X,FR,6,FR,4,HRR,5,2X,RR,6,FR,4,LRFF,2,\
6,B,,,2X,TR,2,RR,4,FR,6,2X,FR,6,FR,4,HRR,3,2X,RR,6,FR,4,FFR,9,\
7,P,FR,6,2X,SPR,10,RR,5,FR,6,2X,FR,6,FR,5,SIR,7,2X,RR,6,FR,5,LRSP,1,\
8,P,RR,6,2X,SPR,12,RR,6,FR,6,2X,FR,6,FR,6,SIR,8,2X,RR,6,FR,6,LRSP,2,\
9,P,,,2X,LIR,4,RR,5,FR,5,2X,FR,5,FR,5,SPR,8,2X,RR,5,FR,5,FFR,10,\
10,P,FR,6,2X,LIR,7,RR,6,FR,6,2X,FR,6,FR,6,MIR,4,2X,RR,6,FR,6,LRSP,2,\
11,T,RR,5,2X,LIR,5,RR,5,FR,5,2X,FR,5,FR,5,MIR,3,FR,9,LRSP,1,\
12,T,,,SPR,5,FR,4,FR,3,FFR,3,RR,2,KM10,1"));
        }
        break;
        }

    }
    break;

    case PTD_HALF_MARATHON: {
        switch (level) {
        case PTL_LOW: {
            SetPlan(wxString("\
1,B,,,FFR,1,FR,2,FR,2,SPR,2,FR,2,LR,1, \
2,B,,,FFR,2,FR,3,FR,2,SPR,1,FR,2,LR,2,\
3,B,,,FFR,1,FR,2,FR,2,SPR,2,FR,2,LR,1,\
4,B,,,FFR,3,FR,3,FR,2,HRR,2,RR,3,LR,3,\
5,B,,,FFR,4,FR,3,FR,3,HRR,4,RR,3,LR,4,\
6,B,,,FFR,2,FR,2,FR,3,HRR,3,RR,3,LR,2,\
7,P,,,TR,1,RR,3,FR,4,SIR,2,RR,3,LR,5,\
8,P,,,CIR,1,RR,4,FR,4,SIR,3,RR,3,LR,6,\
9,P,,,TR,1,RR,3,FR,3,SIR,2,RR,3,LR,3,\
10,P,,,TR,3,RR,4,FR,4,LIR,2,RR,4,LRSP,1,\
11,P,,,TR,4,RR,4,FR,5,LIR,4,RR,4,LRFF,1,\
12,P,,,TR,2,RR,4,FR,4,LIR,3,RR,4,LR,3,\
13,P,,,TR,5,RR,4,FR,5,MIR,1,RR,5,LRFF,2,\
14,P,,,TR,6,RR,5,FR,5,MIR,1,RR,5,LRFF,1,\
15,T,,,FFR,3,FR,3,FR,2,SPR,1,RR,1,HM,1,"));

        }
        break;

        case PTL_MEDIUM: {
            SetPlan(wxString("\
1,B,FR,5,FFR,3,FR,5,FR,5,SPR,4,FR,5,LR,2,\
2,B,FR,5,FFR,4,FR,6,FR,5,SPR,5,FR,5,LR,3,\
3,B,,,FFR,3,FR,5,FR,5,SPR,4,FR,5,LR,1,\
4,B,FR,5,FFR,4,RR,6,FR,6,HRR,5,RR,5,LR,5,\
5,B,FR,5,FFR,5,RR,6,FR,6,HRR,6,RR,6,LR,7,\
6,B,,,FFR,4,RR,5,FR,5,HRR,4,RR,5,LR,3,\
7,P,FR,6,CIR,1,RR,6,FR,6,SIR,4,RR,6,LRSP,1,\
8,P,RR,6,TR,4,RR,6,FR,6,SIR,5,RR,6,LRSP,2,\
9,P,,,CIR,1,RR,5,FR,6,SIR,3,RR,5,LRFF,1,\
10,P,FR,6,TR,5,RR,6,FR,6,LIR,3,RR,6,LRSP,2,\
11,P,RR,6,CIR,2,RR,6,FR,6,LIR,6,RR,6,LRFF,2,\
12,P,,,TR,4,RR,5,FR,6,LIR,3,RR,5,LRSP,1,\
13,P,FR,6,TR,7,RR,6,FR,6,MIR,2,RR,6,LRFF,3,\
14,P,RR,5,TR,5,RR,5,FR,4,MIR,2,RR,4,LRSP,1,\
15,T,,,FFR,5,FR,4,FR,3,SPR,2,RR,2,HM"));
        }
        break;

        case PTL_HIGH: {
            SetPlan(wxString("\
1,B,FR,6,2X,FFR,6,FR,3,FR,6,FR,6,SPR,8,FR,6,LR,3,\
2,B,FR,6,2X,FFR,7,FR,3,FR,7,2X,FR,6,FR,3,SPR,10,FR,6,LR,5,\
3,B,,,2X,FFR,6,FR,3,FR,6,FR,6,SPR,8,FR,6,LR,3,\
4,B,FR,6,2X,FFR,8,FR,4,FR,8,2X,FR,6,FR,4,HRR,7,2X,RR,6,FR,4,LR,7,\
5,B,FR,6,2X,FFR,9,FR,5,FR,8,2X,FR,6,FR,4,HRR,8,2X,RR,6,FR,4,LR,9,\
6,B,,,2X,FFR,7,FR,4,FR,6,2X,FR,6,FR,4,HRR,6,2X,RR,6,FR,4,LR,4,\
7,P,FR,6,2X,CIR,2,FR,5,FR,9,2X,FR,6,FR,5,SIR,6,2X,RR,6,FR,5,LRSP,1,\
8,P,FR,6,2X,TR,6,FR,6,FR,9,2X,FR,6,FR,6,SIR,7,2X,RR,6,FR,6,LRSP,2,\
9,P,,,2X,CIR,1,FR,5,FR,6,2X,FR,5,FR,5,SIR,4,2X,RR,5,FR,5,LRSP,1,\
10,P,FR,6,2X,TR,8,RR,6,FR,9,2X,FR,6,RR,6,LIR,7,2X,RR,6,RR,6,LRSP,3,\
11,P,RR,6,2X,CIR,3,RR,6,FR,9,2X,FR,6,RR,6,LIR,8,2X,RR,6,RR,6,LRSP,3,\
12,P,,,2X,CIR,2,RR,5,FR,6,2X,FR,5,RR,5,LIR,3,2X,RR,5,RR,5,LRFF,1,\
13,P,RR,6,2X,TR,9,RR,6,FR,9,2X,FR,6,RR,6,MIR,4,2X,RR,6,RR,6,LRFF,4,\
14,P,RR,5,2X,TR,6,RR,5,FR,5,2X,FR,5,RR,4,MIR,2,2X,RR,4,RR,4,LRSP,1,\
15,T,,,FFR,6,FR,5,FR,4,SPR,5,RR,2,HM,1"));
        }
        break;
        }
    }
    break;

    case PTD_MARATHON: {
        switch(level) {
        case PTL_LOW: {
            SetPlan(wxString("\
1,B,,,FFR,2,FR,3,FR,3,SPR,1,FR,3,LR,1,\
2,B,,,FFR,3,FR,4,FR,3,SPR,2,FR,3,LR,2,\
3,B,,,FFR,2,FR,3,FR,3,SPR,1,FR,3,LR,1,\
4,B,,,FFR,4,FR,4,FR,3,HRR,1,RR,4,LR,3,\
5,B,,,FFR,6,FR,4,FR,4,HRR,2,RR,4,LR,4,\
6,B,,,FFR,4,FR,3,FR,4,HRR,1,RR,3,LR,2,\
7,B,,,FFR,7,FR,5,FR,4,HRR,4,RR,4,LR,5,\
8,B,,,FFR,8,FR,5,FR,5,HRR,6,RR,4,LR,7,\
9,B,,,FFR,6,FR,4,FR,4,HRR,4,RR,4,LR,4,\
10,P,,,TR,2,RR,5,FR,5,SIR,1,RR,4,LR,9,\
11,P,,,CIR,1,RR,5,FR,5,SIR,2,RR,5,LR,11,\
12,P,,,TR,2,RR,4,FR,5,SIR,1,RR,4,LRSP,1,\
13,P,,,TR,3,RR,5,FR,6,LIR,2,RR,5,LRFF,1,\
14,P,,,TR,4,RR,6,FR,6,LIR,3,RR,5,LRSP,2,\
15,P,,,TR,2,RR,5,FR,5,LIR,1,RR,5,HM,1,\
16,P,,,CIR,2,RR,6,FR,6,MIR,1,RR,6,LRFF,5,\
17,T,,,TR,4,FR,4,FR,4,MIR,1,RR,4,LRSP,2,\
18,T,,,FFR,4,FR,3,FR,3,SPR,2,RR,1,M,1"));
        }
        break;

        case PTL_MEDIUM: {
            SetPlan(wxString("\
1,B,FR,5,FFR,4,FR,5,FR,5,SPR,4,FR,5,LR,3,\
2,B,FR,5,FFR,6,FR,5,FR,5,SPR,5,FR,5,LR,4,\
3,B,,,FFR,4,FR,5,FR,4,SPR,4,FR,5,LR,2,\
4,B,FR,5,FFR,6,FR,5,FR,5,HRR,4,RR,5,LR,5,\
5,B,FR,5,FFR,7,FR,6,FR,5,HRR,5,RR,5,LR,7,\
6,B,,,FFR,6,FR,5,FR,5,HRR,4,RR,5,LR,3,\
7,B,FR,5,FFR,8,FR,6,FR,5,HRR,6,RR,6,LR,9,\
8,B,FR,5,FFR,9,FR,6,FR,6,HRR,8,RR,6,LR,11,\
9,B,,,FFR,6,FR,6,FR,5,HRR,6,RR,6,LR,5,\
10,P,FR,6,CIR,1,RR,6,FR,6,SIR,4,RR,6,LR,13,\
11,P,RR,6,TR,4,RR,6,FR,6,SIR,5,RR,6,LR,15,\
12,P,,,TR,3,RR,5,FR,5,SIR,3,RR,5,LR,7,\
13,P,FR,6,TR,5,RR,6,FR,6,LIR,3,RR,6,LRSP,4,\
14,P,RR,6,CIR,2,RR,6,FR,6,LIR,5,RR,6,LRFF,4,\
15,P,,,TR,4,RR,5,FR,5,LIR,2,RR,5,HM,1,\
16,P,RR,6,TR,6,RR,6,FR,6,MIR,2,RR,6,LRSP,5,\
17,T,RR,5,CIR,1,FR,4,FR,4,MIR,1,RR,4,LRFF,1,\
18,T,,,FFR,4,FR,3,FR,3,SPR,3,RR,1,M,1"));
        }
        break;

        case PTL_HIGH: {
            SetPlan(wxString("\
1,B,FR,6,2X,FFR,6,FR,3,FR,6,FR,6,SPR,6,FR,6,LR,5,\
2,B,FR,6,2X,FFR,6,FR,3,FR,6,2X,FR,6,FR,3,SPR,10,FR,6,LR,7,\
3,B,,,2X,FFR,6,FR,3,FR,6,FR,6,SPR,8,FR,6,LR,5,\
4,B,FR,6,2X,FFR,7,FR,4,FR,6,2X,FR,6,FR,4,HRR,7,RR,6,LR,9,\
5,B,FR,6,2X,FFR,8,FR,4,FR,7,2X,FR,6,FR,4,HRR,8,2X,RR,6,FR,4,LR,11,\
6,B,,,2X,FFR,7,FR,4,FR,6,2X,FR,6,FR,4,HRR,6,RR,6,LR,7,\
7,B,FR,6,2X,FR,9,FR,5,FR,7,2X,FR,6,FR,5,HRR,9,2X,RR,6,FR,5,LR,13,\
8,B,FR,6,2X,FFR,10,FR,6,FR,7,2X,FR,6,FR,6,HRR,1,2X,RR,6,FR,6,LR,15,\
9,B,,,2X,FFR,9,FR,5,FR,6,2X,FR,5,FR,5,HRR,6,2X,RR,5,FR,5,LR,8,\
10,P,FR,6,2X,CIR,2,RR,6,FR,8,2X,FR,6,FR,6,SIR,7,2X,RR,6,FR,6,LRSP,4,\
11,P,RR,6,2X,TR,8,RR,6,FR,8,2X,FR,6,FR,6,SIR,8,2X,RR,6,FR,6,LRFF,4,\
12,P,,,2X,CIR,2,RR,5,FR,6,2X,FR,5,FR,5,SIR,4,2X,RR,5,FR,5,LRSP,3,\
13,P,RR,6,2X,CIR,3,RR,6,FR,9,2X,FR,6,FR,6,LIR,6,2X,RR,6,FR,5,LRSP,5,\
14,P,RR,6,2X,TR,9,RR,6,FR,9,2X,FR,6,FR,6,LIR,7,2X,RR,6,FR,6,LRSP,6,\
15,P,,,2X,TR,4,RR,5,FR,6,2X,FR,5,FR,5,LIR,4,2X,RR,5,FR,5,HM,1,\
16,P,RR,6,2X,CIR,4,RR,6,FR,9,2X,FR,6,FR,6,MIR,4,2X,RR,6,FR,6,LRFF,6,\
17,T,RR,5,2X,TR,6,RR,5,FR,5,2X,FR,5,FR,4,MIR,2,2X,RR,4,FR,4,LRSP,3,\
18,T,,,FFR,6,FR,5,FR,4,SPR,5,RR,2,M,1"));
        }
        break;
        }
    }
    break;
    }

    wxString s;
    s = _("Subject,Start Date,All Day Event,Description,Private");
    textFile.AddLine(s);
    for (int i=0; i<weeks.size(); i++) {
        std::list<Training>::iterator it = weeks[i].training.begin();
        while (it != weeks[i].training.end()) {
            Training &t = *it;
            if (t.type != NONE) {
                wxString shortName = gTrainingType[t.type].shortName;
                wxString dateString = t.date.FormatISODate();
                wxString trainingString = wxString("\"")+t.ToString(false,outUnit)+wxString("\"");
                s = wxString::Format(_("%s %d,%s,False,%s,True"), shortName, t.intensity, dateString, trainingString);
                textFile.AddLine(s);
            }
            it++;
        }
    }
}

void Plan::SetPlan( wxString const &s )
{
    std::list<Week> lWeeks;
    wxStringTokenizer tokenizer( s, ",");
    unsigned long ul;
    wxString sTraining, sIntensity;
    int day = 0;
    while (tokenizer.HasMoreTokens()) {
        wxString token = tokenizer.GetNextToken();
        token.ToULong(&ul);
        lWeeks.push_back( Week() );
        Week &week = lWeeks.back();
        week.number = (int) ul;
        token = tokenizer.GetNextToken();
        week.SetPhase(token);

        for (int i=0; i<7; i++) {
            sTraining = tokenizer.GetNextToken();
            if (sTraining == "2X") {
                sTraining = tokenizer.GetNextToken();
                sIntensity = tokenizer.GetNextToken();
                week.training.push_back(Training());
                Training &training = week.training.back();
                CreateTraining( sTraining, sIntensity, wxDateTime(startTime+wxTimeSpan(24*day)), training );
                sTraining = tokenizer.GetNextToken();
            }
            sIntensity = tokenizer.GetNextToken();
            week.training.push_back(Training());
            Training &training = week.training.back();

            CreateTraining( sTraining, sIntensity, wxDateTime(startTime+wxTimeSpan(24*day)), training );
            day++;
        }
    }
    weeks = std::vector<Week>(lWeeks.size());
    std::list<Week>::iterator it = lWeeks.begin();
    int i=0;
    while (it!=lWeeks.end()) {
        weeks[i] = *it;
        it++;
        i++;
    }
}

void Plan::CreateTraining( wxString const &sTraining, wxString const &sIntensity, wxDateTime const &day, Training &training )
{
    training.date = day;
    if (sTraining.IsEmpty()) {
        training.type = NONE;
    } else if (sTraining.Cmp("RR") == 0 ) {
        training.type = RR;
    } else if (sTraining.Cmp("FR") == 0 ) {
        training.type = FR;
    } else if (sTraining.Cmp("LR") == 0 ) {
        training.type = LR;
    } else if (sTraining.Cmp("FFR") == 0 ) {
        training.type = FFR;
    } else if (sTraining.Cmp("TR") == 0 ) {
        training.type = TR;
    } else if (sTraining.Cmp("CIR") == 0 ) {
        training.type = CIR;
    } else if (sTraining.Cmp("LRSP") == 0 ) {
        training.type = LRSP;
    } else if (sTraining.Cmp("LRFF") == 0 ) {
        training.type = LRFF;
    } else if (sTraining.Cmp("SPR") == 0 ) {
        training.type = SPR;
    } else if (sTraining.Cmp("HRR") == 0 ) {
        training.type = HRR;
    } else if (sTraining.Cmp("SIR") == 0 ) {
        training.type = SIR;
    } else if (sTraining.Cmp("LIR") == 0 ) {
        training.type = LIR;
    } else if (sTraining.Cmp("MIR") == 0 ) {
        training.type = MIR;
    } else if (sTraining.Cmp("HM") == 0 ) {
        training.type = HM;
    } else if (sTraining.Cmp("M") == 0 ) {
        training.type = M;
    } else if (sTraining.Cmp("KM10") == 0 ) {
        training.type = KM10;
    } else if (sTraining.Cmp("KM5") == 0 ) {
        training.type = KM5;
    } else {
        wxLogError(_("Unparsed training: %s"), sTraining);
    }

    if ( sIntensity.IsEmpty() ) {
        training.intensity = 1;
    } else {
        unsigned long ul;
        if (!sIntensity.ToULong( &ul )) {
            wxLogError(_("Unparsed intensity: %s"), sIntensity);
        }
        training.intensity = (int)ul;
    }
}

Plan::Plan()
{
};

wxString Plan::ToString()
{
    return wxString::Format(_("Plan for %s, %s level. Dates %s to %s (%d weeks)"), gDistance[distance], gLevel[level], startTime.FormatISODate(), date.FormatISODate(), (int)weeks.size());
}

std::list<Training*> Plan::GetTraining( wxDateTime const &day )
{
    bool bStarted = false;
    std::list<Training*> trainingList;
    for (int i=0; i<weeks.size(); i++) {
        std::list<Training>::iterator it = weeks[i].training.begin();
        while (it != weeks[i].training.end()) {
            Training &t = *it;
            if (t.date.IsSameDate(day)) {
                trainingList.push_back( &t );
                bStarted = true;
            } else if (bStarted) {
                return trainingList;
            }
            it++;
        }
    }
    return trainingList;
}

void Plan::Print()
{
    wxLogMessage(ToString());
    for (int i=0; i<weeks.size(); i++) {
        wxLogMessage(weeks[i].ToString());
        std::list<Training>::iterator it = weeks[i].training.begin();
        while (it != weeks[i].training.end()) {
            Training &t = *it;
            wxLogMessage(t.ToString(true, outUnit));
            it++;
        }
    }
}

bool Plan::SaveCsv( wxString const &filename )
{
    textFile.Create(filename);
    textFile.Write();
    textFile.Close();
    return true;
}