#include	"LongRun.h"
#include	<wx/intl.h>

LongRun::LongRun()
{
    shortName = _("Long Run");
    type = LR;
    wxString format = wxString("1,1,1.0,1,2,4.5,1,1,0.5,1,-1,\
			 2,1,1.0,1,2,5.5,1,1,0.5,1,-1,\
			 3,1,1.0,1,2,6.5,1,1,0.5,1,-1,\
			 4,1,1.0,1,2,7.5,1,1,0.5,1,-1,\
			 5,1,1.0,1,2,8.5,1,1,0.5,1,-1,\
			 6,1,1.0,1,2,9.5,1,1,0.5,1,-1,\
			 7,1,1.0,1,2,10.5,1,1,0.5,1,-1,\
			 8,1,1.0,1,2,11.5,1,1,0.5,1,-1,\
			 9,1,1.0,1,2,12.5,1,1,0.5,1,-1,\
			 10,1,1.0,1,2,13.5,1,1,0.5,1,-1,\
			 11,1,1.0,1,2,14.5,1,1,0.5,1,-1,\
			 12,1,1.0,1,2,15.5,1,1,0.5,1,-1,\
			 13,1,1.0,1,2,16.5,1,1,0.5,1,-1,\
			 14,1,1.0,1,2,17.5,1,1,0.5,1,-1,\
			 15,1,1.0,1,2,18.5,1,1,0.5,1,-1");

    Create( format );
}