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
#include <Wt/WSignal>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Postgres>
#include "lib/SessionHandle.hpp"
#include "lib/MemorySessionStore.hpp"
#include "model/User.hpp"
#include "lib/BaseApp.hpp"
#include "lib/URLs.hpp"

using wittyPlus::URLs;
using Wt::WApplication;
using Wt::WEnvironment;
using Wt::Signal;
namespace dbo = Wt::Dbo;

namespace my_app {

class MainWindow;

const string my_appCookieName = "my_app_cookie";

typedef wittyPlus::BaseApp<model::User> BaseApp;

class App : public BaseApp {
public:
    typedef Signal<dbo::ptr<model::User>, dbo::ptr<model::User> > UserChangedSignal;
    typedef Signal<> URLChangedSignal;
    typedef Signal<WString> MessageSignal;
protected:
    URLs _urls; /// A map of a url to an action to perform
    dbo::backend::Postgres postgres;
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
    URLChangedSignal* url(const string& url) { return _urls[url]; }
    void urlChanged(const string& newUrl) {
        std::cout << newUrl << std::endl;
        _urls.run(newUrl);
    }
};

WApplication *createApplication(const WEnvironment& env);

App* app();

} // namespace my_app

#endif // APP_HPP
