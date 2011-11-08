/*
 * =====================================================================================
 *
 *       Filename:  wt_test_base.hpp
 *
 *    Description:  Base class for testing witty classes
 *
 *        Version:  1.0
 *        Created:  09/09/2011 23:21:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef wt_test_base_HPP
#define wt_test_base_HPP

#include <Wt/WApplication>
#include <Wt/Test/WTestEnvironment>

struct WT_TestFixture {
    WT_TestFixture() : env(".", "config.test"), app(env) { app.initialize(); }
    Wt::Test::WTestEnvironment env;
    Wt::WApplication app;
};

#endif // wt_test_base_HPP
