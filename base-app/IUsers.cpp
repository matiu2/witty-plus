/*
 * =====================================================================================
 *
 *       Filename:  IUsers.cpp
 *
 *    Description:  Lets you get an instance to your IUsers interface
 *
 *        Version:  1.0
 *        Created:  11/05/2011 15:52:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "IUsers.hpp"
#include "App.hpp"

namespace wittyPlus {

IUsers* IUsers::instance() { return dynamic_cast<IUsers*>(app()); }

}
