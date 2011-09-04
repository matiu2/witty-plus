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
#include "App.hpp"
#include <Wt/WLineEdit>
#include <Wt/WSignal>

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
using Wt::Signal;
using wittyPlus::ButtonBar;

namespace my_app {

class UserEdit : public MoreAwesomeTemplate {
public:
    typedef Signal< dbo::ptr<User> > UserSignal;
private:
    // Helpers
    dbo::ptr<User> _user;
    UserSignal _done;
    Signal<> _cancelled;
    // Fields and labels
    WLabel*    lblName;
    WLineEdit* edtName;
    WLabel*    lblPass1;
    WLineEdit* edtPass1;
    WLabel*    lblPass2;
    WLineEdit* edtPass2;
    ButtonBar* btnBar;
    // Event handlers
    void OKHit();
    void CancelHit();
public:
    UserEdit(WContainerWidget* parent=0);
    // Properties
    void setUser(dbo::ptr<User> user) {
        _user = user;
        if (user) {
            edtName->setText(user->name());
        } else {
            edtName->setText("");
            app()->statusTextChanged()->emit(tr("Adding a new user"));
        }
        edtPass1->setText("");
        edtPass2->setText("");
        edtName->setFocus();
    }
    dbo::ptr<User> getUser() { return _user; }
    // Signals
    UserSignal& done() { return _done; }
    Signal<>& cancelled() { return _cancelled; }
};

} // namespace my_app

#endif // USER_EDIT_HPP
