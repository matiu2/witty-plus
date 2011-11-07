/*
 * =====================================================================================
 *
 *       Filename:  InternalLink.hpp
 *
 *    Description:  Like WAnchor, but defaults to making internal links
 *
 *        Version:  1.0
 *        Created:  09/04/2011 12:50:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef INTERNAL_LINK_HPP
#define INTERNAL_LINK_HPP

#include <Wt/WAnchor>
#include <Wt/WLink>
#include <Wt/WString>
#include <string>

using Wt::WAnchor;
using Wt::WLink;
using Wt::WString;
using Wt::WContainerWidget;
using std::string;

namespace wittyPlus {
namespace base {

// Like WAnchor, but defaults to setting an internal link
class InternalLink : public WAnchor {
public:
    InternalLink(const string& url, const WString& text, WContainerWidget* parent=0) :
        WAnchor(WLink(WLink::InternalPath, url), text, parent) {}
};

} // namespace base
} // namespace wittyPlus

#endif //  INTERNAL_LINK_HPP
