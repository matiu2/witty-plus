#include "ExtensionManager.hpp"

#include <Wt/WObject>
#include "App.hpp"

namespace wittyPlus {

ExtensionManager::ExtensionManager(Wt::WObject* parent) : Wt::WObject(parent) {}

// Public methods

// Static funcs

ExtensionManager* ExtensionManager::instance() {
    return wittyPlus::app()->extensionManager();
}

} // namespace wittyPlus
