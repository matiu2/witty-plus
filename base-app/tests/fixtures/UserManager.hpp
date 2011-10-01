/*
 * =====================================================================================
 *
 *       Filename:  UserManager.hpp
 *
 *    Description:  A fixture for testing the user manager interface
 *
 *        Version:  1.0
 *        Created:  09/11/2011 19:21:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TESTS_FIXTURES_USER_MANAGER_HPP
#define TESTS_FIXTURES_USER_MANAGER_HPP

#include <Wt/WString>
#include <Wt/WDialog>
#include <Wt/WMessageBox>
#include "Login.hpp"
#include "../helpers.hpp"
#include "../../UserManager.hpp"
#include "../../UserEdit.hpp"
#include "../../UserList.hpp"

using Wt::WDialog;
using Wt::WMessageBox;
using Wt::WString;

namespace my_app {
namespace unittests {
namespace fixtures {

namespace h = helpers;

struct UserManagerFixture : public LoginFixture {
    UserManagerFixture() : LoginFixture() {
        // Login
        LoginWindow* loginWindow = clickLogin();
        loginWindow->_usernameEdit->setText("admin");
        loginWindow->_passwordEdit->setText("admin");
        h::keyPress(loginWindow->_passwordEdit, 13);
        checkLoggedIn();
        // Check that we can bring up the user manager
        AdminIndex* cp = main->resolve<AdminIndex*>("controls");
        BOOST_REQUIRE_MESSAGE( cp, "Looks like the control panel didn't appear" );
        // Click the users link
        wittyPlus::InternalLink* usersLink = cp->resolve<wittyPlus::InternalLink*>("link-users");
        BOOST_REQUIRE_MESSAGE( usersLink, "Looks like the users link didn't appear" );
        h::click(usersLink);
    }
    ~UserManagerFixture() { cleanUpUsersTable(); }
    // Fields
    WString lastTitle;   /// last Message dialog title shown
    WString lastMessage; /// last Message dialog text shown
    /// Handle an application dialog being shown
    void onDialogExecuted(WDialog* dlg) {
        WMessageBox* msgBox = dynamic_cast<WMessageBox*>(dlg);
        if (msgBox != 0)
            lastMessage = msgBox->text();
        lastTitle = dlg->caption();
        dlg->accept(); // Close it .. we're running tests
    }
    /// Returns a copy of the UserManager widget
    UserManager* userManager() {
        UserManager* result = main->resolve<UserManager*>("content");
        BOOST_REQUIRE_MESSAGE( result, "Couldn't find the user manager." );
        return result;
    }
    /// Returns a copy of the useredit form, or throws
    UserEdit* userEdit() {
        UserEdit* result = userManager()->userEdit;
        BOOST_REQUIRE_MESSAGE( result, "Couldn't find the user edit form." );
        return result;
    }
    /// Returns a copy of the userlist form, or throws
    UserList* userList() {
        UserList* result = userManager()->userList;
        BOOST_REQUIRE_MESSAGE( result, "Couldn't find the user list form." );
        return result;
    }
};

} // namespace fixtures
} // namespace unittests 
} // namespace my_app

#endif // TESTS_FIXTURES_USER_MANAGER_HPP
