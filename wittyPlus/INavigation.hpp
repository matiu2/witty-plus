/*
 * =====================================================================================
 *
 *       Filename:  INavigation.hpp
 *
 *    Description:  Interface to do navigation in the app
 *
 *        Version:  1.0
 *        Created:  11/05/2011 16:39:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#pragma once

#include <string>

namespace wittyPlus {

class INavigation {
public:
    virtual void go(const std::string& newUrl) = 0;
    virtual bool goBack(bool dontLogout=true) = 0;
    virtual void goBackOrHome() = 0;

    static INavigation* instance();
};

} // namespace wittyPlus
