/*
 * =====================================================================================
 *
 *       Filename:  UserEdit.hpp
 *
 *    Description:  Allows you to edit a user record
 *
 *        Version:  1.0
 *        Created:  08/28/2011 17:09:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef USER_EDIT_HPP
#define USER_EDIT_HPP

#include "lib/MoreAwesomeTemplate.hpp"
#include "model/User.hpp"
#include "lib/ButtonBar.hpp"
#include <Wt/WLineEdit>

namespace dbo = Wt::Dbo;

namespace Wt {
    class WLabel;
    class WSelectionBox;
    class WLineEdit;
};

using wittyPlus::MoreAwesomeTemplate;
using my_app::model::User;
using Wt::WLabel;
using Wt::WLineEdit;
using wittyPlus::ButtonBar;

namespace my_app {

class UserEdit : public MoreAwesomeTemplate {
private:
    dbo::ptr<User> _user;
    WLabel*    lblName;
    WLineEdit* edtName;
    WLabel*    lblPass1;
    WLineEdit* edtPass1;
    WLabel*    lblPass2;
    WLineEdit* edtPass2;
    ButtonBar* btnBar;
public:
    UserEdit(WContainerWidget* parent=0);
    void setUser(dbo::ptr<User> user) {
        _user = user;
        edtName->setText(user->name());
        edtPass1->setText("");
        edtPass2->setText("");
    }
    dbo::ptr<User> getUser() { return _user; }
};

} // namespace my_app

#endif // USER_EDIT_HPP
