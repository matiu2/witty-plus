/*
 * =====================================================================================
 *
 *       Filename:  test_login.cpp
 *
 *    Description:  Tests logging in
 *
 *        Version:  1.0
 *        Created:  09/09/2011 23:20:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE login_module

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include "../MainWindow.hpp"
#include "../LoginWindow.hpp"
#include "../lib/ButtonBar.hpp"
#include "../AdminIndex.hpp"
#include <Wt/WPushButton>
#include "fixtures/App.hpp"
#include "helpers.hpp"

namespace my_app {
namespace unittests {

namespace h = helpers;

// Helper functions
LoginWindow* clickLogin(MainWindow* main) {
    h::click(main->_loginLink);
    LoginWindow* result = main->resolve<LoginWindow*>("content");
    BOOST_REQUIRE_MESSAGE( result, "Looks like the login window didn't appear" );
    return result;
}

BOOST_FIXTURE_TEST_SUITE( login_suite , fixtures::AppFixture );

BOOST_AUTO_TEST_CASE( login_escape_test ) {
    LoginWindow* login = clickLogin(main);
    // Hit escape
    h::keyPress(login->_passwordEdit, 27); // Hit Escape
    // Make sure we didn't log in
    BOOST_CHECK_EQUAL( app.internalPath(), "/" );
    BOOST_CHECK_MESSAGE( main->_loginLink, "The login ling should still be there" );
}

BOOST_AUTO_TEST_CASE( login_enter_test ) {
    LoginWindow* login = clickLogin(main);
    // Fill in the form
    login->_usernameEdit->setText("admin");
    login->_passwordEdit->setText("admin");
    h::keyPress(login->_passwordEdit, 13); // Hit Enter
    // Check that we're logged in
    BOOST_CHECK_MESSAGE( main->_loginLink == 0, "Login link should have disappeared. Maybe admin+admin is not in DB ?" );
    AdminIndex* cp = main->resolve<AdminIndex*>("controls");
    BOOST_REQUIRE_MESSAGE( cp, "Looks like the control panel didn't appear" );
}

BOOST_AUTO_TEST_CASE( login_ok_test ) {
    LoginWindow* login = clickLogin(main);
    // Fill in the form
    login->_usernameEdit->setText("admin");
    login->_passwordEdit->setText("admin");
    // Click the Login button
    h::click(login->_btnBar, "Login");
    app.processEvents();
    // Check that we're logged in
    BOOST_CHECK_MESSAGE( main->_loginLink == 0, "Login link should have disappeared. Maybe admin+admin is not in DB ?" );
    AdminIndex* cp = main->resolve<AdminIndex*>("controls");
    BOOST_REQUIRE_MESSAGE( cp, "Looks like the control panel didn't appear" );
}

BOOST_AUTO_TEST_CASE( login_cancel_test ) {
    LoginWindow* login = clickLogin(main);
    // Fill in the form
    login->_usernameEdit->setText("admin");
    login->_passwordEdit->setText("admin");
    // Click the Cancel button
    h::click(login->_btnBar, "Cancel");
    app.processEvents();
    // Make sure we didn't log in
    BOOST_CHECK_EQUAL( app.internalPath(), "/" );
    BOOST_CHECK_MESSAGE( main->_loginLink, "The login ling should still be there" );
}

BOOST_AUTO_TEST_CASE( login_fail_test ) {
    LoginWindow* login = clickLogin(main);
    // Fill in the form
    login->_usernameEdit->setText("NOT a User");
    login->_passwordEdit->setText("Bad Pass");
    // Click the Login button
    h::click(login->_btnBar, "Login");
    app.processEvents();
    // Make sure we didn't log in
    BOOST_CHECK_EQUAL( app.internalPath(), "/" );
    BOOST_CHECK_MESSAGE( main->_loginLink, "The login ling should still be there" );
}

BOOST_AUTO_TEST_SUITE_END() // login_suite

} // namespace unittests
} // namespace my_app
