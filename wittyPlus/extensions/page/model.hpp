/*
 * =====================================================================================
 *
 *       Filename:  model.hpp
 *
 *    Description:  The Wt::DBO model for a page
 *
 *        Version:  1.0
 *        Created:  11/05/2011 09:33:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <Wt/Dbo/Field>

namspace dbo = Wt::Dbo;

namespace wittyPlus {
namespace page {
namespace model {

class Page {
public:
    typedef Wt::WString WString;
private:
    WString _name;
    WString _title;
    WString _content;
public:
    Page(const WString& name, const WString& title, const WString& content) : _name(name), _title(title), _content(content) {}
    const WString& getName() { return _name; }
    void setName(const WString& newName) { _name = newName; }
    const WString& getTitle() { return _title; }
    void setTitle(const WString& newTitle) { _title = newTitle; }
    const WString& getContent() { return _content; }
    void setContent(const WString& newContent) { _content = newContent; }
    // DBO Support
    template<class Action>
    void persist(Action& a) {
        dbo::field(a, _name, "name");
        dbo::field(a, _title, "title");
        dbo::field(a, _content, "content");
    }
};



} // namespace model
} // namespace page
} // namespace wittyPlus
