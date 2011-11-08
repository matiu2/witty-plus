/*
 * =====================================================================================
 *
 *       Filename:  db.cpp
 *
 *    Description:  Implements getting a reference to the local dbSession
 *
 *        Version:  1.0
 *        Created:  11/06/2011 11:27:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "db.hpp"
#include <Wt/WApplication>
#include "base/BaseApp.hpp"
#include "model/User.hpp"

namespace wittyPlus {

Wt::Dbo::Session& dbSession() {
    return dynamic_cast<base::BaseApp<model::User>*>(Wt::WApplication::instance())->dbSession();
}

} // namespace wittyPlus
