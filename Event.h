#pragma once
#include	<wx/event.h>

wxDEFINE_EVENT(wxEVT_RM_COMMAND, wxCommandEvent);

#define EVT_RM_COMMAND(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        wxEVT_RM_COMMAND, id, wxID_ANY, \
        wxCommandEventHandler(fn), \
        (wxObject *) NULL \
    ),

/*namespace runningmanager
{
	extern const wxEventType RM_EVENT;			//!< Event type for moving in a window

	class Event : public wxCommandEvent
	{
	public:
		Event( wxEventType eventType = wxEVT_NULL, int id = 1 );
		Event( Event const &e );
		~Event();
		Event& operator=(Event const &e );
		virtual wxEvent* Clone() const;

		DECLARE_DYNAMIC_CLASS(Event)
	};

	typedef void (wxEvtHandler::*EventFunction)(Event&);

	#define EVT_RM(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        RM_EVENT, id, -1, \
        (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
        (wxObject *) NULL \
    ),
}*/