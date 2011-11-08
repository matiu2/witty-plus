/*
 * =====================================================================================
 *
 *       Filename:  Extension.cpp
 *
 *    Description:  The page extension's implementation
 *
 *        Version:  1.0
 *        Created:  08/11/11 08:24:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "Extension.hpp"
#include "Page.hpp"
#include <Wt/WObject>

namespace wittyPlus {
namespace page {

const char* Extension::name() const { return "Page"; }
Wt::WObject* Extension::launch(Wt::WObject* parent) const { return new Page(parent); }

} // namespace wittyPlus
} // namespace page
