#include	"Converter.h"
#include	<wx/log.h>

double Converter::Convert( double const &inDistance, PTUnit const &inUnit, PTUnit const &outUnit )
{
    if (inUnit == outUnit) {
        return inDistance;
    }
    if (inUnit == MILES) {
        if (outUnit == KM) {
            return GetKmPerMile()*inDistance;
        }
    }
    if (inUnit == KM) {
        if (outUnit == MILES) {
            return inDistance/GetKmPerMile();
        }
    }

    wxLogError(_("Could not convert from %s to %s"), gUnit[inUnit], gUnit[outUnit]);
    return inDistance;
}

double Converter::GetKmPerMile()
{
    return 1.609344;
}