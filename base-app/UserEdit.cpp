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
#include <Wt/WMessageBox>
#include <Wt/WAnimation>

using Wt::WAnimation;

namespace my_app {

UserEdit::UserEdit(WContainerWidget* parent) : wittyPlus::MoreAwesomeTemplate(parent) {
    setTemplateText(tr("user-edit-template"));
    // Set up the widgets
    bindAndCreateField(lblName, edtName, "name");
    bindAndCreateField(lblPass1, edtPass1, "new-password");
    edtPass1->setEchoMode(WLineEdit::Password);
    bindAndCreateField(lblPass2, edtPass2, "new-password2");    
    edtPass2->setEchoMode(WLineEdit::Password);
    bindAndCreateWidget(btnBar, "btn-bar");
    btnBar->btn1()->clicked().connect(this, &UserEdit::OKHit);
    btnBar->btn2()->clicked().connect(this, &UserEdit::CancelHit);
    // Enter handling and tab indexy stuff
    edtName->enterPressed().connect(edtPass1, &WLineEdit::setFocus);
    edtPass1->enterPressed().connect(edtPass2, &WLineEdit::setFocus);
    edtPass2->enterPressed().connect(this, &UserEdit::OKHit);
    // Escape is cancel
    escapePressed().connect(this, &UserEdit::CancelHit);
}

/// Validates and saves the user
void UserEdit::OKHit() {
    bool isNewUser = !_user;
    // Passwords can't be empty unless they changed the username
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

} // namespace my_app
