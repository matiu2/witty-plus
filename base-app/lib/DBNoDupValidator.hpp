/// Provides a witty field validator that ensure there are no duplicates in the DB
#ifndef DB_NO_DUP_VALIDATOR_HPP
#define DB_NO_DUP_VALIDATOR_HPP

#include <Wt/WValidator>
#include <Wt/Dbo/Query>
#include <Wt/Dbo/ptr>
#include <string>
#include "ServerSideValidator.hpp"

using Wt::WValidator;
using std::string;

namespace dbo = Wt::Dbo;

namespace wittyPlus {

/** A field validator that makes sure an object is not already in the DB **/
template <class ModelClass>
class DBNoDupValidator : public ServerSideValidator {
public:
    typedef dbo::dbo_traits<ModelClass> Traits;
private:
    dbo::Session& _db;
    string _fieldName;
    dbo::Query<int> _query;
public:
    /** This constructor is for when you're editing new objects. It'll return Invalid if any object in the DB has the same name.

          @param db a reference to a dbo::Session
          @param fieldName the fieldName to search for dups on in the db. eg. 'username'
          @param isMandatory true if they must enter this field
          @param foundDupMessage Message to show to the user if a duplicate is found
          @param emptyMessage The message to show if input is empty and isMandatory is true
          @param parent the parent that owns this validator
      **/
    DBNoDupValidator(dbo::Session& db, const std::string& fieldName, bool isMandatory=false,
                     const WString& foundDupMessage="", const WString& emptyMessage="", WObject* parent=0) :
        ServerSideValidator("", foundDupMessage, emptyMessage, isMandatory, parent), _db(db), _fieldName(fieldName),
        _query(DBNoDupValidator::makeQuery(db, fieldName)) {}
    /** This constructor is for when you are editing an existing object. You want there to be zero dups, but of course if
          they leave the name the same as the existing object, then that's fine.

          @param db a reference to a dbo::Session
          @param fieldName the fieldName to search for dups on in the db. eg. 'username'
          @param idToIgnore Don't complain if our input value is the same as the DB Object with this ID
          @param isMandatory true if they must enter this field
          @param foundDupMessage Message to show to the user if a duplicate is found.
          @param emptyMessage The message to show if input is empty and isMandatory is true
          @param parent the parent that owns this validator
    **/
    DBNoDupValidator(
        dbo::Session& db, const std::string& fieldName, typename Traits::IdType idToIgnore,
        bool isMandatory=false, const WString& foundDupMessage="", const WString& emptyMessage="", WObject* parent=0)
        : ServerSideValidator("", foundDupMessage, emptyMessage, isMandatory, parent),
          _db(db), _fieldName(fieldName),
          _query(DBNoDupValidator::makeQuery(db, fieldName, idToIgnore)) {}
    State validate(WString& input) const {
        // Let our ancestor handle the 'mandatory input' side of things
        State result = WValidator::validate(input);
        if (result != Valid) {
            return showMessage(result);
        }
        // If our ancestor validator implementation says we're good..
        // ..return Valid as long as there are zero other rows with that name in the DB
        dbo::Transaction t(_db);
        dbo::Query<int> newQuery = _query;
        result = newQuery.bind(input.toUTF8()).resultValue() == 0 ? Valid : Invalid;
        t.commit();
        return showMessage(result);
    }
    void setIdToIgnore(typename Traits::IdType idToIgnore) { _query = DBNoDupValidator::makeQuery(_db, _fieldName, idToIgnore); }
    void clearIdToIgnore() { _query = DBNoDupValidator::makeQuery(_db, _fieldName); }
    // Static functions
    static dbo::Query<int> makeQuery(dbo::Session& db, const string& fieldName) {
        return db.query<int>(
                string("select count(1) from ") + db.tableName<ModelClass>())
                .where(fieldName + " = ?");
    }
    static dbo::Query<int> makeQuery(dbo::Session& db, const string& fieldName, typename Traits::IdType idToIgnore) {
        return db.query<int>(
                string("select count(1) from ") + db.tableName<ModelClass>())
                .where(string(Traits::surrogateIdField()) + " != ?").bind(idToIgnore) // Ignore the existing record
                .where(fieldName + " = ?");
    }
};

}

#endif // DB_NO_DUP_VALIDATOR_HPP
