/*
 * =====================================================================================
 *
 *       Filename:  BaseApp.hpp
 *
 *    Description:  Base Application type. WApplications plus user management.
 *
 *        Version:  1.0
 *        Created:  08/07/11 18:57:27
 *       Revision:  none
 *       Compiler:  gcc
 *  
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef BASE_APP_HPP
#define BASE_APP_HPP

#include <Wt/WApplication>
#include "SessionHandle.hpp"
#include "MemorySessionStore.hpp"

namespace Wt {
    class WString;
} // namespace Wt

using Wt::WString;


namespace wittyPlus {

template <class User>
class BaseApp : public Wt::WApplication {
public:
    typedef MemorySessionStore SessionStore;
    typedef SessionHandle<SessionStore, User> UserSession;
protected:
    UserSession* _userSession;
    dbo::Session _dbSession;
    const string& _cookieName;
public:
    BaseApp(const Wt::WEnvironment& environment, const string& cookieName) : Wt::WApplication(environment), _cookieName(cookieName) {
        // Load the message bundles
        messageResourceBundle().use(appRoot() + "messages/LoginWindow");
        // Set up the UI
        setTitle(WString::tr("main-title"));
        _userSession = new UserSession(this, dbSession(), cookieName);
        setBodyClass("yui-skin-sam");
    }
    dbo::Session& dbSession() { return _dbSession; }
    const string& cookieName() { return _cookieName; }
    UserSession* userSession() { return _userSession; }
};


} // namespace wittyPlus

#endif //  BASE_APP_HPP
