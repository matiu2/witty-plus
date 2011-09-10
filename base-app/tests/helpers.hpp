/*
 * =====================================================================================
 *
 *       Filename:  helpers.hpp
 *
 *    Description:  Helper macro definitions and functions for defining tests
 *
 *        Version:  1.0
 *        Created:  09/09/2011 23:34:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MY_APP_UNITTESTS_HELPERS_HPP
#define MY_APP_UNITTESTS_HELPERS_HPP

#include <Wt/WEvent>
#include <Wt/WApplication>
#include "../lib/InternalLink.hpp"
#include <Wt/WLink>

using Wt::WMouseEvent;
using Wt::WApplication;
using Wt::WLink;

namespace my_app {
namespace unittests {
namespace helpers {

template<typename Widget>
void click(Widget* w) {
    WMouseEvent click;
    w->clicked().emit(click);
}

template<>
void click<wittyPlus::InternalLink>(InternalLink* il) {
    WLink& link = il->link_;
    if (link.type_ == WLink::InternalPath) {
        WApplication::instance()->setInternalPath(link.internalPath().toUTF8(), true);
    }
}

template<typename Widget>
void keyPress(Widget* w, unsigned char keyCode) {
    if (keyCode == 27) { // escape
        w->escapePressed().emit();
    } else {
        Wt::JavaScriptEvent js;
        js.keyCode = keyCode;
        Wt::WKeyEvent press(js);
        w->keyPressed().emit(press);
    }
}


} // namespace helpers
} // namespace unittests
} // namespace my_app

#endif //  MY_APP_UNITTESTS_HELPERS_HPP
