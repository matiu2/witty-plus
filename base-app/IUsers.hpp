/*
 * =====================================================================================
 *
 *       Filename:  IUsers.hpp
 *
 *    Description:  Allows you to access information about the currently logged in user
 *
 *        Version:  1.0
 *        Created:  11/05/2011 15:18:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#pragma once

#include <string>
#include <Wt/WSignal>
#include <Wt/Dbo/ptr>
#include "model/User.hpp"

namespace wittyPlus {

typedef Wt::Signal< Wt::Dbo::ptr<model::User>, Wt::Dbo::ptr<model::User> > UserChangedSignal;

class IUsers {
public:
    virtual bool tryLogin(const string& username, const string& password) = 0;
    virtual UserChangedSignal* userChanged() = 0; /// An event triggered when a user logs in or logs out
    virtual Wt::Dbo::ptr<model::User> user() = 0;
    virtual void logout() = 0;
    virtual bool isLoggedIn() = 0;

    static IUsers* instance();
};

} // namespace wittyPlus {
