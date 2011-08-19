/*
 * =====================================================================================
 *
 *       Filename:  db.hpp
 *
 *    Description:  Maps all the models to the database
 *
 *        Version:  1.0
 *        Created:  06/08/11 06:45:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef DB_HPP
#define DB_HPP

#include "model/User.hpp"
#include <Wt/Dbo/Session>

namespace dbo = Wt::Dbo;

namespace my_app {

/**
* @brief Maps c++ classes to Dbo objects
*
* @param session the already connected session that'll do the mapping
*/
void mapModels(dbo::Session& session) {
    session.mapClass<model::User>("users");
}

} // namespace my_app {

#endif // DB_HPP
