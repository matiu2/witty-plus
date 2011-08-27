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
#include <Wt/WApplication>
#include <Wt/Dbo/backend/Postgres>
#include "lib/SessionHandle.hpp"
#include "lib/MemorySessionStore.hpp"
#include "model/User.hpp"
#include "lib/BaseApp.hpp"

namespace Wt {
    class WEvent;
}

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
protected:
    URL2Action* _url2ActionMapper; /// Handles turning urls into actions
    dbo::backend::Postgres postgres;
    // Signals
    UserChangedSignal* _userChanged;
    MessageSignal* _statusTextChanged;
    // Windows
    MainWindow* _mainWindow;
    // Methods
    void adminUsers();
    void notify(const WEvent& event);
public:
    App(const WEnvironment& environment);
    UserChangedSignal* userChanged() { return _userChanged; } /// An event triggered when a user logs in or logs out
    MessageSignal* statusTextChanged() { return _statusTextChanged; } /// An event triggered when the status text (shown on the front page) changes
    MainWindow* mainWindow() { return _mainWindow; }
    /// Use to send the user somewhere inside the app
    void go(const string& newUrl) { setInternalPath(newUrl, true); }
    void goBack() { doJavaScript("history.go(-1)"); } // TODO: need to test if this fires the internalPathChanged event
};

WApplication *createApplication(const WEnvironment& env);

App* app();

} // namespace my_app

#endif // APP_HPP
