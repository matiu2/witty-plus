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
#include <Wt/WMenu>
#include <Wt/WMenuItem>
#include <wittyPlus/base/InternalLink.hpp>
#include <wittyPlus/base/ButtonBar.hpp>
#include <wittyPlus/base/SimpleMenu.hpp>
#include <Wt/WLink>
#include <Wt/WString>
#include <string>
#include <boost/test/test_tools.hpp>

using Wt::WMouseEvent;
using Wt::WApplication;
using Wt::WLink;
using Wt::WString;

namespace wittyPlus {
namespace unittests {
namespace helpers {

template<typename Widget>
void click(Widget* w) {
    WMouseEvent click;
    w->clicked().emit(click);
}

template<>
void click<base::InternalLink>(base::InternalLink* il) {
    WLink& link = il->link_;
    if (link.type_ == WLink::InternalPath) {
        WApplication::instance()->setInternalPath(link.internalPath().toUTF8(), true);
    }
}

template<>
void click<Wt::WMenu>(Wt::WMenu* menu) {
    // Just Click the first item in the menu
    vector< Wt::WMenuItem* >::const_iterator first = menu->items().begin();
    if (first != menu->items().end())
        (*first)->select();
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

void click(base::ButtonBar* btns, const std::string label) {
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

void clickOk(base::ButtonBar* btns) { click(btns, "OK"); }
void clickCancel(base::ButtonBar* btns) { click(btns, "Cancel"); }

base::InternalLink* findSimpleMenuItem(base::SimpleMenu* menu, const string& url) {
    base::InternalLink* result = 0;
    for (int i=0; i<menu->_impl->count(); ++i) {
        result = dynamic_cast<base::InternalLink*>(menu->_impl->widget(i));
        if (result != 0)
            if (result->link().internalPath() == url)
                return result;
    }
    return 0;
}

} // namespace helpers
} // namespace unittests
} // namespace wittyPlus

#endif //  MY_APP_UNITTESTS_HELPERS_HPP
