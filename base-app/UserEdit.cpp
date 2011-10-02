/*
 * =====================================================================================
 *
 *       Filename:  UserEdit.cpp
 *
 *    Description:  GUI to edit User records
 *
 *        Version:  1.0
 *        Created:  08/28/2011 17:13:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "UserEdit.hpp"
#include <Wt/WLineEdit>
#include <Wt/WValidator>
#include <Wt/WMessageBox>
#include <Wt/WAnimation>
#include "lib/MatchValidator.hpp"
#include "lib/DBNoDupValidator.hpp"
#include <boost/assert.hpp>

using Wt::WAnimation;
using Wt::WValidator;
using wittyPlus::MatchValidator;
using wittyPlus::DBNoDupValidator;

namespace my_app {

UserEdit::UserEdit(WContainerWidget* parent) : wittyPlus::MoreAwesomeTemplate(parent) {
    setStyleClass("form blue");
    setTemplateText(tr("user-edit-template"));
    // Set up the widgets
    bindAndCreateField(lblName, edtName, msgName, "name");
    DBNoDupValidator<model::User>* nameValidator;
    WString userExistsMsg = tr("user-name-x-exists");
    WString userNeededMsg = tr("user-needs-a-name");
    if (_user)
        nameValidator = new wittyPlus::DBNoDupValidator<User>(app()->dbSession(), "name", _user.id(), true,
                                  userExistsMsg, userNeededMsg);
    else
        nameValidator = new wittyPlus::DBNoDupValidator<User>(app()->dbSession(), "name", true,
                                  userExistsMsg, userNeededMsg);
    nameValidator->msgSignal().connect(this, &UserEdit::updateNameValidationMsg);
    edtName->setValidator(nameValidator);
    bindAndCreateField(lblPass1, edtPass1, msgPass1, "new-password");
    edtPass1->setEchoMode(WLineEdit::Password);
    edtPass1->setValidator(new WValidator(!_user));
    bindAndCreateField(lblPass2, edtPass2, msgPass2, "new-password2");
    edtPass2->setEchoMode(WLineEdit::Password);
    edtPass2->setValidator(new MatchValidator<WLineEdit>(edtPass1, tr("passwords-dont-match"), edtName));
    bindAndCreateWidget(btnBar, "btn-bar");
    btnBar->btn1()->clicked().connect(this, &UserEdit::OKHit);
    btnBar->btn2()->clicked().connect(this, &UserEdit::CancelHit);
    // Enter handling and tab indexy stuff
    edtName->enterPressed().connect(edtPass1, &WLineEdit::setFocus);
    edtPass1->enterPressed().connect(edtPass2, &WLineEdit::setFocus);
    edtPass1->changed().connect(this, &UserEdit::passwordChanged);
    edtPass2->enterPressed().connect(this, &UserEdit::OKHit);
    edtPass2->changed().connect(this, &UserEdit::passwordChanged);
    // Escape is cancel
    escapePressed().connect(this, &UserEdit::CancelHit);
}

void UserEdit::setUser(dbo::ptr<User> user) {
    typedef wittyPlus::DBNoDupValidator<model::User> NameValidator;
    _user = user;
    if (user) {
        NameValidator* nameValidator = dynamic_cast<NameValidator*>(edtName->validator());
        BOOST_ASSERT(nameValidator != 0);
        nameValidator->setIdToIgnore(_user.id());
        edtName->setText(_user->name());
        edtPass1->validator()->setMandatory(false);
        edtPass2->validator()->setMandatory(false);
    } else {
        edtName->setText("");
        dynamic_cast<wittyPlus::DBNoDupValidator<model::User>*>(edtName->validator())->clearIdToIgnore();
        app()->setStatusText(tr("Adding a new user"));
        edtPass1->validator()->setMandatory(true);
        edtPass2->validator()->setMandatory(true);
    }
    edtPass1->setText("");
    edtPass2->setText("");
    edtName->setFocus();
}

/// Validates (more) and saves the user
void UserEdit::OKHit() {
    if (validateAll()) {
        // All entries are valid ..
        // If it's an existing user..
        if (_user) {
            // You have to change something
            if (edtPass1->text().empty() && (_user->name() == edtName->text())) {
                Wt::WMessageBox::show(
                    tr("cant-save"),
                    tr("you-didnt-change-anything"),
                    Wt::Ok,
                    WAnimation(WAnimation::SlideInFromRight, WAnimation::Ease)
                );
                edtName->setFocus();
                return;
            }
        }
        // If it's an existing user .. prompt before overwriting
        Wt::StandardButton userHappy = Wt::Yes;
        if (_user) {
            // If modifying an existing user, prompt to save changes
            if (edtName->text() != _user->name())
                userHappy = Wt::WMessageBox::show(
                    tr("save-changes?"),
                    tr("change-username-from-x-to-y").arg(_user->name()).arg(edtName->text()),
                    Wt::Yes | Wt::No,
                    WAnimation(WAnimation::SlideInFromRight, WAnimation::Ease)
                );
            if ((userHappy == Wt::Yes) && (!edtPass1->text().empty()))
                userHappy = Wt::WMessageBox::show(
                    tr("save-changes?"),
                    tr("save-new-password-user-x").arg(_user->name()),
                    Wt::Yes | Wt::No,
                    WAnimation(WAnimation::SlideInFromRight, WAnimation::Ease)
                );
        }
        // Save it
        if (userHappy == Wt::Yes) {
            dbo::Session& s = app()->dbSession();
            dbo::Transaction t(s);
            if (!_user) {
                // If we don't have an existing user .. make a new one and add it to the DB
               _user = s.add(new User(edtName->text().toUTF8(), edtPass1->text().toUTF8()));
            } else {
                model::User* u = _user.modify();
                u->setName(edtName->text());
                const WString& password = edtPass1->text();
                if (!password.empty())
                    u->setPassword(password.toUTF8());
            }
            t.commit();
        }
        // Let the parent widget (or whoever) know that we're done
        done().emit(_user); // Should switch back to UserList view and update data
    } else {
        Wt::WMessageBox::show(
            tr("cant-save"),
            tr("fix-up-fields"),
            Wt::Ok,
            WAnimation(WAnimation::Pop | WAnimation::Fade, WAnimation::Ease)
        );
    }
}

void UserEdit::CancelHit() {
    cancelled().emit();
}

/// If you change one password, you have to change the other
void UserEdit::passwordChanged() {
    if (_user) {
        // If we're editing an existing user
        WLineEdit* changed = dynamic_cast<WLineEdit*>(sender());
        if (changed) {
            // If one has no text .. make the other not mandatory
            // If first has text, other is now mandatory
            WLineEdit* other = (changed == edtPass1 ? edtPass2 : edtPass1);
            other->validator()->setMandatory(!changed->text().empty());
        }
    }
}


} // namespace my_app
