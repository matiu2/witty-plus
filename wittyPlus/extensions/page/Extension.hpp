/*
 * =====================================================================================
 *
 *       Filename:  Extension.hpp
 *
 *    Description:  The app like object that handles pages
 *
 *        Version:  1.0
 *        Created:  08/11/11 10:33:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#pragma once

#include <Wt/WObject>
#include <string>

namespace wittyPlus {
namespace page {

class Extension: public Wt::WObject {
public:
    Extension(WObject* parent=0);
    void show_a_page();
};

} // namespace page
} // namespace wittyPlus
