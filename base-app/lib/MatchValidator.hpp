/*
 * =====================================================================================
 *
 *       Filename:  MatchValidator.hpp
 *
 *    Description:  Provides a validator that demands that another validator matches it
 *
 *        Version:  1.0
 *        Created:  09/15/2011 09:52:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef WITTY_PLUS_MATCH_VALIDATOR_HPP
#define WITTY_PLUS_MATCH_VALIDATOR_HPP

#include <Wt/WApplication>
#include <Wt/WValidator>
#include <Wt/WJavaScriptPreamble>
#include <Wt/WComboBox>
#include <sstream>
#include <boost/concept/requires.hpp>
#include "js/MatchValidator.js"

namespace Wt {
    class WFormWidget;
}

using Wt::WApplication;
using Wt::WComboBox;
using Wt::WFormWidget;

namespace wittyPlus {
namespace base {

class BaseMatchValidator: public Wt::WValidator {
protected:
    WFormWidget* _mine;
    WFormWidget* _other;
    WString _errorMessage;
public:
    BaseMatchValidator(WFormWidget* other, const WString& errorMessage, WObject* parent=0) :
        WValidator(parent), _mine(dynamic_cast<WFormWidget*>(parent)), _other(other), _errorMessage(errorMessage) { 
    }
    const WString& errorMessage() const { return _errorMessage; }
    void loadJavaScript(WApplication *app) const { LOAD_JAVASCRIPT(app, "js/MatchValidator.js", "MatchValidator", wtjs2); }
    std::string javaScriptValidate () const {
        if (_other) {
            loadJavaScript(WApplication::instance());
            std::stringstream js;
            js << "new " WT_CLASS ".MatchValidator("
               << (isMandatory() ? "true" : "false") << ","
               << WString(_other->id()).jsStringLiteral() << "," 
               << errorMessage().jsStringLiteral() 
               << ");";
            return js.str();
        } else {
            return "";
        }
    }
};

/// A template concept, insuring that MatchValidator widgets have a 'text()' method
template <class WidgetType>
struct HasTextConcept {
    BOOST_CONCEPT_USAGE(HasTextConcept) { const WString& text(); }
};

/// This one works for WLineEdit, WTextArea and WTextEdit
template <class WidgetType>
struct MatchValidator : public BaseMatchValidator {
    BOOST_CONCEPT_ASSERT((HasTextConcept<WidgetType>));
    MatchValidator(WidgetType* other, const WString& errorMessage, WObject* parent=0) :
        BaseMatchValidator(other, errorMessage, parent) {}
    State validate(WString &input) const { return (input == dynamic_cast<WidgetType*>(_other)->text()) ? Valid : Invalid; }
};

/// This one works for WComboBox
template <>
struct MatchValidator<WComboBox> : public BaseMatchValidator {
    MatchValidator(WComboBox* other, const WString& errorMessage, WObject* parent=0) :
        BaseMatchValidator(other, errorMessage, parent) {}
    State validate(WString &input) const { return (input == dynamic_cast<WComboBox*>(_other)->currentText()) ? Valid : Invalid; }
};


} // namespace base {
} // namespace wittyPlus {

#endif // WITTY_PLUS_MATCH_VALIDATOR_HPP
