#pragma once

#if wxUSE_WEBVIEW
#include	<wx/webview.h>

class WebView : public wxWebView {
public:
    WebView( wxWindow *pParent, wxString const &url );
};
#endif
