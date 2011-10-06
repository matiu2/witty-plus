/*
 * =====================================================================================
 *
 *       Filename:  App.hpp
 *
 *    Description:  Main witty App
 *
 *        Version:  1.0
 *        Created:  18/07/11 21:18:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <vector>
#include <string>
#include <Wt/WApplication>
#include <Wt/Dbo/backend/Postgres>
#include "lib/SessionHandle.hpp"
#include "lib/MemorySessionStore.hpp"
#include "model/User.hpp"
#include "lib/BaseApp.hpp"
#include "urls.hpp"

namespace Wt {
    class WEvent;
}

using std::vector;
using std::string;
using Wt::WApplication;
using Wt::WEnvironment;
using Wt::Signal;
using Wt::WEvent;
namespace dbo = Wt::Dbo;

namespace my_app {

class MainWindow;
class URL2Action;

const string my_appCookieName = "my_app_cookie";

typedef wittyPlus::BaseApp<model::User> BaseApp;

class App : public BaseApp {
public:
    typedef Signal<dbo::ptr<model::User>, dbo::ptr<model::User> > UserChangedSignal;
    typedef Signal<> URLChangedSignal;
    typedef Signal<WString> MessageSignal;
    typedef vector<string> UrlHistory;
    typedef vector<string>::const_iterator HistoryIndex;
protected:
    URL2Action* _url2ActionMapper; /// Handles turning urls into actions
    dbo::backend::Postgres postgres;
    UrlHistory urlHistory;
    // Signals
    UserChangedSignal* _userChanged;
    MessageSignal* _statusTextChanged;
    // Windows
    MainWindow* _mainWindow;
    // Methods
    void adminUsers();
    void notify(const WEvent& event);
    void rememberHistory(const string& url) {
        if ((urlHistory.size() >= 1) and (urlHistory.back() == url)) {
            // They probably hit 'back' in the browser.
            // Don't record the url in this case, it's already at the top of the history
            // and we always want the current url in there
            return;
        } else {
            urlHistory.push_back(url);
        }
    }
public:
    App(const WEnvironment& environment);
    UserChangedSignal* userChanged() { return _userChanged; } /// An event triggered when a user logs in or logs out
    MessageSignal* statusTextChanged() { return _statusTextChanged; } /// An event triggered when the status text (shown on the front page) changes
    /// Shows a status message for a period of time
    void setStatusText(const WString& newStatusText) { statusTextChanged()->emit(newStatusText); }
    MainWindow* mainWindow() { return _mainWindow; }
    /// Use to send the user somewhere inside the app
    void go(const string& newUrl) { setInternalPath(newUrl, true); }
    /** Go back one in the history but only if it keeps you inside the app.
     * @param dontLogout don't go if 'back' would take us to /logout
     * @return true if we navigated
     **/
    bool goBack(bool dontLogout=true);
    void goBackOrHome() { if (!goBack()) go(urls::home); }
    /// Returns true if client is running on an iphone TODO: Add more possibilities here
    bool isIPhone() { return environment().userAgent().find("iPhone") != string::npos; }
};

WApplication *createApplication(const WEnvironment& env);

App* app();

} // namespace my_app

#endif // APP_HPP
