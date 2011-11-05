/*
 * =====================================================================================
 *
 *       Filename:  INavigation.cpp
 *
 *    Description:  Implementation for INavigation .. gets you a working copy
 *
 *        Version:  1.0
 *        Created:  11/05/2011 16:51:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "INavigation.hpp"
#include "App.hpp"

namespace wittyPlus {

INavigation* INavigation() { return dynamic_cast<INavigation*>(app()); }

} // namespace wittyPlus
