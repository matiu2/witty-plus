#ifndef WITTYPLUS_PAGE_MODEL_HPP
#define WITTYPLUS_PAGE_MODEL_HPP
#pragma once

#include <string>
#include <Wt/Dbo/Dbo>

namespace wittyPlus {
namespace page {

class Model {
private:
    std::string _name;
    std::string _title;
    std::string _html;
public:
    Model();
    // Getters and Setters
    std::string getName() const { return _name; }
    void setName(const std::string& newName) { _name = newName; }
    std::string getTitle() const { return _title; }
    void setTitle(const std::string& newTitle) { _title = newTitle; }
    std::string getHtml() const { return _html; }
    void setHtml(const std::string& newHtml) { _html = newHtml; }
    // DBO Support
    template<class Action>
    void persist(Action& a) {
        namespace dbo = Wt::Dbo;
        dbo::field(a, _name, "name");
        dbo::field(a, _title, "title");
        dbo::field(a, _html, "html");
    }
};

} // namespace page
} // namespace wittyPlus

#endif // WITTYPLUS_PAGE_MODEL_HPP
