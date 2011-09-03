/*
 * =====================================================================================
 *
 *       Filename:  urls.cpp
 *
 *    Description:  Stores the value of the url constants
 *
 *        Version:  1.0
 *        Created:  08/23/2011 18:04:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "urls.hpp"

namespace my_app {

/// Consts so we don't accidentally change a url somewhere
namespace urls {

    URL home = "/";
    URL login = "/login";
    URL logout = "/logout";
    URL adminUsers = "/admin/users";

} // namespace urls

} // namespace my_app
