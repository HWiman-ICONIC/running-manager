#pragma once

#include	<wx/webview.h>

class WebView : public wxWebView
{
public:
	WebView( wxWindow *pParent, wxString const &url );
};