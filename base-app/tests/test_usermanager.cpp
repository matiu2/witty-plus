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

#define BOOST_TEST_MODULE user_manager_module

#include "helpers.hpp"
#include "fixtures/UserManager.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

namespace my_app {
namespace unittests {

namespace h = helpers;

BOOST_FIXTURE_TEST_SUITE( user_manager_suite, fixtures::UserManagerFixture );

BOOST_AUTO_TEST_CASE( new_user ) {
    UserList* ul = userList();
    BOOST_REQUIRE_MESSAGE( ul->isVisible(), "We expected the userlist to be visible" );
    h::click(ul->btnNew);
    UserEdit* ue = userEdit();
    BOOST_CHECK_MESSAGE( ue->isVisible(), "Click new should show the UserEdit screen" );
    // Now fill in the new user details
    ue->edtName->setText("Test User 1");
    h::keyPress(ue->edtName, 13);
    BOOST_CHECK_MESSAGE(ue->edtPass1->hasFocus(),
        "Clicking enter after typing your name should give focus to the 1st password field");
    ue->edtPass1->setText("Test Pass");
    ue->edtPass2->setText("Test Pass");
    h::keyPress(ue->edtPass2, 13);
}

} // namespace unittests
} // namespace my_app

BOOST_AUTO_TEST_SUITE_END(); // login_suite
