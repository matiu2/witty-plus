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
#include <wittyPlus/IUsers.hpp>
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
        urlManager->urlSignal("/page").connect(this, &Extension::handleURLChange);
    dbSession().mapClass<Model>("page");
    actionMap.insert(ActionPair("view", &Extension::view));
    actionMap.insert(ActionPair("edit", &Extension::edit));
}

void Extension::handleURLChange() {
    // Find the page
    IGui* gui = IGui::instance();
    Wt::WApplication* app = Wt::WApplication::instance();
    std::string pageName = "/";
    std::string action = "view";
    if (app->internalPathMatches("/page/")) {
        pageName = app->internalPathNextPart("/page/");
        std::string pagePath = "/page/" + pageName + "/";
        if (app->internalPathMatches(pagePath))
            action = app->internalPathNextPart(pagePath);
    }
    dbo::Session& s = dbSession();
    dbo::Transaction t(s);
    dbo::ptr<Model> page = s.find<Model>().where("name=?").bind(pageName);
    // Use it
    if (page) {
        ActionMap::const_iterator found = actionMap.find(action);
        if (found != actionMap.end()) {
            ((this)->*(found->second))(*page); // Call the action .. view/edit etc..
        } else {
            Wt::WApplication::instance()->log("ERROR") <<
              "No valid action for page " << page->getName() << " - " <<
              "Action name " << action;
            // Default to view maybe ?
            gui->setBody("ERROR: No such action " + action );
        }
    } else {
        gui->setBody("PAGE NOT FOUND: " + pageName);
    }
    t.commit();
}

void Extension::view(const Model &page) {
    IGui* gui = IGui::instance();
    gui->setTitle(page.getTitle());
    gui->setBody(page.getHtml());
    IUsers* users = IUsers::instance();
    if (users->isLoggedIn()) {
        gui->addAdminMenuItem(Wt::WString::tr("Edit"), "/" + page.getName() + "/edit");
    }
}

void Extension::edit(const Model &page) {
}


} // namespace wittyPlus
} // namespace page
