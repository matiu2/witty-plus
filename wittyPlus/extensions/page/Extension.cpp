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
#include "Model.hpp"
#include <string>
#include <wittyPlus/IGui.hpp>
#include <wittyPlus/IURLs.hpp>
#include <wittyPlus/db.hpp>
#include <Wt/WApplication>
#include <Wt/Dbo/Dbo>

namespace dbo = Wt::Dbo;

namespace wittyPlus {
namespace page {

/// Called every time an app is created
Extension::Extension(WObject* parent) : WObject(parent) {
    IURLs* urlManager = IURLs::instance();
    if (urlManager != 0)
        urlManager->urlSignal("/page").connect(this, &Extension::show_a_page);
    dbSession().mapClass<Model>("page");
}

void Extension::show_a_page() {
    IGui* gui = IGui::instance();
    Wt::WApplication* app = Wt::WApplication::instance();
    std::string pageId = app->internalPathNextPart("/page/");
    std::string action = app->internalPathNextPart("/page/" + pageId + "/");
    if (action == "")
        action = "view";
    dbo::ptr<Model> page2show = dbSession().find<Model>("id=pageId");
    if (page2show)
        gui->setBody("I AM A PAGE: " + pageId);
    else
        gui->setBody("PAGE NOT FOUND: " + pageId);
}



} // namespace wittyPlus
} // namespace page
