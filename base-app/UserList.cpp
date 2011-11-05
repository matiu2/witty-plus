/*
 * =====================================================================================
 *
 *       Filename:  UserList.cpp
 *
 *    Description:  Implementation of the widgets to list users
 *
 *        Version:  1.0
 *        Created:  08/31/2011 07:34:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "UserList.hpp"
#include "App.hpp"
#include "IGui.hpp"
#include <Wt/Dbo/QueryModel>
#include <Wt/WPushButton>
#include <Wt/WSelectionBox>
#include <Wt/WLogger>
#include <Wt/WMessageBox>
#include <Wt/WAnimation>

using wittyPlus::model::User;
using Wt::WAnimation;

namespace wittyPlus {

UserList::UserList(WContainerWidget* parent) : MoreAwesomeTemplate(parent) {
    setStyleClass("form blue");
    setTemplateText(tr("user-list-template"));
    // Set up the widgets
    createUserList();
    // New Button
    bindAndCreateButton(btnNew, "btnNew", tr("New"), &UserList::newClicked);
    bindAndCreateButton(btnEdit, "btnEdit", tr("Edit"), &UserList::editClicked);
    bindAndCreateButton(btnDelete, "btnDelete", tr("Delete"), &UserList::deleteClicked);
}

/**
* @brief Creates and sets up our list of users
*/
inline void UserList::createUserList() {
    bindAndCreateWidget(lstUsers, "contents");
    lstUsers->setInline(false);
    lstUsers->setSelectionMode(Wt::SingleSelection);
    lstUsers->doubleClicked().connect(this, &UserList::editClicked); // Double click is same as edit
    lstUsers->enterPressed().connect(this, &UserList::editClicked);  // Enter is same as edit
    dbo::Session& db = app()->dbSession();
    usersModel.setQuery(db.find<User>()); // Get all users
    usersModel.addColumn("name");
    lstUsers->setModel(&usersModel);
    // Fill it with data
    refillUserList();
}

void UserList::refillUserList() {
    // Fill it with data
    dbo::Session& db = app()->dbSession();
    dbo::Transaction t(db);
    usersModel.reload();
    lstUsers->setCurrentIndex(1);
    lstUsers->setFocus();
    t.commit();
}

void UserList::newClicked() {
    userChosen().emit(dbo::ptr<User>()); // Let the world know
}

/**
* @brief Called when the client double clicks the list or hits the edit button
* @param id an Integer index into the lstUsers
*/
void UserList::editClicked() {
    // Get the User that was selected
    dbo::ptr<User> user = currentUser();
    if (user)
        userChosen().emit(user); // Let the world know
    else
        IGui::instance()->setStatusText(tr("You didn't select a user"));
}

inline void UserList::deleteClicked() {
    // Now prompt if we can delete it
    dbo::ptr<User> user = currentUser();
    if (user) {
        // Can't delete the current user
        if (user == app()->userSession()->user()) {
            // Tell the user they can't delete themselves
            Wt::WMessageBox::show(
                tr("cant-delete-self"),
                tr("you-cant-delete-yourself"),
                Wt::Ok,
                WAnimation(WAnimation::SlideInFromRight, WAnimation::Ease)
            );
            return;
        }
        // Get the user to confirm
        Wt::StandardButton result = Wt::WMessageBox::show(
            tr("confirm-delete?"),
            tr("confirm-delete-user-x").arg(user->name()),
            Wt::Yes | Wt::No,
            WAnimation(WAnimation::SlideInFromRight, WAnimation::Ease)
        );
        if (result == Wt::Yes) {
            dbo::ptr<User> user = currentUser();
            if (user) {
                dbo::Session& db = app()->dbSession();
                dbo::Transaction t(db);
                user.remove();
                refillUserList();
                t.commit();
            }
        }
    }
}

// Help methods

/**
* @brief Called to easily create buttons and fill in their info
*
* @param btn A reference to a pointer to the actual button to be created
* @param address The address in the template to fill
* @param caption The caption for the button (call tr yourself outside this func)
* @param onCalled The address of the method to call when the button is clicked
*/
inline void UserList::bindAndCreateButton(
    WPushButton*& btn, const char* address,
    const WString& caption, ButtonMethod onCalled) 
{ 
    bindAndCreateWidget(btn, address);
    btn->setText(caption);
    btn->clicked().connect(this, onCalled);
}

/// returns the user info for the user that was selected
inline dbo::ptr<User> UserList::currentUser() {
    dbo::ptr<User> result;
    int currentIndex = lstUsers->currentIndex();
    if (currentIndex >= 0)
        result = usersModel.resultRow(currentIndex);
    return result;
}

} // namespace my_app
