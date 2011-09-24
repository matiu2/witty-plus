/*
 * =====================================================================================
 *
 *       Filename:  App.hpp
 *
 *    Description:  A fixture that creates a test app to play with
 *
 *        Version:  1.0
 *        Created:  09/09/2011 23:26:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TESTS_FIXTURES_APP_HPP
#define TESTS_FIXTURES_APP_HPP

#include "../../App.hpp"
#include <Wt/WEnvironment>
#include <Wt/Test/WTestEnvironment>

namespace my_app {
namespace unittests {
namespace fixtures {

struct AppFixture {
    AppFixture() : env(".", "wt-config.xml"), app(env), main(app.mainWindow()) { app.initialize(); }
    ~AppFixture() { app.quit(); }
    Wt::Test::WTestEnvironment env;
    my_app::App app;
    my_app::MainWindow* main;
};

} // namespace fixtures
} // namespace unittests 
} // namespace my_app

#endif // TESTS_FIXTURES_APP_HPP
