/*
 * =====================================================================================
 *
 *       Filename:  BaseSessionHandle.cpp
 *
 *    Description:  Implementation for the non-template parts of the handle to a user session for an app
 *
 *        Version:  1.0
 *        Created:  08/08/11 23:23:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "BaseSessionHandle.hpp"
#include <Wt/WApplication>
#include <Wt/WEnvironment>

using Wt::WApplication;
using Wt::WEnvironment;

namespace wittyPlus {

/**
* @brief Get's the cookie from the app
*
* @return The cookie that the client's browser is giving us
*/
const string& BaseSessionHandle::getCookie() const {
    // First ask the browser
    WApplication* app = WApplication::instance();
    const WEnvironment::CookieMap& cookies = app->environment().cookies();
    WEnvironment::CookieMap::const_iterator i = cookies.find(_cookieName);
    if (i != cookies.end()) {
        return (*i).second;
    }
    // Fall back to cached version
    // If the browser doesn't have a cookie, we might have just set it and no requests have happened yet
    // Even if this server side cache is old (and the user has logged out, and the client side cookie deleted)
    // It shouldn't matter because the session store still won't return a username for it.
    // But still if there is a browser side cookie, that takes precedence
    return cookieCache;
}

/**
* @brief Call to let us know that the user is still logged in. Doesn't cost much.
*/
void BaseSessionHandle::touchSession() {
    if (touchSessionsTimer == 0) {
        touchSessionsTimer = new WTimer(this);
        touchSessionsTimer->timeout().connect(this, &BaseSessionHandle::onTouchSessionsActivate);
        touchSessionsTimer->setSingleShot(true);
        touchSessionsTimer->setInterval(getStoreTimeout());
    }
}

/**
* @brief Called when the timer runs out. Touches the session to let the store know it's still alive.
*/
void BaseSessionHandle::onTouchSessionsActivate() {
    doTouchSession();
    delete touchSessionsTimer;
    touchSessionsTimer = 0;
}

} // namespace wittyPlus
