/*
 * =====================================================================================
 *
 *       Filename:  register.cpp
 *
 *    Description:  Performs the registration of the page extension
 *
 *        Version:  1.0
 *        Created:  08/11/11 08:28:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "../../ExtensionManager.hpp"
#include "Extension.hpp"
#include <memory>

namespace wittyPlus {
namespace page {

class Register {
public:
    Register() {
        ExtensionManager::instance().registerExtension(std::unique_ptr<wittyPlus::Extension>(new page::Extension()));
    }
};

Register reg;

} // namespace page
} // namespace wittyPlus
