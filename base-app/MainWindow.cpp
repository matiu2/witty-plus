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
#include "lib/InternalLink.hpp"
#include "AdminIndex.hpp"
#include "App.hpp"
#include "urls.hpp"
#include <Wt/WLogger>
#include <Wt/WStackedWidget>

namespace my_app {

MainWindow::MainWindow(WContainerWidget* parent) :
    wittyPlus::MoreAwesomeTemplate(parent), _statusTextSet(time(NULL)), _loginLink(0),
    fade(WAnimation::SlideInFromRight|WAnimation::Fade, WAnimation::Ease, 500)
{
    setTemplateText(tr("main-template"));
    // Set up the status text
    bindAndCreateWidget(_statusTextHolder, "status-text");
    _statusTextHolder->setStyleClass("status-text");
    _statusTextHolder->setTransitionAnimation(fade, true);
    _statusTextHolder->addWidget(_statusText = new WText());
    _statusTextHolder->addWidget(_oldStatusText = new WText());
    _statusText->setInline(false);
    _oldStatusText->setInline(false);
    // Set up any widets you have like the navigation tree
    bindString("nav", "Bind Nav box widget here");
    if (app()->userSession()->isLoggedIn()) {
        if (_loginLink != 0) {
            delete _loginLink;
            _loginLink = 0;
        }
        bindAndCreateWidget(_controlPanel, "controls");
    } else {
        _loginLink = new InternalLink(urls::login, tr("Login"));
        bindWidget("controls", _loginLink);
    }
    // Look out for people logging in and out
    app()->userChanged()->connect(this, &MainWindow::handleUserChanged);
    // Don't show 'login' when on the 'login page'
    app()->internalPathChanged().connect(this, &MainWindow::onInternalPathChanged); 
}

void MainWindow::handleUserChanged(dbo::ptr<User>, dbo::ptr<User> newUser) {
    // If they just logged in
    if (newUser) {
        // We'll be using the admin control panel, instead of a login link
        bindAndCreateWidget(_controlPanel, "controls");
        _loginLink = 0; // Needs to be zeroed so we can know whether to hide it or not later
        // Say hello
        app()->setStatusText(tr("welcome-1").arg(newUser->name()));
    } else {
        // Someone's logging out
        app()->setStatusText(tr("goodbye"));
        _loginLink = new InternalLink(urls::login, tr("Login"));
        bindWidget("controls", _loginLink);
        _loginLink->setRefInternalPath(urls::login);
        _loginLink->setText(tr("Login"));
    }
}
    
/**
* Stops us showing the login link on the login page and fades out old status text messages
*/
void MainWindow::onInternalPathChanged(const string &url) {
    // See if we need to render the login link or not
    if (_loginLink != 0) {
        if (url == urls::login)
            _loginLink->hide();
        else
            _loginLink->show();
    }
    // Also check if status text needs to fade out
    app()->log("DEBUG") << "Time since last status text update: " << difftime(time(NULL), _statusTextSet);
    if (difftime(time(NULL), _statusTextSet) > 1) { // if older than 1 seconds
        app()->log("DEBUG") << "Fading out status text";
        setStatusText("");
    }
}

//------------------------
// Public methods
//------------------------

/// Shows the new status text near the top of the page
void MainWindow::setStatusText(const WString& newMessage) {
    // Flip the text messages around with effects 
    int current = _statusTextHolder->currentIndex();
    WText* hiddenStatus = dynamic_cast<WText*>(_statusTextHolder->widget(1-current));
    hiddenStatus->setText(newMessage);
    _statusTextHolder->setCurrentIndex(1-current);
    _statusTextSet = time(NULL); // Remember when we set it
}

} // namespace my_app
