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

#include <stdexcept>
#include <Wt/WString>
#include <Wt/WLogger>

namespace Wt {
    class WEnvironment;
}

using Wt::WEnvironment;
using Wt::WString;
using std::string;

namespace my_app {

App::App(const WEnvironment& environment) :
    BaseApp(environment, my_appCookieName) {
    // Set up the db
    string postgresConnectionString;
    readConfigurationProperty("DB", postgresConnectionString);
    postgres.connect(postgresConnectionString);
    dbSession().setConnection(postgres);
    log("notice") << "Mapping classes";
    mapModels(dbSession());
    // Load the message bundles
    messageResourceBundle().use(appRoot() + "messages/App");
    messageResourceBundle().use(appRoot() + "messages/MainWindow");
    messageResourceBundle().use(appRoot() + "messages/LoginWindow");
    messageResourceBundle().use(appRoot() + "messages/ButtonBar");
    messageResourceBundle().use(appRoot() + "messages/AdminIndex", false);
    messageResourceBundle().use(appRoot() + "messages/UserList", false);
    messageResourceBundle().use(appRoot() + "messages/UserEdit", false);
    // Set up our signals
    _userChanged = new UserChangedSignal(this);
    _statusTextChanged = new MessageSignal(this);
    internalPathChanged().connect(this, &App::rememberHistory);
    // Set up the general URL handling
    _url2ActionMapper = new URL2Action(this);
    // Set up the UI
    useStyleSheet("http://fonts.googleapis.com/css?family=Spinnaker");
    useStyleSheet(resourcesUrl() + "/themes/" + cssTheme() + "/fonts.css");
    useStyleSheet(resourcesUrl() + "/themes/" + cssTheme() + "/forms.css");
    useStyleSheet(resourcesUrl() + "/themes/" + cssTheme() + "/controlPanel.css");
    setTitle(WString::tr("main-title"));
    _mainWindow = new MainWindow(root());
    _statusTextChanged->connect(_mainWindow, &MainWindow::setStatusText);
    setBodyClass("yui-skin-sam");
    // Set up custom JS
    declareJavaScriptFunction("validate", WString::tr("js-validate").toUTF8());
    // Fire an internal path changed event off as user may have navigated straight here
    internalPathChanged().emit(app()->internalPath());
}

/// Called when we want to administrate our list of users
void App::adminUsers() {
    // Check if we have the rights
    dbo::ptr<User> user = userSession()->user();
    if (!user) {
        go(urls::home);
        setStatusText(WString::tr("access-denied"));
    }
}

void App::notify(const WEvent& event) {
    // Grab resources for during request handling
    try {
        WApplication::notify(event);
    } catch (std::logic_error& e) {
        // handle this exception in a central place
        log("error") << "Uncaught Exception: " << e.what();
        throw (e);
    }
}


bool App::goBack(bool dontLogout) {
    if (urlHistory.size() >= 2) {
        // last is one past the current url
        // last-1 is where we are now
        // last-2 is where we want to go
        HistoryIndex last=urlHistory.end()-2;
        const string& newURL = *last;
        if (dontLogout && (newURL == urls::logout))
            return false;
        urlHistory.pop_back(); // pop the current url we just navigated to from the stack
        go(newURL);  // rememberHistory will realize we're going back and pop the url from the history
        return true;
    } else {
      return false;
    }
}

WApplication *createApplication(const WEnvironment& env) { return new App(env); }

App* app() { return dynamic_cast<App*>(WApplication::instance()); }

} // namespace my_app
