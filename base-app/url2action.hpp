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
#include "UserManager.hpp"
#include "Wt/WString"

using Wt::WString;

namespace my_app {

class URL2Action : public WObject {
protected:
    App* app;
    // Utility methods
    bool isLoggedIn() { return app->userSession()->user(); }
    template<class Widget> void setBody() { app->mainWindow()->bindWidget("content", new Widget()); }
    template<class Widget> void setBodyIfLoggedIn() {
        if (isLoggedIn())
            setBody<Widget>();
        else
            app->statusTextChanged()->emit(WString::tr("permission-denied"));
    }
public:
    URL2Action(App* app) : WObject(app), app(app) {
        // Hook up all the urls
        app->url("")->connect(this, &URL2Action::home);
        app->url(urls::login)->connect(this, &URL2Action::login);
        app->url(urls::logout)->connect(this, &URL2Action::logout);
        app->url(urls::adminUsers)->connect(this, &URL2Action::adminUsers);
    }
    // URL Handlers
    void home() { app->mainWindow()->bindString("content", "PUT YOUR DEFAULT BODY TEXT OR WIDDGETS HERE"); }
    /// Actually logs you out
    void logout() {
        dbo::ptr<User> oldUser = app->userSession()->user();
        app->userSession()->logout();
        dbo::ptr<User> newUser = app->userSession()->user();
        if (oldUser != newUser)
            app->userChanged()->emit(oldUser, newUser);
        app->redirect("/");
        app->statusTextChanged()->emit(WString::tr("you-are-logged-out"));
    }
    /// Shows the login form
    void login() { setBody<LoginWindow>(); }
    /* Admin tasks - must be logged in for these */

    /// /admin/users - if you're logged in, lets you adminster the users
    void adminUsers() { setBodyIfLoggedIn<UserManager>(); }
};


} // namespace my_app {

#endif // URL2ACTION_HPP
