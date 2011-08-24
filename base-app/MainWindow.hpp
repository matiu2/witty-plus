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
#include "LoginWindow.hpp"
#include "App.hpp"

namespace Wt {
    class WContainerWidget;
    class WString;
    class WWidget;
    class WAnchor;
}

using Wt::WTemplate;
using Wt::WContainerWidget;
using Wt::WString;
using Wt::WWidget;
using Wt::WAnchor;
using my_app::model::User;

namespace my_app {

class MainWindow : public wittyPlus::MoreAwesomeTemplate {
protected:
    // Fields
    WAnchor* _loginLink;
    // Signal handlers
    void handleUserChanged(dbo::ptr<User> oldUser,  dbo::ptr<User> newUser);
    void toggleLoginLink(const string& url);
public:
    MainWindow(WContainerWidget* parent=0);
    void setStatusText(const WString& newMessage) { bindString("status-text", newMessage); }
    void setBody(const WString& text="") { bindString("content", text); }
    void setBody(WWidget* widget) { bindWidget("content", widget); }
};

} // namespace my_app

#endif // MAINWINDOW_HPP

