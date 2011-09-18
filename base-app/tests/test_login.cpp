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
#include "fixtures/Login.hpp"

namespace my_app {
namespace unittests {

namespace h = helpers;

BOOST_FIXTURE_TEST_SUITE( login_suite , fixtures::LoginFixture );

BOOST_AUTO_TEST_CASE( login_escape ) {
    LoginWindow* login = clickLogin();
    // Hit escape
    h::keyPress(login->_passwordEdit, 27); // Hit Escape
    // Make sure we didn't log in
    BOOST_CHECK_EQUAL( app.internalPath(), "/" );
    BOOST_CHECK_MESSAGE( main->_loginLink, "The login ling should still be there" );
}

BOOST_AUTO_TEST_CASE( login_enter ) {
    LoginWindow* login = clickLogin();
    // Fill in the form
    login->_usernameEdit->setText("admin");
    login->_passwordEdit->setText("admin");
    h::keyPress(login->_passwordEdit, 13); // Hit Enter
    // Check that we're logged in
    checkLoggedIn();
}

BOOST_AUTO_TEST_CASE( login_ok ) {
    LoginWindow* login = clickLogin();
    // Fill in the form
    login->_usernameEdit->setText("admin");
    login->_passwordEdit->setText("admin");
    // Click the Login button
    h::click(login->_btnBar, "Login");
    app.processEvents();
    // Check that we're logged in
    checkLoggedIn();
}

BOOST_AUTO_TEST_CASE( login_cancel ) {
    LoginWindow* login = clickLogin();
    // Fill in the form
    login->_usernameEdit->setText("admin");
    login->_passwordEdit->setText("admin");
    // Click the Cancel button
    h::click(login->_btnBar, "Cancel");
    app.processEvents();
    // Make sure we didn't log in
    checkLoggedOut();
}

BOOST_AUTO_TEST_CASE( login_fail ) {
    LoginWindow* login = clickLogin();
    // Fill in the form
    login->_usernameEdit->setText("NOT a User");
    login->_passwordEdit->setText("Bad Pass");
    // Click the Login button
    h::click(login->_btnBar, "Login");
    app.processEvents();
    // Make sure we didn't log in
    checkLoggedOut();
}

BOOST_AUTO_TEST_CASE( login_logout ) {
    LoginWindow* login = clickLogin();
    // Fill in the form
    login->_usernameEdit->setText("admin");
    login->_passwordEdit->setText("admin");
    // Click the Login button
    h::click(login->_btnBar, "Login");
    app.processEvents();
    // Check that we're logged in
    checkLoggedIn();
    // Click the logout link
    AdminIndex* cp = main->resolve<AdminIndex*>("controls");
    BOOST_REQUIRE( cp );
    wittyPlus::InternalLink* logout = cp->resolve<wittyPlus::InternalLink*>("link-logout");
    BOOST_REQUIRE( logout );
    h::click(logout);
    // Check it worked
    checkLoggedOut("/logout");
}

BOOST_AUTO_TEST_SUITE_END() // login_suite

} // namespace unittests
} // namespace my_app
