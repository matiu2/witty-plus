/*
 * =====================================================================================
 *
 *       Filename:  Extension.hpp
 *
 *    Description:  A base extension
 *
 *        Version:  1.0
 *        Created:  11/05/2011 09:47:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#pragma once

#include <Wt/WObject>
#include <Wt/Dbo/Session>

namespace wittyPlus {

class Extension {
public:
    /** Called once for each app (and thread) .. use this to map classes to tables, register with URLs you're interested
     * in etc. Check out the Page plugin for an example
      **/
    virtual const char* name() const = 0; /// The name of the extension
    /// Launch the extension for a single app / thread
    /// @param parent the new parent of object of the extension instance's class hierachy (usually a Wt::WApplication).
    /// @return The actual instance of the extension for this app
    virtual Wt::WObject* launch(Wt::WObject* parent) const = 0; 
};

} // namespace wittyPlus {
