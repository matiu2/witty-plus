/*
 * =====================================================================================
 *
 *       Filename:  setupDB.cpp
 *
 *    Description:  A quick app to set up the base db (create and fill the tables with basic info)
 *
 *        Version:  1.0
 *        Created:  06/08/11 06:45:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Postgres>
#include "model/User.hpp"
#include "lib/UserManager.hpp"
#include "db.hpp"
#include <iostream>

namespace dbo = Wt::Dbo;
using namespace my_app;
using std::cout;
using std::endl;

// The below string is defined in cmake and the make system
#define FINAL_CONNECT_STRING " ## DB_CONNECTION_STRING ## "

int main(int , char** ) {
    dbo::backend::Postgres postgres(FINAL_CONNECT_STRING);
    dbo::Session session;
    session.setConnection(postgres);
    dbo::Transaction transaction(session);
    // Create the schema
    mapModels(session);
    // Fill some nice data
    wittyPlus::UserManager<model::User> users(session);
    users.addUser("admin", "admin");
    transaction.commit();
}
