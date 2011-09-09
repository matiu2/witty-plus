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

namespace my_app {
namespace unittests {
namespace helpers {

template<typename Widget>
void click(Widget* w) {
    Wt::WMouseEvent click;
    w->clicked().emit(click);
}

template<typename Widget>
void keyPress(Widget* w, unsigned char keyCode) {
    Wt::JavaScriptEvent js;
    js.keyCode = keyCode;
    Wt::WKeyEvent press(js);
    w->keyPressed().emit(press);
}


} // namespace helpers
} // namespace unittests
} // namespace my_app

#endif //  MY_APP_UNITTESTS_HELPERS_HPP
