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

/// Our special login fixture for testing the login window
namespace fixtures {
struct LoginFixture : public AppFixture {
    /// Clicks the login link
    LoginWindow* clickLogin() {
        h::click(main->_loginLink);
        LoginWindow* result = main->resolve<LoginWindow*>("content");
        BOOST_REQUIRE_MESSAGE( result, "Looks like the login window didn't appear" );
        return result;
    }
    /// Makes sure we *are* logged in
    void checkLoggedIn() {
        // Make sure the login link died
        BOOST_CHECK_MESSAGE( main->_loginLink == 0, "Login link should have disappeared. Maybe admin+admin is not in DB ?" );
        // Make sure the control panel appears
        AdminIndex* cp = main->resolve<AdminIndex*>("controls");
        BOOST_CHECK_MESSAGE( cp, "Looks like the control panel didn't appear" );
        // Make sure the logout link is there
        BOOST_CHECK_MESSAGE( cp->resolve<wittyPlus::InternalLink*>("link-logout"),
                             "Looks like the logout link didn't appear" );
    }
    /// Makes sure we're *not* logged in
    void checkLoggedOut(const std::string& path="/") {
        if (!path.empty())
            BOOST_CHECK_EQUAL( app.internalPath(), path );
        BOOST_CHECK_MESSAGE( main->_loginLink, "The login ling should still be there" );
    }
};
} // namespace fixtures

// /////// Tests start here //////////////////////////////////////////////

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
