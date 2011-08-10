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
#include "model/User.hpp"

#include <Wt/WString>

namespace Wt {
    class WEnvironment;
}

using Wt::WEnvironment;
using std::string;

namespace my_app {

App::App(const WEnvironment& environment) : BaseApp(environment, my_appCookieName) {
    // Load the message bundles
    messageResourceBundle().use(appRoot() + "messages/MainWindow");
    messageResourceBundle().use(appRoot() + "messages/LoginWindow");
    // Set up our signals
    _userChanged = new UserChangedSignal(this);
    _statusTextChanged = new MessageSignal(this);
    // Set up the UI
    useStyleSheet(resourcesUrl() + "/themes/" + cssTheme() + "/forms.css");
    useStyleSheet(resourcesUrl() + "/themes/" + cssTheme() + "/fonts.css");
    useStyleSheet(resourcesUrl() + "/themes/" + cssTheme() + "/controlPanel.css");
    setTitle(WString::tr("main-title"));
    _mainWindow = new MainWindow(root());
    setBodyClass("yui-skin-sam");
    // Trigger any path sensetive stuff
    setInternalPath(internalPath(), true);
}

WApplication *createApplication(const WEnvironment& env) { return new App(env); }

App* getApp() { return dynamic_cast<App*>(WApplication::instance()); }

} // namespace my_app
