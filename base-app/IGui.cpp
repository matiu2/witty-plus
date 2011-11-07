/*
 * =====================================================================================
 *
 *       Filename:  IGui.cpp
 *
 *    Description:  Points seekers of the IGui interface to App
 *
 *        Version:  1.0
 *        Created:  11/05/2011 13:56:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "IGui.hpp"
#include "App.hpp"
#include "MainWindow.hpp"

namespace wittyPlus {

IGui* IGui::instance() {
    return app()->mainWindow();
}

} // namespace wittyPlus
