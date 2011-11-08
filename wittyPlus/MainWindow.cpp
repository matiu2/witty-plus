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
#include "base/InternalLink.hpp"
#include "AdminIndex.hpp"
#include "IUsers.hpp"
#include "IGui.hpp"
#include "urls.hpp"
#include <Wt/WLogger>
#include <Wt/WStackedWidget>
#include <Wt/WApplication>

namespace wittyPlus {

MainWindow::MainWindow(WContainerWidget* parent) :
    base::MoreAwesomeTemplate(parent), _statusTextSet(time(NULL)), _loginMenu(0)
{
    // Different display depending on if we're iphone or something bigger
    setTemplateText(tr("main-template"));
    // Set up the status text
    bindAndCreateWidget(_statusTextHolder, "status-text");
    _statusTextHolder->setStyleClass("status-text");
    _statusTextHolder->addWidget(_statusText = new WText());
    _statusTextHolder->addWidget(_oldStatusText = new WText());
    _statusText->setInline(false);
    _oldStatusText->setInline(false);
    // Set up any widets you have like the navigation tree
    bindString("nav", "Bind Nav box widget here");
    IUsers* users = IUsers::instance();
    if (users->isLoggedIn()) {
        _loginMenu = 0; // Needs to be zeroed so we can know whether to hide it or not later
        bindAndCreateWidget(_controlPanel, "controls");
    } else {
        makeLoginMenu();
    }
    // Put your content in the middle
    bindString("content", tr("sample-content"));
    // Look out for people logging in and out
    users->userChanged()->connect(this, &MainWindow::handleUserChanged);
    // Don't show 'login' when on the 'login page'
    Wt::WApplication::instance()->internalPathChanged().connect(this, &MainWindow::onInternalPathChanged); 
}

void MainWindow::makeLoginMenu() {
    _loginMenu = new WMenu(Wt::Horizontal);
    _loginMenu->itemSelected().connect(this, &MainWindow::menuClicked);
    bindWidget("controls", _loginMenu);
    _loginMenu->setRenderAsList(true);
    addMenuLink(_loginMenu, tr("Login"), urls::login);
}

void MainWindow::handleUserChanged(dbo::ptr<User>, dbo::ptr<User> newUser) {
    // If they just logged in
    IGui* gui = IGui::instance();
    if (newUser) {
        // We'll be using the admin control panel, instead of a login link
        bindAndCreateWidget(_controlPanel, "controls");
        _loginMenu = 0; // Needs to be zeroed so we can know whether to hide it or not later
        // Say hello
        gui->setStatusText(tr("welcome-1").arg(newUser->name()));
    } else {
        // Someone's logging out
        gui->setStatusText(tr("goodbye"));
        makeLoginMenu();
    }
}
    
/**
* Stops us showing the login link on the login page and fades out old status text messages
*/
void MainWindow::onInternalPathChanged(const string &url) {
    // See if we need to render the login link or not
    if (_loginMenu != 0) {
        if (url == urls::login)
            _loginMenu->hide();
        else
            _loginMenu->show();
    }
    Wt::WApplication* app = Wt::WApplication::instance();
    // Also check if status text needs to fade out
    app->log("DEBUG") << "Time since last status text update: " << difftime(time(NULL), _statusTextSet);
    if (difftime(time(NULL), _statusTextSet) > 1) { // if older than 1 seconds
        app->log("DEBUG") << "Fading out status text";
        setStatusText("");
    }
}

//------------------------
// Public methods
//------------------------


// IGui implementation

void MainWindow::setBody(const WString& text) { bindString("content", text); }
void MainWindow::setBody(Wt::WWidget* widget) { bindWidget("content", widget); }

/// Shows the new status text near the top of the page
void MainWindow::setStatusText(const WString& newMessage) {
    // Flip the text messages around with effects 
    int current = _statusTextHolder->currentIndex();
    WText* hiddenStatus = dynamic_cast<WText*>(_statusTextHolder->widget(1-current));
    hiddenStatus->setText(newMessage);
    _statusTextHolder->setCurrentIndex(1-current);
    _statusTextSet = time(NULL); // Remember when we set it
}

} // namespace wittyPlus

