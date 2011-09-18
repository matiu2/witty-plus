/*
 * =====================================================================================
 *
 *       Filename:  MemorySessionStore.cpp
 *
 *    Description:  G
 *
 *        Version:  1.0
 *        Created:  06/22/2011 09:00:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "MemorySessionStore.hpp"
#include <stdexcept>

using std::invalid_argument;

namespace wittyPlus {

MemorySessionStore* MemorySessionStore::globalInstance = 0;
const unsigned int MemorySessionStore::defaultTimeout = 1800; // If a user doesn't touch a session for 30 minutes .. they log out

/**
* @brief Records that a user has logged in and a new session is started
*
* @param userId the login of the user
* @param cookie the cookie that we stored on their machine
*/
void MemorySessionStore::login(int userId, const string& cookie) {
    FullLock lock(_lock);
    sessions.insert(SessionMap::value_type(cookie, Session(userId)));
}

/**
* @brief Logs a user out
* @param cookie of the logged in user
*/
void MemorySessionStore::logout(const string& cookie) {
    FullLock lock(_lock);
    sessions.erase(cookie);
}

/**
* @brief Returns the userId of the currently logged in user.
* Throws std::invalid_argument if no user with that cookie found.
*
* @param cookie the cookie that the client browser gave us
* @param touch If true, updates the session time out
*
* @return userId of the currently logged in user
*/
int MemorySessionStore::userId(const string& cookie, bool touch) {
    ReadOnlyLock lock(_lock);
    Session* session = findSession(lock, cookie);
    if (session != 0) {
        if (session->age() < _timeout) {
            if (touch) {
                ReadWriteLock touchLock(_lock);
                // Session is still good, update its timeout on our end
                session->updateLoginTime();
            }
            return session->userId();
        } else {
            // Cookie is expired - delete its session and return empty
            ReadWriteLock eraseLock(_lock);
            sessions.erase(cookie);
        }
    }
    throw invalid_argument("No user with cookie " + cookie + " found");
}
    
/**
* @brief Resets the server side timeout for this session
*/
void MemorySessionStore::touch(const string& cookie) {
    ReadOnlyLock lock(_lock);
    Session* session = findSession(lock, cookie);
    if (session != 0) {
        ReadWriteLock bigLock(_lock);
        session->updateLoginTime();
    }
}

/**
* @brief Gets the write lock and purges all the old sessions
*/
void MemorySessionStore::purgeOldSessions() {
    FullLock lock(_lock);
    for (PSession it = sessions.begin(); it != sessions.end();) {
        if ((*it).second.age() > _timeout) {
            sessions.erase(it++);
        } else {
            ++it;
        }
    }
}

} // namespace wittyPlus
