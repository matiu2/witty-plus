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
#include "fixtures/App.hpp"
#include "helpers.hpp"

namespace my_app {
namespace unittests {

namespace h = helpers;

// Helper functions
LoginWindow* clickLogin(App& app) {
    MainWindow* main = app.mainWindow();
    h::click(main->_loginLink);
    LoginWindow* result = main->resolve<LoginWindow*>("content");
    BOOST_REQUIRE( result );
    return result;
}

BOOST_FIXTURE_TEST_SUITE( login_suite , fixtures::AppFixture );

BOOST_AUTO_TEST_CASE( login_escape_test ) {
    LoginWindow* login = clickLogin(app);
    // Hit escape
    h::keyPress(login->_passwordEdit, 27); // Hit Escape
    // Should now be back at the original location
    BOOST_CHECK_EQUAL( app.internalPath(), "/" );
}

BOOST_AUTO_TEST_CASE( login_enter_test ) {
    MainWindow* main = app.mainWindow();
    h::click(main->_loginLink);
    // Now we should have a login form
    LoginWindow* login = main->resolve<LoginWindow*>("content");
    BOOST_REQUIRE( login );
    login->_usernameEdit->setText("admin");
    login->_passwordEdit->setText("admin");
    h::keyPress(login->_passwordEdit, 13); // Hit Enter
    // TODO: Check that we're logged in
}

BOOST_AUTO_TEST_SUITE_END() // login_suite

} // namespace unittests
} // namespace my_app
