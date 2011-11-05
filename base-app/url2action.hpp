/*
 * =====================================================================================
 *
 *       Filename:  url2action.hpp
 *
 *    Description:  Maps URLs to actions
 *
 *        Version:  1.0
 *        Created:  08/23/2011 01:43:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef URL2ACTION_HPP
#define URL2ACTION_HPP

#include "urls.hpp"
#include "App.hpp"
#include "IGui.hpp"
#include "IUsers.hpp"
#include "UserManager.hpp"
#include "LoginWindow.hpp"
#include "lib/URLs.hpp"
#include <Wt/WString>

using Wt::WString;

namespace wittyPlus {

using base::URLs;

class URL2Action : public WObject {
protected:
    URLs _urls; /// Allows us to connect urls to actions
    App* app;
    // Utility methods
    bool isLoggedIn() { return IUsers::instance()->user(); }
    template<class Widget> void setBody() { IGui::instance()->setBody(new Widget()); }
    template<class Widget> void setBodyIfLoggedIn() {
        if (isLoggedIn()) {
            setBody<Widget>();
        } else {
            IGui::instance()->setBody(WString::tr("access-denied"));
        }
    }
public:
    URL2Action(App* app) : WObject(app), app(app) {
        app->internalPathChanged().connect(&_urls, &URLs::run);
        // Hook up all the urls
        _urls[urls::home].connect(this, &URL2Action::home);
        _urls[urls::login].connect(this, &URL2Action::login);
        _urls[urls::logout].connect(this, &URL2Action::logout);
        _urls[urls::admin_users].connect(this, &URL2Action::admin_users);
    }
    // URL Handlers
    void home() { app->mainWindow()->bindString("content", WString::tr("sample-content")); }
    /// Actually logs you out
    void logout() {
        IUsers* users = IUsers::instance();
        dbo::ptr<User> oldUser = users->user();
        users->logout();
        dbo::ptr<User> newUser = users->user();
        if (oldUser != newUser)
            app->userChanged()->emit(oldUser, newUser);
        app->go(urls::home);
        app->setStatusText(WString::tr("you-are-logged-out"));
    }
    /// Shows the login form
    void login() { setBody<LoginWindow>(); }
    /* Admin tasks - must be logged in for these */
    /// /admin/users - if you're logged in, lets you adminster the users
    void admin_users() { setBodyIfLoggedIn<UserManager>(); }
};


} // namespace my_app {

#endif // URL2ACTION_HPP
