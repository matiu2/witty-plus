/*
 * =====================================================================================
 *
 *       Filename:  SessionHandle.hpp
 *
 *    Description:  A handle to a long lived session. Use it in your app
 *
 *        Version:  1.0
 *        Created:  06/25/2011 08:58:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SESSION_HANDLE_HPP
#define SESSION_HANDLE_HPP

#include <string>
#include <Wt/WObject>
#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WRandom>
#include <Wt/WTimer>
#include "UserManager.hpp"

using std::string;
using Wt::WObject;
using Wt::WRandom;
using Wt::WTimer;
using Wt::WApplication;
using Wt::WEnvironment;

namespace wittyPlus {

/**
* @brief A handle to the session of the currently logged in user. This is what you use in your app
*/
template<class SessionStore, class User>
class SessionHandle : public WObject {
private:
    UserManager<User> userManager;
    SessionStore& sessions;
    string cookieCache;
    dbo::ptr<User> userCache;
    WTimer* touchSessionsTimer;     /// Used to stop sessions timing out without touching them too much
    const string& _cookieName;      /// The name of the cookie we're after .. this is global across the whole application and all threads.
    /// Returns The cookie that the client's browser is giving us
    const string& getCookie() const {
        WApplication* app = WApplication::instance();
        const WEnvironment::CookieMap& cookies = app->environment().cookies();
        WEnvironment::CookieMap::const_iterator i = cookies.find(_cookieName);
        if (i != cookies.end()) {
            return (*i).second;
        }
        // If the browser doesn't have a cookie, we might have just set it
        // Even if this server side cache is old (and the user has logged out, and the client side cookie deleted)
        // It shouldn't matter because the session store still won't return a username for it.
        // But still if there is a browser side cookie, that takes precedence
        return cookieCache;
    }
    /// Called when the timer activates, now we go lock some threads and tell the session store
    void onTouchSessionsActivate() {
        sessions.touch(getCookie());
        delete touchSessionsTimer;
        touchSessionsTimer = 0;
    }
public:
    SessionHandle(WObject* parent, dbo::Session& dbSession, const string& cookieName) :
        WObject(parent), userManager(dbSession), sessions(SessionStore::getInstance()), _cookieName(cookieName) 
    {
        // Check if we're already logged in
        const string& cookie =  getCookie();
        if (!cookie.empty()) {
            string username = sessions.username(getCookie(), true); // Touch the session as new app/view is openning for it
            if (username.empty())
                userCache.reset();
            else
                userCache = userManager.userFromName(username);
        }

    }
    /// Tries to log the user in, creates the session, and sets the session cookie. @return true if login was succesful
    bool tryLogin(const string& username, const string& password) {
        if (userManager.checkLogin(username, password)) {
            cookieCache = WRandom::generateId();
            WApplication* app = WApplication::instance();
            app->setCookie(_cookieName, cookieCache, 60*60*24*365, "", "/", true); // TODO: set secure based on settings
            sessions.login(username, cookieCache);  // Record that they're logged in for other SessionHandles to find
            return true;
        }
        return false;
    }
    ///  Logs the user out of all sessions eventually; this session immediately. 
    void logout() {
        userManager.logout();
        sessions.logout(getCookie());
    }
    /// Let us know that the user is still here. a session, (doesn't cost much .. just starts the timer if it's not already started)
    void touchSession() {
        if (touchSessionsTimer == 0) {
            touchSessionsTimer = new WTimer(this);
            touchSessionsTimer->setSingleShot(true);
            touchSessionsTimer->setInterval(sessions.getTimeout());
        }
    }
    /// Returns a dbo::ptr to the currently logged in user *
    dbo::ptr<User> user(bool touchSession) {
        // Check the session thing live .. this will possibly slow things down by locking if another thread is writing
        // but on the plus side it means if one thread los out .. all threads log out
        dbo::ptr<User> user;
        string cookie = getCookie();
        if (!cookie.empty()) {
            string username = sessions.username(cookie);
            if (!user) {
                // If they have an old session cookie, but they're not logged in now .. delete the old cookie
                WApplication::instance()->setCookie(_cookieName, cookie, 0, "", "/", true);
                cookieCache = "";
            }
        }
        return user;
    }
    bool isLoggedIn() { return user; }
};

} // namespace wittyPlus

#endif // SESSION_HANDLE_HPP
