/*
 * =====================================================================================
 *
 *       Filename:  LoginWindow.hpp
 *
 *    Description:  Login screen to be placed at /login url
 *
 *        Version:  1.0
 *        Created:  06/01/2011 02:43:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef LOGIN_WINDOW_HPP
#define LOGIN_WINDOW_HPP

#include "lib/MoreAwesomeTemplate.hpp"
#include "lib/ButtonBar.hpp"
#include "lib/SessionHandle.hpp"
#include <Wt/WLineEdit>
#include <string>

namespace Wt {
    class WString;
    class WLabel;
    class WContainerWidget;
    class WPushButton;
}

using Wt::WTemplate;
using Wt::WString;
using Wt::WLabel;
using Wt::WContainerWidget;
using Wt::WPushButton;
using Wt::WLineEdit;

namespace my_app {

class LoginWindow : public wittyPlus::MoreAwesomeTemplate {
private:
    WLabel* _usernameLabel;
    WLineEdit* _usernameEdit;
    WLabel* _passwordLabel;
    WLineEdit* _passwordEdit;
    wittyPlus::ButtonBar* _btnBar;
protected:
    void handleOKHit();
    void handleCancelHit();
public:
    LoginWindow(WContainerWidget* parent);
    void setFocus() { _usernameEdit->setFocus(); }
};

} // namespace my_app

#endif // LOGIN_WINDOW_HPP
