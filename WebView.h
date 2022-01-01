#pragma once

#if wxUSE_WEBVIEW
#include	<wx/webview.h>

/**
 * @brief web browser to order the 80/20 book
 * @todo Extend web view to enable e.g. Garmin and Strava homepages
*/
class WebView : public wxWebView {
public:
    WebView( wxWindow *pParent, wxString const &url );
};
#endif
