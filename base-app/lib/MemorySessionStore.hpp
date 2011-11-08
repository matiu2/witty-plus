/*
 * =====================================================================================
 *
 *       Filename:  MemorySessionStore.hpp
 *
 *    Description:  An in memory, thread safe Session manager
 *                  Because witty's 'internalPathChanged' thing is not being too happy
 *                  with html5 api .. this makes your witty app more like a web app and
 *                  have logged in sessions last a long time.
 *
 *                  I call this memory session store, because later I'll probably write
 *                  a DB session store. Memory one should be faster, but less scalable
 *                  and of course if you restart your app, all your users are logged out.
 *
 *        Version:  1.0
 *        Created:  06/22/2011 08:32:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MEMORY_SESSION_STORE_HPP
#define MEMORY_SESSION_STORE_HPP

#include <string>
#include <ctime>
#include <map>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

using std::string;
using std::time_t;
using std::time;
using std::map;
using boost::shared_mutex;
using boost::lock_guard;
using boost::shared_lock;
using boost::upgrade_lock;

namespace wittyPlus {
namespace base {

/**
* Info about a single logged in session ..
* As these can be shared between threads, we *copy* around userIds. dbo::ptr objects are not thread safe, so we can't pass those between threads
*/
class Session {
private:
    int _userId;
    time_t _loginTime;
public:
    Session(int userId) : _userId(userId), _loginTime(time(NULL)) {}
    int userId() const { return _userId; };
    const time_t& loginTime() const { return _loginTime; };
    void updateLoginTime() { _loginTime = time(NULL); }
    unsigned int age() { return time(NULL) - _loginTime; } /// Returns the last touched age of this session in seconds
};

/**
* @brief Handles logged in users.
*
* All this class provides is a thread safe 'cookie to user' map.
* It handles timeouts on the server side .. so you prolly wanna make your browser cookies quite long lived.
*/
class MemorySessionStore {
public:
    static const unsigned int defaultTimeout;
    typedef map<string, Session > SessionMap;
    typedef std::pair<string, Session > SessionPair;
    typedef SessionMap::iterator PSession;
    typedef shared_mutex StoreMutex;
    typedef shared_lock<StoreMutex> ReadOnlyLock;
    typedef lock_guard<StoreMutex> FullLock;
    typedef upgrade_lock<StoreMutex> ReadWriteLock;
private:
    static MemorySessionStore* globalInstance;
    shared_mutex _lock; // Many can read session info .. but only one can write it
    #if (__cplusplus > 199711L)
    atomic<unsigned long> _timeout; /// How long a single session lasts - c++0x style
    #else
    volatile unsigned long _timeout; /// How long a single session lasts - old c++ style
    #endif
    SessionMap sessions; /// Holds data for logged in users. Key is the cookie. This is protected through thread locks
    /**
    * @brief Just finds a session. Doesn't care about expiry time.
    *
    * @param lock A reference to a scoped lock. You must have one to call this func
    * @param cookie The cookie for the session we're looking for
    *
    * @return a pointer to the session if found, or 0
    */
    Session* findSession(ReadOnlyLock& /* prove you have a lock */, const string& cookie) {
        PSession pSession = sessions.find(cookie);
        if (pSession != sessions.end()) {
            return &((*pSession).second);
        }
        return 0;
    }
    // structors
    MemorySessionStore() : _timeout(defaultTimeout) {}
    ~MemorySessionStore() {
        // Delete all the sessions but while locked
        lock_guard<shared_mutex> lock(_lock);
        sessions.erase(sessions.begin(), sessions.end());
    }
public:
    static MemorySessionStore& getInstance() {
        if (globalInstance == 0)
            globalInstance = new MemorySessionStore(); // Create one for life of whole app. Will be deleted when app ends.
        return *globalInstance;
    }
    // Atomic (thread safe without locking) (hopefully) operations
    unsigned int getTimeout() { return _timeout; } /// timeout in secs .. default is 5 mins .. hopefully this is atomic
    void setTimeout(unsigned int newTimeout) { _timeout = newTimeout; }
    // Thread safe operations
    void login(int userId, const string& cookie); /// @brief Records that a user has logged in and a new session is started
    void logout(const string& cookie); /// Logs a user out
    /// Returns the currently logged in userId or throws invalid_argument if no-one's logged in
    int userId(const string& cookie, bool touch=true);  
    void touch(const string& cookie); /// Let us know that a lesson hasn't timed out
    void purgeOldSessions(); /// Clean out expired sessions
};

} // namespace base
} // namespace wittyPlus

#endif // MEMORY_SESSION_STORE_HPP
