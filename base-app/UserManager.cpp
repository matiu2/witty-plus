//
//  UserManager.cpp
//  my_app
//
//  Created by Matthew Sherborne on 22/08/11.
//  Copyright 2011 Slicehost LLC. All rights reserved.
//

#include <iostream>
#include <Wt/WLabel>
#include <Wt/WSelectionBox>
#include <Wt/WLineEdit>
#include <Wt/Dbo/Transaction>
#include <Wt/Dbo/Query>
#include <Wt/Dbo/ptr>
#include "UserManager.hpp"
#include "App.hpp"

namespace dbo = Wt::Dbo;

using Wt::WString;

namespace my_app {
    
UserManager::UserManager(WContainerWidget* parent) : wittyPlus::MoreAwesomeTemplate(parent) {
    setStyleClass("yui-g");
    setTemplateText(tr("user-manager-template"));
    // Set up the widgets
    bindAndCreateField(lblList, lstUsers, "userList");
    bindAndCreateField(lblName, edtName, "name");
    bindAndCreateField(lblPass1, edtPass1, "new-password");
    bindAndCreateField(lblPass2, edtPass2, "new-password2");    
    bindAndCreateWidget(btnBar, "btn-bar");
    fillUserList();
}

void UserManager::fillUserList() {
    dbo::Session& db = app()->dbSession();
    dbo::Transaction t(db);
    usersModel.setQuery(db.find<User>()); // Get all users
    usersModel.addColumn("name");
    lstUsers->setModel(&usersModel);
    t.commit();
}
    
}
