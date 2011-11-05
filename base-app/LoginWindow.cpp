/*
 * =====================================================================================
 *
 *       Filename:  LoginWindow.cpp
 *
 *    Description:  Login Screen
 *
 *        Version:  1.0
 *        Created:  06/01/2011 02:51:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "LoginWindow.hpp"

#include <Wt/WRandom>
#include <Wt/WString>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WLogger>
#include <Wt/WPushButton>
#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/Dbo/ptr>
#include <string>
#include "IGui.hpp"
#include "IUsers.hpp"
#include "INavigation.hpp"
#include "model/User.hpp"

using Wt::WString;
using std::string;
namespace dbo = Wt::Dbo;
using wittyPlus::model::User;

namespace wittyPlus {

LoginWindow::LoginWindow(WContainerWidget* parent) : MoreAwesomeTemplate(parent) {
    setTemplateText(tr("login-template"));
    addStyleClass("form");
    // User Field
    bindAndCreateField(_usernameLabel, _usernameEdit, "username");
    _usernameEdit->setFocus();
    _usernameEdit->setId("username");
    // Password Field
    bindAndCreateField(_passwordLabel, _passwordEdit, "password");
    _passwordEdit->setEchoMode(WLineEdit::Password);
    _passwordEdit->setId("password");
    // Buttons
    bindWidget("btn-bar", _btnBar = new base::ButtonBar(tr("Login"), tr("Cancel")));
    _btnBar->btn1()->clicked().connect(this, &LoginWindow::handleOKHit);
    _btnBar->btn2()->clicked().connect(this, &LoginWindow::handleCancelHit);
    // Hook up accept and reject signals
    // All these do an accept
    _passwordEdit->enterPressed().connect(this, &LoginWindow::handleOKHit);    
    // These do reject
    _usernameEdit->escapePressed().connect(this, &LoginWindow::handleCancelHit);
    _passwordEdit->escapePressed().connect(this, &LoginWindow::handleCancelHit);
}

/**
* @brief Called when the user hits OK to login
*/
void LoginWindow::handleOKHit() {
    Wt::WApplication* app = wittyPlus::app();
    IUsers* users = IUsers::instance();
    IGui*  gui = IGui::instance();
    INavigation* nav = INavigation::instance();
    // See if we can log them in
    string username = _usernameEdit->text().toUTF8();
    string password = _passwordEdit->text().toUTF8();
    dbo::ptr<User> oldUser = users->user();
    dbo::ptr<User> newUser;
    if (users->tryLogin(username, password)) {
        // Let the application know
        app->log("SECURITY") << username << " logged in";
        newUser = users->user();
    } else {
        app->log("SECURITY") << username << " failed log in";
        gui->setStatusText(tr("invalid-login"));
    }
    if (oldUser != newUser)
        users->userChanged()->emit(oldUser, newUser);
    // Go back to what we were doing (but now with different set of powerz)
    if (!nav->goBack())
        nav->go(urls::home);
}

void LoginWindow::handleCancelHit() {
    IGui::instance()->setStatusText(tr("Login Cancelled"));
    INavigation::instance()->goBack();
}

} // namespace wittyPlus
