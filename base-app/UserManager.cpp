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
#include "UserManager.hpp"

namespace my_app {
    
UserManager::UserManager(WContainerWidget* parent) : wittyPlus::MoreAwesomeTemplate(parent) {
    setTemplateText(tr("user-manager-template"));
    // Set up the widgets
    bindAndCreateField(lblList, lstUsers, "listUsers");
    bindAndCreateField(lblName, edtName, "name");
    bindAndCreateField(lblPass1, edtPass1, "new-password");
    bindAndCreateField(lblPass2, edtPass2, "new-password2");    
    bindWidget("btn -bar", btnBar);
}
    
}
