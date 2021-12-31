#pragma once

#include	"Defines.h"
#include	<boost/shared_ptr.hpp>
#include	<map>

class User;

//! Smart pointer to a user
typedef boost::shared_ptr<User> UserPtr;

/** A user has all the properties needed for defining a training plan.*/
class User {
public:
    User();

    //! The distance unit
    PTUnit unit;

    //! The training level
    PTLevel level;

    //! The competition distance
    PTDistance distance;

    //! The lactate threshold pulse
    int pulse;

    //! True if pace is set
    bool use_pace;

    //! Date of competition
    wxDateTime raceDate;

    //! Returns references to all users by name
    static std::map<wxString,UserPtr>& GetUsers();

    /** Get a named user.
    \param name The name of the user
    */
    static UserPtr GetUser(wxString const &name);

    /** Add a named user and get a User structure back.
    \return The user attributes for the created user.*/
    static UserPtr AddUser(wxString const &name);

    /** Returns name of a user.
    \param pUser User to get name for.*/
    static wxString GetName(UserPtr pUser);

    /** Get the active / current user*/
    static UserPtr GetUser();

    /** Set the active / current user.*/
    static void SetCurrentUser( UserPtr pUser );

private:
    static std::map<wxString,UserPtr> cUserMap;
    static UserPtr cpCurrentUser;
};