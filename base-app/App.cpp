/*
 * =====================================================================================
 *
 *       Filename:  App.cpp
 *
 *    Description:  Witty Application
 *
 *        Version:  1.0
 *        Created:  18/07/11 21:07:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "App.hpp"
#include "MainWindow.hpp"
#include "model/User.hpp"
#include "db.hpp"
#include "url2action.hpp"

#include <Wt/WString>

namespace Wt {
    class WEnvironment;
}

using Wt::WEnvironment;
using Wt::WString;
using std::string;

namespace my_app {

App::App(const WEnvironment& environment) : BaseApp(environment, my_appCookieName) {
    // Set up the db
    string postgresConnectionString;
    readConfigurationProperty("DB", postgresConnectionString);
    postgres.connect(postgresConnectionString);
    dbSession().setConnection(postgres);
    mapModels(dbSession());
    // Load the message bundles
    messageResourceBundle().use(appRoot() + "messages/MainWindow");
    messageResourceBundle().use(appRoot() + "messages/LoginWindow");
    messageResourceBundle().use(appRoot() + "messages/ButtonBar");
    // Set up our signals
    _userChanged = new UserChangedSignal(this);
    _statusTextChanged = new MessageSignal(this);
    // Set up the general URL handling
    _url2ActionMapper = new URL2Action(this);
    internalPathChanged().connect(&_urls, &URLs::run);
    _urls[urls::adminUsers]->connect(this, &App::adminUsers);
    // Set up the UI
    useStyleSheet(resourcesUrl() + "/themes/" + cssTheme() + "/forms.css");
    useStyleSheet(resourcesUrl() + "/themes/" + cssTheme() + "/fonts.css");
    useStyleSheet(resourcesUrl() + "/themes/" + cssTheme() + "/controlPanel.css");
    setTitle(WString::tr("main-title"));
    _mainWindow = new MainWindow(root());
    _statusTextChanged->connect(_mainWindow, &MainWindow::setStatusText);
    setBodyClass("yui-skin-sam");
    // Fire one off as user may have navigated straight here
    app()->internalPathChanged().emit(app()->internalPath());
}

/// Called when we want to administrate our list of users
void App::adminUsers() {
    // Check if we have the rights
    dbo::ptr<User> user = userSession()->user();
    if (!user) {
        go(urls::home);
        statusTextChanged()->emit(WString::tr("access-denied"));
    }
};

WApplication *createApplication(const WEnvironment& env) { return new App(env); }

App* app() { return dynamic_cast<App*>(WApplication::instance()); }

} // namespace my_app
