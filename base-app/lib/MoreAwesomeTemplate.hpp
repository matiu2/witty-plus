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
#include <Wt/WJavaScriptSlot>
#include <boost/algorithm/string.hpp>
#include <locale>

namespace Wt {
    class WContainerWidget;
}

using Wt::WTemplate;
using Wt::WContainerWidget;
using Wt::JSlot;
using Wt::WText;
using Wt::WLabel;
using Wt::WString;

namespace wittyPlus {

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
    * @param widget A pointer to hold the widget
    * @param prefix The prefix to do all the naming stuff.
    */
    template <class T> void bindAndCreateField(WLabel*& label, T*& widget, const std::string prefix) {
        WString labelText = tr(prefix + "-label");
        if (labelText == ("??" + prefix + "-label??")) {
            std::string capPrefix = prefix; // Capitalized prefix ..eg. 'name' becomes 'Name'
            capPrefix[0] = std::toupper(capPrefix[0]);
            labelText = tr(capPrefix);
        }
        bindAndCreateWidget(label, prefix + "-label", labelText);
        bindAndCreateWidget(widget, prefix + "-field");
        label->setBuddy(widget);
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
        bindAndCreateField(label, widget,prefix);
        bindAndCreateWidget(validationMsgText, prefix + "-msg");
        // Hook up a javascript handler, to show a message when the content is invalid
        JSlot* validateHandler = new JSlot(this);
        // Unfortunately we have to run validate ourselves, as witty puts the validation code after other event handlers
        WString validateFunc = "function (sender, event) { {1}.validate(sender); {2}.innerHTML = sender.getAttribute('title'); }";
        validateHandler->setJavaScript(validateFunc.arg(WT_CLASS).arg(validationMsgText->jsRef()).toUTF8());
        widget->focussed().connect(*validateHandler);
        widget->changed().connect(*validateHandler);
        widget->keyWentUp().connect(*validateHandler);
        widget->keyWentDown().connect(*validateHandler);
        widget->clicked().connect(*validateHandler);
    }
public:
    MoreAwesomeTemplate(WContainerWidget* parent=0) : WTemplate(parent) {}
};

}

#endif // MORE_AWESOME_TEMPLATE_HPP
