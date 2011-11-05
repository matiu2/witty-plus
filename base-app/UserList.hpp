/*
 * =====================================================================================
 *
 *       Filename:  UserList.hpp
 *
 *    Description:  Lists the users on the system
 *
 *        Version:  1.0
 *        Created:  08/31/2011 07:31:38
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef USER_LIST_HPP
#define USER_LIST_HPP

#include "lib/MoreAwesomeTemplate.hpp"
#include "model/User.hpp"
#include <Wt/Dbo/QueryModel>
#include <Wt/Dbo/ptr>
#include <Wt/WSignal>

namespace Wt {
    class WSelectionBox;
    class WPushButton;
};

namespace dbo = Wt::Dbo;
using Wt::WSelectionBox;
using Wt::Signal;
using Wt::WPushButton;
using wittyPlus::model::User;

namespace wittyPlus {

class UserList : public base::MoreAwesomeTemplate {
public:
    typedef Signal< dbo::ptr<User> > UserSignal;
    typedef void (UserList::*ButtonMethod)();
private:
    dbo::QueryModel< dbo::ptr<User> > usersModel; 
    UserSignal _userChosen; // Fired when the user is chosen to be edited
    // Fields
    WPushButton* btnNew;
    WPushButton* btnEdit;
    WPushButton* btnDelete;
    WSelectionBox* lstUsers;
    // Helper Methods
    void bindAndCreateButton(
        WPushButton*& btn, const char* address,
        const WString& caption, ButtonMethod onCalled);
    dbo::ptr<User> currentUser();
    // Methods
    void createUserList();
    void onUserSelected();
    void backToUserList();
    // Button event handlers
    void newClicked();
    void editClicked();
    void deleteClicked();
public:
    UserList(WContainerWidget* parent=0);
    UserSignal& userChosen() { return _userChosen; }
    void refillUserList();
};

} // namespace wittyPlus

#endif // USER_LIST_HPP
