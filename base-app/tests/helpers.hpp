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
#include <Wt/WString>
#include <string>

using Wt::WMouseEvent;
using Wt::WApplication;
using Wt::WLink;
using Wt::WString;

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
    switch (keyCode) {
        case 27: // escape
            w->escapePressed().emit();
            break;
        case 13:
            w->enterPressed().emit();
            break;
        default:
            Wt::JavaScriptEvent js;
            js.keyCode = keyCode;
            Wt::WKeyEvent press(js);
            w->keyPressed().emit(press);
    }
}

void click(wittyPlus::ButtonBar* btns, const std::string label) {
    WString translated = WString::tr(label);
    WPushButton* btn1 = btns->btn1();
    if (btn1->text() == translated) {
        click(btn1);
        return;
    }
    WPushButton* btn2 = btns->btn2();
    if (btn2->text() == translated) {
        click(btns->btn2());
        return;
    }
    BOOST_ERROR("Couldn't find button with label: " + label + " that translates to " + translated +
                "\nOptions are: " + btn1->text() + " and " + btn2->text());
}

void clickOk(wittyPlus::ButtonBar* btns) { click(btns, "OK"); }
void clickCancel(wittyPlus::ButtonBar* btns) { click(btns, "Cancel"); }

} // namespace helpers
} // namespace unittests
} // namespace my_app

#endif //  MY_APP_UNITTESTS_HELPERS_HPP
