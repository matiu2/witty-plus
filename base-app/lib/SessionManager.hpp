/*
 * =====================================================================================
 *
 *       Filename:  SessionManager.hpp
 *
 *    Description:  Hooks together witty-sessions- and the mongo UserManager
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

#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP

#include <Wt/WObject>
#include "SessionStore.hpp"
#include "UserManager.hpp"

namespace wittyPlus {

/**
* @brief A handle to the session of the currently logged in user
*/
class SessionManager : public WObject {
public:
    bool tryLogin(const string& username, const string& password);
    void touchSession();
    string username();

};

} // namespace wittyPlus

#endif // SESSION_MANAGER_HPP

