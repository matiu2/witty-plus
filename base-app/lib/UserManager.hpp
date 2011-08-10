/*
 * =====================================================================================
 *
 *       Filename:  UserManager.hpp
 *
 *    Description:  Handles users and permssions
 *
 *        Version:  1.0
 *        Created:  06/01/2011 04:10:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef USER_MANAGER_HPP
#define USER_MANAGER_HPP

#include <string>
#include <Wt/Dbo/Dbo>

#include <openssl/sha.h>
const unsigned int SHALength = 20;
typedef unsigned char SHAValue[SHALength];
using std::string;
namespace dbo = Wt::Dbo;

/**
* @brief c++ version of SHA1. Pass input string, get a hash.
*
* @param input the string to have sha run on
* @param value auto pointer to the SHAValue
*/
void sha1(const std::string input, SHAValue& value);

namespace wittyPlus {

/**
* Add this to your app, to have long lived and thread safe 'user sessions'. Tracks the currently logged in user.
*
* @tparam User A Wt::Dbo model class that represents the user and has a 'name' db field we can look up on, and the
* following methods: const string& username(); const string& PasswordHash();
* setName(const string& newName); setPasswordHash(const string& newHash);
* methods .. and of course the ability to persist
*/
template <class User>
class UserManager {
private:
    void ensureIndex();
    dbo::Session& _session;
    dbo::ptr<User> _user;                             /// A ptr to the currently logged in user
public:
    UserManager(dbo::Session& session) : _session(session) {}
    void logout() { _user.reset(); }                  /// Logs out the current user
    bool isLoggedIn() const { return _user; }         /// Returns true if someone is logged in
    dbo::ptr<User> getUser() const { return _user; }  /// Return a pointer to the currently logged in user
    /**
    * Returns true if the username and password match are in the DB. Always takes the same amount of time (roughly)
    * to calculate. This is to prevent remote timing attacks.
    *
    * @param username the username being used to log in
    * @param password the password being used to log in
    *
    * @return True if db has a match
    */
    bool checkLogin(const string& username, const string& password) {
        dbo::Transaction transaction(_session);
        dbo::ptr<User> myUser = _session.find<User>().where("name = ?").bind(username);
        string hashFromDB(20, '0'); // This'll be the hash we'll compare on
        if (myUser)
            hashFromDB = myUser->passwordHash();
        // Check the password
        SHAValue hashFromNet;
        sha1(password, hashFromNet);
        // Always compare 20 bytes, no shortcuts allowed. Don't wanna be hit by a timing attack
        assert(hashFromDB.size() == SHALength);
        volatile bool result = myUser; // If there's no user .. it'll always be a false result .. marked as volatile to prevent optimization
        // Always do this loop to prevent staistical timing attacks
        for(size_t i=0; i < SHALength; ++i) {
            if (hashFromDB[i] != hashFromNet[i])
                result = false; // Don't just return from here .. make all checks constant time to prevent timing attacks
        }
        _user = myUser;
        transaction.commit();
        return result;
    }
    /**
    * @brief Adds or updates the password of a new user in the table
    *
    * @param username username to update/insert
    * @param password new password
    */
    void addUser(const string& username, const string& password) {
        // Make an SHA hash of the password we are saving to the DB
        dbo::Transaction transaction(_session);
        dbo::ptr<User> myUser = _session.find<User>().where("name = ?").bind(username);
        if (!myUser)
            myUser = new User();
        SHAValue passHash;
        sha1(password, passHash);
        myUser.modify()->setName(username);
        myUser.modify()->setPasswordHash(reinterpret_cast<const char*>(&passHash[0]));
        transaction.commit();
        _user = myUser; // save it
    }
    /**
    * @brief Looks up a user by their name
    * @param username The name to lookup in the database
    * @return A pointer to the user we found
    */
    dbo::ptr<User> userFromName(const string& username) {
        dbo::Transaction transaction(_session);
        return _session.find<User>().where("name = ?").bind(username);
    }
};

} // namespace my_app

#endif //  USER_MANAGER_HPP

