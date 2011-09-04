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
#include "LoginWindow.hpp"
#include "AdminIndex.hpp"
#include "App.hpp"
#include "urls.hpp"
#include <Wt/WAnchor>

namespace my_app {

MainWindow::MainWindow(WContainerWidget* parent) : wittyPlus::MoreAwesomeTemplate(parent), _loginLink(0) {
    setTemplateText(tr("main-template"));
    setStatusText("");
    // Set up any widets you have like the navigation tree
    bindString("nav", "Bind Nav box widget here");
    if (app()->userSession()->isLoggedIn()) {
        if (_loginLink != 0) {
            delete _loginLink;
            _loginLink = 0;
        }
        bindAndCreateWidget(_controlPanel, "controls");
    } else {
        _loginLink = urls::newInternalLink(urls::login, tr("Login"));
        bindWidget("controls", _loginLink);
    }
    // Look out for people logging in and out
    app()->userChanged()->connect(this, &MainWindow::handleUserChanged);
    // Don't show 'login' when on the 'login page'
    app()->internalPathChanged().connect(this, &MainWindow::checkLoginLink); 
}

void MainWindow::handleUserChanged(dbo::ptr<User>, dbo::ptr<User> newUser) {
    // If they just logged in
    if (newUser) {
        // We'll be using the admin control panel, instead of a login link
        bindAndCreateWidget(_controlPanel, "controls");
        _loginLink = 0; // Needs to be zeroed so we can know whether to hide it or not later
        // Say hello
        app()->statusTextChanged()->emit(tr("welcome-1").arg(newUser->name()));
    } else {
        // Someone's logging out
        app()->statusTextChanged()->emit(tr("goodbye"));
        bindAndCreateWidget(_loginLink, "controls");
        _loginLink->setRefInternalPath(urls::login);
        _loginLink->setText(tr("Login"));
    }
}
    
void MainWindow::checkLoginLink(const string &url) {
    if (_loginLink != 0) {
        if (url == urls::login)
            _loginLink->hide();
        else
            _loginLink->show();
    }
}

} // namespace my_app
