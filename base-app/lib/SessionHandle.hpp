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
#include <stdexcept>
#include <Wt/WObject>
#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WRandom>
#include <Wt/WTimer>
#include <Wt/Dbo/Dbo>
#include <ctime>
#include "BaseSessionHandle.hpp"
#include "sha.hpp"

using std::string;
using std::invalid_argument;
using Wt::WObject;
using Wt::WRandom;
using Wt::WTimer;
using Wt::WApplication;
using Wt::WEnvironment;
using std::time_t;
using std::time;

namespace dbo = Wt::Dbo;

namespace wittyPlus {

/**
* @brief A handle to the session of the currently logged in user. This is what you use in your app
*/
template<class SessionStore, class User>
class SessionHandle : public BaseSessionHandle {
private:
    SessionStore& _userSessionStore;
    dbo::Session& _dbSession;        /// dbSession handle
    time_t _cacheTime;               /// Cache times out
    dbo::ptr<User> _userCache;       /// A ptr to the currently logged in user
    /**
    * Returns true if the username and password match are in the DB. Always takes the same amount of time (roughly)
    * to calculate. This is to prevent remote timing attacks.
    *
    * @param username the username being used to log in
    * @param password the password being used to log in
    *
    * @return the user object if successful .. or an empty object if failed login
    */
    dbo::ptr<User> _doTryLogin(const string& username, const string& password) {
        dbo::Transaction transaction(_dbSession);
        dbo::ptr<User> userFromDB = _dbSession.find<User>().where("name = ?").bind(username);
        // (even if they enter a hash of all zeros if user is not found they still won't be able to log in .. check 'result' below \/
        StdSHAValue hashFromDB(20, 0); // This'll be the hash we'll compare on.
        if (userFromDB)
            hashFromDB = userFromDB->passwordHash();
        // Check the password
        StdSHAValue hashFromNet = sha1(password);
        // Always compare 20 bytes, no shortcuts allowed. Don't wanna be hit by a timing attack
        assert(hashFromDB.size() == SHALength);
        // If there's no user .. it'll always be a false result .. marked as volatile to prevent optimization, to prevent timing attacks
        volatile bool result = userFromDB; 
        // Always do this loop and compare *every* element to prevent statistical timing attacks
        for(size_t i=0; i < SHALength; ++i) {
            if (hashFromDB[i] != hashFromNet[i])
                result = false; // Don't just return from here .. make all checks constant time to prevent timing attacks
        }
        _userCache = userFromDB; // Store the logged in user
        transaction.commit();
        if (!result)
            userFromDB = dbo::ptr<User>();
        return userFromDB;
    }
protected:
    unsigned long getStoreTimeout() { return _userSessionStore.getTimeout(); }
    /// Does the actual touching of the session store user session
    void doTouchSession() { _userSessionStore.touch(getCookie()); }
public:
    SessionHandle(WObject* parent, dbo::Session& dbSession, const string& cookieName) :
        BaseSessionHandle(parent, cookieName), _userSessionStore(SessionStore::getInstance()), _dbSession(dbSession), _cacheTime(time(NULL))
    {
        // Check if we're already logged in
        const string& cookie = getCookie();
        if (!cookie.empty()) {
            int userId;
            try {
                userId = _userSessionStore.userId(getCookie(), true); // Touch the session as new app/view is openning for it
            } catch (invalid_argument e) {
                // Nobody's logged in right now
                _userCache.reset();
                return;
            }
            // Remember our user object
            dbo::Transaction transaction(_dbSession);
            _userCache = _dbSession.find<User>().where("id = ?").bind((int)userId);
            transaction.commit();
        }
    }
    /// Tries to log the user in, creates the session, and sets the session cookie. @return true if login was succesful
    bool tryLogin(const string& username, const string& password) {
        dbo::ptr<User> user = _doTryLogin(username, password);
        if (user) {
            cookieCache = WRandom::generateId();
            WApplication* app = WApplication::instance();
            app->setCookie(_cookieName, cookieCache, 60*60*24*365, "", "/", true); // TODO: set secure based on settings
            _userSessionStore.login(user.id(), cookieCache);  // Record that they're logged in for other SessionHandles to find
            return true;
        }
        return false;
    }
    /// Logs the user out of all _userSessionStore eventually; this session immediately. 
    void logout() {
        _userCache.reset();
        _userSessionStore.logout(getCookie());
    }
    /// Returns a dbo::ptr to the currently logged in user *
    dbo::ptr<User> user() {
        if (_userCache) {
            if (time(NULL) - _cacheTime > _userSessionStore.getTimeout())
                _userCache.reset();
            else
                return _userCache;
        }
        // Check the session thing live .. this will possibly slow things down by locking if another thread is writing
        // but on the plus side it means if one thread los out .. all threads log out
        string cookie = getCookie();
        if (!cookie.empty()) {
            unsigned int userId;
            try {
                userId = _userSessionStore.userId(cookie);
            } catch (invalid_argument e) {
                // If they have an old session cookie, but they're not logged in now .. delete the old cookie
                WApplication::instance()->setCookie(_cookieName, cookie, 0, "", "/", true);
                cookieCache = "";
                return dbo::ptr<User>(); // Empty pointer
            }
            touchSession();
            // Cache and return the result
            dbo::Transaction t(_dbSession);
            _userCache = _dbSession.find<User>().where("id = ?").bind((int)userId);
            _cacheTime = time(NULL); // (now)
            t.commit();
            return _userCache;
        } else {
            return dbo::ptr<User>(); // Empty pointer
        }
    }
    bool isLoggedIn() { return user(); }
};

} // namespace wittyPlus

#endif // SESSION_HANDLE_HPP
