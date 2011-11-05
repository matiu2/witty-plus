#include "ExtensionManager.hpp"

#include <Wt/WObject>
#include "App.hpp"

namespace wittyPlus {

ExtensionManager::ExtensionManager(Wt::WObject* parent) : Wt::WObject(parent) {}

// Public methods

App* ExtensionManager::app() {
    return wittyPlus::app();
}

// Static funcs

ExtensionManager* ExtensionManager::instance() {
    return wittyPlus::app()->extensionManager();
}

} // namespace wittyPlus
