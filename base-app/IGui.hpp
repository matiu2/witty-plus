/*
 * =====================================================================================
 *
 *       Filename:  IGui.hpp
 *
 *    Description:  An interface to the gui
 *
 *        Version:  1.0
 *        Created:  11/05/2011 13:52:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne ( msherborne@gmail.com )
 *        Company:  
 *
 * =====================================================================================
 */

#pragma once

#include <Wt/WObject>
#include <Wt/WString>
#include <Wt/WWidget>

namespace wittyPlus {

class IGui {
public:
    virtual void setStatusText(const Wt::WString& newStatusText) = 0;
    virtual void setBody(const Wt::WString& newStatusText) = 0;
    virtual void setBody(Wt::WWidget* newWidget) = 0;

    static IGui* instance();
};


} // namespace wittyPlus
