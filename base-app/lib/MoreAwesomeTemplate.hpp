/*
 * =====================================================================================
 *
 *       Filename:  MoreAwesomeTemplate.hpp
 *
 *    Description:  A bunch of shared helper code
 *
 *        Version:  1.0
 *        Created:  06/03/2011 10:15:48 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MORE_AWESOME_TEMPLATE_HPP
#define MORE_AWESOME_TEMPLATE_HPP

#include <Wt/WTemplate>
#include <Wt/WLabel>
#include <Wt/WText>
#include <Wt/WString>
#include <Wt/WFormWidget>
#include <Wt/WValidator>
#include <Wt/WJavaScriptSlot>
#include <Wt/WApplication>
#include <boost/algorithm/string.hpp>
#include <locale>
#include <vector>

namespace Wt {
    class WContainerWidget;
}

using Wt::WTemplate;
using Wt::WContainerWidget;
using Wt::JSlot;
using Wt::WApplication;
using Wt::WText;
using Wt::WLabel;
using Wt::WString;
using Wt::WFormWidget;
using Wt::WValidator;
using std::vector;

namespace wittyPlus {

/// A row in a form, basically has a label, a widget, and an optional message text
struct FieldRow {
    WLabel* label;
    WFormWidget* widget;
    WText* messageText;
    FieldRow(WLabel* label, WFormWidget* widget, WText* messageText=0) :
        label(label), widget(widget), messageText(messageText) {}
};

class MoreAwesomeTemplate : public WTemplate {
protected:
    /**
    * @brief Replace a template placeholder 'name' with a widget (pointed to by pointer).
    *
    * Used in implementation of WTemplateWidget.
    *
    * @tparam T The type of widget to create
    * @param pointer The pointer to the newly created Widget
    * @param name of the place in the template we're replacing
    * @param labelName The name to give a label or button, etc. optional
    */
    template <class T> void bindAndCreateWidget(T*& pointer, const std::string& name, const WString& labelName) {
        bindWidget(name,  pointer = new T(labelName));
    }
    /**
    * @brief Replace a template placeholder 'name' with a widget (pointed to by pointer).
    *
    * Used in implementation of WTemplateWidget.
    *
    * @tparam T The type of widget to create
    * @param pointer The pointer to the newly created Widget
    * @param name of the place in the template we're replacing
    */
    template <class T> void bindAndCreateWidget(T*& pointer, const std::string& name) {
        bindWidget(name,  pointer = new T());
    }

    /**
    * @brief creates a Widget and it's field and binds it into the template.
    * 
    * The template must be of the format:
    *
    * <message id="some-template">
    *  <div class="yui-gd">
    *      <div class="yui-u first">${name-label}</div>
    *      <div class="yui-u">${name-field}</div>
    *  </div>
    * </message>
    * <message id="name-label">Name</message> <!-- OR the line below -->
    * <message id="Name">Name</message>
    *
    * In this case 'name' would be the prefix.
    * The label would be labeled: tr("name-label")
    * If no tr("name-label") is found .. it'll use tr("Name") (with an uppercase first letter)
    *
    * @tparam T The type of the widget eg Wt::WLineEdit
    * @param label A pointer to hold the label.
    * @param widget A pointer to hold the WFormWidget
    * @param prefix The prefix to do all the naming stuff.
    */
    template <class T> FieldRow* bindAndCreateField(WLabel*& label, T*& widget, const std::string prefix) {
        WString labelText = tr(prefix + "-label");
        if (labelText == ("??" + prefix + "-label??")) {
            std::string capPrefix = prefix; // Capitalized prefix ..eg. 'name' becomes 'Name'
            capPrefix[0] = std::toupper(capPrefix[0]);
            labelText = tr(capPrefix);
        }
        bindAndCreateWidget(label, prefix + "-label", labelText);
        bindAndCreateWidget(widget, prefix + "-field");
        label->setBuddy(widget);
        // If we have a form widget, remember it in our vector of field rows for validation later
        WFormWidget* formWidget = dynamic_cast<WFormWidget*>(widget);
        if (formWidget != 0) {
            fieldRows.push_back(FieldRow(label, formWidget));
            return &(*(fieldRows.end()-1));
        }
        return 0;
    }
    /**
    * @brief creates a Widget and it's field and binds it into the template.
    *
    * The template must be of the format:
    *
    * <message id="some-template">
    *  <div class="yui-gb">
    *      <div class="yui-u first">${name-label}</div>
    *      <div class="yui-u">${name-field}</div>
    *      <div class="yui-u">${name-msg}</div>
    *  </div>
    * </message>
    * <message id="name-label">Name</message> <!-- OR the line below -->
    * <message id="Name">Name</message>
    *
    * In this case 'name' would be the prefix.
    * The label would be labeled: tr("name-label")
    * If no tr("name-label") is found .. it'll use tr("Name") (with an uppercase first letter)
    *
    * @tparam T The type of the widget eg Wt::WLineEdit
    * @param label A pointer to hold the label.
    * @param widget A pointer to hold the widget
    * @param validationMsgText A pointer to hold the validation message text
    * @param prefix The prefix to do all the naming stuff.
    */
    template <class T> void bindAndCreateField(WLabel*& label, T*& widget, WText*& validationMsgText, const std::string prefix) {
        FieldRow* row = bindAndCreateField(label, widget,prefix);
        bindAndCreateWidget(validationMsgText, prefix + "-msg");
        if (row != 0)
            row->messageText = validationMsgText;
        // Hook up the widget and the validation message text in JS on client side
        // This will be used by BaseApp's customized 'validate' function
        widget->setJavaScriptMember("msgTxt", validationMsgText->jsRef());
    }
    // Fields
    vector<FieldRow> fieldRows;
    // convenience methods
    /// Does a client side validation on all fields, and puts the solution in their text message.
    /// Focusses the first widget invalid widget.
    /// Returns true if all widget's pass server side validation, or false if any fail
    bool validateAll() {
        bool result = true;
        bool haveFocussed = false;
        WApplication* app = WApplication::instance();
        for(vector<FieldRow>::const_iterator row=fieldRows.begin(); row != fieldRows.end(); ++row) {
            // We can't set the message text if it doesn't exist
            if (row->messageText == 0)
                continue;
            // Validate on client side. (Using BaseApp's custom validate function,
            // this will show the message on the client's side)
            app->doJavaScript( app->javaScriptClass() + "WT.validate(" + row->widget->jsRef() + ");" );
            WValidator::State validness = row->widget->validate(); // Validate on server side
            if (validness != WValidator::Valid) {
                result = false;
                if (!haveFocussed) {
                    row->widget->setFocus();
                    haveFocussed = true;
                }
            }
        }
        return result;
    }
public:
    MoreAwesomeTemplate(WContainerWidget* parent=0) : WTemplate(parent), fieldRows() {}
};

}

#endif // MORE_AWESOME_TEMPLATE_HPP
