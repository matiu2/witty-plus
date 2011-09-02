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
    class WTableView;
    class WPushButton;
};

namespace dbo = Wt::Dbo;
using Wt::WTableView;
using Wt::Signal;
using Wt::WPushButton;
using my_app::model::User;

namespace my_app {

class UserList : public wittyPlus::MoreAwesomeTemplate {
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
    WTableView* lstUsers;
    // Helper Methods
    void bindAndCreateButton(
        WPushButton*& btn, const char* address,
        const WString& caption, ButtonMethod onCalled);
    dbo::ptr<User> currentUser();
    // Methods
    void createUserList();
    void refillUserList();
    void onUserSelected();
    void backToUserList();
    // Button event handlers
    void newClicked();
    void editClicked();
    void deleteClicked();
public:
    UserList(WContainerWidget* parent=0);
    UserSignal& userChosen() { return _userChosen; }
};

} // namespace my_app {

#endif // USER_LIST_HPP
