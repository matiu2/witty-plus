/*
 * =====================================================================================
 *
 *       Filename:  common.hpp
 *
 *    Description:  Nice utilities that a lot of files import
 *
 *        Version:  1.0
 *        Created:  08/07/11 14:53:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include <Wt/WApplication>

namespace my_app {

class App;

App& getApp() { dynamic_cast<App>(Wt::WApplication::getInstance()); }


} // namespace my_app

#endif // COMMON_HPP
