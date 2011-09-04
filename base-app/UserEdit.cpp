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
#include "App.hpp"
#include <Wt/WLineEdit>
#include <Wt/WMessageBox>
#include <Wt/WAnimation>

using Wt::WAnimation;

namespace my_app {

UserEdit::UserEdit(WContainerWidget* parent) : wittyPlus::MoreAwesomeTemplate(parent) {
    setTemplateText(tr("user-edit-template"));
    // Set up the widgets
    bindAndCreateField(lblName, edtName, "name");
    edtName->setFocus();
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
}

/// Validates and saves the user
void UserEdit::OKHit() {
    bool isNewUser = !_user;
    // Passwords can't be empty unless they changed the username
    if (edtPass1->text().empty() && (_user->name() == edtName->text())) {
        Wt::WMessageBox::show(
            tr("cant-save"),
            tr("password-is-empty"),
            Wt::Ok,
            WAnimation(WAnimation::SlideInFromRight, WAnimation::Ease)
        );
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
        return;
    }
    Wt::StandardButton result = Wt::Yes;
    if (isNewUser) {
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
        model::User* u = _user.modify();
        u->setName(edtName->text());
        u->setPassword(edtPass1->text());
        if (isNewUser)
           s.add(_user);
        t.commit();
    }
    // Let the parent widget (or whoever) know that we're done
    done().emit(_user);
}

void UserEdit::CancelHit() {
    cancelled().emit();
}

} // namespace my_app
