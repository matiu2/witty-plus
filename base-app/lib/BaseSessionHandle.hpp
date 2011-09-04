/*
 * =====================================================================================
 *
 *       Filename:  BaseSessionHandle.hpp
 *
 *    Description:  Provides all the non-template parts of SessionHandle. A handle to the user's session for the app.
 *
 *        Version:  1.0
 *        Created:  08/08/11 23:20:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef BASESESSIONHANDLE_HPP
#define BASESESSIONHANDLE_HPP

#include <string>
#include <Wt/WObject>
#include <Wt/WTimer>

using Wt::WObject;
using Wt::WTimer;
using std::string;

namespace wittyPlus {

class BaseSessionHandle : public WObject {
protected:
    string cookieCache;
    WTimer* touchSessionsTimer;     /// Used to not hit the user sessions store (provided by overrider) too much.
    const string& getCookie() const;
    /// Called when the timer runs out. Locks threads/db resources and touches the session to let the store know it's still alive.
    void onTouchSessionsActivate() { doTouchSession(); }
    const string& _cookieName;      /// The name of the cookie we're after .. this is global across the whole application and all threads.
    virtual unsigned long getStoreTimeout() = 0; /// Override this to let us know how often we should hit the user session store
    virtual void doTouchSession() = 0; /// Called by onTouchSessionsActivate
public:
    BaseSessionHandle(WObject* parent, const string& cookieName) : WObject(parent), _cookieName(cookieName) {}
    void touchSession();   /// Let us know that the user is still here. a session, (doesn't cost much .. just starts the timer if it's not already started)
};

} // namespace wittyPlus

#endif // BASESESSIONHANDLE_HPP

