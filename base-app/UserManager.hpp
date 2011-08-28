//
//  UserList.hpp
//  my_app
//
//  Created by Matthew Sherborne on 22/08/11.
//  Copyright 2011 Slicehost LLC. All rights reserved.
//

#ifndef my_app_UserList_hpp
#define my_app_UserList_hpp

#include <Wt/WString>
#include <Wt/Dbo/QueryModel>
#include "lib/MoreAwesomeTemplate.hpp"
#include "lib/ButtonBar.hpp"
#include "model/User.hpp"

namespace Wt {
    class WLabel;
    class WSelectionBox;
    class WLineEdit;
};

using Wt::WLabel;
using Wt::WSelectionBox;
using Wt::WLineEdit;
using wittyPlus::ButtonBar;
using my_app::model::User;

namespace dbo = Wt::Dbo;

namespace my_app {
    
/// GUI to manage users
class UserManager : public wittyPlus::MoreAwesomeTemplate {
private:
    // data related
    dbo::QueryModel< dbo::ptr<User> > usersModel; 
    // Fields
    WLabel*        lblList;
    WSelectionBox* lstUsers;
    WLabel*    lblName;
    WLineEdit* edtName;
    WLabel*    lblPass1;
    WLineEdit* edtPass1;
    WLabel*    lblPass2;
    WLineEdit* edtPass2;
    ButtonBar* btnBar;
protected:
    void fillUserList();
public:
    UserManager(WContainerWidget* parent=0);    
};
    
} // namespace my_app


#endif
