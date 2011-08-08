/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.hpp
 *
 *    Description:  The main window of the account application
 *
 *        Version:  1.0
 *        Created:  18/07/11 22:31:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "lib/MoreAwesomeTemplate.hpp"

namespace Wt {
    class WContainerWidget;
    class WString;
}

using Wt::WTemplate;
using Wt::WContainerWidget;
using Wt::WString;

namespace my_app {

class MainWindow : public wittyPlus::MoreAwesomeTemplate {
public:
    MainWindow(WContainerWidget* parent=0);
    void setStatusText(const WString& newMessage) { bindString("status-text", newMessage); }
};

} // namespace my_app

#endif // MAINWINDOW_HPP

