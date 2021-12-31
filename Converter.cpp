#include	<Converter.h>
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

void Converter::Convert( ESpeedType const &from, ESpeedType const &to, int const &val1, int const &val2, int &outVal1, int &outVal2 )
{
    switch (from) {
    case MIN_PER_KM: {
        double totSeconds = val1*60+val2;
        switch (to ) {
        case MIN_PER_MILE: {
            double secondsPerMile = totSeconds * Converter::GetKmPerMile();
            outVal1 = secondsPerMile / 60;
            outVal2 = (int) (secondsPerMile - 60*outVal1 + 0.5);
        }
        break;

        case KM_PER_HOUR: {
            double kmPerHour = 3600.0/totSeconds;
            outVal1 = (int) (kmPerHour);
            outVal2 = (int) ((kmPerHour-outVal1)*100 + 0.5);
        }
        break;

        }
    }
    break;

    case MIN_PER_MILE: {
        double totSeconds = val1*60+val2;
        switch (to ) {
        case MIN_PER_KM: {
            double secondsPerKm = totSeconds / Converter::GetKmPerMile();
            outVal1 = secondsPerKm / 60;
            outVal2 = (int) (secondsPerKm - 60*outVal1 + 0.5);
        }
        break;

        case KM_PER_HOUR: {
            double secondsPerKm = totSeconds / Converter::GetKmPerMile();
            double kmPerHour = 3600.0/secondsPerKm;
            outVal1 = (int) (kmPerHour);
            outVal2 = (int) ((kmPerHour-outVal1)*100 + 0.5);
        }
        break;

        }
    }
    break;

    case KM_PER_HOUR:
        break;
    }
}

wxTimeSpan Converter::GetTime(double const &distance, wxTimeSpan const &pace, ESpeedType type)
{
    wxTimeSpan time;
    wxLongLong sec = pace.GetSeconds();
    double totTime = distance * sec.ToDouble();
    sec = (int) (totTime);
    if (sec < 120) {
        totTime = 1000.0*(totTime-sec.ToDouble());
    } else {
        totTime = 0.0;
    }

    time = wxTimeSpan(0,0,sec,(int)(totTime+0.5));

    return time;
}
