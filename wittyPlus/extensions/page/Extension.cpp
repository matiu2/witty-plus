/*
 * =====================================================================================
 *
 *       Filename:  Extension.cpp
 *
 *    Description:  Implementatoin of the page plugin
 *
 *        Version:  1.0
 *        Created:  08/11/11 17:12:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "Extension.hpp"
#include <wittyPlus/IGui.hpp>
#include <wittyPlus/IURLs.hpp>
#include <Wt/WApplication>

namespace wittyPlus {
namespace page {

/// Called every time an app is created
Extension::Extension(WObject* parent) : WObject(parent) {
    IURLs::instance()->urlSignal("/page").connect(this, &Extension::show_a_page);
}

void Extension::show_a_page() {
    IGui* gui = IGui::instance();
    Wt::WApplication* app = Wt::WApplication::instance();
    gui->setBody("I AM A PAGE: " + app->internalPath());
}


} // namespace wittyPlus
} // namespace page
