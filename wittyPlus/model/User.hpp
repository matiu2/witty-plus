/*
 * =====================================================================================
 *
 *       Filename:  User.hpp
 *
 *    Description:  Gives a basic user model
 *
 *        Version:  1.0
 *        Created:  21/07/11 20:43:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MODEL_USER_HPP
#define MODEL_USER_HPP

#include <Wt/Dbo/Dbo>
#include <Wt/WString>
#include <string>
#include <wittyPlus/base/sha.hpp>

namespace dbo = Wt::Dbo;
using std::string;
using Wt::WString;
using wittyPlus::base::StdSHAValue;

namespace wittyPlus {
namespace model {

class User {
private:
    // Fields
    string _name;
    StdSHAValue _passwordHash;
public:
    // Structors
    User(const string& name="") : _name(name), _passwordHash(20, 0) {};
    User(const string& name, const StdSHAValue& passwordHash) : _name(name), _passwordHash(passwordHash) {};
    User(const string& name, const string& password) : _name(name), _passwordHash(base::sha1(password)) {};
    // Accessors
    const string& name() const { return _name; }
    void setName(const string& newName) { _name = newName; }
    void setName(const WString& newName) { _name = newName.toUTF8(); }
    const StdSHAValue& passwordHash() const { return _passwordHash; }
    void setPasswordHash(const StdSHAValue& newHash) { _passwordHash = newHash; }
    void setPassword(const string& newPassword) { setPasswordHash(base::sha1(newPassword)); }
    // DBO Support
    template<class Action>
    void persist(Action& a) {
        dbo::field(a, _name, "name");
        dbo::field(a, _passwordHash, "passwordHash");
    }
};

} // namespace model
} // namspace my_app

#endif // MODEL_USER_HPP
