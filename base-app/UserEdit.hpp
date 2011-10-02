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
#include <Wt/WText>

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
using Wt::WText;
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
    WText* msgName;
    WLabel*    lblPass1;
    WLineEdit* edtPass1;
    WText* msgPass1;
    WLabel*    lblPass2;
    WLineEdit* edtPass2;
    WText* msgPass2;
    ButtonBar* btnBar;
    // Event handlers
    void OKHit();
    void CancelHit();
    void passwordChanged();
public:
    UserEdit(WContainerWidget* parent=0);
    // Properties
    void setUser(dbo::ptr<User> user);
    dbo::ptr<User> getUser() { return _user; }
    // Slots
    /// Called when edtUser is validated on the server side.
    /// Updates the display to show the validation message.
    void updateNameValidationMsg(WValidator::State validationResult, WString msg) {
        if (validationResult == WValidator::Invalid) {
            // If user is invalid, it's because they're trying to add a duplicate user
            // So the message we're displaying will need that username as an argument
            msg.arg(edtName->text());
        }
        edtName->setAttributeValue("title", msg);
        msgName->setText(msg);
    }
    // Signals
    UserSignal& done() { return _done; }
    Signal<>& cancelled() { return _cancelled; }
};

} // namespace my_app

#endif // USER_EDIT_HPP
