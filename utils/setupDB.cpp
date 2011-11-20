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
#include <Wt/Test/WTestEnvironment>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Postgres>
#include <wittyPlus/base/sha.hpp>
#include <wittyPlus/model/User.hpp>
#include <wittyPlus/base/BaseApp.hpp>
#include <wittyPlus/db.hpp>
#include <wittyPlus/extensions/page/Extension.hpp>
#include <wittyPlus/extensions/page/Model.hpp>
#include <iostream>

namespace dbo = Wt::Dbo;
using namespace wittyPlus;
using std::cout;
using std::endl;
using wittyPlus::model::User;

const std::string ADMIN_USERNAME = "admin";
const std::string ADMIN_PASSWORD = "admin";

int main(int , char** ) {
    Wt::Test::WTestEnvironment env;
    wittyPlus::base::BaseApp<User> app(env, "setupDB");
    dbo::backend::Postgres postgres(CMAKE_DB_CONNECTION_STRING); // CMAKE_DB_CONNECTION_STRING is configured in ccmake
    dbo::Session& session = app.dbSession();
    session.setConnection(postgres);
    // Register the user model
    session.mapClass<User>("users");
    // Load all the extensions necessary
    page::Extension pageExtension;
    // Build the tables
    dbo::Transaction transaction(session);
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
    // Add a page
    dbo::ptr<page::Model> page = session.find<page::Model>().where("name = ?").bind("/");
    isNew = !page;
    if (isNew)
        page = new page::Model();
    page.modify()->setName("/");
    page.modify()->setTitle("Welcome to wittyPlus");
    page.modify()->setHtml("<p>Welcome to wittyPlus.</p> <p>This is a default page content created so you can view something :)</p>");
    if (isNew)
        session.add(page);
    transaction.commit();
}
