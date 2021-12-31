#include	<User.h>


std::map<wxString,UserPtr> User::cUserMap;
UserPtr User::cpCurrentUser;

User::User() :
    unit(KM),
    level(PTL_LOW),
    distance(PTD_10KM),
    pulse(160),
    use_pace(false),
    raceDate(wxDateTime::Today()+wxDateSpan(0,0,11)),
    calculatorSpeedMin(5),
    calculatorSpeedSec(0)
{
}

User::User(UserPtr pOther)
{
    *this = *pOther;
}

std::map<wxString,UserPtr> &User::GetUsers()
{
    return cUserMap;
}

UserPtr User::GetUser(wxString const &name)
{
    std::map<wxString,UserPtr>::iterator it;
    for (it=cUserMap.begin(); it!=cUserMap.end(); it++) {
        if (name.IsSameAs(it->first)) {
            return it->second;
        }
    }
    return UserPtr();
}

UserPtr User::AddUser(wxString const &name)
{
    UserPtr pUser = GetUser(name);
    if (pUser) {
        return UserPtr();
    }
    pUser = UserPtr(new User());

    cUserMap[name] = pUser;
    return pUser;
}

void User::SetCurrentUser( UserPtr pUser )
{
    cpCurrentUser = pUser;
}

UserPtr User::GetUser()
{
    if (!cpCurrentUser) {
        cpCurrentUser = GetUser(wxString("Default"));
        if ( !cpCurrentUser ) {
            cpCurrentUser = User::AddUser(wxString("Default"));
        }
    }
    return cpCurrentUser;
}

wxString User::GetName(UserPtr pUser)
{
    std::map<wxString,UserPtr> &aMap = GetUsers();
    std::map<wxString,UserPtr>::iterator it = aMap.begin(), e = aMap.end();
    while (it != e ) {
        if (it->second == pUser ) {
            return it->first;
        }
    }
    return wxEmptyString;
}
