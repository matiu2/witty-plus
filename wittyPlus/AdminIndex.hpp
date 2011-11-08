/*
 * =====================================================================================
 *
 *       Filename:  AdminIndex.hpp
 *
 *    Description:  Shows the window for the admins after they login
 *
 *        Version:  1.0
 *        Created:  08/25/2011 19:37:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ADMIN_INDEX_HPP
#define ADMIN_INDEX_HPP

#include "urls.hpp"
#include "base/InternalLink.hpp"
#include "base/SimpleMenu.hpp"


namespace wittyPlus {

using base::SimpleMenu;
using base::InternalLink;

class AdminIndex : public SimpleMenu {
public:
    AdminIndex (WContainerWidget* parent=0) : SimpleMenu(parent) {
        addLink(tr("Users"), urls::admin_users);
        addLink(tr("Logout"), urls::logout);
    }
};

} // namespace wittyPlus

#endif //  ADMIN_INDEX_HPP
