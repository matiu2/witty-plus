/*
 * =====================================================================================
 *
 *       Filename:  Login.hpp
 *
 *    Description:  Login Fixture
 *
 *        Version:  1.0
 *        Created:  09/11/2011 18:57:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TESTS_FIXTURES_LOGIN_HPP
#define TESTS_FIXTURES_LOGIN_HPP

#include "App.hpp"
#include "../helpers.hpp"
#include "../../LoginWindow.hpp"
#include "../../MainWindow.hpp"
#include "../../AdminIndex.hpp"

namespace my_app {
namespace unittests {
namespace fixtures {

namespace h = helpers;

/// Our special login fixture for testing the login window
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
} // namespace unittests 
} // namespace my_app

#endif // TESTS_FIXTURES_LOGIN_HPP
