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
using Wt::WAnimation;
using my_app::model::User;

namespace dbo = Wt::Dbo;

namespace my_app {
    

/// GUI to manage users
class UserManager : public WStackedWidget {
private:
    // Helpers
    WAnimation slide;
    // Fields
    UserList* userList;
    UserEdit* userEdit;
    // Helper funcs
    template <class Widget>
    void createAndAddWidget(Widget*& widget) { addWidget(widget = new Widget()); }
    // Event handlers
    void userChosen(dbo::ptr<User> user) {
        setCurrentIndex(1, slide, true);
        userEdit->setUser(user);
    }
    void userEdited(dbo::ptr<User>) {
        setCurrentIndex(0, slide, true);
        // TODO: See if this needs calling .. it might automagically update ?
        // userList->refillUserList();
    }
    void userEditCancelled() { setCurrentIndex(0, slide, true); }
public:
    UserManager(WContainerWidget* parent=0) :
        WStackedWidget(parent), slide(WAnimation::SlideInFromBottom) 
    {
        createAndAddWidget(userList);
        userList->userChosen().connect(this, &UserManager::userChosen);
        createAndAddWidget(userEdit);
        userEdit->done().connect(this, &UserManager::userEdited);
        userEdit->cancelled().connect(this, &UserManager::userEditCancelled);
    }
};
    
} // namespace my_app


#endif
