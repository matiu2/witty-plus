/*
 * =====================================================================================
 *
 *       Filename:  UserEdit.cpp
 *
 *    Description:  GUI to edit User records
 *
 *        Version:  1.0
 *        Created:  08/28/2011 17:13:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "UserEdit.hpp"
#include <Wt/WLineEdit>

namespace my_app {

UserEdit::UserEdit(WContainerWidget* parent) : wittyPlus::MoreAwesomeTemplate(parent) {
    setTemplateText(tr("user-edit-template"));
    // Set up the widgets
    bindAndCreateField(lblName, edtName, "name");
    bindAndCreateField(lblPass1, edtPass1, "new-password");
    bindAndCreateField(lblPass2, edtPass2, "new-password2");    
    bindAndCreateWidget(btnBar, "btn-bar");
}

} // namespace my_app
