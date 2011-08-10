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

#include <Wt/WApplication>
#include <Wt/WSignal>
#include "lib/SessionHandle.hpp"
#include "lib/MemorySessionStore.hpp"
#include "model/User.hpp"
#include "MainWindow.hpp"
#include "lib/BaseApp.hpp"

using Wt::WApplication;
using Wt::WEnvironment;
using Wt::Signal;

namespace my_app {

const string my_appCookieName = "my_app_cookie";

typedef wittyPlus::BaseApp<model::User> BaseApp;

class App : public BaseApp {
public:
    typedef Signal<App*> UserChangedSignal;
    typedef Signal<WString> MessageSignal;
protected:
    // Signals
    UserChangedSignal* _userChanged;
    MessageSignal* _statusTextChanged;
    // Windows
    MainWindow* _mainWindow;
public:
    App(const WEnvironment& environment);
    UserChangedSignal* userChanged() { return _userChanged; } /// An event triggered when a user logs in or logs out
    MessageSignal* statusTextChanged() { return _statusTextChanged; } /// An event triggered when the status text (shown on the front page) changes
    MainWindow* mainWindow() { return _mainWindow; }
};

WApplication *createApplication(const WEnvironment& env);

App* getApp();

} // namespace my_app

#endif // APP_HPP
