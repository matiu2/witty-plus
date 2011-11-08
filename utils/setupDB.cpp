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

#include <cassert> // This is needed because the file imported in the line below has an 'assert' in it
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Postgres>
#include <wittyPlus/base/sha.hpp>
#include <wittyPlus/model/User.hpp>
#include <wittyPlus/db.hpp>
#include <iostream>

namespace dbo = Wt::Dbo;
using namespace wittyPlus;
using std::cout;
using std::endl;
using wittyPlus::model::User;

const std::string ADMIN_USERNAME = "admin";
const std::string ADMIN_PASSWORD = "admin";

int main(int , char** ) {
    dbo::backend::Postgres postgres(CMAKE_DB_CONNECTION_STRING); // CMAKE_DB_CONNECTION_STRING is configured in ccmake
    dbo::Session session;
    session.setConnection(postgres);
    dbo::Transaction transaction(session);
    // Create the schema
    session.mapClass<User>("users");
    session.createTables();
    // Fill some nice data
    // Add a user
    // Make an SHA hash of the password we are saving to the DB
    dbo::ptr<User> pUser = session.find<User>().where("name = ?").bind(ADMIN_USERNAME);
    bool isNew = !pUser;
    if (isNew)
        pUser = new User();
    pUser.modify()->setName(ADMIN_USERNAME);
    pUser.modify()->setPasswordHash(base::sha1(ADMIN_PASSWORD));
    if (isNew)
        session.add(pUser);
    transaction.commit();
}
