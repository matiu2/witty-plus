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
#include <wittyPlus/tests/helpers.hpp>
#include <wittyPlus/urls.hpp>
#include <wittyPlus/LoginWindow.hpp>
#include <wittyPlus/MainWindow.hpp>
#include <wittyPlus/AdminIndex.hpp>
#include <wittyPlus/model/User.hpp>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/Transaction>
#include <Wt/Dbo/ptr>
#include <boost/foreach.hpp>

namespace dbo = Wt::Dbo;

namespace wittyPlus {
namespace unittests {
namespace fixtures {

namespace h = helpers;

/// Our special login fixture for testing the login window
struct LoginFixture : public AppFixture {
    LoginFixture() : AppFixture() { cleanUpUsersTable(); }
    /// Clicks the login link
    LoginWindow* clickLogin() {
        h::click(main->_loginMenu);
        LoginWindow* result = main->resolve<LoginWindow*>("content");
        BOOST_REQUIRE_MESSAGE( result, "Looks like the login window didn't appear" );
        return result;
    }
    /// Makes it so we only have a single user 'admin' 'admin'
    void cleanUpUsersTable() {
        dbo::Session& db = app.dbSession();
        dbo::Transaction t(db);
        // Delete everyone except admin
        db.execute("delete from users where name != ?").bind("admin");
        // Make sure admin has the right info
        dbo::ptr<model::User> adminUser = db.find<model::User>().where("name = ?").bind("admin").resultValue();
        if (!adminUser) {
            // If there was no admin user .. make a new one
            adminUser = new model::User("admin", "admin");
            db.add(adminUser);
        } else {
            // If admin exists .. make sure the password is 'admin'
            adminUser.modify()->setPassword("admin");
        }
        t.commit();
    }
    /// Makes sure we *are* logged in
    void checkLoggedIn() {
        // Make sure the login link died
        BOOST_CHECK_MESSAGE( main->_loginMenu == 0, "Login link should have disappeared. Maybe admin+admin is not in DB ?" );
        // Make sure the control panel appears
        AdminIndex* cp = main->resolve<AdminIndex*>("controls");
        BOOST_CHECK_MESSAGE( cp, "Looks like the control panel didn't appear" );
        // Make sure the logout link is there
        BOOST_CHECK_MESSAGE( h::findSimpleMenuItem(cp, urls::logout),
                             "Looks like the logout link didn't appear" );
    }
    /// Makes sure we're *not* logged in
    void checkLoggedOut(const std::string& path="/") {
        if (!path.empty())
            BOOST_CHECK_EQUAL( app.internalPath(), path );
        BOOST_CHECK_MESSAGE( main->_loginMenu, "The login ling should still be there" );
    }
};

} // namespace fixtures
} // namespace unittests 
} // namespace my_app

#endif // TESTS_FIXTURES_LOGIN_HPP
