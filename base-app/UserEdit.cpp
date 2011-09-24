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

using Wt::WAnimation;
using Wt::WValidator;
using wittyPlus::MatchValidator;

namespace my_app {

UserEdit::UserEdit(WContainerWidget* parent) : wittyPlus::MoreAwesomeTemplate(parent) {
    setTemplateText(tr("user-edit-template"));
    // Set up the widgets
    bindAndCreateField(lblName, edtName, "name");
    edtName->setValidator(new WValidator(true, edtName));
    bindAndCreateField(lblPass1, edtPass1, "new-password");
    edtPass1->setEchoMode(WLineEdit::Password);
    edtPass1->setValidator(new WValidator(!_user));
    bindAndCreateField(lblPass2, edtPass2, "new-password2");    
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
    _user = user;
    if (user) {
        edtName->setText(user->name());
        edtPass1->validator()->setMandatory(false);
        edtPass2->validator()->setMandatory(false);
    } else {
        edtName->setText("");
        app()->setStatusText(tr("Adding a new user"));
        edtPass1->validator()->setMandatory(true);
        edtPass2->validator()->setMandatory(true);
    }
    edtPass1->setText("");
    edtPass2->setText("");
    edtName->setFocus();
}

/// Validates and saves the user
void UserEdit::OKHit() {
bool isNewUser = !_user;

    // If it's a new user
    // Must have a password
    // Passwords must match

    // If it's an existing user
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
    } else {
        // If it's a new user
        // Must have a password
        if (edtPass1->text().empty())
            Wt::WMessageBox::show(
                tr("cant-save"),
                tr("new-user-needs-a-password"),
                Wt::Ok,
                WAnimation(WAnimation::Pop | WAnimation::Fade, WAnimation::Ease)
            );
            edtPass1->setFocus();
            return;
    }
    // Passwords must match
    if (edtPass1->text() != edtPass2->text()) {
        Wt::WMessageBox::show(
            tr("cant-save"),
            tr("passwords-dont-match"),
            Wt::Ok,
            WAnimation(WAnimation::SlideInFromRight, WAnimation::Ease)
        );
        edtPass1->setFocus();
        return;
    }
    Wt::StandardButton result = Wt::Yes;
    if (!isNewUser) {
        // If modifying an existing object, prompt to save changes
        result = Wt::WMessageBox::show(
            tr("save-changes?"),
            tr("save-new-password-user-x").arg(_user->name()),
            Wt::Yes | Wt::No,
            WAnimation(WAnimation::SlideInFromRight, WAnimation::Ease)
        );
    }
    // Save it
    if (result == Wt::Yes) {
        dbo::Session& s = app()->dbSession();
        dbo::Transaction t(s);
        if (isNewUser) {
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
    done().emit(_user);
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
