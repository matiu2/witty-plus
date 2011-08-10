/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.cpp
 *
 *    Description:  Library code for the main window
 *
 *        Version:  1.0
 *        Created:  19/07/11 20:38:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "MainWindow.hpp"

namespace my_app {

MainWindow::MainWindow(WContainerWidget* parent) : wittyPlus::MoreAwesomeTemplate(parent) {
    setTemplateText(tr("main-template"));
    setStatusText("");
    // Set up any widets you have like the navigation tree
    // bindAndCreateWidget(_controls) // You need to define this somewhere like: MyControlWidget* _controls
    // bindAndCreateWidget(_nav)
    bindString("controls", "Bind Controls Widget here");
    bindString("nav", "Bind Nav box widget here");
    bindString("content", "Put the meat of your APP here");
}

} // namespace my_app
