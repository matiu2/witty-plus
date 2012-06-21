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
#include "Model.hpp"

namespace wittyPlus {
namespace page {

class Extension: public Wt::WObject {
public:
    typedef void (Extension::*ActionMethod)(const Model&);
    typedef std::map<std::string, ActionMethod> ActionMap;
    typedef std::pair<std::string, ActionMethod> ActionPair;
private:
    ActionMap actionMap;
public:
    Extension(WObject* parent=0);
    void handleURLChange();
    void view(const Model& page);
    void edit(const Model& page);
};

} // namespace page
} // namespace wittyPlus
