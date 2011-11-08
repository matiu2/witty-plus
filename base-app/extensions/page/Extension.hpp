/*
 * =====================================================================================
 *
 *       Filename:  Extension.hpp
 *
 *    Description:  A basic page extension .. it renders pages and allows you to edit them
 *
 *        Version:  1.0
 *        Created:  07/11/11 22:51:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "../Extension.hpp"
#include "../../db.hpp"
#include "../../IURLManager.hpp"

namespace Wt {
    class WObject;
}

namespace wittyPlus {
namespace page {

class Extension : public wittyPlus::Extension {
public:
    virtual const char* name() const; /// The name of the extension
    virtual Wt::WObject* launch(Wt::WObject* parent) const; // Launch the extension for a single app / thread
};

} // namespace wittyPlus
} // namespace page
