/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.hpp
 *
 *    Description:  The main window of the account application
 *
 *        Version:  1.0
 *        Created:  18/07/11 22:31:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "lib/MoreAwesomeTemplate.hpp"
#include "model/User.hpp"
#include "App.hpp"
#include <Wt/WText>
#include <Wt/WAnimation>
#include <ctime>

namespace Wt {
    class WContainerWidget;
    class WString;
    class WWidget;
    class WStackedWidget;
}

namespace wittyPlus {
    class InternalLink;
}

using Wt::WTemplate;
using Wt::WContainerWidget;
using Wt::WString;
using Wt::WWidget;
using Wt::WText;
using Wt::WAnimation;
using Wt::WStackedWidget;
using wittyPlus::InternalLink;
using my_app::model::User;

namespace my_app {

class AdminIndex;

class MainWindow : public wittyPlus::MoreAwesomeTemplate {
protected:
    // Fields
    WStackedWidget* _statusTextHolder;
    WText* _statusText;
    WText* _oldStatusText;
    time_t _statusTextSet; // When it was set
    InternalLink* _loginLink;
    AdminIndex* _controlPanel; // Lets logged in users do stuff
    // Helpers
    WAnimation fade;
    // Signal handlers
    void handleUserChanged(dbo::ptr<User> oldUser,  dbo::ptr<User> newUser);
    void onInternalPathChanged(const string& url);
public:
    MainWindow(WContainerWidget* parent=0);
    void setBody(const WString& text="") { bindString("content", text); }
    void setBody(WWidget* widget) { bindWidget("content", widget); }
    void setStatusText(const WString& newMessage);
};

} // namespace my_app

#endif // MAINWINDOW_HPP

