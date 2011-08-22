/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.cpp
 *
 *    Description:  Library code for the main window
 *
 *        Version:  1.0
 *        Created:  19/07/11 20:38:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "MainWindow.hpp"
#include "urls.hpp"
#include "LoginWindow.hpp"
#include "App.hpp"
#include <Wt/WAnchor>

namespace my_app {

MainWindow::MainWindow(WContainerWidget* parent) : wittyPlus::MoreAwesomeTemplate(parent) {
    setTemplateText(tr("main-template"));
    setStatusText("");
    // Set up any widets you have like the navigation tree
    bindString("nav", "Bind Nav box widget here");
    if (app()->userSession()->isLoggedIn()) {
        _loginLink = new WAnchor(urls::logout, tr("Logout"));
    } else {
        _loginLink = new WAnchor(urls::login, tr("Login"));
    }
    bindWidget("controls", _loginLink); // Put more controls in a div if you like
    // Hook up all the urls
    App* app = my_app::app();
    app->url("")->connect(this, &MainWindow::home);
    app->url(urls::login)->connect(this, &MainWindow::login);
    app->url(urls::logout)->connect(this, &MainWindow::logout);
    // Look out for people logging in and out
    app->userChanged()->connect(this, &MainWindow::handleUserChanged);
    // Fire one off as user may have navigated straight here
    app->internalPathChanged().emit(app->internalPath());
}

void MainWindow::logout() {
    App* app = my_app::app();
    dbo::ptr<User> oldUser = app->userSession()->user();
    app->userSession()->logout();
    dbo::ptr<User> newUser = app->userSession()->user();
    if (oldUser != newUser)
        app->userChanged()->emit(oldUser, newUser);
    app->redirect("/");
    app->statusTextChanged()->emit(tr("you-are-logged-out"));
}

void MainWindow::handleUserChanged(dbo::ptr<User>, dbo::ptr<User> newUser) {
    // If they just logged in
    if (newUser) {
        // Set the link to say logout
        _loginLink->setRefInternalPath(urls::logout);
        _loginLink->setText(tr("Logout"));
        // Say hello
        app()->statusTextChanged()->emit(tr("welcome-1").arg(newUser->name()));
    } else {
        // I'm assuming someone's logging out
        app()->statusTextChanged()->emit(tr("goodbye"));
    }
}
    
void MainWindow::toggleLoginLink(const string &url) {
    if (url == "/login")
        _loginLink->hide();
    else
        _loginLink->show();
}

} // namespace my_app
