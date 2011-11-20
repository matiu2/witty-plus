/*
 * =====================================================================================
 *
 *       Filename:  test_usermanager.hpp
 *
 *    Description:  Tests for the user manager interface
 *
 *        Version:  1.0
 *        Created:  09/11/2011 18:49:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "helpers.hpp"
#include "fixtures/UserManager.hpp"
#include <Wt/WSelectionBox>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

namespace wittyPlus {
namespace unittests {

namespace h = helpers;

BOOST_FIXTURE_TEST_SUITE( usermanager_suite, fixtures::UserManagerFixture );

BOOST_AUTO_TEST_CASE( new_user ) {
    // Get this list of users
    UserList* ul = userList();
    BOOST_REQUIRE_MESSAGE( ul->isVisible(), "We expected the userlist to be visible" );
    // Make sure only one uer in the list at first
    BOOST_REQUIRE_EQUAL( ul->lstUsers->count(), 1 );
    // Click the new user button
    h::click(ul->btnNew);
    UserEdit* ue = userEdit();
    BOOST_CHECK_MESSAGE( ue->isVisible(), "Click new should show the UserEdit screen" );
    // Now fill in the new user details
    const string testUsername = "Test User 1";
    ue->edtName->setText(testUsername);
    h::keyPress(ue->edtName, 13);
    BOOST_CHECK_MESSAGE(ue->edtPass1->hasFocus(),
        "Clicking enter after typing your name should give focus to the 1st password field");
    ue->edtPass1->setText("Test Pass");
    ue->edtPass2->setText("Test Pass");
    h::keyPress(ue->edtPass2, 13);
    // Now check we're back at the list
    ul = userList();
    BOOST_REQUIRE_MESSAGE( ul->isVisible(),
        "We expected it to go back to the user list after hitting enter when editing a user");
    // Check our new user is in the list
    BOOST_CHECK_GT( ul->lstUsers->count(), 1); // Need more than one user
    int index = ul->lstUsers->findText(testUsername, Wt::MatchStringExactly);
    BOOST_CHECK_MESSAGE( index >= 0, "Couldn't find our user in the list" );
}

BOOST_AUTO_TEST_CASE( new_forget_password ) {
    // Get this list of users
    UserList* ul = userList();
    BOOST_REQUIRE_MESSAGE( ul->isVisible(), "We expected the userlist to be visible" );
    // Make sure only one uer in the list at first
    BOOST_REQUIRE_EQUAL( ul->lstUsers->count(), 1 );
    // Click the new user button
    h::click(ul->btnNew);
    UserEdit* ue = userEdit();
    BOOST_CHECK_MESSAGE( ue->isVisible(), "Click new should show the UserEdit screen" );
    // Now fill in the new user details
    const string testUsername = "Test User 1";
    ue->edtName->setText(testUsername);
    h::keyPress(ue->edtName, 13);
    BOOST_CHECK_MESSAGE(ue->edtPass1->hasFocus(),
        "Clicking enter after typing your name should give focus to the 1st password field");
    // Testing what happpens if we forgot to add passwords ;)
    h::keyPress(ue->edtPass2, 13);
    // Check if the dialog message was shown
    BOOST_CHECK_EQUAL(lastMessage, WString::tr("fix-up-fields"));
    // BOOST_CHECK(ue->edtPass1->hasFocus()); // TODO: Make this line work. At the moment the dialog removes focus.
    // We should still be on the user edit page
    BOOST_REQUIRE_MESSAGE( ue->isVisible(), "We should still be on the user edit page");
}

} // namespace unittests
} // namespace my_app

BOOST_AUTO_TEST_SUITE_END(); // usermanager_suite
