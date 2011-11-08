/*
 * =====================================================================================
 *
 *       Filename:  ButtonBar.hpp
 *
 *    Description:  Provides a generic two button bar, for ok/cancel or whatever..
 *
 *        Version:  1.0
 *        Created:  06/17/2011 10:30:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef BUTTON_BAR_HPP
#define BUTTON_BAR_HPP

#include <Wt/WPushButton>
#include "MoreAwesomeTemplate.hpp"

using Wt::WPushButton;

namespace wittyPlus {
namespace base {

/**
* @brief A nice two buttons next to each other on a panel
*
* Cancel will navigate the app back to "/".
* OK will trigger the 'onOk' event
*/
class ButtonBar : public MoreAwesomeTemplate {
protected:
    WPushButton* _btn1;
    WPushButton* _btn2;
public:
    /**
    * @brief Gives you a nice pair of buttons
    *
    * @param parent Parent Widget
    */
    ButtonBar(const WString& button1Text="", const WString& button2Text="", WContainerWidget* parent=0) : MoreAwesomeTemplate(parent) {
        WString btn1Text = button1Text.empty() ? WString::tr("OK") : button1Text;
        WString btn2Text = button2Text.empty() ? WString::tr("Cancel") : button2Text;
        setTemplateText(tr("button-bar"));
        setStyleClass("button-bar");
        bindAndCreateWidget(_btn1, "btn-1", btn1Text);
        bindAndCreateWidget(_btn2, "btn-2", btn2Text);
    }
    WPushButton* btn1() { return _btn1; }
    WPushButton* btn2() { return _btn2; }
};


} // namespace base
} // namespace wittyPlus

#endif // BUTTON_BAR_HPP
