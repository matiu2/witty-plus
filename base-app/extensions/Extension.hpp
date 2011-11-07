/*
 * =====================================================================================
 *
 *       Filename:  Extension.hpp
 *
 *    Description:  A base extension
 *
 *        Version:  1.0
 *        Created:  11/05/2011 09:47:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <Wt/WObject>
#include <Wt/Dbo/Session>

namespace wittyPlus {

class BaseExtension : WT::WObject {
public:
    BaseExtension(Wt::WObject* parent=0) : Wt::WObject(parent) {}
    /** Called once for each app (and thread) .. use this to map classes to tables
      * @param session for you to call session.mapClass<YourClass>("tableName");
      **/
    virtual void mapClasses(Wt::Dbo::Session& session) {}
    /** Override this to handle a url when the user navigates there
      * @return true if you've handled the url and no-one else should bother. false if you didn't handle it and we
      * should keep searching for a handler.
     **/
    virtual bool handleUrl(const string& url) {}
};

} // namespace wittyPlus {
