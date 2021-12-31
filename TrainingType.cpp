#include	"TrainingType.h"
#include	<wx/tokenzr.h>
#include    <boost/make_shared.hpp>

TrainingType::TrainingType( PTTrainingType type, wxString const &shortName, wxString const &description, wxString const &format ) :
    type(type), shortName(shortName), description(description)
{
    Create( format );
}

bool TrainingType::Create( wxString const &format )
{
    IntensityPtr i;
    std::list<IntensityPtr> lIntensity;
    wxStringTokenizer tokenizer( format, ",");
    long ul;
    double val;
    PTZone zone;
    PTUnit unit;
    SectionPtr s;
    SectionPtr sGroup;
    wxString sZone, sValue, sUnit, sRest;
    bool hasMoreSections;

    wxString token = tokenizer.GetNextToken();
    token.ToLong(&ul);

    if (ul == -1) {
        return true;
    }
    unit = (PTUnit) ul;

    while (tokenizer.HasMoreTokens()) {
        token = tokenizer.GetNextToken();
        token.ToLong(&ul);

        i = boost::make_shared<Intensity>(ul);

        hasMoreSections = true;
        while (hasMoreSections) {
            sZone = tokenizer.GetNextToken();
            if (sZone.EndsWith(wxString("X"), &sRest)) {
                sZone = sRest;
                sZone.ToLong(&ul);
                if (ul == 1) {
                    sGroup = SectionPtr();
                } else {
                    sGroup  = SectionBase::Create(ZONE0, ul);
                    i->section.push_back( sGroup );
                }
                continue;
            }

            sZone.ToLong(&ul);
            if (ul == -1) {
                lIntensity.push_back(i);
                hasMoreSections = false;
                break;
            }
            zone = (PTZone) ul;
            sValue = tokenizer.GetNextToken();
            sValue.ToDouble(&val);

            s = SectionBase::Create(zone, val, unit);
            if (sGroup) {
                if ( zone > sGroup->zone ) {
                    sGroup->zone = zone;
                }
                sGroup->Add( s );
            } else {
                i->section.push_back( s );
            }
        }
    }

    intensity = std::vector<IntensityPtr>(lIntensity.size());
    std::list<IntensityPtr>::iterator it = lIntensity.begin();
    int n = 0;
    while (it != lIntensity.end()) {
        intensity[n++] = *(it++);
    }

    return true;
}
