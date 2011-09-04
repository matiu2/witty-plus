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

#include "lib/MoreAwesomeTemplate.hpp"
#include "urls.hpp"
#include "lib/InternalLink.hpp"

using wittyPlus::MoreAwesomeTemplate;
using wittyPlus::InternalLink;

namespace my_app {

class AdminIndex : public MoreAwesomeTemplate {
public:
    AdminIndex (WContainerWidget* parent=0) : MoreAwesomeTemplate(parent) {
        setTemplateText(tr("admin-index-template"));
        bindWidget("link-users", new InternalLink(urls::adminUsers, tr("Users")));
        bindWidget("link-logout", new InternalLink(urls::logout, tr("Logout")));
    }
};

} // namespace my_app
