/*
 * =====================================================================================
 *
 *       Filename:  urls.hpp
 *
 *    Description:  A nice place too keep all the urls
 *
 *        Version:  1.0
 *        Created:  10/08/11 22:10:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef URLS_HPP
#define URLS_HPP

#include <Wt/WString>
#include <Wt/WAnchor>
#include <Wt/WLink>

using Wt::WString;
using Wt::WAnchor;
using Wt::WLink;

namespace my_app {

/// Consts so we don't accidentally change a url somewhere
namespace urls {
    typedef const char* URL;
    extern URL home;
    extern URL login;
    extern URL logout;
    extern URL adminUsers;
    inline WAnchor* newInternalLink(URL url, const WString& text) { return new WAnchor(WLink(WLink::InternalPath, url), text); }
} // namespace urls

} // namespace my_app

#endif //  URLS_HPP
