//
//  UserList.hpp
//  my_app
//
//  Created by Matthew Sherborne on 22/08/11.
//  Copyright 2011 Slicehost LLC. All rights reserved.
//

#ifndef my_app_UserList_hpp
#define my_app_UserList_hpp

#include <Wt/WStackedWidget>
#include "UserList.hpp"
#include "UserEdit.hpp"
#include "model/User.hpp"
#include <Wt/WAnimation>

using Wt::WStackedWidget;
using my_app::model::User;

namespace dbo = Wt::Dbo;

namespace my_app {
    

/// GUI to manage users
class UserManager : public WStackedWidget {
private:
    // Fields
    UserList* userList;
    UserEdit* userEdit;
    // Helper funcs
    template <class Widget>
    void createAndAddWidget(Widget*& widget) { addWidget(widget = new Widget()); }
    // Event handlers
    void userChosen(dbo::ptr<User> user) {
        //userList->animateHide(Wt::WAnimation(Wt::WAnimation::Fade));
        setCurrentWidget(userEdit);
        userEdit->setUser(user);
    }
public:
    UserManager(WContainerWidget* parent=0) : WStackedWidget(parent) {
        createAndAddWidget(userList);
        userList->userChosen().connect(this, &UserManager::userChosen);
        createAndAddWidget(userEdit);
    }
};
    
} // namespace my_app


#endif
