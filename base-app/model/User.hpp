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
#include <string>

namespace dbo = Wt::Dbo;
using std::string;

namespace my_app {
namespace model {

class User {
private:
    // Fields
    string _name;
    string _passwordHash;
public:
    // Structors
    User(const string& name="", const string& passwordHash="") : _name(name), _passwordHash(passwordHash) {};
    // Accessors
    const string& name() const { return _name; }
    void setName(const string& newName) { _name = newName; }
    const string& passwordHash() const { return _passwordHash; }
    void setPasswordHash(const string& newHash) { _passwordHash = newHash; }
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
